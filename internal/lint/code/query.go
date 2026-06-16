// query.go contains the tree-sitter query execution engine used by GetComments
// to extract scoped comment fragments from parsed source code.
//
// The engine supports two query modes:
//   - run(): executes plain Expr queries (e.g. "(text) @comment"). Used by all
//     languages for general comment extraction.
//   - runCommandMatch(): finds commands matching a CommandMatch regex pattern
//     and reconstructs their full text argument by walking markup siblings
//     across inline-command boundaries. Currently used by QDoc for scoped
//     extraction of \brief, \section, \note, \warning, and \title text.
//
// When both modes are active, run() accepts a skip set of consumed node start
// bytes from runCommandMatch to avoid re-capturing the same text.
package code

import (
	"bytes"
	"fmt"
	"strings"

	sitter "github.com/smacker/go-tree-sitter"

	"github.com/errata-ai/vale/v3/internal/core"
)

// QueryEngine executes tree-sitter queries against a parsed syntax tree and
// returns Comment slices with scoped text suitable for Vale's lint pipeline.
type QueryEngine struct {
	tree   *sitter.Tree
	lang   *Language
	cutset string // characters stripped from the left of each comment line
}

// NewQueryEngine creates a QueryEngine for the given parse tree and language.
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

// run executes a plain Expr query (e.g. "(text) @comment") and returns one
// Comment per @comment capture. Nodes whose StartByte is in skip are excluded
// — this is how CommandMatch results from Pass 1 prevent the catch-all query
// in Pass 2 from re-capturing the same text and producing duplicate alerts.
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
			// Only process @comment captures; skip helper captures like @_cmd.
			if q.CaptureNameForId(c.Index) != "comment" {
				continue
			}
			// Skip nodes already consumed by a CommandMatch query (Pass 1).
			if skip[c.Node.StartByte()] {
				continue
			}
			rText := c.Node.Content(source)
			cText := qe.lang.Delims.ReplaceAllString(rText, "")

			// Some in-grammar tokens (notably image_alt for \inlineimage)
			// include the inter-token horizontal whitespace that the parser
			// would otherwise consume as `extras`. The grammar regex matches
			// only `{...}` but tree-sitter reports the node's start position
			// at the preceding space when the token follows a field at the
			// same nesting level. The leading whitespace ends up in the
			// captured Source/Text and the node's StartPoint, which makes
			// adjustAlerts compute a negative `padding` via leadingSpaces()
			// (leading_space_count - comment.Offset) and zeroes out the
			// offset addition, reporting alerts at the wrong column.
			//
			// External-scanner tokens (image_alt_text, image_filename) skip
			// this whitespace themselves via lexer->advance(skip=true), so
			// only in-grammar tokens are affected.
			//
			// The fix: for non-catch-all single-line captures, strip leading
			// horizontal whitespace from both rText and cText and advance
			// startCol by the same amount.
			startCol := int(c.Node.StartPoint().Column)
			if scope.Name != "" && !strings.ContainsRune(rText, '\n') {
				trim := 0
				for trim < len(rText) && (rText[trim] == ' ' || rText[trim] == '\t') {
					trim++
				}
				if trim > 0 {
					rText = rText[trim:]
					cText = strings.TrimLeft(cText, " \t")
					startCol += trim
				}
			}

			if scope.FirstLine {
				// Extract only the first non-empty line (heading text).
				cText = strings.TrimLeft(cText, " \t")
				if idx := strings.Index(cText, "\n"); idx >= 0 {
					cText = cText[:idx]
				}
				cText = strings.TrimSpace(cText)
			}

			prefix := "text.comment"
			if scope.ScopePrefix != "" {
				prefix = scope.ScopePrefix
			} else if qe.lang.ScopePrefix != "" {
				prefix = qe.lang.ScopePrefix
			}
			blkScope := prefix + meta + ".line"
			if !scope.FirstLine && strings.Count(cText, "\n") > 1 {
				blkScope = prefix + meta + ".block"

				// Dedent like Python's inspect.cleandoc: the first line sits on
				// (or just after) the opening delimiter, so its leading
				// whitespace is incidental and is trimmed fully; the remaining
				// lines are dedented only by the indentation common to them.
				// This removes a comment's base indentation while preserving
				// relative indentation, which is significant for markup such as
				// RST literal blocks and Markdown indented code. See #1028.
				lines := strings.Split(cText, "\n")
				common := commonIndent(lines[1:], qe.cutset)

				buf := bytes.Buffer{}
				for i, line := range lines {
					if i == 0 {
						buf.WriteString(strings.TrimLeft(line, qe.cutset))
					} else {
						buf.WriteString(stripIndent(line, common, qe.cutset))
					}
					buf.WriteString("\n")
				}

				cText = buf.String()
			}

			comments = append(comments, Comment{
				Line:   int(c.Node.StartPoint().Row) + 1,
				Offset: startCol,
				Scope:  blkScope,
				Text:   cText,
				Source: rText,
			})
		}
	}

	return comments
}

