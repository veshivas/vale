// qdoc.go implements the QDoc markup lint handler (lintQDoc) and its helpers.
//
// QDoc is the Qt documentation format. Unlike Markdown or RST, there is no
// upstream HTML conversion pipeline — Vale parses QDoc source directly via a
// tree-sitter grammar (github.com/veshivas/tree-sitter-qdoc).
//
// The handler uses a two-pass architecture (see runQDocPasses):
//
//	Pass 1 (GetComments): extracts scoped comment fragments — headings, briefs,
//	        notes, warnings, and plain text — and lints each with lintLines or
//	        lintProse depending on scope type.
//	Pass 2 (GetQDocProseBlocks): reconstructs full prose per block_comment,
//	        spanning inline-command boundaries, and lints via lintProse to
//	        enable scope:sentence rules (OxfordComma, SentenceLength, etc.).
//
// File routing: .qdoc/.qdocinc → format "markup" → lintQDoc (this file).
// Embedded QDoc in .cpp/.qml → lintFragments → lintQDocFragments → lintQDocBlock.
package lint

import (
	"regexp"
	"strings"

	"github.com/errata-ai/regexp2"
	"github.com/errata-ai/vale/v3/internal/core"
	"github.com/errata-ai/vale/v3/internal/glob"
	"github.com/errata-ai/vale/v3/internal/lint/code"
	"github.com/errata-ai/vale/v3/internal/nlp"
)

// reQDocComment matches /*!...*/ doc-comment blocks, used to scope
// BlockIgnores to comment content rather than the whole file.
var reQDocComment = regexp.MustCompile(`(?s)/\*!.*?\*/`)

func (l *Linter) lintQDoc(f *core.File) error {
	originalContent := f.Content

	// Apply BlockIgnores and TokenIgnores before parsing. Matched regions are
	// replaced with whitespace to preserve line numbers for alert accuracy.
	content, err := applyQDocPatterns(l.Manager.Config, f.NormedExt, f.RealExt, originalContent)
	if err != nil {
		return err
	}

	if err = l.runQDocPasses(f, content, 0); err != nil {
		return err
	}

	f.SetText(originalContent)
	return nil
}

// applyQDocPatterns applies BlockIgnores and TokenIgnores from the config to
// the raw QDoc file content. Unlike the markup pipeline (which wraps matched
// regions in code-fence syntax for an HTML parser), QDoc patterns replace
// matched content with whitespace so that the tree-sitter parser still sees a
// valid document while the linted text contains no triggering content.
// Newlines within matched regions are preserved so that alert line numbers
// remain accurate.
//
// BlockIgnores are applied per /*!...*/ doc-comment block rather than globally.
// This prevents patterns like (?s)\\code.*?\\endcode from matching \code in
// surrounding C++ line comments and spanning across comment boundaries.
func applyQDocPatterns(c *core.Config, normedExt, realExt, content string) (string, error) {
	matchesExt := func(syntax string) bool {
		sec, err := glob.Compile(syntax)
		if err != nil {
			return false
		}
		return sec.Match(normedExt) || sec.Match(realExt)
	}

	// Compile all applicable BlockIgnore patterns up front.
	var blockPats []*regexp2.Regexp
	for syntax, regexes := range c.BlockIgnores {
		if !matchesExt(syntax) {
			continue
		}
		for _, r := range regexes {
			pat, errc := regexp2.CompileStd(r)
			if errc != nil {
				return content, core.NewE201FromTarget(errc.Error(), r, c.Flags.Path)
			}
			blockPats = append(blockPats, pat)
		}
	}

	if len(blockPats) > 0 {
		// Apply BlockIgnores within each /*!...*/ doc-comment independently.
		var applyErr error
		content = reQDocComment.ReplaceAllStringFunc(content, func(docBlock string) string {
			if applyErr != nil {
				return docBlock
			}
			result := docBlock
			for _, pat := range blockPats {
				var err error
				result, err = pat.ReplaceFunc(result, func(m regexp2.Match) string {
					return blankNonNewlines(m.String())
				}, 0, -1)
				if err != nil {
					applyErr = err
					return docBlock
				}
			}
			return result
		})
		if applyErr != nil {
			return content, applyErr
		}
	}

	for syntax, regexes := range c.TokenIgnores {
		if !matchesExt(syntax) {
			continue
		}
		for _, r := range regexes {
			pat, errc := regexp2.CompileStd(r)
			if errc != nil {
				return content, core.NewE201FromTarget(errc.Error(), r, c.Flags.Path)
			}
			var rerr error
			content, rerr = pat.ReplaceFunc(content, func(m regexp2.Match) string {
				return blankNonNewlines(m.String())
			}, 0, -1)
			if rerr != nil {
				return content, core.NewE201FromTarget(rerr.Error(), r, c.Flags.Path)
			}
		}
	}

	return content, nil
}

