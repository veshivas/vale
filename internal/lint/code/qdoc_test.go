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

// TestGetQDocProseBlocksImageAlt verifies that alt text from \image and
// \inlineimage is NOT included in prose blocks (it is linted separately via
// the image.alt Pass-1 query in GetComments, which uses lintLines to avoid
// false SentenceLength alerts from NLP joining short alt-text phrases with
// surrounding paragraphs).
func TestGetQDocProseBlocksImageAlt(t *testing.T) {
	src := []byte(`/*!
    \class QWidget
    \brief The base class of all UI objects.

    \image widget.png The widget is shown by the framework.

    Use \inlineimage logo.png {It is displayed by the system} here.
*/`)

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}

	combined := ""
	for _, b := range blocks {
		combined += b.Text
	}

	// Alt text must NOT appear in the reconstructed prose (handled via lintLines).
	if strings.Contains(combined, "widget is shown by the framework") {
		t.Errorf(`prose block should not contain \image alt text; got:\n%s`, combined)
	}
	if strings.Contains(combined, "It is displayed by the system") {
		t.Errorf(`prose block should not contain \inlineimage alt text; got:\n%s`, combined)
	}
	// Filenames must not appear either.
	if strings.Contains(combined, "widget.png") {
		t.Errorf(`prose should not contain image filename; got:\n%s`, combined)
	}
	if strings.Contains(combined, "logo.png") {
		t.Errorf(`prose should not contain inlineimage filename; got:\n%s`, combined)
	}
}

