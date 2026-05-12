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

// TestGetQDocCommentsTableCellLineNumbers verifies that Pass 1 (GetComments)
// reports alerts for passive voice inside \table cells at the correct source
// line. BUG B: text nodes after \li include trailing \n + leading whitespace of
// the next line, causing coalesce() to merge adjacent \li text nodes and
// addSourceLine to insert a phantom blank line, shifting alerts by +1.
func TestGetQDocCommentsTableCellLineNumbers(t *testing.T) {
	src := []byte(`/*!
    \class QPluginLoader
    \brief Loads a plugin at run-time.

    \table
      \row
        \li fileName
        \li The plugin is loaded from this path on disk.
      \row
        \li isLoaded
        \li Returns true if the plugin was loaded successfully.
      \row
        \li loadHints
        \li Hints are used to control how the plugin is resolved.
    \endtable

    The loader is used to resolve symbols exported by the plugin.
*/`)
	// Source line numbers (1-indexed):
	//   8: \li The plugin is loaded from this path on disk.
	//  11: \li Returns true if the plugin was loaded successfully.
	//  14: \li Hints are used to control how the plugin is resolved.
	//  18: The loader is used to resolve symbols exported by the plugin.

	comments, err := GetComments(src, QDoc())
	if err != nil {
		t.Fatal(err)
	}

	want := map[string]int{
		"The plugin is loaded from this path on disk.": 8,
		"loaded successfully":                          11,
		"control how the plugin is resolved":           14,
	}

	for substr, wantLine := range want {
		var gotLine int
		for _, c := range comments {
			if strings.Contains(c.Text, substr) {
				gotLine = c.Line
				break
			}
		}
		if gotLine == 0 {
			t.Errorf("text containing %q not found in comments", substr)
		} else if gotLine != wantLine {
			t.Errorf("text %q: got line %d, want %d (BUG B off-by-one)", substr, gotLine, wantLine)
		}
	}
}

// TestGetQDocProseBlocksTableLineNumbers verifies that Pass 2 (GetQDocProseBlocks)
// preserves line offsets across a skipped \table block, so that prose after
// \endtable is reported at the correct source line.
//
// BUG A: qdocCollectProse skips table_block without emitting newlines, shifting
// all post-table alerts N lines too early (N = lines in table block).
//
// adjustAlerts computes source_line = prose_line + comment.Line - 1.
// For a block_comment starting at line 1, comment.Line = 1, so:
//   source_line = prose_line + 1 - 1 = prose_line.
// The prose line of each sentence must therefore equal its source line.
func TestGetQDocProseBlocksTableLineNumbers(t *testing.T) {
	src := []byte(`/*!
    \class QPluginLoader
    \brief Loads a plugin at run-time.

    \table
      \header
        \li Property \li Behavior
      \row
        \li fileName
        \li The plugin is loaded from this path on disk.
      \row
        \li isLoaded
        \li Returns true if the plugin was loaded successfully.
    \endtable

    The loader is used to resolve symbols exported by the plugin.
*/`)
	// Source line layout (1-indexed):
	//   1: /*!
	//   2:     \class QPluginLoader
	//   3:     \brief Loads a plugin at run-time.
	//   4:     (blank)
	//   5-14:  \table ... \endtable  (10 lines)
	//  15:     (blank)
	//  16:     The loader is used to resolve symbols exported by the plugin.
	//  17: */

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}

	const wantSubstr = "The loader is used"
	const wantLine = 16 // source line; equals prose line since comment.Line = 1

	for _, b := range blocks {
		if !strings.Contains(b.Text, wantSubstr) {
			continue
		}
		lines := strings.Split(b.Text, "\n")
		gotLine := -1
		for i, l := range lines {
			if strings.Contains(l, wantSubstr) {
				gotLine = i + 1 // 1-indexed
				break
			}
		}
		if gotLine != wantLine {
			t.Errorf("post-table prose %q: prose line %d, want %d (BUG A line shift)\nprose text:\n%q",
				wantSubstr, gotLine, wantLine, b.Text)
		}
		return
	}
	t.Errorf("post-table prose %q not found in prose blocks", wantSubstr)
}

