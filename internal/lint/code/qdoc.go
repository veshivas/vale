package code

import (
	"regexp"
	"unsafe"

	qdoc "github.com/veshivas/tree-sitter-qdoc/bindings/go"

	sitter "github.com/smacker/go-tree-sitter"

	"github.com/errata-ai/vale/v3/internal/core"
)

func QDoc() *Language {
	return &Language{
		Delims: regexp.MustCompile(`/\*!|\*/`),
		Parser: sitter.NewLanguage(unsafe.Pointer(qdoc.Language())),
		Queries: []core.Scope{
			{Name: "", Expr: "(text) @comment"},
			{Name: "heading", CommandMatch: `^section[1-6]$`},
			{Name: "brief", CommandMatch: `^brief$`},
			{Name: "title", CommandMatch: `^title$`},
		{Name: "image", Expr: `[(image_command filename: (image_filename) @comment .) (inlineimage_command filename: (inline_text) @comment .)]`},
		},
		Padding: cStyle,
	}
}