// lintQDocBlock processes a single QDoc doc-comment block whose delimiters
// have already been stripped by a code-language comment parser (e.g. Cpp()).
// blockText is the raw comment content without /*! and */; startLine is the
// 1-based line of the opening /*! in the source file.
//
// The block is re-wrapped in /*!...*/ so the QDoc tree-sitter grammar can
// identify the block_comment node, then run through the same two-pass pipeline
// as lintQDoc via runQDocPasses.
//
// Called by lintQDocFragments when [formats] maps a code extension to .qdoc.
func (l *Linter) lintQDocBlock(f *core.File, blockText string, startLine int) error {
	// Re-wrap so the QDoc grammar can parse it. blockText already begins with
	// the '\n' that followed '/*!' in the original source, so we prepend '/*!'
	// directly (no extra newline) to keep node line numbers in sync with the
	// source file. Prepending "/*!\n" would shift every line by +1.
	wrapped := "/*!" + blockText + "\n*/"

	content, err := applyQDocPatterns(l.Manager.Config, f.NormedExt, f.RealExt, wrapped)
	if err != nil {
		return err
	}

	originalContent := f.Content

	// lineOffset shifts comment.Line from wrapped-content coordinates back to
	// source-file coordinates: source_line = comment.Line + (startLine - 1).
	if err = l.runQDocPasses(f, content, startLine-1); err != nil {
		return err
	}

	f.SetText(originalContent)
	return nil
}

