// qdoc.go defines the QDoc Language for Vale's tree-sitter comment extraction.
//
// QDoc is the Qt documentation markup format. Unlike other markup formats,
// QDoc has no upstream HTML conversion pipeline — Vale parses it directly
// via a tree-sitter grammar (github.com/veshivas/tree-sitter-qdoc).
//
// The Language returned by QDoc() is consumed by:
//   - GetComments (comments.go): extracts scoped comment fragments for lintLines.
//   - GetQDocProseBlocks (qdocprose.go): reconstructs full prose for lintProse.
//
// File routing:
//
//	.qdoc/.qdocinc → format "markup" → lintQDoc (internal/lint/qdoc.go)
//	.qml           → format "code"   → lintCode → GetLanguageFromExt → QDoc()
package code

import (
	"regexp"
	"unsafe"

	qdoc "github.com/veshivas/tree-sitter-qdoc/bindings/go"

	sitter "github.com/smacker/go-tree-sitter"

	"github.com/errata-ai/vale/v3/internal/core"
)

// QDoc returns the Language definition for QDoc markup.
//
// Queries are evaluated in two passes by GetComments (see comments.go):
//
//	Pass 1 — CommandMatch queries: each matched command's text argument is
//	         reconstructed by walking markup siblings (see runCommandMatch).
//	         Consumed text-node start bytes are recorded so Pass 2 skips them.
//	Pass 2 — Plain Expr queries: the catch-all "(text) @comment" captures any
//	         text node not already consumed by Pass 1, preventing duplicates.
func QDoc() *Language {
	return &Language{
		Delims: regexp.MustCompile(`/\*!|\*/`),
		Parser: sitter.NewLanguage(unsafe.Pointer(qdoc.Language())),
		Queries: []core.Scope{
			// Catch-all: every text node not consumed by a CommandMatch query.
			{Name: "", Expr: "(text) @comment"},

			// \section1 through \section6. CommandMatch implies first-line-only.
			{Name: "heading", CommandMatch: `^section[1-6]$`},

			// Admonition-style commands: text spans until the first blank line
			// (\n\n). Their prose is excluded from GetQDocProseBlocks (Pass 2)
			// via skipQDocProseUntilBlank to prevent duplicate alerts.
			{Name: "brief", CommandMatch: `^brief$`, UntilBlankLine: true},
			{Name: "note", CommandMatch: `^note$`, UntilBlankLine: true},
			{Name: "warning", CommandMatch: `^warning$`, UntilBlankLine: true},

			// \title — single-line like headings.
			{Name: "title", CommandMatch: `^title$`},

			// Image commands missing alt text. The trailing-dot anchor (`. `)
			// fires only when the filename is the last child, i.e. no alt text.
			// ScopePrefix "meta" produces "meta.image.line" instead of
			// "text.comment.image.line" so that text-scoped rules (Vale.Terms,
			// Microsoft.*) do not fire on image filenames; only Qt.QDocImageAlt
			// (scoped to "meta.image") matches this scope.
			{Name: "image", ScopePrefix: "meta", Expr: `[(image_command filename: (image_filename) @comment .) (inlineimage_command filename: (inline_text) @comment .)]`},

			// \target and \keyword anchor identifiers. ScopePrefix "meta"
			// prevents text-scoped rules from firing on anchor names; only rules
			// explicitly scoped to "meta.anchor" (e.g. Qt.QDocAnchorAPIName) match.
			{Name: "anchor", ScopePrefix: "meta", CommandMatch: `^(target|keyword)$`},
		},
		Padding: cStyle,
	}
}