// TestQDocScopesImageAlt verifies that the image.alt Pass-1 query produces
// text.comment.image.alt.line scope comments for alt text content.
func TestQDocScopesImageAlt(t *testing.T) {
	src := []byte(`/*!
    \class QWidget
    \brief The base class of all UI objects.

    \image widget.png The widget overview.

    Use \inlineimage logo.png {Inline alt text} here.
*/`)

	comments, err := GetComments(src, QDoc())
	if err != nil {
		t.Fatal(err)
	}

	foundImage := false
	foundInline := false
	for _, c := range comments {
		if c.Scope == "text.comment.image.alt.line" {
			if strings.Contains(c.Text, "widget overview") {
				foundImage = true
			}
			if strings.Contains(c.Text, "Inline alt text") {
				foundInline = true
			}
		}
	}
	if !foundImage {
		t.Errorf(`expected text.comment.image.alt.line for \image alt text; got: %v`, comments)
	}
	if !foundInline {
		t.Errorf(`expected text.comment.image.alt.line for \inlineimage alt text; got: %v`, comments)
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
// into prose-bearing block commands (\list, \table, \legalese, \quotation) and
// skips non-prose block commands (\raw).
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
		"Table cell data.",
		"Final prose after blocks.",
	} {
		if !strings.Contains(combined, want) {
			t.Errorf("expected prose %q not found in:\n%s", want, combined)
		}
	}

	// \raw block: content must NOT appear (raw passthrough, not prose).
	if strings.Contains(combined, "Raw passthrough content") {
		t.Errorf("raw block content should not appear in prose:\n%s", combined)
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

// TestGetQDocProseBlocksSkipUntilNewline verifies that \title and section
// headings (linted separately in Pass 1) are excluded from prose
// reconstruction. Prose immediately following a heading (no blank line) must
// be collected normally. This tests the regression where \title text leaked
// into Pass 2 prose and merged with the following paragraph, producing
// spurious SentenceLength alerts when the combined sentence exceeded the limit.
func TestGetQDocProseBlocksSkipUntilNewline(t *testing.T) {
	src := []byte(`/*!
    \page automotive-demo
    \title \QUL Automotive Cluster Demo
    \brief Demonstrates integrating QML and C++.

    \section1 Overview
    Body prose after section heading.
    Another sentence here.
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

	// Title and section heading text must NOT appear (handled by Pass 1).
	for _, reject := range []string{
		"Automotive Cluster Demo",
		"Overview",
	} {
		if strings.Contains(combined, reject) {
			t.Errorf("skipUntilNewline content %q should not appear in prose:\n%s", reject, combined)
		}
	}

	// Prose after heading/title must be present.
	for _, want := range []string{
		"Body prose after section heading.",
		"Another sentence here.",
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
// TestGetQDocProseBlocksLinkCommand verifies link_command handling in
// qdocCollectProse:
//
//  1. \l{target}{alias} — alias text appears in prose; target does not.
//  2. \l{target}        — no alias; target does not appear (bare reference).
//  3. Column accuracy   — text following either form aligns with source columns.
//
// Source layout (block_comment starts at source line 1):
//
//	1:  /*!
//	2:  \class Foo
//	3:  \brief A class.
//	4:  (blank)
//	5:  The \l{Qt Resource System}{Qt resource system} allows files to be stored.
//	6:  (blank)
//	7:  See \l{Qt::QObject} for details.
//	8:  */
func TestGetQDocProseBlocksLinkCommand(t *testing.T) {
	src := []byte("/*!\n\\class Foo\n\\brief A class.\n\n" +
		"The \\l{Qt Resource System}{Qt resource system} allows files to be stored.\n\n" +
		"See \\l{Qt::QObject} for details.\n*/")

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}

	var allText string
	for _, b := range blocks {
		allText += b.Text
	}

	// --- Content checks ---

	// Alias text must appear; target text must not.
	if !strings.Contains(allText, "Qt resource system") {
		t.Errorf("alias 'Qt resource system' not found in prose:\n%q", allText)
	}
	if strings.Contains(allText, "Qt Resource System") {
		t.Errorf("target 'Qt Resource System' must not appear in prose:\n%q", allText)
	}

	// No-alias target must not appear.
	if strings.Contains(allText, "Qt::QObject") {
		t.Errorf("no-alias target 'Qt::QObject' must not appear in prose:\n%q", allText)
	}

	// --- Column accuracy checks ---
	//
	// \l{Qt Resource System}{Qt resource system} = 42 bytes
	//   aliasOffset (len of \l{Qt Resource System}) = 22
	//   emitted: 22 spaces + 1({) + "Qt resource system"(18) + 1(}) = 42
	//   "allows" col (0-indexed): len("The ") + 42 + len(" ") = 47
	//
	// \l{Qt::QObject} = 15 bytes, no alias → blanked entirely
	//   "for" col (0-indexed): len("See ") + 15 + len(" ") = 20
	type colCheck struct {
		lineSubstr string // unique substring to find the source line
		word       string // word whose column to check
		wantCol    int    // expected 0-indexed column
	}
	checks := []colCheck{
		{"allows files", "allows", 47},
		{"for details", "for", 20},
	}
	for _, c := range checks {
		found := false
		for _, b := range blocks {
			for _, line := range strings.Split(b.Text, "\n") {
				if strings.Contains(line, c.lineSubstr) {
					col := strings.Index(line, c.word)
					if col != c.wantCol {
						t.Errorf("word %q: col %d, want %d\nline: %q", c.word, col, c.wantCol, line)
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
			t.Errorf("line containing %q not found in prose:\n%q", c.lineSubstr, allText)
		}
	}
}

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

// TestGetQDocProseBlocksTwoSections reproduces a line-shift bug seen in
// profiling.qdoc where prose after the second \section1 lands one line early.
//
// Source layout (block_comment starts at line 1):
//
//	 1: /*!
//	 2: \page test.html
//	 3: \ingroup testgroup
//	 4: \title Test Title
//	 5: \brief Short brief for this page.
//	 6: (blank)
//	 7: \section1 First Section
//	 8: (blank)
//	 9: First section prose line one here.
//	10: First section prose line two here.
//	11: (blank)
//	12: \section1 Second Section
//	13: (blank)
//	14: Second section prose starts here.
//	15: Content can later be loaded here.
//	16: */
func TestGetQDocProseBlocksTwoSections(t *testing.T) {
	// Reproduces the structure of profiling.qdoc: two \section1 headings,
	// \l{target:colon}{alias} link commands, and \{macro}'s brace syntax.
	src := []byte("/*!\n" +
		"\\page test.html\n" +
		"\\ingroup testgroup\n" +
		"\\title Test Title\n" +
		"\\brief Short brief for this page.\n" +
		"\n" +
		"\\section1 First Section\n" +
		"\n" +
		"With the \\l{QC: Some Page}{QML Profiler} you can analyze\n" +
		"your code for issues. The tool is part of\n" +
		"both \\QC and \\QDS. Use \\{QC}'s or \\{QDS}'s defaults.\n" +
		"\n" +
		"If building manually, enable the \\l{QML debugging infrastructure}.\n" +
		"\n" +
		"\\section1 Second Section\n" +
		"\n" +
		"Second section prose starts here.\n" +
		"Content can later be loaded here.\n" +
		"*/")

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}

	want := map[string]int{
		"Second section prose starts here.": 17,
		"Content can later be loaded here.": 18,
	}

	for substr, wantLine := range want {
		found := false
		for _, b := range blocks {
			lines := strings.Split(b.Text, "\n")
			for i, l := range lines {
				if strings.Contains(l, substr) {
					gotLine := i + 1
					if gotLine != wantLine {
						t.Errorf("prose %q: prose line %d, want %d\nprose text:\n%q",
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

// TestGetQDocProseBlocksSectionArgLineNumbers reproduces the qt-edu-for-designers.qdoc
// structure: two \section1 headings with a numeric argument (e.g. "9." / "10."),
// an \image command between sections, and prose after the second section heading.
//
// Source layout (comment.Line = 1):
//
//	 1: /*!
//	 2:     \section1 9. Finish the installation
//	 3:
//	 4:     Select something here.
//	 5:
//	 6:     \image some-image.png
//	 7:
//	 8:     Select another thing.
//	 9:
//	10:     \section1 10. Open Qt Design Studio
//	11:
//	12:     Go to the folder to see the tools that were installed.
//	13:     Qt Design Studio is located under its own folder.
//	14: */
func TestGetQDocProseBlocksSectionArgLineNumbers(t *testing.T) {
	src := []byte("/*!\n" +
		"    \\section1 9. Finish the installation\n" +
		"\n" +
		"    Select something here.\n" +
		"\n" +
		"    \\image some-image.png\n" +
		"\n" +
		"    Select another thing.\n" +
		"\n" +
		"    \\section1 10. Open Qt Design Studio\n" +
		"\n" +
		"    Go to the folder to see the tools that were installed.\n" +
		"    Qt Design Studio is located under its own folder.\n" +
		"*/")

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}

	want := map[string]int{
		"Go to the folder to see the tools that were installed.": 12,
		"Qt Design Studio is located under its own folder.":      13,
	}

	for substr, wantLine := range want {
		found := false
		for _, blk := range blocks {
			lines := strings.Split(blk.Text, "\n")
			for i, l := range lines {
				if strings.Contains(l, substr) {
					gotLine := i + 1
					if gotLine != wantLine {
						t.Errorf("prose %q: prose line %d, want %d\nprose text:\n%q",
							substr, gotLine, wantLine, blk.Text)
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


func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

// TestGetQDocProseBlocksIncludeNewlines checks that \include commands
// do not drop newlines from the reconstructed prose buffer.
func TestGetQDocProseBlocksIncludeNewlines(t *testing.T) {
	// Reproduces qt-edu-for-designers.qdoc: \include with brace args on a line,
	// followed by a blank line, then prose.
	//
	//  1: /*!
	//  2:     \include foo.qdocinc {arg1} {arg2}
	//  3:
	//  4:     Prose here on line four.
	//  5: */
	src := []byte("/*!\n" +
		"    \\include foo.qdocinc {arg1} {arg2}\n" +
		"\n" +
		"    Prose here on line four.\n" +
		"*/")

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}

	want := map[string]int{
		"Prose here on line four.": 4,
	}
	for substr, wantLine := range want {
		found := false
		for _, blk := range blocks {
			lines := strings.Split(blk.Text, "\n")
			for i, l := range lines {
				if strings.Contains(l, substr) {
					gotLine := i + 1
					if gotLine != wantLine {
						t.Errorf("prose %q: prose line %d, want %d\nprose:\n%q", substr, gotLine, wantLine, blk.Text)
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
			t.Errorf("prose %q not found", substr)
		}
	}
}

// TestGetQDocProseBlocksQDocMarkers checks that //! [snippet] markers inside
// block comments do not drop newlines.
func TestGetQDocProseBlocksQDocMarkers(t *testing.T) {
	// Structure matches qt-edu-for-designers.qdoc lines 8-17:
	//
	//  1: /*!
	//  2: //! [intro]
	//  3:     Prose line three.
	//  4: //! [intro]
	//  5:
	//  6:     Prose line six.
	//  7: */
	src := []byte("/*!\n" +
		"//! [intro]\n" +
		"    Prose line three.\n" +
		"//! [intro]\n" +
		"\n" +
		"    Prose line six.\n" +
		"*/")

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}

	want := map[string]int{
		"Prose line three.": 3,
		"Prose line six.":   6,
	}
	for substr, wantLine := range want {
		found := false
		for _, blk := range blocks {
			lines := strings.Split(blk.Text, "\n")
			for i, l := range lines {
				if strings.Contains(l, substr) {
					gotLine := i + 1
					if gotLine != wantLine {
						t.Errorf("prose %q: prose line %d, want %d\nprose:\n%q", substr, gotLine, wantLine, blk.Text)
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
			t.Errorf("prose %q not found", substr)
		}
	}
}

// TestGetQDocProseBlocksFullDesignersStructure builds a close approximation of
// qt-edu-for-designers.qdoc to find which construct drops 3 newlines before
// the prose after the second \section1.
func TestGetQDocProseBlocksCrossLineLink(t *testing.T) {
	// Mirrors qt-edu-for-designers.qdoc lines 4-43 (comment.Line=4 in source,
	// but here comment.Line=1 since block starts at row 0).
	src := []byte("/*!\n" +
		"    \\page qt-edu-for-designers.html\n" +
		"    \\title Qt Edu for Designers\n" +
		"\n" +
		"//! [intro]\n" +
		"    \\e {Qt Edu for Designers} package contains \\l {Qt Design Studio Manual}\n" +
		"    {Qt Design Studio Enterprise}, allowing you to import.\n" +
		"//! [intro]\n" +
		"\n" +
		"    These instructions walk you through the installation.\n" +
		"\n" +
		"    \\include qt-edu-steps.qdocinc {qt-edu-common-steps} {Qt Design Studio}\n" +
		"\n" +
		"    \\image qt-edu-install-design-studio.png\n" +
		"\n" +
		"    With \\e {Qt Edu for Designers} license, you get access to Qt Design\n" +
		"    Studio. Select the \\uicontrol {Design Tools} shortcut to install.\n" +
		"\n" +
		"    Select \\uicontrol {Next}.\n" +
		"\n" +
		"    \\include qt-edu-steps.qdocinc qt-edu-license-agreement\n" +
		"\n" +
		"    \\section1 9. Finish the installation\n" +
		"\n" +
		"    Select \\uicontrol {Install} to start the installation process.\n" +
		"\n" +
		"    Once installation is complete, you'll see the screen.\n" +
		"\n" +
		"    \\image qt-edu-install-finish-design-studio.png\n" +
		"\n" +
		"    Select \\uicontrol {Finish} to exit the installer.\n" +
		"\n" +
		"    \\section1 10. Open Qt Design Studio\n" +
		"\n" +
		"    Go to the folder to see the tools that were installed.\n" +
		"    Qt Design Studio is located under its own folder.\n" +
		"*/")

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}

	// With comment.Line=1, prose line == source line within this block.
	// "\section1 10..." is on line 33, blank on 34, prose on 35-36.
	want := map[string]int{
		"Go to the folder to see the tools that were installed.": 35,
		"Qt Design Studio is located under its own folder.":      36,
	}
	for substr, wantLine := range want {
		found := false
		for _, blk := range blocks {
			lines := strings.Split(blk.Text, "\n")
			for i, l := range lines {
				if strings.Contains(l, substr) {
					gotLine := i + 1
					if gotLine != wantLine {
						t.Errorf("prose %q: prose line %d, want %d\nprose (lines 34-42):\n%s",
							substr, gotLine, wantLine,
							strings.Join(lines[max(0, 33):min(42, len(lines))], "\n"))
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
			t.Errorf("prose %q not found", substr)
		}
	}
}

// TestGetQDocProseBlocksSectionNewlineBisect bisects the full-designers-structure
// test to find which construct drops the remaining newline after the link fix.
func TestGetQDocProseBlocksSectionNewlineBisect(t *testing.T) {
	cases := []struct {
		name     string
		src      string
		substr   string
		wantLine int
	}{
		{
			name: "link_only",
			src: "/*!\n" +
				"    \\l {Qt Design Studio Manual}\n" +
				"    {Qt Design Studio Enterprise}, rest.\n" +
				"\n" +
				"    Prose on line five.\n" +
				"*/",
			substr: "Prose on line five.", wantLine: 5,
		},
		{
			name: "include_then_section",
			src: "/*!\n" +
				"    \\include foo.qdocinc {arg1} {arg2}\n" +
				"\n" +
				"    \\section1 9. Finish\n" +
				"\n" +
				"    Select something.\n" +
				"\n" +
				"    \\section1 10. Open\n" +
				"\n" +
				"    Prose on line ten.\n" +
				"*/",
			substr: "Prose on line ten.", wantLine: 10,
		},
		{
			name: "link_then_section",
			src: "/*!\n" +
				"    \\l {Manual}\n" +
				"    {Enterprise}, rest.\n" +
				"\n" +
				"    \\section1 9. Finish\n" +
				"\n" +
				"    Select something.\n" +
				"\n" +
				"    \\section1 10. Open\n" +
				"\n" +
				"    Prose on line eleven.\n" +
				"*/",
			substr: "Prose on line eleven.", wantLine: 11,
		},
	}

	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			blocks, err := GetQDocProseBlocks([]byte(tc.src))
			if err != nil {
				t.Fatal(err)
			}
			for _, blk := range blocks {
				lines := strings.Split(blk.Text, "\n")
				for i, l := range lines {
					if strings.Contains(l, tc.substr) {
						gotLine := i + 1
						if gotLine != tc.wantLine {
							t.Errorf("prose %q: prose line %d, want %d\nfull prose:\n%q",
								tc.substr, gotLine, tc.wantLine, blk.Text)
						}
						return
					}
				}
			}
			t.Errorf("prose %q not found", tc.substr)
		})
	}
}

// TestGetQDocProseBlocksLinkDebug dumps the raw prose buffer for a cross-line link.
func TestGetQDocProseBlocksLinkDebug(t *testing.T) {
	src := []byte("/*!\n" +
		"    \\l {Qt Design Studio Manual}\n" +
		"    {Qt Design Studio Enterprise}, rest.\n" +
		"\n" +
		"    Prose on line five.\n" +
		"*/")

	blocks, err := GetQDocProseBlocks(src)
	if err != nil {
		t.Fatal(err)
	}
	for i, b := range blocks {
		t.Logf("block[%d] raw prose (lines annotated):", i)
		for j, l := range strings.Split(b.Text, "\n") {
			t.Logf("  L%02d: %q", j+1, l)
		}
	}
}

// TestGetQDocProseBlocksLinkRawLines calls GetQDocProseBlocks on a simple
// cross-line \l command and prints the clean prose lines for manual inspection.
func TestGetQDocProseBlocksLinkRawLines(t *testing.T) {
	cases := []struct {
		name string
		src  string
	}{
		{
			name: "same_line_link",
			src:  "/*!\n    \\l {Manual} {Alias}, rest.\n\n    Prose line three.\n*/",
		},
		{
			name: "cross_line_link",
			src:  "/*!\n    \\l {Manual}\n    {Alias}, rest.\n\n    Prose line four.\n*/",
		},
	}
	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			blocks, err := GetQDocProseBlocks([]byte(tc.src))
			if err != nil {
				t.Fatal(err)
			}
			for _, blk := range blocks {
				for j, l := range strings.Split(blk.Text, "\n") {
					t.Logf("L%02d: %q", j+1, l)
				}
			}
		})
	}
}

