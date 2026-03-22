package lint

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
	"regexp"
	"testing"

	"github.com/errata-ai/vale/v3/internal/core"
	"github.com/errata-ai/vale/v3/internal/system"
)

func TestSymlinkFixture(t *testing.T) {
	// This is an integration test: it shells out to an installed `vale`
	// binary. Skip when one isn't on PATH (e.g., local `go test ./...` or a
	// CI job that builds the binary without installing it) rather than failing.
	if _, err := exec.LookPath("vale"); err != nil {
		t.Skip("vale binary not found on PATH")
	}

	fixture := "../../testdata/fixtures/misc/symlinks"

	targetSrc := system.AbsPath(filepath.Join(fixture, "Symlinked"))
	targetDst := system.AbsPath(filepath.Join(fixture, "styles", "Symlinked"))

	if _, err := os.Stat(targetSrc); os.IsNotExist(err) {
		t.Fatalf("Target source does not exist: %v", targetSrc)
	}

	if err := os.Symlink(targetSrc, targetDst); err != nil {
		t.Fatalf("Failed to create symlink: %v", err)
	}

	t.Cleanup(func() {
		err := os.Remove(targetDst)
		if err != nil {
			t.Fatalf("Failed to remove symlink: %v", err)
		}
	})

	info, err := os.Lstat(targetDst)
	if err != nil {
		t.Fatalf("Failed to stat symlink: %v", err)
	}

	if info.Mode()&os.ModeSymlink == 0 {
		t.Fatalf("Expected %v to be a symlink", targetDst)
	}

	resolvedPath, err := os.Readlink(targetDst)
	if err != nil {
		t.Fatalf("Failed to read symlink: %v", err)
	}

	if resolvedPath != targetSrc {
		t.Fatalf("Symlink points to %v, expected %v", resolvedPath, targetSrc)
	}

	// Call Vale on the symlinked file.
	cmd := exec.Command("vale", "--output=JSON", "--no-global", "test.md")
	cmd.Dir = fixture

	out, err := cmd.CombinedOutput()
	if err != nil {
		t.Fatalf("Failed to run Vale: %s", string(out))
	}

	if !bytes.Contains(out, []byte("Symlinked")) {
		t.Fatalf("Expected output from Vale, got %s", string(out))
	}
}

func TestGenderBias(t *testing.T) {
	reToMatches := map[string][]string{
		"(?:alumna|alumnus)":          {"alumna", "alumnus"},
		"(?:alumnae|alumni)":          {"alumnae", "alumni"},
		"(?:mother|father)land":       {"motherland", "fatherland"},
		"air(?:m[ae]n|wom[ae]n)":      {"airman", "airwoman", "airmen", "airwomen"},
		"anchor(?:m[ae]n|wom[ae]n)":   {"anchorman", "anchorwoman", "anchormen", "anchorwomen"},
		"camera(?:m[ae]n|wom[ae]n)":   {"cameraman", "camerawoman", "cameramen", "camerawomen"},
		"chair(?:m[ae]n|wom[ae]n)":    {"chairman", "chairwoman", "chairmen", "chairwomen"},
		"congress(?:m[ae]n|wom[ae]n)": {"congressman", "congresswoman", "congressmen", "congresswomen"},
		"door(?:m[ae]n|wom[ae]n)":     {"doorman", "doorwoman", "doormen", "doorwomen"},
		"drafts(?:m[ae]n|wom[ae]n)":   {"draftsman", "draftswoman", "draftsmen", "draftswomen"},
		"fire(?:m[ae]n|wom[ae]n)":     {"fireman", "firewoman", "firemen", "firewomen"},
		"fisher(?:m[ae]n|wom[ae]n)":   {"fisherman", "fisherwoman", "fishermen", "fisherwomen"},
		"fresh(?:m[ae]n|wom[ae]n)":    {"freshman", "freshwoman", "freshmen", "freshwomen"},
		"garbage(?:m[ae]n|wom[ae]n)":  {"garbageman", "garbagewoman", "garbagemen", "garbagewomen"},
		"mail(?:m[ae]n|wom[ae]n)":     {"mailman", "mailwoman", "mailmen", "mailwomen"},
		"middle(?:m[ae]n|wom[ae]n)":   {"middleman", "middlewoman", "middlemen", "middlewomen"},
		"news(?:m[ae]n|wom[ae]n)":     {"newsman", "newswoman", "newsmen", "newswomen"},
		"ombuds(?:man|woman)":         {"ombudsman", "ombudswoman"},
		"work(?:m[ae]n|wom[ae]n)":     {"workman", "workwoman", "workmen", "workwomen"},
		"police(?:m[ae]n|wom[ae]n)":   {"policeman", "policewoman", "policemen", "policewomen"},
		"repair(?:m[ae]n|wom[ae]n)":   {"repairman", "repairwoman", "repairmen", "repairwomen"},
		"sales(?:m[ae]n|wom[ae]n)":    {"salesman", "saleswoman", "salesmen", "saleswomen"},
		"service(?:m[ae]n|wom[ae]n)":  {"serviceman", "servicewoman", "servicemen", "servicewomen"},
		"steward(?:ess)?":             {"steward", "stewardess"},
		"tribes(?:m[ae]n|wom[ae]n)":   {"tribesman", "tribeswoman", "tribesmen", "tribeswomen"},
	}
	for re, matches := range reToMatches {
		regex := regexp.MustCompile(re)
		for _, match := range matches {
			if !regex.MatchString(match) {
				t.Errorf("expected = %v, got = %v", true, false)
			}
		}
	}
}

