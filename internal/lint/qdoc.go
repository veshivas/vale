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
	// Save the original content before any f.SetText calls modify f.Content.
	originalContent := f.Content
	lang := code.QDoc()

	// Apply BlockIgnores and TokenIgnores to suppress code blocks and tokens
	// before parsing. Matched regions are replaced with whitespace to preserve
	// line numbers so that alert positions remain accurate.
	content, err := applyQDocPatterns(l.Manager.Config, f.NormedExt, f.RealExt, originalContent)
	if err != nil {
		return err
	}

	comments, err := code.GetComments([]byte(content), lang)
	if err != nil {
		return err
	}

	last := 0
	for _, comment := range comments {
		if strings.HasSuffix(comment.Scope, ".block") {
			// Prose blocks are handled by the GetQDocProseBlocks pass below,
			// which reconstructs complete sentences across inline-command
			// boundaries. Skip them here to avoid duplicate alerts.
			continue
		}

		l.SetMetaScope(comment.Scope)
		f.SetText(comment.Text)

		// Headings and single-line scopes (brief, line): lintLines with lookup=true.
		err = l.lintLines(f)
		if err != nil {
			return err
		}

		size := len(f.Alerts)
		if size != last {
			f.Alerts = adjustAlerts(f.Alerts, last, comment, lang)
		}
		last = size
	}

	// Second pass: reconstruct complete prose per block_comment, spanning
	// inline-command boundaries. This ensures sentences are never fragmented
	// and enables scope: sentence rules (OxfordComma, SentenceLength, etc.).
	proseBlocks, err := code.GetQDocProseBlocks([]byte(content))
	if err != nil {
		return err
	}
	for _, comment := range proseBlocks {
		l.SetMetaScope(comment.Scope)
		f.SetText(comment.Text)

		block := nlp.NewBlock("", f.Content, "text"+l.metaScope+f.RealExt)
		err = l.lintProse(f, block, len(f.Lines))
		if err != nil {
			return err
		}

		size := len(f.Alerts)
		if size != last {
			f.Alerts = adjustAlerts(f.Alerts, last, comment, lang)
		}
		last = size
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
			content, rerr = pat.Replace(content, " ", 0, -1)
			if rerr != nil {
				return content, core.NewE201FromTarget(rerr.Error(), r, c.Flags.Path)
			}
		}
	}

	return content, nil
}

// lintQDocBlock processes a single QDoc doc-comment block whose delimiters
// have already been stripped by a code-language comment parser (e.g. Cpp()).
// blockText is the raw comment content without /*!  and */; startLine is the
// 1-based line of the opening /*!  in the source file.
//
// The block is re-wrapped in /*!...*/ so the QDoc tree-sitter grammar can
// identify the block_comment node, then run through the same two-pass pipeline
// as lintQDoc. Alert line numbers are corrected for the re-wrap offset so that
// they map back to the correct positions in the original source file.
//
// Called by lintQDocFragments when [formats] maps a code extension to .qdoc.
func (l *Linter) lintQDocBlock(f *core.File, blockText string, startLine int) error {
	lang := code.QDoc()

	// Re-wrap so the QDoc grammar can parse it. blockText already begins with
	// the '\n' that followed '/*!' in the original source, so we append '/*!'
	// directly (no extra newline) to keep node line numbers in sync with the
	// source file. Adding "/*!\n" would shift every line by +1.
	wrapped := "/*!" + blockText + "\n*/"

	content, err := applyQDocPatterns(l.Manager.Config, f.NormedExt, f.RealExt, wrapped)
	if err != nil {
		return err
	}

	originalContent := f.Content

	// Pass 1: heading / brief / title / line scopes.
	comments, err := code.GetComments([]byte(content), lang)
	if err != nil {
		return err
	}

	last := len(f.Alerts)
	for _, comment := range comments {
		if strings.HasSuffix(comment.Scope, ".block") {
			continue
		}

		l.SetMetaScope(comment.Scope)
		f.SetText(comment.Text)

		if err = l.lintLines(f); err != nil {
			return err
		}

		size := len(f.Alerts)
		if size != last {
			// comment.Line is relative to the wrapped content (line 1 = "/*!").
			// Shift by startLine - 1 so adjustAlerts maps it to the correct
			// line in the source file: source_line = startLine + comment.Line - 1.
			adj := comment
			adj.Line += startLine - 1
			f.Alerts = adjustAlerts(f.Alerts, last, adj, lang)
		}
		last = size
	}

	// Pass 2: reconstruct full prose per block_comment for sentence-scope rules.
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
			adj.Line += startLine - 1
			f.Alerts = adjustAlerts(f.Alerts, last, adj, lang)
		}
		last = size
	}

	f.SetText(originalContent)
	return nil
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
