// qdocprose.go reconstructs full prose from QDoc block_comment nodes, spanning
// inline-command boundaries so that NLP sentence splitting operates on complete
// sentences rather than fragments interrupted by \c{...}, \b{...}, etc.
//
// This is used by lintQDoc Pass 2 (internal/lint/qdoc.go) to enable
// scope:sentence rules (OxfordComma, SentenceLength, Semicolon) on QDoc prose.
//
// The reconstruction algorithm is a single-pass linear walk over the flat
// block_comment → markup* AST structure. Each markup node has exactly one named
// child: command, inline_command, text, or block_command. State flags track
// code blocks and skip regions to exclude non-prose content.
package code

import (
	"bytes"
	"context"
	"strings"

	sitter "github.com/smacker/go-tree-sitter"
)

// codeBlockEnterCommands lists QDoc commands that begin a verbatim code block.
// Text nodes after these commands (until the matching end command) contain
// source code, not prose, and must be excluded from reconstruction.
var codeBlockEnterCommands = map[string]bool{
	"code": true, "qml": true, "badcode": true, "snippet": true,
}

// codeBlockExitInlineTexts maps the inline_text content that signals the end
// of a code block. The QDoc grammar tokenizes \endcode as inline_command \e
// with inline_text "ndcode" (because "e" is a recognized inline_command_name
// and the rest becomes inline_text). Similarly: \endqml → "ndqml",
// \endsnippet → "ndsnippet".
var codeBlockExitInlineTexts = map[string]bool{
	"ndcode": true, "ndqml": true, "ndsnippet": true,
}

// skipQDocProseUntilBlank lists commands whose text content (until the first
// blank line) is already linted via their own CommandMatch scope in Pass 1
// (brief.line, note.line, warning.line). qdocCollectProse skips all siblings
// after these commands until a \n\n boundary, then resumes. Without this,
// scope:text rules would fire twice — once in Pass 1 and again in Pass 2.
var skipQDocProseUntilBlank = map[string]bool{
	"brief": true, "note": true, "warning": true,
}

// skipQDocProseArgs lists commands whose immediately-following text node holds
// a structured argument (identifier, signature, or reference list) rather than
// prose. These are excluded from reconstruction to avoid contaminating NLP
// sentence splitting with non-prose content like "QNetworkReply" or
// "int Calculator::add(int a, int b)".
var skipQDocProseArgs = map[string]bool{
	// Topic commands — argument is an identifier / signature.
	"class": true, "enum": true, "fn": true, "property": true, "variable": true,
	"typedef": true, "typealias": true, "namespace": true, "module": true,
	"group": true, "page": true, "example": true, "macro": true, "headerfile": true,
	"qmltype": true, "qmlproperty": true, "qmlmethod": true, "qmlsignal": true,
	"qmlenum": true, "qmlmodule": true, "qmlattachedproperty": true,
	"qmlattachedsignal": true, "qmlvaluetype": true, "inqmlmodule": true,
	// Cross-reference commands — argument is a symbol / page name.
	"sa": true, "see": true,
}

// GetQDocProseBlocks parses source with the QDoc grammar and returns one
// Comment per block_comment node whose reconstructed prose is non-empty.
//
// Unlike GetComments (which returns one Comment per text node, fragmenting
// sentences at inline-command boundaries), this function walks all markup
// siblings per block_comment and concatenates text + inline_command content
// into continuous prose. The result is suitable for lintProse + NLP sentence
// segmentation, enabling scope:sentence rules on complete QDoc prose.
//
// Skipped content:
//   - Code blocks (\code...\endcode, \qml...\endqml, \snippet...\endsnippet)
//   - Topic-command arguments (\class, \fn, \property, etc.)
//   - brief/note/warning text (linted separately in Pass 1 via CommandMatch)
//
// Newlines in skipped regions are preserved so prose line numbers stay aligned
// with source line numbers for accurate alert positioning.
func GetQDocProseBlocks(source []byte) ([]Comment, error) {
	lang := QDoc()
	parser := sitter.NewParser()
	parser.SetLanguage(lang.Parser)

	tree, err := parser.ParseCtx(context.Background(), nil, source)
	if err != nil {
		return nil, err
	}

	// Use a query rather than iterating root children because the grammar wraps
	// each block_comment inside a comment node: source_file → comment → block_comment.
	// A query finds them at any depth.
	q, qErr := sitter.NewQuery([]byte("(block_comment) @block"), lang.Parser)
	if qErr != nil {
		return nil, qErr
	}

	var comments []Comment
	qc := sitter.NewQueryCursor()
	qc.Exec(q, tree.RootNode())

	for {
		m, ok := qc.NextMatch()
		if !ok {
			break
		}
		for _, c := range m.Captures {
			node := c.Node
			raw, clean := qdocReconstructProse(node, source)
			if strings.TrimSpace(clean) == "" {
				continue
			}
			comments = append(comments, Comment{
				Text:   clean,
				Source: raw,
				Line:   int(node.StartPoint().Row) + 1,
				Offset: int(node.StartPoint().Column),
				Scope:  "text.comment.block",
			})
		}
	}

	return comments, nil
}

