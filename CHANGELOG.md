# Changelog

All notable changes to the QDoc support fork are documented here.

---

## [v3.14.2-qdoc] - 2026-06-04

### Added

- **Image alt text linted as prose** — Alt text from `\image` and `\inlineimage` commands is now extracted with a `text.comment.image.alt` scope and passed through the prose pipeline (Pass 2), enabling sentence-scope rules (OxfordComma, SentenceLength, Semicolon) to fire on captions.

### Fixed

- **False `SentenceLength` on lead sentence before `\qml`/`\code` blocks** — `BlockIgnores` blanks `\qml`/`\code` regions before tree-sitter parsing, leaving blank-line boundaries that the Punkt NLP tokenizer bridges, joining the colon-terminated sentence before the code block with the paragraph that follows it. Prose blocks are now split at blank-line boundaries into per-paragraph sub-Comments before NLP processing, preventing the tokenizer from crossing code-block boundaries.

- **`.cpp` column offsets reported too low** — `lintQDocFragments` passed `comment.Text` to `lintQDocBlock`. The query engine's `TrimLeft` cutset strips leading indentation from `.cpp` doc-comment lines, causing column numbers to be underreported by the indentation width (typically 4). Fixed by using `comment.Source` with only the `/*!`/`*/` delimiters stripped, preserving per-line indentation.

- **Doxygen-style prefixes in `.cpp` blocks** — `@brief`, `@param`, and similar Doxygen-style command lines inside `/*!...*/` blocks were passed to the prose pipeline, producing false alerts. `stripDoxygenPrefixes` now blanks these lines before tree-sitter parsing.

- **Negative column numbers for continuation lines** — `adjustAlerts` applied `comment.Offset` unconditionally, producing negative column numbers for alerts on continuation lines in `.cpp` doc-comment blocks where the first content character carries no indentation offset. The offset is now clamped to zero on subsequent lines.

- **`\title` and section heading text excluded from prose** — Heading command arguments were included in the `qdocCollectProse` output, inflating word counts for the following paragraph and triggering spurious `Microsoft.SentenceLength` alerts. These commands are now in the `skipQDocProseUntilBlank` map.

- **tree-sitter-qdoc upgraded to v0.2.2** — Grammar update with fixes for `macro_name` and inline command parsing edge cases.

---

## [v3.14.2-qdoc-rc2] - 2026-05-19

### Fixed

- **Table cell prose not linted** — `table_block` was falling through to the `raw_block` default case in `qdocCollectProse`, which only preserved newlines without recursing into the block's markup children. Table blocks share the same `repeat(markup)` AST structure as `list_block` and are now recursed into identically, so prose in `\table` cells is linted by Pass 2.

- **`\l` alias column/line accuracy for space-separated syntax** — When the link target and alias are separated by whitespace (`\l {target} {alias}` or `\l {target}\n    {alias}`), the `link_alias` grammar token includes the leading whitespace in its byte range. The previous code indexed `aliasRaw[1:]`, which skipped only one byte regardless of the whitespace length, causing the opening `{` to appear verbatim in the reconstructed prose and the inter-line `\n` to be lost for cross-line aliases. The fix locates the `{` character within `aliasRaw` using `IndexByte` and loops from the child start through that position, preserving `\n` throughout.

---

## [v3.14.2-qdoc-rc1] - 2026-05-14

### Fixed

- **Duplicate alerts between Pass 1 and Pass 2** — When a `\brief`, `\note`, or `\warning` block was linted by both the scoped pass (Pass 1) and the prose-reconstruction pass (Pass 2), identical alerts were emitted twice. Resolved by building a `(line, check, match)` keyed set from Pass 2 results and suppressing matching Pass 1 alerts in `runQDocPasses`.

- **Section heading arguments polluting prose** — `\section1`–`\section4` heading text was included in the prose output of `qdocCollectProse`, causing the following paragraph's word count to be inflated and triggering spurious `Microsoft.SentenceLength` alerts. Section heading commands are now in the `skipQDocProseUntilBlank` map; their arguments are excluded from prose reconstruction.

- **Command keyword bytes causing line/column shifts** — `qdocCollectProse` was emitting the command keyword (e.g. `\li`, `\section2`) as literal text before blanking it, shifting the column positions of all subsequent tokens on that line. The keyword bytes are now replaced with length-preserving spaces, keeping positions aligned.

- **Unrecognized command nodes (`\{QC}` style) dropping newlines** — Multi-line unrecognized command nodes (parsed as a single node covering their full content) had all bytes replaced with spaces, losing embedded newlines. This caused subsequent prose paragraphs to be joined, wrong line numbers, and missing blank-line paragraph boundaries. The blanking loop now preserves `\n` characters.

- **`\l` link command column accuracy** — `\l{target}{alias}` and `\l{target}` link commands were listed in `TokenIgnores`, which blanked the entire token before column positions were assigned, causing incorrect `Span` values for alerts in the surrounding sentence. These commands are now handled at the AST level in `qdocCollectProse`: alias text is emitted at the correct byte position; no-alias bare targets are fully blanked.

- **Multi-line note/warning column offset applied to all lines** — `adjustAlerts` was applying `comment.Offset` (the source-column of the first content character) to every alert line in a multi-line `\note` or `\warning` block. The offset now applies only to alerts on line 1 of the comment text; subsequent lines start at column 0 in the source.

---

## [v3.14.2-qdocsupport-beta1] - 2026-04-16

### Added

