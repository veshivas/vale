package code

import (
	"bytes"
	"fmt"
	"strings"

	sitter "github.com/smacker/go-tree-sitter"

	"github.com/errata-ai/vale/v3/internal/core"
)

type QueryEngine struct {
	tree   *sitter.Tree
	lang   *Language
	cutset string
}

func NewQueryEngine(tree *sitter.Tree, lang *Language) *QueryEngine {
	cutset := lang.Cutset
	if cutset == "" {
		cutset = " "
	}

	return &QueryEngine{
		tree:   tree,
		lang:   lang,
		cutset: cutset,
	}
}

func (qe *QueryEngine) run(scope core.Scope, q *sitter.Query, source []byte, skip map[uint32]bool) []Comment {
	var comments []Comment

	meta := scope.Name
	if meta != "" {
		meta = "." + meta
	}

	qc := sitter.NewQueryCursor()
	qc.Exec(q, qe.tree.RootNode())

	for {
		m, ok := qc.NextMatch()
		if !ok {
			break
		}

		m = qc.FilterPredicates(m, source)
		for _, c := range m.Captures {
			if q.CaptureNameForId(c.Index) != "comment" {
				continue
			}
			if skip[c.Node.StartByte()] {
				continue
			}
			rText := c.Node.Content(source)
			cText := qe.lang.Delims.ReplaceAllString(rText, "")

			if scope.FirstLine {
				// Extract only the first non-empty line (heading text).
				cText = strings.TrimLeft(cText, " \t")
				if idx := strings.Index(cText, "\n"); idx >= 0 {
					cText = cText[:idx]
				}
				cText = strings.TrimSpace(cText)
			}

			prefix := "text.comment"
			if qe.lang.ScopePrefix != "" {
				prefix = qe.lang.ScopePrefix
			}
			blkScope := prefix + meta + ".line"
			if !scope.FirstLine && strings.Count(cText, "\n") > 1 {
				blkScope = prefix + meta + ".block"

				buf := bytes.Buffer{}
				for _, line := range strings.Split(cText, "\n") {
					buf.WriteString(strings.TrimLeft(line, qe.cutset))
					buf.WriteString("\n")
				}

				cText = buf.String()
			}

			comments = append(comments, Comment{
				Line:   int(c.Node.StartPoint().Row) + 1,
				Offset: int(c.Node.StartPoint().Column),
				Scope:  blkScope,
				Text:   cText,
				Source: rText,
			})
		}
	}

	return comments
}

// extractInlineText returns the display text of an inline_command node with
// brace delimiters stripped from the inline_text child.
func extractInlineText(node *sitter.Node, source []byte) string {
	for i := 0; i < int(node.NamedChildCount()); i++ {
		child := node.NamedChild(i)
		if child.Type() == "inline_text" {
			t := strings.TrimSpace(child.Content(source))
			t = strings.TrimPrefix(t, "{")
			t = strings.TrimSuffix(t, "}")
			return t
		}
	}
	return ""
}

// collectCommandText walks markup siblings starting after markupNode and
// returns the concatenated text content and the start bytes of all text/
// inline_command nodes visited, spanning inline-command boundaries.
// Collection stops when a block command or another top-level command is reached.
func collectCommandText(markupNode *sitter.Node, source []byte) (string, []uint32) {
	var b strings.Builder
	var consumed []uint32
	sibling := markupNode.NextNamedSibling()
	for sibling != nil {
		if sibling.Type() != "markup" {
			sibling = sibling.NextNamedSibling()
			continue
		}
		child := sibling.NamedChild(0)
		if child == nil {
			sibling = sibling.NextNamedSibling()
			continue
		}
		switch child.Type() {
		case "text":
			consumed = append(consumed, child.StartByte())
			b.WriteString(child.Content(source))
		case "inline_command":
			if t := extractInlineText(child, source); t != "" {
				consumed = append(consumed, child.StartByte())
				b.WriteString(t)
			}
		case "command", "block_command":
			return b.String(), consumed
		}
		sibling = sibling.NextNamedSibling()
	}
	return b.String(), consumed
}

// runCommandMatch finds all QDoc commands matching scope.CommandMatch and
// returns one Comment per match with the full text argument reconstructed by
// walking markup siblings — including text across inline-command boundaries.
//
// Stopping behaviour:
//   - UntilBlankLine (e.g. \brief, \note): collect until first \n\n.
//   - Default (e.g. \section*, \title): keep only the first non-empty line.
func (qe *QueryEngine) runCommandMatch(scope core.Scope, source []byte) ([]Comment, map[uint32]bool, error) {
	expr := fmt.Sprintf(
		`(block_comment (markup (command (command_name) @cmd (#match? @cmd "%s"))))`,
		scope.CommandMatch,
	)
	q, qErr := sitter.NewQuery([]byte(expr), qe.lang.Parser)
	if qErr != nil {
		return nil, nil, qErr
	}

	meta := scope.Name
	if meta != "" {
		meta = "." + meta
	}
	prefix := "text.comment"
	if qe.lang.ScopePrefix != "" {
		prefix = qe.lang.ScopePrefix
	}
	blkScope := prefix + meta + ".line"

	var comments []Comment
	consumed := make(map[uint32]bool)

	qc := sitter.NewQueryCursor()
	qc.Exec(q, qe.tree.RootNode())

	for {
		m, ok := qc.NextMatch()
		if !ok {
			break
		}
		m = qc.FilterPredicates(m, source)
		for _, c := range m.Captures {
			if q.CaptureNameForId(c.Index) != "cmd" {
				continue
			}

			// Navigate up: command_name -> command -> markup
			commandNode := c.Node.Parent()
			if commandNode == nil {
				continue
			}
			markupNode := commandNode.Parent()
			if markupNode == nil || markupNode.Type() != "markup" {
				continue
			}

			// Use the first text sibling's position for accurate line reporting.
			startRow := int(markupNode.StartPoint().Row)
			startCol := int(markupNode.StartPoint().Column)
			if first := markupNode.NextNamedSibling(); first != nil {
				startRow = int(first.StartPoint().Row)
				startCol = int(first.StartPoint().Column)
			}

			cText, nodeBytes := collectCommandText(markupNode, source)
			for _, b := range nodeBytes {
				consumed[b] = true
			}

			if scope.UntilBlankLine {
				if idx := strings.Index(cText, "\n\n"); idx >= 0 {
					cText = cText[:idx]
				}
			} else {
				// Single-line command: keep only the first non-empty line.
				cText = strings.TrimLeft(cText, " \t")
				if idx := strings.Index(cText, "\n"); idx >= 0 {
					cText = cText[:idx]
				}
			}
			cText = strings.TrimSpace(cText)

			if cText == "" {
				continue
			}

			comments = append(comments, Comment{
				Line:   startRow + 1,
				Offset: startCol,
				Scope:  blkScope,
				Text:   cText,
				Source: cText,
			})
		}
	}

	return comments, consumed, nil
}
