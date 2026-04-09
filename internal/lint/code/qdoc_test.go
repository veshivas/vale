package code

import (
	"os"
	"path/filepath"
	"strings"
	"testing"
)

// TestQDocComments verifies that the QDoc language extracts prose text,
// \brief descriptions, and \section headings into the correct scopes.
func TestQDocComments(t *testing.T) {
	const fixture = "../../../testdata/comments/in/9.qdoc"
	const expected = "../../../testdata/comments/out/9.json"

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
		_ = os.WriteFile(filepath.Join(binDir, "9.json"), []byte(got), 0600)
		t.Fatalf("missing expected fixture %s (actual output written to bin/9.json): %v", expected, err)
	}

	if got != string(want) {
		_ = os.WriteFile(filepath.Join(binDir, "9.json"), []byte(got), 0600)
		t.Errorf("output mismatch for %s (actual written to bin/9.json):\n%s", fixture, got)
	}
}

// TestQDocScopes checks scopes not covered by TestQDocComments fixture tests:
// \title scope, and \image/\inlineimage alt-text suppression.
//
// Brief, heading, note, warning, and image-without-alt scopes are already
// validated by TestQDocComments via fixtures 6.qdoc and 8.qdoc.
func TestQDocScopes(t *testing.T) {
	src := []byte(`/*!
    \page example.html
    \title The Page Title

    \image has-alt.png This image has alt text.

    \inlineimage has-alt-inline.png {Inline alt text}
*/`)

	comments, err := GetComments(src, QDoc())
	if err != nil {
		t.Fatal(err)
	}

	// \title must produce title scope.
	found := false
	for _, c := range comments {
		if c.Scope == "text.comment.title.line" && c.Text == "The Page Title" {
			found = true
		}
	}
	if !found {
		t.Errorf("expected text.comment.title.line with text %q; got: %v", "The Page Title", comments)
	}

	// \image and \inlineimage WITH alt text must NOT produce image scope.
	for _, c := range comments {
		if c.Scope == "text.comment.image.line" {
			t.Errorf("image with alt text should not fire image scope; got %q", c.Text)
		}
	}
}

// TestGetQDocProseBlocks verifies that GetQDocProseBlocks reconstructs prose
// across inline-command boundaries and skips topic-command arguments.
func TestGetQDocProseBlocks(t *testing.T) {
	src := []byte(`/*!
    \class QProcess
    \brief Used to start external programs.

    Set the program name; then call start() to launch the process.
    Use \c{write()} to send data; use \c{read()} to receive output.
*/`)

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}
	if len(blocks) == 0 {
		t.Fatal("expected at least one prose block, got none")
	}

	// All returned blocks must have the correct scope.
	for _, b := range blocks {
		if b.Scope != "text.comment.block" {
			t.Errorf("unexpected scope %q", b.Scope)
		}
	}

	// The prose must contain the semicolons from the body text.
	combined := ""
	for _, b := range blocks {
		combined += b.Text
	}
	if !strings.Contains(combined, ";") {
		t.Errorf("prose blocks do not contain expected semicolon; got:\n%s", combined)
	}
	// Topic-command argument ("QProcess") must not appear.
	if strings.Contains(combined, "QProcess") {
		t.Errorf("prose block should not contain topic-command argument 'QProcess'; got:\n%s", combined)
	}
}

// TestGetQDocProseBlocksCodeBlocks verifies that prose reconstruction correctly
// excludes content inside \code...\endcode, \badcode...\endcode, and
// \qml...\endqml blocks, and includes prose that follows them.
func TestGetQDocProseBlocksCodeBlocks(t *testing.T) {
	src := []byte(`/*!
    \class Widget
    \brief A test widget.

    Prose before code block.

    \code
    int x = 1;
    QString s = "hello";
    \endcode

    Prose after code block.

    \badcode
    $ make install
    \endcode

    Prose after badcode block.

    \qml
    import QtQuick 2.0
    Item { width: 100 }
    \endqml

    Prose after qml block.
*/`)

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}
	if len(blocks) == 0 {
		t.Fatal("expected at least one prose block, got none")
	}

	combined := ""
	for _, b := range blocks {
		combined += b.Text
	}

	// Prose around code blocks must be present.
	for _, want := range []string{
		"Prose before code block.",
		"Prose after code block.",
		"Prose after badcode block.",
		"Prose after qml block.",
	} {
		if !strings.Contains(combined, want) {
			t.Errorf("expected prose %q not found in:\n%s", want, combined)
		}
	}

	// Code block content must NOT be present.
	for _, reject := range []string{
		"int x = 1",
		"make install",
		"import QtQuick",
	} {
		if strings.Contains(combined, reject) {
			t.Errorf("code block content %q should not appear in prose:\n%s", reject, combined)
		}
	}
}

