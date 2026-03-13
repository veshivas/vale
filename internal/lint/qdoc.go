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
