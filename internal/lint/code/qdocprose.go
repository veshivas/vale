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
// Text nodes after these commands (until the matching \end* command) contain
// source code, not prose, and must be excluded from reconstruction.
//
// Note: \snippet is NOT included — it is a single-line command that includes
// code from an external file and has no \endsnippet counterpart.
var codeBlockEnterCommands = map[string]bool{
	"code": true, "qml": true, "badcode": true,
}

// codeBlockExitCommands lists the command names (via macro_name) that end a
// code block. The grammar parses \endcode as command → macro_name "endcode"
// (not as a block_command pair), so qdocCollectProse must detect these in the
// "command" case to clear the inCodeBlock flag.
//
// Per QDoc docs: \badcode is terminated by \endcode (not \endbadcode).
var codeBlockExitCommands = map[string]bool{
	"endcode": true, "endqml": true,
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
//   - Code blocks (\code...\endcode, \badcode...\endcode, \qml...\endqml)
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
// It handles the markup child types:
//   - block_command: recurses into prose-bearing blocks (list, table, legalese, quotation);
//     skips raw_block and others without prose content.
//   - section_command, title_command: heading text captured elsewhere (Pass 1 Expr
//     query); the entire node is blanked with length-preserving spaces.
//   - brief_command, note_command, warning_command: admonition text captured
//     elsewhere; the entire node is blanked with length-preserving spaces.
//   - command: manages code-block state. When TokenIgnore replaces \l{target}
//     with length-preserving spaces, emitting the command node's trailing bytes
//     preserves line-number alignment and column accuracy.
//   - text: appended normally when not inside a code block.
//   - inline_command: inline_text content appended with braces stripped.
//   - link_command: emits the alias text (or blanks the node if no alias).
//
// After each markup node, newlines from the extras gap to the next markup node
// are emitted. Dedicated terminal nodes (heading_text, brief_text, admonition_text)
// stop before \n or \n\n, leaving those bytes in the extras gap; emitting them
// here keeps prose line numbers aligned with source line numbers.
func qdocCollectProse(node *sitter.Node, source []byte, b *strings.Builder) {
	inCodeBlock := false

	for i := 0; i < int(node.NamedChildCount()); i++ {
		markup := node.NamedChild(i)
		if markup.Type() != "markup" {
			continue
		}

		for j := 0; j < int(markup.NamedChildCount()); j++ {
			child := markup.NamedChild(j)

			switch child.Type() {
			case "section_command", "title_command":
				// Heading text is captured by a Pass 1 Expr query; blank the
				// entire node here so the heading does not flow into prose and
				// cause spurious SentenceLength alerts on the title text.
				// The trailing \n lives in the extras gap and is emitted below.
				for _, r := range child.Content(source) {
					if r == '\n' {
						b.WriteRune('\n')
					} else {
						b.WriteByte(' ')
					}
				}

			case "brief_command", "note_command", "warning_command":
				// Admonition text (brief_text / admonition_text) is captured by
				// a Pass 1 Expr query. Blank the node content so it is excluded
				// from prose reconstruction; preserve embedded newlines (from
				// continuation lines) so subsequent line numbers stay aligned.
				// The trailing \n\n (blank-line separator) lives in the extras
				// gap between this markup and the next, and is emitted below.
				for _, r := range child.Content(source) {
					if r == '\n' {
						b.WriteRune('\n')
					} else {
						b.WriteByte(' ')
					}
				}

			case "block_command":
				// block_command has one named child: the specific block type.
				// Recurse into prose-bearing blocks; skip raw and table.
				if child.NamedChildCount() > 0 {
					inner := child.NamedChild(0)
					switch inner.Type() {
					case "list_block", "table_block", "legalese_block", "quotation_block":
						// Emit \n for source lines occupied by the opening keyword
						// (\list, \table, \legalese, \quotation) before recursing,
						// and by the closing keyword after recursing. Without this,
						// prose line numbers inside the block are shifted N lines too
						// early (N = number of keyword lines skipped), causing alerts
						// to land on the wrong source line.
						nc := int(inner.NamedChildCount())
						if nc > 0 {
							// Rows between block start and first markup child.
							gapRows := int(inner.NamedChild(0).StartPoint().Row) - int(inner.StartPoint().Row)
							for r := 0; r < gapRows; r++ {
								b.WriteByte('\n')
							}
						}
						qdocCollectProse(inner, source, b)
						if nc > 0 {
							// Rows between last markup child end and block end.
							lastChild := inner.NamedChild(nc - 1)
							gapRows := int(inner.EndPoint().Row) - int(lastChild.EndPoint().Row)
							for r := 0; r < gapRows; r++ {
								b.WriteByte('\n')
							}
						}
					default:
						// raw_block, table_block: no prose, but preserve newlines
						// so that post-block prose alerts land on the correct source
						// line. Without this, all subsequent alerts are shifted N
						// lines too early (N = number of lines in the skipped block).
						for _, r := range inner.Content(source) {
							if r == '\n' {
								b.WriteRune('\n')
							}
						}
					}
				}

			case "command":
				// Extract the command name from either command_name (known QDoc
				// commands) or macro_name (custom macros and \end* commands).
				// The grammar parses \endcode as command → macro_name "endcode",
				// not command_name, so both must be checked.
				cmdName := ""
				for k := 0; k < int(child.NamedChildCount()); k++ {
					cn := child.NamedChild(k)
					if cn.Type() == "command_name" || cn.Type() == "macro_name" {
						cmdName = cn.Content(source)
					}
				}
				if codeBlockExitCommands[cmdName] {
					inCodeBlock = false
				} else if codeBlockEnterCommands[cmdName] {
					inCodeBlock = true
				}
				// Emit the command node with length-preserving blanks for
				// the keyword prefix (\keyword) and any trailing content after
				// the keyword (rest). Without blanking the keyword prefix, commands
				// like \li (3 bytes) and \section2 (9 bytes) are silently dropped,
				// shifting column positions of subsequent text and — for commands
				// that occupy their own line — shifting line numbers as well.
				//
				// When TokenIgnore replaces \l{target} with length-preserving
				// spaces, the grammar absorbs the replacement whitespace plus any
				// leftover {alias} into the preceding command node's byte range
				// as anonymous content. Emitting that content preserves:
				//   - line-number alignment: \n\n after a macro heading
				//   - column accuracy: {alias} text at the right source offset
				// In suppressed regions (code block, skip-until-blank) only
				// newlines are emitted so line numbers stay aligned.
				keywordEnd := child.EndByte() // default: no trailing content
				for k := 0; k < int(child.NamedChildCount()); k++ {
					cn := child.NamedChild(k)
					if cn.Type() == "command_name" || cn.Type() == "macro_name" {
						keywordEnd = cn.EndByte()
						break
					}
				}
				// Blank \keyword prefix bytes for length preservation,
				// preserving any embedded newlines so that line numbers of
				// subsequent prose remain correct. Normal command keywords
				// (\li, \section2, etc.) contain no newlines, so this is a
				// no-op for them. For unrecognised commands — e.g. \{QC}'s
				// where no command_name child is found and keywordEnd ==
				// child.EndByte() — the "keyword" may span multiple lines;
				// preserving those newlines prevents the blank line between
				// paragraphs from being silently dropped.
				for i := child.StartByte(); i < keywordEnd; i++ {
					if source[i] == '\n' {
						b.WriteRune('\n')
					} else {
						b.WriteByte(' ')
					}
				}
				if keywordEnd < child.EndByte() {
					rest := source[keywordEnd:child.EndByte()]
					if inCodeBlock {
						for _, r := range string(rest) {
							if r == '\n' {
								b.WriteRune('\n')
							}
						}
					} else {
						b.Write(rest) //nolint:errcheck
					}
				}

			case "text":
				content := child.Content(source)
				if inCodeBlock {
					// Preserve newlines from skipped text so that prose line
					// offsets stay in sync with source line numbers.
					for _, r := range content {
						if r == '\n' {
							b.WriteRune('\n')
						}
					}
				} else {
					b.WriteString(content)
				}

			case "inline_command":
				if inCodeBlock {
					break
				}
				// Emit inline_command content with the command wrapper blanked so
				// that byte positions in the reconstructed prose match the source.
				// Without this, \e{not} (7 bytes) would emit only "not" (3 bytes),
				// shifting every subsequent column by −4 and causing Pass 1 and
				// Pass 2 to report the same alert at different columns, defeating
				// the f.history deduplication that suppresses duplicate alerts.
				//
				// e.g. \e{not}      → "   not " (3 leading spaces + content + 1)
				//      \b{bold text} → "   bold text " (same length as source)
				//
				// Note: \c{...} never reaches this case because \c is in
				// TokenIgnores and is blanked before tree-sitter parsing.
				raw := child.Content(source)
				open := strings.Index(raw, "{")
				close := strings.LastIndex(raw, "}")
				if open >= 0 && close > open {
					for i := 0; i <= open; i++ {
						b.WriteByte(' ') // blank \cmd{ prefix
					}
					b.WriteString(raw[open+1 : close]) // emit inner text
					b.WriteByte(' ')                   // blank } suffix
				} else {
					b.WriteString(raw) // fallback: no braces found
				}

			case "link_command":
				if inCodeBlock {
					// Preserve newlines from skipped link content.
					for _, r := range child.Content(source) {
						if r == '\n' {
							b.WriteRune('\n')
						}
					}
					break
				}
				// \l{target} or \l{target}{alias}:
				//   - Alias present (link_alias child): blank \l{target}{ bytes,
				//     emit alias inner text, blank closing }. The alias IS display
				//     prose and should be linted.
				//   - No alias: \l{target} is a bare reference/identifier (e.g.
				//     \l{qt_add_qml_module}, \l{QTP0001}). Blank the entire node
				//     with length-preserving spaces so column positions of
				//     subsequent text are not shifted.
				//
				// Note: \l is NOT in TokenIgnores. Pre-blanking \l before
				// tree-sitter breaks link_command parsing (the grammar can no
				// longer see the \l keyword), leaving an orphan {alias} brace_group
				// that shifts all following column positions. Suppressing the target
				// at the AST level is the correct approach — equivalent to how
				// HTML-pipeline formats strip href values during format conversion.
				var aliasNode *sitter.Node
				for k := 0; k < int(child.NamedChildCount()); k++ {
					if cn := child.NamedChild(k); cn.Type() == "link_alias" {
						aliasNode = cn
					}
				}
				if aliasNode == nil {
					// No alias: blank entire node, preserving newlines.
					for _, r := range child.Content(source) {
						if r == '\n' {
							b.WriteRune('\n')
						} else {
							b.WriteByte(' ')
						}
					}
				} else {
					// Alias present: blank \l{target}[ ]{alias} with column and line
					// accuracy. The link_alias token includes any whitespace between
					// target and '{', so aliasNode.Content may be " {Alias}" (same
					// line) or "\n    {Alias}" (next line). Find the '{' within the
					// alias content so we blank the right bytes and preserve '\n'.
					aliasRaw := aliasNode.Content(source)
					braceOffset := strings.IndexByte(aliasRaw, '{')
					if braceOffset < 0 || len(aliasRaw)-braceOffset < 2 {
						// Degenerate: no '{' found — blank the whole node.
						for i := child.StartByte(); i < child.EndByte(); i++ {
							if source[i] == '\n' {
								b.WriteRune('\n')
							} else {
								b.WriteByte(' ')
							}
						}
					} else {
						// Blank from child start through (and including) the '{'.
						// This covers: \l, target brace-group, any inter-token
						// whitespace, and the alias opening brace.
						aliasBrace := aliasNode.StartByte() + uint32(braceOffset)
						for i := child.StartByte(); i <= aliasBrace; i++ {
							if source[i] == '\n' {
								b.WriteRune('\n')
							} else {
								b.WriteByte(' ')
							}
						}
						// Emit alias inner text.
						b.WriteString(aliasRaw[braceOffset+1 : len(aliasRaw)-1])
						// Blank closing '}'.
						b.WriteByte(' ')
					}
				}

			default:
				// Unknown or future node types (e.g. brace_group from a
				// partially-blanked \l{target}{alias} where TokenIgnore erased
				// \l{target} but left {alias} as an orphan). Emit
				// length-preserving spaces so subsequent column positions in the
				// reconstructed prose match the source. Newlines are preserved so
				// line numbers stay aligned.
				for _, r := range child.Content(source) {
					if r == '\n' {
						b.WriteRune('\n')
					} else {
						b.WriteByte(' ')
					}
				}
			}
		}

		// Emit newlines from the extras gap between this markup node and the
		// next. Dedicated terminal nodes (heading_text, brief_text,
		// admonition_text) stop before \n or \n\n, leaving those bytes as
		// extras between markup nodes. Without emitting them, prose line numbers
		// after the gap drift away from the source line numbers.
		if i+1 < int(node.NamedChildCount()) {
			next := node.NamedChild(i + 1)
			for _, ch := range source[markup.EndByte():next.StartByte()] {
				if ch == '\n' {
					b.WriteByte('\n')
				}
			}
		}
	}
}