func initLinter() (*Linter, error) {
	cfg, err := core.NewConfig(&core.CLIFlags{})
	if err != nil {
		return nil, err
	}

	cfg.MinAlertLevel = 0
	cfg.GBaseStyles = []string{"Vale"}
	cfg.Flags.InExt = ".txt" // default value

	return NewLinter(cfg)
}

func benchmarkLint(b *testing.B, path string) {
	b.Helper()

	linter, err := initLinter()
	if err != nil {
		b.Fatal(err)
	}

	path, err = filepath.Abs(path)
	if err != nil {
		b.Fatal(err)
	}

	for n := 0; n < b.N; n++ {
		_, err = linter.Lint([]string{path}, "*")
		if err != nil {
			b.Fatal(err)
		}
	}
}

func BenchmarkLintRST(b *testing.B) {
	benchmarkLint(b, "../../testdata/fixtures/benchmarks/bench.rst")
}

func BenchmarkLintMD(b *testing.B) {
	benchmarkLint(b, "../../testdata/fixtures/benchmarks/bench.md")
}

// lintWithConfig loads the given .vale.ini and lints the file at path,
// returning all alerts. IgnoreGlobal is set so that the user's own Vale
// config does not interfere with the fixture config.
func lintWithConfig(t *testing.T, iniPath, filePath string) []core.Alert {
	t.Helper()

	absIni, err := filepath.Abs(iniPath)
	if err != nil {
		t.Fatal(err)
	}
	absFile, err := filepath.Abs(filePath)
	if err != nil {
		t.Fatal(err)
	}

	cfg, err := core.ReadPipeline(&core.CLIFlags{
		Path:         absIni,
		IgnoreGlobal: true,
		InExt:        ".txt", // default; tells NewFile to infer format from the src path
	}, false)
	if err != nil {
		t.Fatal(err)
	}

	linter, err := NewLinter(cfg)
	if err != nil {
		t.Fatal(err)
	}

	files, err := linter.Lint([]string{absFile}, "*")
	if err != nil {
		t.Fatal(err)
	}
	if len(files) == 0 {
		t.Fatalf("no files linted for %s", filePath)
	}
	return files[0].Alerts
}

// alertsByCheck returns all alerts that match the given rule name.
func alertsByCheck(alerts []core.Alert, check string) []core.Alert {
	var out []core.Alert
	for _, a := range alerts {
		if a.Check == check {
			out = append(out, a)
		}
	}
	return out
}

// hasAlertAtLine returns whether any alert with the given check fires at line.
func hasAlertAtLine(alerts []core.Alert, check string, line int) bool {
	for _, a := range alerts {
		if a.Check == check && a.Line == line {
			return true
		}
	}
	return false
}

// hasNoAlertAtLine returns whether NO alert fires at the given line.
func hasNoAlertAtLine(alerts []core.Alert, line int) bool {
	for _, a := range alerts {
		if a.Line == line {
			return false
		}
	}
	return true
}

