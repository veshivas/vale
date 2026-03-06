package lint

import (
	"github.com/errata-ai/vale/v3/internal/core"
	"github.com/errata-ai/vale/v3/internal/lint/code"
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

	f.SetText(wholeFile)
	return nil
}
