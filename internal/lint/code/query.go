package code

import (
	"bytes"
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

func (qe *QueryEngine) run(scope core.Scope, q *sitter.Query, source []byte) []Comment {
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
