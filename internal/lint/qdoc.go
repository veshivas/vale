package lint

import (
	"strings"

	"github.com/errata-ai/vale/v3/internal/core"
	"github.com/errata-ai/vale/v3/internal/lint/code"
	"github.com/errata-ai/vale/v3/internal/nlp"
)

func (l *Linter) lintQDoc(f *core.File) error {
	lang := code.QDoc()

	comments, err := code.GetComments([]byte(f.Content), lang)
	if err != nil {
		return err
	}
	wholeFile := f.Content

	last := 0
	for _, comment := range comments {
		l.SetMetaScope(comment.Scope)
		f.SetText(comment.Text)

		if strings.Contains(comment.Scope, "heading") {
			// Headings are single lines; use lintLines (no NLP needed).
			err = l.lintLines(f)
		} else if strings.HasSuffix(comment.Scope, ".block") {
			// Multi-line prose blocks: use lintProse to enable sentence-scope rules.
			block := nlp.NewBlock("", f.Content, "text"+l.metaScope+f.RealExt)
			err = l.lintProse(f, block, len(f.Lines))
		} else {
			// Single-line scopes (brief, line): use lintLines with lookup=true.
			err = l.lintLines(f)
		}
		if err != nil {
			return err
		}

		size := len(f.Alerts)
		if size != last {
			f.Alerts = adjustAlerts(f.Alerts, last, comment, lang)
		}
		last = size
	}

	f.SetText(wholeFile)
	return nil
}
