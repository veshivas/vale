package code

import (
	"bytes"
	"context"
	"strings"

	sitter "github.com/smacker/go-tree-sitter"
)

// codeBlockEnterCommands lists QDoc commands that begin a code block. Text
// nodes following these commands (until the corresponding end command) are not
// prose and must be excluded from prose reconstruction.
var codeBlockEnterCommands = map[string]bool{
	"code": true, "qml": true, "badcode": true, "snippet": true,
}

// codeBlockExitInlineTexts maps the inline_text portion that signals the end
// of a code block. The tree-sitter QDoc grammar parses \endcode as the inline
// command \e with argument "ndcode" (because "e" is an inline_command_name and
// "nd..." is an inline_text), and similarly for \endqml and \endsnippet.
var codeBlockExitInlineTexts = map[string]bool{
	"ndcode": true, "ndqml": true, "ndsnippet": true,
}

// skipQDocProseArgs contains QDoc commands whose immediately-following text
// node holds a structured argument (identifier, signature, or reference list)
// rather than prose. Text nodes after these commands are excluded from prose
// reconstruction so they don't contaminate NLP sentence splitting.
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
// Unlike GetComments with the "(text) @comment" query, this function spans
// inline-command boundaries so that sentences are never split mid-text by
// inline markup (e.g. "\c{code}"). The result is suitable for lintProse,
// enabling scope: sentence rules to fire on complete QDoc prose.
//
// Note: comment.Line is set to the block_comment start line. When command
// lines are skipped during reconstruction the reported line may be off by a
// small amount; the matched text in each alert remains accurate.
func GetQDocProseBlocks(source []byte) ([]Comment, error) {
	lang := QDoc()
	parser := sitter.NewParser()
	parser.SetLanguage(lang.Parser)

	tree, err := parser.ParseCtx(context.Background(), nil, source)
	if err != nil {
		return nil, err
	}

	// Use a query to find all block_comment nodes regardless of nesting depth.
	// (The grammar wraps each block_comment in a comment node, so they are
	// NOT direct children of source_file.)
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
//
// Rules:
//   - command nodes: set skip flag when the command name is in skipQDocProseArgs
//   - text nodes: appended unless skip flag is set; flag is then cleared
//   - inline_command nodes: inline_text argument appended with braces stripped;
//     flag is cleared (inline commands are never topic commands)
func qdocReconstructProse(node *sitter.Node, source []byte) (raw, clean string) {
	var b strings.Builder
	skipNextText := false
	inCodeBlock := false

	for i := 0; i < int(node.NamedChildCount()); i++ {
		markup := node.NamedChild(i)
		if markup.Type() != "markup" {
			continue
		}

		for j := 0; j < int(markup.NamedChildCount()); j++ {
			child := markup.NamedChild(j)

			switch child.Type() {
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
				} else {
					skipNextText = skipQDocProseArgs[cmdName]
				}

			case "text":
				if !skipNextText && !inCodeBlock {
					b.WriteString(child.Content(source))
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
				} else if !inCodeBlock {
					skipNextText = false
					if icText != "" {
						b.WriteString(icText)
					}
				}
			}
		}
	}

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