// TestGetQDocProseBlocksBlockCommands verifies that qdocCollectProse recurses
// into prose-bearing block commands (\list, \legalese, \quotation) and skips
// non-prose block commands (\raw, \table).
func TestGetQDocProseBlocksBlockCommands(t *testing.T) {
	src := []byte(`/*!
    \class Container
    \brief A container widget.

    Intro prose.

    \list
    \li First item with prose.
    \li Second item with prose.
    \endlist

    \legalese
    Copyright notice text.
    \endlegalese

    \quotation
    A famous quotation here.
    \endquotation

    \table
    \header \li Column
    \row \li Table cell data.
    \endtable

    \raw HTML
    <p>Raw passthrough content.</p>
    \endraw

    Final prose after blocks.
*/`)

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}
	if len(blocks) == 0 {
		t.Fatal("expected at least one prose block, got none")
	}

	combined := ""
	for _, b := range blocks {
		combined += b.Text
	}

	// Prose-bearing blocks: content must appear in reconstructed prose.
	for _, want := range []string{
		"First item with prose.",
		"Second item with prose.",
		"Copyright notice text.",
		"A famous quotation here.",
		"Final prose after blocks.",
	} {
		if !strings.Contains(combined, want) {
			t.Errorf("expected prose %q not found in:\n%s", want, combined)
		}
	}

	// Non-prose blocks: content must NOT appear.
	for _, reject := range []string{
		"Table cell data",
		"Raw passthrough content",
	} {
		if strings.Contains(combined, reject) {
			t.Errorf("non-prose block content %q should not appear in prose:\n%s", reject, combined)
		}
	}
}

// TestGetQDocProseBlocksSkipUntilBlank verifies that brief/note/warning text
// (up to the first blank line) is excluded from prose reconstruction, since
// it is linted separately via CommandMatch scopes in Pass 1. Prose after the
// blank line must still be included.
func TestGetQDocProseBlocksSkipUntilBlank(t *testing.T) {
	src := []byte(`/*!
    \class Receiver
    \brief Handles incoming data packets.

    Body prose after brief.

    \note Always validate input before processing.

    Prose after note.

    \warning Do not call this from the main thread.

    Prose after warning.
*/`)

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}
	if len(blocks) == 0 {
		t.Fatal("expected at least one prose block, got none")
	}

	combined := ""
	for _, b := range blocks {
		combined += b.Text
	}

	// Brief/note/warning text must NOT appear (handled by Pass 1).
	for _, reject := range []string{
		"Handles incoming data packets",
		"Always validate input",
		"Do not call this from the main thread",
	} {
		if strings.Contains(combined, reject) {
			t.Errorf("skipUntilBlank content %q should not appear in prose:\n%s", reject, combined)
		}
	}

	// Prose after blank lines must be present.
	for _, want := range []string{
		"Body prose after brief.",
		"Prose after note.",
		"Prose after warning.",
	} {
		if !strings.Contains(combined, want) {
			t.Errorf("expected prose %q not found in:\n%s", want, combined)
		}
	}
}

// TestGetQDocProseBlocksMacroNames verifies that commands parsed as macro_name
// (custom macros like \macos, \QUL) do not suppress following prose text.
// The grammar parses unknown commands as command → macro_name; these should
// be treated as inert by qdocCollectProse (no skip flags set).
func TestGetQDocProseBlocksMacroNames(t *testing.T) {
	src := []byte(`/*!
    \class Example
    \brief A brief description.

    This works on \macos and \linux platforms.
    The \QUL framework handles rendering accordingly.
    Final sentence after macros.
*/`)

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}
	if len(blocks) == 0 {
		t.Fatal("expected at least one prose block, got none")
	}

	combined := ""
	for _, b := range blocks {
		combined += b.Text
	}

	// Prose around macros must be preserved.
	if !strings.Contains(combined, "platforms") {
		t.Errorf("expected 'platforms' in prose; got:\n%s", combined)
	}
	if !strings.Contains(combined, "rendering accordingly") {
		t.Errorf("expected 'rendering accordingly' in prose; got:\n%s", combined)
	}
	if !strings.Contains(combined, "Final sentence after macros") {
		t.Errorf("expected 'Final sentence after macros' in prose; got:\n%s", combined)
	}
}

// TestGetQDocProseBlocksSnippet verifies that \snippet is treated as a
// single-line command (not a code block). It should skip only its immediate
// text argument, not suppress all following prose.
func TestGetQDocProseBlocksSnippet(t *testing.T) {
	src := []byte(`/*!
    \class Loader
    \brief Loads resources.

    Use the loader as follows:
    \snippet examples/loader.cpp setup
    Prose after snippet should be included.
*/`)

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}
	if len(blocks) == 0 {
		t.Fatal("expected at least one prose block, got none")
	}

	combined := ""
	for _, b := range blocks {
		combined += b.Text
	}

	if !strings.Contains(combined, "Prose after snippet should be included") {
		t.Errorf("prose after \\snippet not found; got:\n%s", combined)
	}
}
