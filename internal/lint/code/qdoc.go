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

	sitter "github.com/smacker/go-tree-sitter"
	qdoc "github.com/veshivas/tree-sitter-qdoc/bindings/go"

	"github.com/errata-ai/vale/v3/internal/core"
)

// QDoc returns the Language definition for QDoc markup.
//
// Queries are evaluated in two passes by GetComments (see comments.go):
//
//	Pass 1 — CommandMatch queries: used only for \target and \keyword anchors,
//	         where the argument is a bare identifier reconstructed by sibling walking.
//	         Consumed node start bytes are recorded so Pass 2 skips them.
//	Pass 2 — Plain Expr queries: captures scoped comment text directly via
//	         tree-sitter node queries. Headings, title, brief, note, and warning
//	         text are captured from dedicated grammar nodes (section_command,
//	         title_command, brief_command, note_command, warning_command).
//	         The catch-all "(text) @comment" captures remaining prose text nodes.
func QDoc() *Language {
	return &Language{
		Delims: regexp.MustCompile(`/\*!|\*/`),
		Parser: sitter.NewLanguage(qdoc.Language()),
		Queries: []core.Scope{
			// Catch-all: every prose text node not captured by a named scope below.
			{Name: "", Expr: "(text) @comment"},

			// \section1–\section4: heading text captured from the dedicated grammar
			// node. FirstLine clips to the heading line (heading_text already stops
			// at \n, so this is redundant functionally but makes .line scope explicit).
			{Name: "heading", Expr: `(section_command text: (heading_text) @comment)`, FirstLine: true},

			// \title: page title, scoped separately from headings so that
			// Qt.QDocPageTitle (title-style capitalisation) fires only on \title.
			{Name: "title", Expr: `(title_command text: (heading_text) @comment)`, FirstLine: true},

			// \brief: one-sentence class or function description.
			{Name: "brief", Expr: `(brief_command text: (brief_text) @comment)`},

			// \note, \warning: admonition text spanning continuation lines until
			// the first blank line or next QDoc command.
			{Name: "note", Expr: `(note_command    text: (admonition_text) @comment)`},
			{Name: "warning", Expr: `(warning_command text: (admonition_text) @comment)`},

			// Image commands missing alt text. The trailing-dot anchor (`. `)
			// fires only when the filename is the last child, i.e. no alt text.
			// ScopePrefix "meta" produces "meta.image.line" instead of
			// "text.comment.image.line" so that text-scoped rules (Vale.Terms,
			// Microsoft.*) do not fire on image filenames; only Qt.QDocImageAlt
			// (scoped to "meta.image") matches this scope.
			{Name: "image", ScopePrefix: "meta", Expr: `[(image_command filename: (image_filename) @comment .) (inlineimage_command filename: (inline_text) @comment .)]`},

			// Alt text for \image and \inlineimage. Captured with a text.comment
			// scope so that isQDocProseCommandScope routes it through lintProse
			// in isolation — each alt text is its own NLP pass. This lets
			// SentenceLength fire on a genuinely long caption while preventing
			// the NLP from joining a short, unpunctuated alt text with an
			// adjacent prose paragraph and producing a false positive.
			{Name: "image.alt", Expr: `[(image_command alt: (image_alt_text) @comment) (inlineimage_command alt: (image_alt) @comment)]`},

			// \target and \keyword anchor identifiers. ScopePrefix "meta"
			// prevents text-scoped rules from firing on anchor names; only rules
			// explicitly scoped to "meta.anchor" (e.g. Qt.QDocAnchorAPIName) match.
			{Name: "anchor", ScopePrefix: "meta", CommandMatch: `^(target|keyword)$`},
		},
		Padding: cStyle,
	}
}