// commonIndent returns the length, in bytes, of the longest run of leading
// `cutset` characters shared by every non-blank line. Blank lines (those that
// are empty after trimming) are ignored so they don't force the indent to zero.
func commonIndent(lines []string, cutset string) int {
	common := -1
	for _, line := range lines {
		if strings.TrimLeft(line, cutset) == "" {
			continue
		}
		n := len(line) - len(strings.TrimLeft(line, cutset))
		if common == -1 || n < common {
			common = n
		}
	}
	if common < 0 {
		return 0
	}
	return common
}

// stripIndent removes up to `n` leading `cutset` characters from `line` (a line
// with fewer than `n` leading cutset characters -- e.g. a blank line -- loses
// only what it has).
func stripIndent(line string, n int, cutset string) string {
	if n <= 0 {
		return line
	}
	cut := len(line) - len(strings.TrimLeft(line, cutset))
	if cut > n {
		cut = n
	}
	return line[cut:]
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
// inline_command nodes visited. This spans inline-command boundaries so that
// "\brief Use \c{write()} to send data" produces "Use write() to send data"
// rather than just "Use".
//
// Collection stops when a block_command or another top-level command is
// reached, which marks the boundary of the current command's text argument.
//
// The returned start bytes are used by GetComments to mark these nodes as
// consumed, preventing the catch-all "(text) @comment" query from
// re-capturing the same text.
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
// Returns:
//   - comments: one Comment per matched command with reconstructed text.
//   - consumed: start bytes of all text/inline_command nodes visited during
//     reconstruction. GetComments passes this to run() so the catch-all
//     "(text) @comment" query skips these nodes.
//
// Text truncation:
//   - UntilBlankLine (e.g. \brief, \note): collect until first \n\n.
//   - Default (e.g. \section*, \title): keep only the first non-empty line.
func (qe *QueryEngine) runCommandMatch(scope core.Scope, source []byte) ([]Comment, map[uint32]bool, error) {
	// Build a query that matches the command_name inside a block_comment.
	// The tree-sitter #match? predicate filters by the CommandMatch regex.
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
	if scope.ScopePrefix != "" {
		prefix = scope.ScopePrefix
	} else if qe.lang.ScopePrefix != "" {
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

			// Navigate up the AST: command_name → command → markup.
			// We need the markup node to walk its siblings for text content.
			commandNode := c.Node.Parent()
			if commandNode == nil {
				continue
			}
			markupNode := commandNode.Parent()
			if markupNode == nil || markupNode.Type() != "markup" {
				continue
			}

			// Report the alert at the text position, not the command position.
			// Fall back to the command's markup node if no text sibling exists.
			startRow := int(markupNode.StartPoint().Row)
			startCol := int(markupNode.StartPoint().Column)
			if first := markupNode.NextNamedSibling(); first != nil {
				startRow = int(first.StartPoint().Row)
				startCol = int(first.StartPoint().Column)
			}

			// Walk all markup siblings after the command, collecting text and
			// inline_command content. Mark visited nodes as consumed so the
			// catch-all pass in GetComments skips them.
			cText, nodeBytes := collectCommandText(markupNode, source)
			for _, b := range nodeBytes {
				consumed[b] = true
			}

			// rawCText is used below to measure leading whitespace that is
			// trimmed from cText, so we can advance startCol past the space(s)
			// between the command name and the first content character.
			rawCText := cText

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

			// Advance startCol past any leading whitespace that was trimmed
			// from the raw text so the alert column points at the first
			// content character, not the space after the command name.
			startCol += len(rawCText) - len(strings.TrimLeft(rawCText, " \t"))

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
