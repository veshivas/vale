package code

import (
	"strings"
	"testing"
)

// TestQDocProseLineNumbersSkippedArgs verifies that prose blocks preserve the
// correct line offsets when topic-command arguments (e.g. \class, \fn) are
// skipped during reconstruction. The skipped text nodes may contain newlines
// that must still be counted so that adjustAlerts maps prose lines back to
// the correct source lines.
func TestQDocProseLineNumbersSkippedArgs(t *testing.T) {
	// Source layout (1-indexed):
	//   1: /*!
	//   2:     \class QNetworkReply          <- skipped arg on line 2
	//   3:     \brief Provides a means...
	//   4:                                    <- blank
	//   5:     The request is sent...        <- target sentence
	//   6:     Headers are parsed...
	//   7: */
	src := []byte("/*!\n    \\class QNetworkReply\n    \\brief Provides a means of accessing network responses.\n\n    The request is sent and a reply is returned by the network manager.\n    Headers are parsed automatically.\n*/")

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}
	if len(blocks) == 0 {
		t.Fatal("expected prose blocks, got none")
	}

	text := blocks[0].Text

	// "The request is sent" must appear on prose line 5 (matching source line 5).
	// adjustAlerts computes: source_line = prose_line + comment.Line - 1
	//   = prose_line + 1 - 1 = prose_line.
	// So prose line number must equal source line number.
	lines := strings.Split(text, "\n")
	targetLine := -1
	for i, l := range lines {
		if strings.Contains(l, "The request is sent") {
			targetLine = i + 1 // 1-indexed
			break
		}
	}
	if targetLine == -1 {
		t.Fatalf("target sentence not found in prose text:\n%q", text)
	}
	const wantLine = 5
	if targetLine != wantLine {
		t.Errorf("prose line for 'The request is sent' = %d, want %d\n(prose text:\n%q)", targetLine, wantLine, text)
	}
}