// runQDocPasses runs the two-pass QDoc linting pipeline on content:
//
//	Pass 1 (GetComments): headings, briefs, titles, and plain text fragments.
//	  - ".block" scoped comments are skipped (handled by Pass 2).
//	  - brief/note/warning scopes use lintProse only — not lintLines + lintProse
//	    — because the two paths produce different Span[0] values, causing
//	    f.history deduplication to miss and producing duplicate alerts.
//	  - All other scopes (headings, title, plain text) use lintLines.
//
//	Pass 2 (GetQDocProseBlocks): reconstructs full prose per block_comment,
//	  spanning inline-command boundaries. Enables scope:sentence rules
//	  (OxfordComma, SentenceLength, etc.) on complete, unfragmented sentences.
//
// lineOffset is added to each comment's Line before adjustAlerts. For
// standalone .qdoc files this is 0; for embedded /*!...*/ blocks it is
// startLine-1 so wrapped-content line numbers map back to the source file.
func (l *Linter) runQDocPasses(f *core.File, content string, lineOffset int) error {
	lang := code.QDoc()

	// --- Pass 1: scoped comment fragments ---
	comments, err := code.GetComments([]byte(content), lang)
	if err != nil {
		return err
	}

	initialLast := len(f.Alerts)
	last := initialLast
	for _, comment := range comments {
		if strings.HasSuffix(comment.Scope, ".block") {
			// Prose blocks are handled by Pass 2, which reconstructs complete
			// sentences across inline-command boundaries. Linting them here
			// would produce duplicate alerts.
			continue
		}

		l.SetMetaScope(comment.Scope)
		f.SetText(comment.Text)

		if isQDocProseCommandScope(comment.Scope) {
			// brief/note/warning: lintProse covers both scope:text and
			// scope:sentence rules in one pass.
			//
			// NewLinedBlock with line=0 ensures assignLoc returns line=1 for
			// single-line text, avoiding a findLine(source, 0) panic that
			// would occur with NewBlock's default Line=-1.
			block := nlp.NewLinedBlock("", f.Content, "text"+l.metaScope+f.RealExt, 0)
			if err = l.lintProse(f, block, len(f.Lines)); err != nil {
				return err
			}
		} else if !strings.HasPrefix(comment.Scope, "text") {
			// Non-text scope (e.g. "meta.image.line"): use comment.Scope
			// directly so the block scope is not prefixed with "text". This
			// prevents text-scoped rules (Vale.Terms, Microsoft.*) from firing
			// on non-prose content such as image filenames, while still
			// allowing rules scoped specifically to "meta.image" to match.
			block := nlp.NewBlock("", f.Content, comment.Scope+f.RealExt)
			if err = l.lintBlock(f, block, len(f.Lines), 0, true); err != nil {
				return err
			}
		} else {
			// Headings and other single-line scopes: lintLines with lookup=true.
			if err = l.lintLines(f); err != nil {
				return err
			}
		}

		size := len(f.Alerts)
		if size != last {
			adj := comment
			adj.Line += lineOffset
			f.Alerts = adjustAlerts(f.Alerts, last, adj, lang)
		}
		last = size
	}

	pass1End := len(f.Alerts)

	// --- Pass 2: reconstructed prose blocks ---
	proseBlocks, err := code.GetQDocProseBlocks([]byte(content))
	if err != nil {
		return err
	}
	for _, comment := range proseBlocks {
		l.SetMetaScope(comment.Scope)
		f.SetText(comment.Text)

		block := nlp.NewBlock("", f.Content, "text"+l.metaScope+f.RealExt)
		if err = l.lintProse(f, block, len(f.Lines)); err != nil {
			return err
		}

		size := len(f.Alerts)
		if size != last {
			adj := comment
			adj.Line += lineOffset
			f.Alerts = adjustAlerts(f.Alerts, last, adj, lang)
		}
		last = size
	}

	// --- Dedup: remove Pass 1 alerts superseded by Pass 2 ---
	//
	// When inline markup (\e{not}, partially-blanked \l{target}{alias}) splits
	// a \li item text node mid-line, the post-split fragment gets scope ".line"
	// and is linted by Pass 1. Pass 2 reconstructs the full prose and lints
	// the same content at a different (correct) column. Because f.history keys
	// on line:col:check, the different columns prevent dedup, producing two
	// alerts for one real issue.
	//
	// Fix: after both passes, for any (line, check, match) triple that appears
	// in Pass 2, suppress the corresponding Pass 1 alert. Pass 2's column is
	// authoritative because it is measured against the full reconstructed prose.
	if pass1End > initialLast && len(f.Alerts) > pass1End {
		type lcm struct {
			line  int
			check string
			match string
		}
		pass2Set := make(map[lcm]bool, len(f.Alerts)-pass1End)
		for _, a := range f.Alerts[pass1End:] {
			pass2Set[lcm{a.Line, a.Check, a.Match}] = true
		}
		var filteredPass1 []core.Alert
		for _, a := range f.Alerts[initialLast:pass1End] {
			if !pass2Set[lcm{a.Line, a.Check, a.Match}] {
				filteredPass1 = append(filteredPass1, a)
			}
		}
		combined := make([]core.Alert, initialLast, initialLast+len(filteredPass1)+len(f.Alerts)-pass1End)
		copy(combined, f.Alerts[:initialLast])
		combined = append(combined, filteredPass1...)
		combined = append(combined, f.Alerts[pass1End:]...)
		f.Alerts = combined
	}

	return nil
}

// isQDocProseCommandScope reports whether the comment scope was produced by a
// CommandMatch query whose content should also be run through lintProse for
// scope: sentence rule coverage (SentenceLength, OxfordComma, Semicolon).
// These are brief/note/warning (excluded from GetQDocProseBlocks to prevent
// duplicates) and image.alt (linted in isolation so NLP cannot concatenate a
// short unpunctuated caption with adjacent prose paragraphs).
func isQDocProseCommandScope(scope string) bool {
	return strings.Contains(scope, ".brief.") ||
		strings.Contains(scope, ".note.") ||
		strings.Contains(scope, ".warning.") ||
		strings.Contains(scope, ".image.alt.")
}

// blankNonNewlines replaces every non-newline character in s with a space,
// preserving newlines so that alert line numbers remain accurate after a
// BlockIgnores replacement.
func blankNonNewlines(s string) string {
	var b strings.Builder
	b.Grow(len(s))
	for _, r := range s {
		if r == '\n' {
			b.WriteRune('\n')
		} else {
			b.WriteByte(' ')
		}
	}
	return b.String()
}