// TestQDocFragments verifies that /*!...*/ QDoc doc-comment blocks embedded in
// .cpp and .qml source files are routed through the full QDoc two-pass pipeline
// when [formats] cpp = qdoc / qml = qdoc is configured.
//
// Test fixture layout (test.cpp and test.qml share the same structure):
//
//	 1: /*!
//	 2:     \class Widget          (or \qmltype Button)
//	 3:     \brief BADBRIEF text.  → BriefMarker at line 3
//	 4:     (blank)
//	 5:     BADPROSE body. BADSENTENCE body.  → ProseMarker + SentenceMarker (NLP offset: line 4)
//	 6:     (blank)
//	 7:     \section1 BADHEADING Title  → HeadingMarker at line 7
//	 8:     (blank)
//	 9:     \code
//	10:     BADPROSE suppressed.        → BlockIgnores: no alert here
//	11:     \endcode
//	12: */
//	13: // BADLINE line comment         → LineMarker at line 13
//	14: (blank)
//	15: /*
//	16:     BADPROSE block comment.     → ProseMarker at line 16 (lintLines path)
//	17: */
//	18: (blank)
//	19: /*!
//	20:     \class Button              (second QDoc block)
//	21:     \brief Second block brief.
//	22:     (blank)
//	23:     \section1 BADHEADING Second  → HeadingMarker at line 23 (line-number accuracy)
//	24: */
func TestQDocFragments(t *testing.T) {
	const ini = "../../testdata/fixtures/qdoc-fragments/.vale.ini"

	for _, file := range []string{
		"../../testdata/fixtures/qdoc-fragments/test.cpp",
		"../../testdata/fixtures/qdoc-fragments/test.qml",
	} {
		t.Run(file, func(t *testing.T) {
			alerts := lintWithConfig(t, ini, file)

			// --- QDoc two-pass pipeline: heading scope ---
			// \section1 BADHEADING at source line 7 → HeadingMarker at line 7.
			if !hasAlertAtLine(alerts, "Test.HeadingMarker", 7) {
				t.Errorf("expected Test.HeadingMarker at line 7 (\\section1); alerts: %v", alerts)
			}

			// --- QDoc two-pass pipeline: brief scope ---
			// \brief BADBRIEF at source line 3 → BriefMarker at line 3.
			if !hasAlertAtLine(alerts, "Test.BriefMarker", 3) {
				t.Errorf("expected Test.BriefMarker at line 3 (\\brief); alerts: %v", alerts)
			}

			// --- QDoc two-pass pipeline: prose body (lintProse pass 2) ---
			// BADPROSE in prose body fires via lintProse. Line offset from NLP
			// sentence reconstruction places it at line 4 (one before source line 5).
			if len(alertsByCheck(alerts, "Test.ProseMarker")) == 0 {
				t.Errorf("expected at least one Test.ProseMarker alert; alerts: %v", alerts)
			}

			// --- QDoc two-pass pipeline: sentence scope (lintProse pass 2) ---
			// BADSENTENCE fires via sentence-scoped rule on prose body.
			if len(alertsByCheck(alerts, "Test.SentenceMarker")) == 0 {
				t.Errorf("expected at least one Test.SentenceMarker alert; alerts: %v", alerts)
			}

			// --- BlockIgnores: \code...\endcode content is suppressed ---
			// BADPROSE at line 10 (inside \code block) must not produce an alert.
			if !hasNoAlertAtLine(alerts, 10) {
				t.Errorf("expected no alert at line 10 (inside \\code block); alerts: %v", alerts)
			}

			// --- Regular // line comment (lintLines path) ---
			// BADLINE in // comment at source line 13 → LineMarker at line 13.
			if !hasAlertAtLine(alerts, "Test.LineMarker", 13) {
				t.Errorf("expected Test.LineMarker at line 13 (// comment); alerts: %v", alerts)
			}

			// --- Regular /* */ block comment (lintLines path) ---
			// Multi-line /* */ comment with BADPROSE at source line 16 →
			// ProseMarker at line 16 (lintLines adjusts by comment.Line - 1).
			if !hasAlertAtLine(alerts, "Test.ProseMarker", 16) {
				t.Errorf("expected Test.ProseMarker at line 16 (/* */ block comment); alerts: %v", alerts)
			}

			// --- Second QDoc block: line-number accuracy ---
			// \section1 BADHEADING Second at source line 23 → HeadingMarker at line 23.
			if !hasAlertAtLine(alerts, "Test.HeadingMarker", 23) {
				t.Errorf("expected Test.HeadingMarker at line 23 (second block \\section1); alerts: %v", alerts)
			}
		})
	}
}
