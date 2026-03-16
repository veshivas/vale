package core

import (
	"regexp"
	"strings"

	"github.com/errata-ai/vale/v3/internal/nlp"
)

// initialPosition calculates the position of a match (given by the location in
// the reference document, `loc`) in the source document (`ctx`).
func initialPosition(ctx, txt string, a Alert) (int, string) {
	var idx int
	var pat *regexp.Regexp

	if a.Match == "" {
		// We have nothing to look for -- assume the rule applies to the entire
		// document (e.g., readability).
		return 1, ""
	}

	offset := strings.Index(ctx, txt)
	if offset >= 0 {
		ctx, _ = Substitute(ctx, ctx[:offset], '@')
	}

	sub := strings.ToValidUTF8(a.Match, "")
	pat = regexp.MustCompile(`(?:^|\b|_)` + regexp.QuoteMeta(sub) + `(?:_|\b|$)`)

	fsi := pat.FindAllStringIndex(ctx, -1)
	if len(fsi) == 0 {
		idx = strings.Index(ctx, sub)
		if idx < 0 {
			// This should only happen if we're in a scope that contains inline
			// markup (e.g., a sentence with code spans).
			return guessLocation(ctx, txt, sub)
		}
		// Ensure the fallback position is not a partial-word match (e.g.,
		// "us" found inside "status" in an HTML attribute value). When the
		// surrounding characters are word characters the match is embedded in
		// a longer token and the position is unreliable.
		before := idx > 0 && isWordChar(ctx[idx-1])
		after := idx+len(sub) < len(ctx) && isWordChar(ctx[idx+len(sub)])
		if before || after {
			return guessLocation(ctx, txt, sub)
		}
	} else {
		// NOTE: This is a workaround for #673.
		//
		// In cases where we have more than one match, we skip any that look
		// like they're inside inline code (e.g., `code`).
		//
		// This is a bit of a hack: ideally, we'd handle this at the AST level
		// by ignoring these inline code spans.
		//
		// We also skip matches where the apparent word boundary is formed by
		// an '@' character. The walker substitutes processed text-node content
		// with '@', which can create artificial word boundaries inside HTML
		// attribute values (e.g. "status" partly @-substituted to "st@@us").
		// Matching against such a position is a false positive from position
		// mapping, not a real match in prose.
		//
		// TODO: What about `scope: raw`?
		idx = -1
		size := nlp.StrLen(ctx)
		for _, fs := range fsi {
			start := fs[0] - 1
			end := fs[1] + 1
			if start > 0 && (ctx[start] == '`' || ctx[start] == '-' || ctx[start] == '@') {
				continue
			} else if end < size && (ctx[end] == '`' || ctx[end] == '-' || ctx[end] == '@') {
				continue
			}
			idx = fs[0]
			break
		}
		if idx < 0 {
			return guessLocation(ctx, txt, sub)
		}
	}

	if strings.HasPrefix(ctx[idx:], "_") {
		idx++ // We don't want to include the underscore boundary.
	}

	return nlp.StrLen(ctx[:idx]) + 1, sub
}

func guessLocation(ctx, sub, match string) (int, string) {
	target := ""
	for _, s := range nlp.SentenceTokenizer.Segment(sub) {
		if s == match || strings.Index(s, match) > 0 {
			target = s
		}
	}

	if target == "" {
		return -1, sub
	}

	tokens := nlp.WordTokenizer.Tokenize(target)
	for _, text := range strings.Split(ctx, "\n") {
		if allStringsInString(tokens, text) {
			return strings.Index(ctx, text) + 1, text
		}
	}

	return -1, sub
}

func allStringsInString(subs []string, s string) bool {
	for _, sub := range subs {
		if !strings.Contains(s, sub) {
			return false
		}
	}
	return true
}

// isWordChar reports whether b is a word character (ASCII letter, digit, or
// underscore) — matching the \w character class used in word-boundary checks.
func isWordChar(b byte) bool {
	return b == '_' ||
		(b >= 'a' && b <= 'z') ||
		(b >= 'A' && b <= 'Z') ||
		(b >= '0' && b <= '9')
}
