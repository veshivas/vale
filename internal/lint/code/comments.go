package code

import (
	"bytes"
	"context"
	"fmt"
	"sort"
	"strings"

	sitter "github.com/smacker/go-tree-sitter"
)

// Comment represents an in-code comment (line or block).
type Comment struct {
	Text   string
	Source string
	Line   int
	Offset int
	Scope  string
}

// doneMerging reports whether curr should NOT be merged with prev in coalesce.
// Line-scoped comments are merged only when they are on consecutive lines at
// the same column offset and share the same scope. The scope check prevents
// comments with different scopes (e.g. a brief.line after a text.comment.line)
// from being merged, which would lose their distinct scope identity.
func doneMerging(curr, prev Comment) bool {
	switch {
	case prev.Scope != curr.Scope:
		return true
	case prev.Line != curr.Line-1:
		return true
	case prev.Offset != curr.Offset:
		return true
	}
	// A text node whose raw Source spans a line boundary with trailing content
	// after the newline was produced by a greedy grammar rule that consumed
	// leading whitespace from the next source line. Merging it with the following
	// node inserts a phantom blank line in addSourceLine, shifting alert lines.
	// This arises in QDoc table and list cells whose text nodes include trailing
	// indentation. Single-line code comments (// ...\n) end with just \n and are
	// not affected: for them idx == len(Source)-1, so the condition is false.
	if idx := strings.Index(prev.Source, "\n"); idx >= 0 && idx < len(prev.Source)-1 {
		return true
	}
	return false
}

func addSourceLine(line string, atEnd bool) string {
	if line == "" {
		return "\n\n"
	}

	if !strings.HasPrefix(line, "\n") && !atEnd {
		line = strings.TrimLeft(line, " ")
		line = fmt.Sprintf("\n%s", line)
	} else if !strings.HasSuffix(line, "\n") && atEnd {
		line = strings.TrimLeft(line, " ")
		line = fmt.Sprintf("%s\n", line)
	}

	return line
}

// coalesce merges consecutive line-scoped comments into single Comments.
// Block-scoped comments (.block suffix) are never merged — they are added
// as independent entries. This merging is important for languages like C++
// where consecutive // comments form a logical paragraph.
func coalesce(comments []Comment) []Comment {
	var joined []Comment

	tBuf := bytes.Buffer{}
	sBuf := bytes.Buffer{}

	// flush merges any pending line-comment text into the most recently
	// appended comment, which is always the one this run of lines belongs to.
	flush := func() {
		if tBuf.Len() > 0 {
			last := joined[len(joined)-1]

			last.Text += addSourceLine(tBuf.String(), false)
			last.Source += addSourceLine(sBuf.String(), false)

			joined[len(joined)-1] = last

			tBuf.Reset()
			sBuf.Reset()
		}
	}

	for i, comment := range comments {
		// Block comments and anchor commands should not be merged with adjacent
		// comments. Block comments are inherently multi-line; anchor commands
		// (like \target, \keyword) should each maintain their individual source
		// position for correct column reporting, even when consecutive.
		// Flush first: a pending run of line comments belongs to the preceding
		// line comment, not this block -- see #1020.
		if comment.Scope == "text.comment.block" || strings.Contains(comment.Scope, "meta.anchor") { //nolint:gocritic
			flush()
			joined = append(joined, comment)
		} else if i == 0 || doneMerging(comment, comments[i-1]) {
			flush()
			joined = append(joined, comment)
		} else {
			tBuf.WriteString(addSourceLine(comment.Text, true))
			sBuf.WriteString(addSourceLine(comment.Source, true))
		}
	}

	flush()

	for i, comment := range joined {
		joined[i].Text = strings.TrimLeft(comment.Text, " ")
	}

	return joined
}

// GetComments returns all comments in the given source code, extracted via
// tree-sitter queries defined in the Language.
//
// When the Language defines CommandMatch queries, extraction uses two passes:
//
//	Pass 1 — CommandMatch queries: reconstructs full text arguments via
//	         runCommandMatch. Records start bytes of consumed nodes.
//	Pass 2 — Plain Expr queries: captures remaining text nodes, skipping
//	         any already consumed by Pass 1 to prevent duplicates.
//
// For languages without CommandMatch queries, only Pass 2 runs.
//
// Results are sorted by line number and coalesced (consecutive line-scoped
// comments at the same offset are merged into a single Comment).
func GetComments(source []byte, lang *Language) ([]Comment, error) {
	var comments []Comment

	parser := sitter.NewParser()
	parser.SetLanguage(lang.Parser)

	tree, err := parser.ParseCtx(context.Background(), nil, source)
	if err != nil {
		return comments, err
	}
	engine := NewQueryEngine(tree, lang)

	// --- Pass 1: CommandMatch queries ---
	// Collect consumed text-node start bytes so Pass 2 can skip them.
	consumed := make(map[uint32]bool)
	for _, query := range lang.Queries {
		if query.CommandMatch == "" {
			continue
		}
		results, nodeBytes, matchErr := engine.runCommandMatch(query, source)
		if matchErr != nil {
			return comments, matchErr
		}
		comments = append(comments, results...)
		for k := range nodeBytes {
			consumed[k] = true
		}
	}

	// --- Pass 2: plain Expr queries ---
	for _, query := range lang.Queries {
		if query.CommandMatch != "" {
			continue
		}
		q, qErr := sitter.NewQuery([]byte(query.Expr), lang.Parser)
		if qErr != nil {
			return comments, qErr
		}
		comments = append(comments, engine.run(query, q, source, consumed)...)
	}

	if len(lang.Queries) > 1 {
		// Interleave Pass 1 and Pass 2 results by source order so coalesce
		// can correctly merge consecutive line-scoped comments.
		sort.SliceStable(comments, func(p, q int) bool {
			return comments[p].Line < comments[q].Line
		})
	}

	return coalesce(comments), nil
}
