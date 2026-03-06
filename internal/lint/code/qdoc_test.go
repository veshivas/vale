package code

import (
	"os"
	"path/filepath"
	"testing"
)

// TestQDocComments verifies that the QDoc language extracts prose text,
// \brief descriptions, and \section headings into the correct scopes.
func TestQDocComments(t *testing.T) {
	const fixture = "../../../testdata/comments/in/6.qdoc"
	const expected = "../../../testdata/comments/out/6.json"

	src, err := os.ReadFile(fixture)
	if err != nil {
		t.Fatal(err)
	}

	comments, err := GetComments(src, QDoc())
	if err != nil {
		t.Fatal(err)
	}

	got := toJSON(comments)

	want, err := os.ReadFile(expected)
	if err != nil {
		// First run: write actual output so the developer can inspect it.
		_ = os.MkdirAll(filepath.Join(binDir), 0755)
		_ = os.WriteFile(filepath.Join(binDir, "6.json"), []byte(got), 0600)
		t.Fatalf("missing expected fixture %s (actual output written to bin/6.json): %v", expected, err)
	}

	if got != string(want) {
		_ = os.WriteFile(filepath.Join(binDir, "6.json"), []byte(got), 0600)
		t.Errorf("output mismatch for %s (actual written to bin/6.json):\n%s", fixture, got)
	}
}

// TestQDocScopes checks that each capture kind produces the correct scope.
func TestQDocScopes(t *testing.T) {
	src := []byte(`/*!
    \class Foo
    \brief A brief without a period

    Some body text here.

    \section1 A title-case Section Heading

    More body text.
*/`)

	comments, err := GetComments(src, QDoc())
	if err != nil {
		t.Fatal(err)
	}

	// Build a map of scope → texts for easy assertion.
	byScope := map[string][]string{}
	for _, c := range comments {
		byScope[c.Scope] = append(byScope[c.Scope], c.Text)
	}

	cases := []struct {
		scope string
		want  string
	}{
		// \brief text captured in the brief scope, first line only.
		{"text.qdoc.brief.line", "A brief without a period"},
		// \section1 text captured in the heading scope, first line only.
		{"text.qdoc.heading.line", "A title-case Section Heading"},
	}

	for _, tc := range cases {
		t.Run(tc.scope, func(t *testing.T) {
			texts, ok := byScope[tc.scope]
			if !ok {
				t.Fatalf("no comment with scope %q; got scopes: %v", tc.scope, keys(byScope))
			}
			found := false
			for _, text := range texts {
				if text == tc.want {
					found = true
					break
				}
			}
			if !found {
				t.Errorf("scope %q: want %q; got %v", tc.scope, tc.want, texts)
			}
		})
	}
}

func keys(m map[string][]string) []string {
	out := make([]string, 0, len(m))
	for k := range m {
		out = append(out, k)
	}
	return out
}
