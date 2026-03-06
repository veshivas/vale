package code

import (
	"regexp"

	"github.com/errata-ai/vale/v3/internal/core"
	"github.com/errata-ai/vale/v3/internal/lint/code/qdocparser"
)

func QDoc() *Language {
	return &Language{
		Delims: regexp.MustCompile(`/\*!|\*/`),
		Parser: qdocparser.GetLanguage(),
		Queries: []core.Scope{
			{Name: "", Expr: "(text) @comment"},
			{Name: "heading", CommandMatch: `^section[1-6]$`},
			{Name: "brief", CommandMatch: `^brief$`},
		},
		Padding:     cStyle,
		ScopePrefix: "text.qdoc",
	}
}