// TestGetQDocProseBlocksSectionWithMacroLineNumbers verifies that Pass 2
// (GetQDocProseBlocks) preserves correct line offsets when \section1 headings
// end with a custom macro command. This tests for a regression where Fix A1
// (default case in block_command switch) incorrectly shifted prose lines -2
// per section heading.
//
// Source line layout (1-indexed, block_comment starts at line 1):
//   1: /*!
//   2:     \class QRuntimeLoader
//   3:     \brief Loads resources at run-time.
//   4:     (blank)
//   5:     \section1 Startup behavior on \MACRO1
//   6:     (blank)
//   7:     \l{QObject}{QObjects} are initialized when the application starts.
//   8:     All components are loaded from the resource bundle automatically.
//   9:     (blank)
//  10:     \section1 Shutdown with \BUILDVAR
//  11:     (blank)
//  12:     \l{QObject::deleteLater()}{deleteLater()} is called before the loop.
//  13:     All resources are released when the object is destroyed.
//  14: */
//
// comment.Line = 1 (block starts at row 0), so source_line = prose_line.
func TestGetQDocProseBlocksSectionWithMacroLineNumbers(t *testing.T) {
	src := []byte(`/*!
    \class QRuntimeLoader
    \brief Loads resources at run-time.

    \section1 Startup behavior on \MACRO1

    \l{QObject}{QObjects} are initialized when the application starts.
    All components are loaded from the resource bundle automatically.

    \section1 Shutdown with \BUILDVAR

    \l{QObject::deleteLater()}{deleteLater()} is called before the loop.
    All resources are released when the object is destroyed.
*/`)

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}

	want := map[string]int{
		"are initialized when the application starts": 7,
		"All components are loaded":                   8,
		"is called before the loop":                   12,
		"All resources are released":                  13,
	}

	for substr, wantLine := range want {
		found := false
		for _, b := range blocks {
			lines := strings.Split(b.Text, "\n")
			for i, l := range lines {
				if strings.Contains(l, substr) {
					gotLine := i + 1 // prose line (= source line since comment.Line=1)
					if gotLine != wantLine {
						t.Errorf("prose %q: line %d, want %d\nprose text:\n%q",
							substr, gotLine, wantLine, b.Text)
					}
					found = true
					break
				}
			}
			if found {
				break
			}
		}
		if !found {
			t.Errorf("prose %q not found in prose blocks", substr)
		}
	}
}

// TestGetQDocProseBlocksListLineNumbers verifies that list_block newline
// preservation keeps prose line numbers aligned with source lines after a
// \list...\endlist block. The \list and \endlist keyword lines each occupy one
// source line, so they must contribute \n chars to the prose string even though
// they contain no prose text.
//
// Source layout (block_comment starts at line 1, so source_line = prose_line):
//   1:  /*!
//   2:      \class Foo
//   3:      \brief A foo.
//   4:      (blank)
//   5:      Intro prose.
//   6:      \list
//   7:      \li First list item is set by default.
//   8:      \li Second list item is set to NEW.
//   9:      \endlist
//  10:      (blank)
//  11:      Post-list prose.
//  12:  */
func TestGetQDocProseBlocksListLineNumbers(t *testing.T) {
	src := []byte("/*!\n    \\class Foo\n    \\brief A foo.\n\n    Intro prose.\n    \\list\n    \\li First list item is set by default.\n    \\li Second list item is set to NEW.\n    \\endlist\n\n    Post-list prose.\n*/")

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}

	want := map[string]int{
		"Intro prose.":                       5,
		"First list item is set by default.": 7,
		"Second list item is set to NEW.":    8,
		"Post-list prose.":                   11,
	}

	for substr, wantLine := range want {
		found := false
		for _, b := range blocks {
			lines := strings.Split(b.Text, "\n")
			for i, l := range lines {
				if strings.Contains(l, substr) {
					gotLine := i + 1
					if gotLine != wantLine {
						t.Errorf("prose %q: line %d, want %d\nprose text:\n%q",
							substr, gotLine, wantLine, b.Text)
					}
					found = true
					break
				}
			}
			if found {
				break
			}
		}
		if !found {
			t.Errorf("prose %q not found in prose blocks", substr)
		}
	}
}
