# Changelog

All notable changes to the QDoc support fork are documented here.

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
