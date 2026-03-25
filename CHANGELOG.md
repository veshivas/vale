# feat/qdoc-parser

## Changelog

*   [`20551d1`](https://github.com/veshivas/vale/commit/20551d19) feat(lint): add lintQDocFragments pipeline for .cpp/.qml sources
*   [`f0eb664`](https://github.com/veshivas/vale/commit/f0eb664d) refactor(code): source QDoc parser from external Go module
*   [`a8a1e44`](https://github.com/veshivas/vale/commit/a8a1e447) fix(lint): use syntax key in lintData error message
*   [`307ff86`](https://github.com/veshivas/vale/commit/307ff865) feat(code): upgrade QDoc parser with block/image command support
*   [`b5b61924`](https://github.com/veshivas/vale/commit/b5b61924) feat(lint): add BlockIgnores/TokenIgnores support for QDoc files
*   [`6fb4178`](https://github.com/veshivas/vale/commit/6fb4178b) fix(lint): route QDoc block comments through lintProse for NLP support
*   [`41a563a`](https://github.com/veshivas/vale/commit/41a563a5) feat(code): add .qml → QDoc() mapping in GetLanguageFromExt
*   [`62f8a9b`](https://github.com/veshivas/vale/commit/62f8a9b2) fix(code): restore Cpp() as default for .cpp; use Formats for QDoc opt-in
*   [`13e6cfd`](https://github.com/veshivas/vale/commit/13e6cfdf) feat: add QDoc tree-sitter parser and markup linter
