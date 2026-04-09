// fragment.go handles linting of markup embedded in code files, reached via
// [formats] config (e.g. [formats] cpp = md, cpp = qdoc).
//
// lintFragments extracts comments from the code file using the source
// language's tree-sitter grammar, then lints each comment's text through
// the target markup handler (lintMarkdown, lintRST, lintADoc, lintOrg).
//
// For QDoc ([formats] cpp = qdoc), lintQDocFragments provides a specialized
// path that routes /*!...*/ doc-comment blocks through the full two-pass
// QDoc pipeline via lintQDocBlock.
package lint

import (
	"fmt"
	"strings"

	"github.com/errata-ai/vale/v3/internal/core"
	"github.com/errata-ai/vale/v3/internal/lint/code"
)

func findLine(s string, line int) string {
	lines := strings.Split(s, "\n")
	if line > len(lines) {
		return ""
	}
	return lines[line-1]
}

func leadingSpaces(line string, offset int) int {
	spaces := 0
	for _, r := range line {
		if r == ' ' {
			spaces++
		} else {
			break
		}
	}
	return spaces - offset
}

func adjustAlerts(alerts []core.Alert, last int, comment code.Comment, lang *code.Language) []core.Alert {
	for i := range alerts {
		if i >= last {
			line := findLine(comment.Source, alerts[i].Line)

			padding := lang.Padding(line)
			if strings.HasPrefix(line, " ") {
				padding += leadingSpaces(line, comment.Offset)
			}

			alerts[i].Line += comment.Line - 1
			alerts[i].Span = []int{
				alerts[i].Span[0] + comment.Offset + padding,
				alerts[i].Span[1] + comment.Offset + padding,
			}
		}
	}
	return alerts
}

func (l *Linter) lintFragments(f *core.File) error {
	// We want to set up our processing servers as if we were dealing with
	// a directory since we likely have many fragments to convert.
	l.HasDir = true

	lang, err := code.GetLanguageFromExt(f.RealExt)
	if err != nil {
		return err
	}

	found, err := updateQueries(f, l.Manager.Config.Views)
	if err != nil {
		return err
	} else if len(found) > 0 {
		lang.Queries = found
	}

	// QDoc markup embedded in code files (.cpp, .qml via [formats] cpp = qdoc)
	// needs the full QDoc two-pass pipeline (heading/brief/prose scope support,
	// BlockIgnores, sentence segmentation) rather than a markup→HTML converter.
	// NormedExt is ".qdoc" here because [formats] mapped the original extension.
	if f.NormedExt == ".qdoc" {
		return l.lintQDocFragments(f, lang)
	}

	comments, err := code.GetComments([]byte(f.Content), lang)
	if err != nil {
		return err
	}

	last := 0
	for _, comment := range comments {
		l.SetMetaScope(comment.Scope)
		f.SetText(comment.Text)

		switch f.NormedExt {
		case ".md":
			err = l.lintMarkdown(f)
		case ".rst":
			err = l.lintRST(f)
		case ".adoc":
			err = l.lintADoc(f)
		case ".org":
			err = l.lintOrg(f)
		default:
			return fmt.Errorf("unsupported markup format '%s'", f.NormedExt)
		}

		size := len(f.Alerts)
		if size != last {
			f.Alerts = adjustAlerts(f.Alerts, last, comment, lang)
		}
		last = size
	}

	return err
}

// lintQDocFragments handles QDoc markup embedded in code files such as .cpp
// and .qml (reached via [formats] cpp = qdoc in .vale.ini). It extracts all
// comment blocks using the code language's grammar, routes /*!...*/ doc-comment
// blocks through the full QDoc two-pass pipeline, and processes regular
// comments with lintLines.
func (l *Linter) lintQDocFragments(f *core.File, lang *code.Language) error {
	// Use Cpp() to extract comments — both .cpp and .qml use C-style delimiters,
	// so Cpp() correctly identifies /*!...*/ block boundaries. We cannot use
	// QDoc() here because QDoc() has a different Delims regex (matches /*! and
	// */ separately) and Queries designed for QDoc markup, not C++ source.
	cppLang := code.Cpp()
	comments, err := code.GetComments([]byte(f.Content), cppLang)
	if err != nil {
		return err
	}

	wholeFile := f.Content
	for _, comment := range comments {
		if strings.HasSuffix(comment.Scope, ".block") &&
			strings.HasPrefix(comment.Source, "/*!") {
			// QDoc doc-comment block: use the full two-pass QDoc pipeline.
			// lintQDocBlock handles its own alert position adjustment and
			// restores f.Content before returning.
			if err = l.lintQDocBlock(f, comment.Text, comment.Line); err != nil {
				return err
			}
			continue
		}

		// Skip single-line (//) C++ comments — only /*!...*/ doc-comment
		// blocks are QDoc documentation.
		if strings.HasSuffix(comment.Scope, ".line") {
			continue
		}

		// Regular block comment (/* ... */): process with lintLines.
		l.SetMetaScope(comment.Scope)
		f.SetText(comment.Text)
		last := len(f.Alerts)
		if err = l.lintLines(f); err != nil {
			return err
		}
		if len(f.Alerts) != last {
			f.Alerts = adjustAlerts(f.Alerts, last, comment, lang)
		}
	}

	f.SetText(wholeFile)
	return nil
}
