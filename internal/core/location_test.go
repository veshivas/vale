package core

import (
	"testing"
)

// TestInitialPosition_AtSubstitutedAttributeValue is a regression test for
// https://github.com/errata-ai/vale/issues/1086.
//
// The HTML walker progressively @-substitutes processed text-node content in
// its context (subInplace). When a text node's content is a substring of an
// adjacent HTML attribute value, the substitution corrupts that value. For
// example, a text node "at" substituted into "status" produces "st@@us". The
// word-boundary regex then matches "us" in "st@@us" because '@' is not a \w
// character, producing a false-positive alert at the attribute's column.
//
// An empty element has no text content (txt = ""), so strings.Index(ctx, "")
// returns 0 and nothing is blanked before the search — the full @-corrupted
// context is exposed to the regex.
func TestInitialPosition_AtSubstitutedAttributeValue(t *testing.T) {
	cases := []struct {
		name    string
		ctx     string
		txt     string
		match   string
		wantCol bool // true = expect a valid column (col > 0)
	}{
		{
			// The walker has @-substituted "at" from a text node into "status",
			// leaving "st@@us". The empty <span> has no text content, so txt=""
			// and the full corrupted context is searched. The regex matches "us"
			// in "st@@us" because '@' creates an artificial word boundary.
			// The fix: skip fsi matches where the adjacent char is '@'.
			name:    "us in @-corrupted attribute value (fsi path)",
			ctx:     `<td class="st@@us technology-preview"></td>`,
			txt:     "",
			match:   "us",
			wantCol: false,
		},
		{
			// No @ corruption, but "us" is a substring of "status". The regex
			// finds no word-boundary match (s and s are \w), so it falls back to
			// strings.Index which finds "us" inside "status".
			// The fix: check that the char before/after the Index match is a \w
			// character and fall back to guessLocation if so.
			name:    "us as substring of attribute value, no @ corruption (fallback path)",
			ctx:     `<td class="status technology-preview"></td>`,
			txt:     "",
			match:   "us",
			wantCol: false,
		},
		{
			// Positive case: "us" appears as a real standalone word in prose.
			// The fix must not suppress this legitimate match.
			name:    "us as standalone word in prose",
			ctx:     `@@@@@@@@@@@@@@@@@@@@call us to start.</td>`,
			txt:     "call us to start.",
			match:   "us",
			wantCol: true,
		},
	}

	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			a := Alert{Match: tc.match}
			col, _ := initialPosition(tc.ctx, tc.txt, a)
			if tc.wantCol && col <= 0 {
				t.Errorf("initialPosition() = %d; want > 0 (real prose match suppressed)", col)
			} else if !tc.wantCol && col > 0 {
				t.Errorf("initialPosition() = %d; want ≤ 0 (false positive not suppressed)", col)
			}
		})
	}
}