// qdocReconstructProse walks the markup children of a block_comment node and
// returns the prose as two strings:
//   - raw:   original whitespace preserved (passed to adjustAlerts as Source)
//   - clean: leading whitespace stripped per line  (passed to lintProse as Text)
func qdocReconstructProse(node *sitter.Node, source []byte) (raw, clean string) {
	var b strings.Builder
	qdocCollectProse(node, source, &b)
	raw = b.String()
	if raw == "" {
		return
	}

	var cleanBuf bytes.Buffer
	for _, line := range strings.Split(raw, "\n") {
		cleanBuf.WriteString(strings.TrimLeft(line, " \t"))
		cleanBuf.WriteString("\n")
	}
	clean = cleanBuf.String()
	return
}

// qdocCollectProse appends prose text from the markup children of node to b.
// It handles the four markup child types:
//   - block_command: recurses into prose-bearing blocks (list, legalese, quotation);
//     skips raw_block and table_block.
//   - command: sets skip/code-block flags for the following text node.
//   - text: appended when not suppressed by a skip or code-block flag.
//   - inline_command: inline_text appended with braces stripped.
//     Also detects \endcode/\endqml/\endsnippet, which the grammar tokenizes as
//     inline_command \e with inline_text "ndcode"/"ndqml"/"ndsnippet".
func qdocCollectProse(node *sitter.Node, source []byte, b *strings.Builder) {
	skipNextText := false
	inCodeBlock := false
	skipUntilBlankLine := false

	for i := 0; i < int(node.NamedChildCount()); i++ {
		markup := node.NamedChild(i)
		if markup.Type() != "markup" {
			continue
		}

		for j := 0; j < int(markup.NamedChildCount()); j++ {
			child := markup.NamedChild(j)

			switch child.Type() {
			case "block_command":
				skipNextText = false
				skipUntilBlankLine = false
				// block_command has one named child: the specific block type.
				// Recurse into prose-bearing blocks; skip raw and table.
				if child.NamedChildCount() > 0 {
					inner := child.NamedChild(0)
					switch inner.Type() {
					case "list_block", "legalese_block", "quotation_block":
						qdocCollectProse(inner, source, b)
					// raw_block, table_block: no prose, skip.
					}
				}

			case "command":
				cmdName := ""
				for k := 0; k < int(child.NamedChildCount()); k++ {
					if cn := child.NamedChild(k); cn.Type() == "command_name" {
						cmdName = cn.Content(source)
					}
				}
				if codeBlockEnterCommands[cmdName] {
					inCodeBlock = true
					skipNextText = false
					skipUntilBlankLine = false
				} else if skipQDocProseUntilBlank[cmdName] {
					// brief/note/warning: skip all content until first blank
					// line. Their text is linted separately via lintLines +
					// lintProse on the .line comment produced by runCommandMatch.
					skipUntilBlankLine = true
					skipNextText = false
				} else {
					skipUntilBlankLine = false
					skipNextText = skipQDocProseArgs[cmdName]
				}

			case "text":
				content := child.Content(source)
				if inCodeBlock || skipNextText {
					// Preserve newlines from skipped text so that prose line
					// offsets stay in sync with source line numbers.
					for _, r := range content {
						if r == '\n' {
							b.WriteRune('\n')
						}
					}
				} else if skipUntilBlankLine {
					// Skip content until the first blank line (\n\n), then
					// resume prose collection from that point onward.
					if idx := strings.Index(content, "\n\n"); idx >= 0 {
						for _, r := range content[:idx] {
							if r == '\n' {
								b.WriteRune('\n')
							}
						}
						b.WriteString(content[idx:])
						skipUntilBlankLine = false
					} else {
						for _, r := range content {
							if r == '\n' {
								b.WriteRune('\n')
							}
						}
					}
				} else {
					b.WriteString(content)
				}
				skipNextText = false

			case "inline_command":
				icName := ""
				icText := ""
				for k := 0; k < int(child.NamedChildCount()); k++ {
					ic := child.NamedChild(k)
					switch ic.Type() {
					case "inline_command_name":
						icName = ic.Content(source)
					case "inline_text":
						t := strings.TrimSpace(ic.Content(source))
						t = strings.TrimPrefix(t, "{")
						t = strings.TrimSuffix(t, "}")
						icText = t
					}
				}
				// \endcode/\endqml/\endsnippet are tokenized by the grammar as
				// inline_command \e with inline_text "ndcode"/"ndqml"/"ndsnippet".
				if inCodeBlock && icName == "e" && codeBlockExitInlineTexts[icText] {
					inCodeBlock = false
				} else if !inCodeBlock && !skipUntilBlankLine {
					skipNextText = false
					if icText != "" {
						b.WriteString(icText)
					}
				}
			}
		}
	}
}