- **Meta scopes for non-prose QDoc commands** — `\image`, `\inlineimage`, `\target`, and `\keyword` arguments now receive `meta.*` scopes (`meta.image.line`, `meta.anchor.line`) instead of the default `text.*` prefix. This prevents text-scoped rules (e.g. `Vale.Terms`, `Microsoft.*`) from firing on filenames and anchor identifiers that are not prose.

### Fixed

- **Code block exit detection broken by grammar upgrade** — The tree-sitter-qdoc grammar upgrade in alpha2 changed `\endcode`, `\endqml`, and similar terminators from `inline_command` nodes to `command → macro_name` nodes. `qdocCollectProse` now reads both `command_name` and `macro_name` children and uses an updated exit-command set, restoring correct code block boundary detection.

- **Incorrect `\endsnippet` and `\endbadcode` exit markers removed** — `\badcode` is terminated by `\endcode` (not `\endbadcode`), and `\snippet` is a single-line inclusion command with no end counterpart. The stale entries have been removed from the exit map.

---

## [v3.14.2-qdocsupport-alpha2] - 2026-04-07

### Added

- **Macro name support in QDoc grammar** — Unknown QDoc macros (`\QUL`, `\macos`, `\BUILDVAR`, etc.) are now parsed as `command` nodes via a new `macro_name` catch-all rule in the tree-sitter grammar. Previously, macros were misparsed as `inline_command` nodes (swallowing subsequent prose) or split at single letters (`\orderedlist` → `\o` + `rderedlist`), causing false-positive spelling alerts.

### Fixed

- **Single-line C++ comments skipped in QDoc fragment linting** — `//` comments inside `/*!...*/` doc-comment blocks were incorrectly linted as prose. These are now excluded from the QDoc pipeline.

---

## [v3.14.2-qdocsupport-alpha1] - 2026-03-31

### Added

- **`\note` and `\warning` scopes** — `\note` and `\warning` admonition commands now produce `text.comment.note.line` and `text.comment.warning.line` scopes, mirroring the existing `\brief` behaviour. Full text spanning inline-command boundaries (`\c`, `\l`, etc.) is captured until the first blank line.

### Fixed

- **Duplicate alerts for `\brief`, `\note`, `\warning`** — Two independent sources of duplication eliminated:
  - The catch-all `(text)` query was re-capturing text nodes already consumed by a `CommandMatch` query. Fixed by tracking consumed node byte ranges in `GetComments` and skipping them in the catch-all pass.
  - Calling `lintLines` then `lintProse` on the same text ran `lintBlock` twice with different position-finding paths (`FindLoc` vs `assignLoc`), producing different `Span[0]` values that defeated `f.history` deduplication. Fixed by using `lintProse` exclusively for `\brief`/`\note`/`\warning` scopes.

- **Prose line numbers wrong after skipped command arguments** — `qdocCollectProse` discarded newlines when skipping topic-command arguments (`\class`, `\fn`, etc.) and code block content, causing all subsequent prose alerts to report the wrong source line. Fixed by preserving newlines from skipped nodes.

---

## [v3.14.1-qdocsupport-alpha] - 2026-03-25

### Added

- **QDoc source file support** — Vale now lints `.qdoc` and `.qdocinc` files natively using a tree-sitter grammar. A two-pass pipeline handles structured command scopes in Pass 1 and reconstructs full prose spanning inline-command boundaries in Pass 2, enabling `scope: sentence` rules (OxfordComma, SentenceLength, Semicolon) to fire on complete sentences.

  Scopes produced:
  | Scope | Command |
  |---|---|
  | `text.comment.brief` | `\brief` (until first blank line) |
  | `text.comment.heading` | `\section1`–`\section6` (first line) |
  | `text.comment.title` | `\title` (first line) |
  | `text.comment.image` | `\image` / `\inlineimage` without alt text |
  | `text.comment.block` | general multi-line prose |
  | `text.comment.line` | general single-line comments |

- **QDoc embedded in C++ and QML** — `.cpp` and `.qml` files can be opted in to QDoc linting via `[formats]` in `.vale.ini`. `/*!...*/` doc-comment blocks are routed through the full QDoc two-pass pipeline; regular `//` and `/* */` comments use `lintLines`.

  ```ini
  [formats]
  cpp = qdoc
  ```

- **BlockIgnores and TokenIgnores for QDoc** — `BlockIgnores` and `TokenIgnores` patterns are applied per `/*!...*/` block before tree-sitter parsing. Matched regions are replaced with whitespace, preserving newlines so alert line numbers remain accurate.

- **Upgraded QDoc grammar** — Block commands (`\list`, `\table`, `\code`, `\qml`, `\snippet`, `\legalese`, `\quotation`) and image commands (`\image`, `\inlineimage`) with optional alt text are now supported. Code block content is excluded from prose reconstruction.

- **External Go module for QDoc parser** — The tree-sitter grammar is sourced from `github.com/veshivas/tree-sitter-qdoc` rather than a vendored local directory.

  ```sh
  go get github.com/veshivas/tree-sitter-qdoc@latest
  ```

### Fixed

- **`.cpp` files default restored** — `.cpp` files no longer default to the QDoc parser. QDoc linting requires explicit opt-in via `[formats]`, preserving existing behaviour for projects that do not use QDoc.

- **QDoc block comments through `lintProse`** — Multi-line prose blocks are now processed with full NLP support, enabling sentence-scope rules that were previously silently skipped.

- **Syntax key used in `lintData` error messages** — Error messages from the `lintData` path now report the correct syntax key instead of a generic fallback.
