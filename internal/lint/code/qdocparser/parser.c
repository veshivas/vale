#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#ifdef _MSC_VER
#pragma optimize("", off)
#elif defined(__clang__)
#pragma clang optimize off
#elif defined(__GNUC__)
#pragma GCC optimize ("O0")
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 76
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 43
#define ALIAS_COUNT 0
#define TOKEN_COUNT 26
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 5
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 6

enum {
  anon_sym_SLASH_STAR_BANG = 1,
  anon_sym_STAR_SLASH = 2,
  anon_sym_BSLASH = 3,
  anon_sym_list = 4,
  anon_sym_endlist = 5,
  anon_sym_table = 6,
  anon_sym_endtable = 7,
  anon_sym_raw = 8,
  anon_sym_endraw = 9,
  anon_sym_legalese = 10,
  anon_sym_endlegalese = 11,
  anon_sym_quotation = 12,
  anon_sym_endquotation = 13,
  sym_raw_content_chunk = 14,
  sym_command_name = 15,
  sym_inline_command_name = 16,
  anon_sym_image = 17,
  anon_sym_inlineimage = 18,
  sym_image_content = 19,
  sym_image_alt = 20,
  sym_block_argument = 21,
  sym_cell_span = 22,
  sym_command_argument = 23,
  sym_inline_text = 24,
  sym_text = 25,
  sym_source_file = 26,
  sym_comment = 27,
  sym_block_comment = 28,
  sym_markup = 29,
  sym_block_command = 30,
  sym_list_block = 31,
  sym_table_block = 32,
  sym_raw_block = 33,
  sym_legalese_block = 34,
  sym_quotation_block = 35,
  sym_command = 36,
  sym_inline_command = 37,
  sym_image_command = 38,
  sym_inlineimage_command = 39,
  aux_sym_source_file_repeat1 = 40,
  aux_sym_block_comment_repeat1 = 41,
  aux_sym_raw_block_repeat1 = 42,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_SLASH_STAR_BANG] = "/*!",
  [anon_sym_STAR_SLASH] = "*/",
  [anon_sym_BSLASH] = "\\",
  [anon_sym_list] = "list",
  [anon_sym_endlist] = "endlist",
  [anon_sym_table] = "table",
  [anon_sym_endtable] = "endtable",
  [anon_sym_raw] = "raw",
  [anon_sym_endraw] = "endraw",
  [anon_sym_legalese] = "legalese",
  [anon_sym_endlegalese] = "endlegalese",
  [anon_sym_quotation] = "quotation",
  [anon_sym_endquotation] = "endquotation",
  [sym_raw_content_chunk] = "raw_content_chunk",
  [sym_command_name] = "command_name",
  [sym_inline_command_name] = "inline_command_name",
  [anon_sym_image] = "image",
  [anon_sym_inlineimage] = "inlineimage",
  [sym_image_content] = "image_content",
  [sym_image_alt] = "image_alt",
  [sym_block_argument] = "block_argument",
  [sym_cell_span] = "cell_span",
  [sym_command_argument] = "command_argument",
  [sym_inline_text] = "inline_text",
  [sym_text] = "text",
  [sym_source_file] = "source_file",
  [sym_comment] = "comment",
  [sym_block_comment] = "block_comment",
  [sym_markup] = "markup",
  [sym_block_command] = "block_command",
  [sym_list_block] = "list_block",
  [sym_table_block] = "table_block",
  [sym_raw_block] = "raw_block",
  [sym_legalese_block] = "legalese_block",
  [sym_quotation_block] = "quotation_block",
  [sym_command] = "command",
  [sym_inline_command] = "inline_command",
  [sym_image_command] = "image_command",
  [sym_inlineimage_command] = "inlineimage_command",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_block_comment_repeat1] = "block_comment_repeat1",
  [aux_sym_raw_block_repeat1] = "raw_block_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_SLASH_STAR_BANG] = anon_sym_SLASH_STAR_BANG,
  [anon_sym_STAR_SLASH] = anon_sym_STAR_SLASH,
  [anon_sym_BSLASH] = anon_sym_BSLASH,
  [anon_sym_list] = anon_sym_list,
  [anon_sym_endlist] = anon_sym_endlist,
  [anon_sym_table] = anon_sym_table,
  [anon_sym_endtable] = anon_sym_endtable,
  [anon_sym_raw] = anon_sym_raw,
  [anon_sym_endraw] = anon_sym_endraw,
  [anon_sym_legalese] = anon_sym_legalese,
  [anon_sym_endlegalese] = anon_sym_endlegalese,
  [anon_sym_quotation] = anon_sym_quotation,
  [anon_sym_endquotation] = anon_sym_endquotation,
  [sym_raw_content_chunk] = sym_raw_content_chunk,
  [sym_command_name] = sym_command_name,
  [sym_inline_command_name] = sym_inline_command_name,
  [anon_sym_image] = anon_sym_image,
  [anon_sym_inlineimage] = anon_sym_inlineimage,
  [sym_image_content] = sym_image_content,
  [sym_image_alt] = sym_image_alt,
  [sym_block_argument] = sym_block_argument,
  [sym_cell_span] = sym_cell_span,
  [sym_command_argument] = sym_command_argument,
  [sym_inline_text] = sym_inline_text,
  [sym_text] = sym_text,
  [sym_source_file] = sym_source_file,
  [sym_comment] = sym_comment,
  [sym_block_comment] = sym_block_comment,
  [sym_markup] = sym_markup,
  [sym_block_command] = sym_block_command,
  [sym_list_block] = sym_list_block,
  [sym_table_block] = sym_table_block,
  [sym_raw_block] = sym_raw_block,
  [sym_legalese_block] = sym_legalese_block,
  [sym_quotation_block] = sym_quotation_block,
  [sym_command] = sym_command,
  [sym_inline_command] = sym_inline_command,
  [sym_image_command] = sym_image_command,
  [sym_inlineimage_command] = sym_inlineimage_command,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_block_comment_repeat1] = aux_sym_block_comment_repeat1,
  [aux_sym_raw_block_repeat1] = aux_sym_raw_block_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_SLASH_STAR_BANG] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BSLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_list] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endlist] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_table] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endtable] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_raw] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endraw] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_legalese] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endlegalese] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_quotation] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_endquotation] = {
    .visible = true,
    .named = false,
  },
  [sym_raw_content_chunk] = {
    .visible = true,
    .named = true,
  },
  [sym_command_name] = {
    .visible = true,
    .named = true,
  },
  [sym_inline_command_name] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_image] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_inlineimage] = {
    .visible = true,
    .named = false,
  },
  [sym_image_content] = {
    .visible = true,
    .named = true,
  },
  [sym_image_alt] = {
    .visible = true,
    .named = true,
  },
  [sym_block_argument] = {
    .visible = true,
    .named = true,
  },
  [sym_cell_span] = {
    .visible = true,
    .named = true,
  },
  [sym_command_argument] = {
    .visible = true,
    .named = true,
  },
  [sym_inline_text] = {
    .visible = true,
    .named = true,
  },
  [sym_text] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_block_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_markup] = {
    .visible = true,
    .named = true,
  },
  [sym_block_command] = {
    .visible = true,
    .named = true,
  },
  [sym_list_block] = {
    .visible = true,
    .named = true,
  },
  [sym_table_block] = {
    .visible = true,
    .named = true,
  },
  [sym_raw_block] = {
    .visible = true,
    .named = true,
  },
  [sym_legalese_block] = {
    .visible = true,
    .named = true,
  },
  [sym_quotation_block] = {
    .visible = true,
    .named = true,
  },
  [sym_command] = {
    .visible = true,
    .named = true,
  },
  [sym_inline_command] = {
    .visible = true,
    .named = true,
  },
  [sym_image_command] = {
    .visible = true,
    .named = true,
  },
  [sym_inlineimage_command] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_comment_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_raw_block_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_alt = 1,
  field_arg = 2,
  field_content = 3,
  field_filename = 4,
  field_span = 5,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_alt] = "alt",
  [field_arg] = "arg",
  [field_content] = "content",
  [field_filename] = "filename",
  [field_span] = "span",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 1},
  [4] = {.index = 3, .length = 2},
  [5] = {.index = 5, .length = 1},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_span, 2},
  [1] =
    {field_content, 2},
  [2] =
    {field_filename, 2},
  [3] =
    {field_alt, 3},
    {field_filename, 2},
  [5] =
    {field_arg, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 6,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 30,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 32,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(290);
      if (lookahead == '*') ADVANCE(9);
      if (lookahead == '/') ADVANCE(4);
      if (lookahead == '\\') ADVANCE(294);
      if (lookahead == 'a') ADVANCE(316);
      if (lookahead == 'b') ADVANCE(315);
      if (lookahead == 'c') ADVANCE(318);
      if (lookahead == 'd') ADVANCE(77);
      if (lookahead == 'e') ADVANCE(319);
      if (lookahead == 'f') ADVANCE(172);
      if (lookahead == 'g') ADVANCE(214);
      if (lookahead == 'h') ADVANCE(91);
      if (lookahead == 'i') ADVANCE(168);
      if (lookahead == 'k') ADVANCE(79);
      if (lookahead == 'l') ADVANCE(317);
      if (lookahead == 'm') ADVANCE(18);
      if (lookahead == 'n') ADVANCE(19);
      if (lookahead == 'o') ADVANCE(163);
      if (lookahead == 'p') ADVANCE(27);
      if (lookahead == 'q') ADVANCE(162);
      if (lookahead == 'r') ADVANCE(20);
      if (lookahead == 's') ADVANCE(17);
      if (lookahead == 't') ADVANCE(21);
      if (lookahead == 'u') ADVANCE(123);
      if (lookahead == 'v') ADVANCE(22);
      if (lookahead == 'w') ADVANCE(24);
      if (lookahead == '{') ADVANCE(288);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == '!') ADVANCE(291);
      END_STATE();
    case 2:
      if (lookahead == '*') ADVANCE(9);
      if (lookahead == '\\') ADVANCE(294);
      if (lookahead == '{') ADVANCE(346);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(344);
      if (lookahead != 0) ADVANCE(348);
      END_STATE();
    case 3:
      if (lookahead == '*') ADVANCE(9);
      if (lookahead == '\\') ADVANCE(294);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(347);
      if (lookahead != 0) ADVANCE(348);
      END_STATE();
    case 4:
      if (lookahead == '*') ADVANCE(1);
      END_STATE();
    case 5:
      if (lookahead == '*') ADVANCE(331);
      if (lookahead == '\\') ADVANCE(294);
      if (lookahead == '{') ADVANCE(345);
      if (lookahead == '}') ADVANCE(348);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(342);
      if (lookahead != 0) ADVANCE(330);
      END_STATE();
    case 6:
      if (lookahead == '*') ADVANCE(334);
      if (lookahead == '\\') ADVANCE(295);
      if (lookahead == '{') ADVANCE(336);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(343);
      if (lookahead != 0) ADVANCE(338);
      END_STATE();
    case 7:
      if (lookahead == '*') ADVANCE(339);
      if (lookahead == '\\') ADVANCE(295);
      if (lookahead == '{') ADVANCE(336);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(343);
      if (lookahead != 0) ADVANCE(338);
      END_STATE();
    case 8:
      if (lookahead == ',') ADVANCE(289);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 9:
      if (lookahead == '/') ADVANCE(292);
      END_STATE();
    case 10:
      if (lookahead == '\\') ADVANCE(294);
      if (lookahead == '{') ADVANCE(306);
      if (lookahead == '}') ADVANCE(309);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(307);
      if (lookahead != 0) ADVANCE(331);
      END_STATE();
    case 11:
      if (lookahead == '\\') ADVANCE(294);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(308);
      if (lookahead != 0) ADVANCE(309);
      END_STATE();
    case 12:
      if (lookahead == 'a') ADVANCE(316);
      if (lookahead == 'b') ADVANCE(315);
      if (lookahead == 'c') ADVANCE(318);
      if (lookahead == 'd') ADVANCE(77);
      if (lookahead == 'e') ADVANCE(323);
      if (lookahead == 'f') ADVANCE(172);
      if (lookahead == 'g') ADVANCE(214);
      if (lookahead == 'h') ADVANCE(91);
      if (lookahead == 'i') ADVANCE(168);
      if (lookahead == 'k') ADVANCE(79);
      if (lookahead == 'l') ADVANCE(317);
      if (lookahead == 'm') ADVANCE(18);
      if (lookahead == 'n') ADVANCE(19);
      if (lookahead == 'o') ADVANCE(163);
      if (lookahead == 'p') ADVANCE(27);
      if (lookahead == 'q') ADVANCE(162);
      if (lookahead == 'r') ADVANCE(20);
      if (lookahead == 's') ADVANCE(17);
      if (lookahead == 't') ADVANCE(21);
      if (lookahead == 'u') ADVANCE(123);
      if (lookahead == 'v') ADVANCE(22);
      if (lookahead == 'w') ADVANCE(24);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(12)
      END_STATE();
    case 13:
      if (lookahead == 'a') ADVANCE(316);
      if (lookahead == 'b') ADVANCE(315);
      if (lookahead == 'c') ADVANCE(318);
      if (lookahead == 'd') ADVANCE(77);
      if (lookahead == 'e') ADVANCE(320);
      if (lookahead == 'f') ADVANCE(172);
      if (lookahead == 'g') ADVANCE(214);
      if (lookahead == 'h') ADVANCE(91);
      if (lookahead == 'i') ADVANCE(168);
      if (lookahead == 'k') ADVANCE(79);
      if (lookahead == 'l') ADVANCE(317);
      if (lookahead == 'm') ADVANCE(18);
      if (lookahead == 'n') ADVANCE(19);
      if (lookahead == 'o') ADVANCE(163);
      if (lookahead == 'p') ADVANCE(27);
      if (lookahead == 'q') ADVANCE(162);
      if (lookahead == 'r') ADVANCE(20);
      if (lookahead == 's') ADVANCE(17);
      if (lookahead == 't') ADVANCE(21);
      if (lookahead == 'u') ADVANCE(123);
      if (lookahead == 'v') ADVANCE(22);
      if (lookahead == 'w') ADVANCE(24);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(13)
      END_STATE();
    case 14:
      if (lookahead == 'a') ADVANCE(316);
      if (lookahead == 'b') ADVANCE(315);
      if (lookahead == 'c') ADVANCE(318);
      if (lookahead == 'd') ADVANCE(77);
      if (lookahead == 'e') ADVANCE(321);
      if (lookahead == 'f') ADVANCE(172);
      if (lookahead == 'g') ADVANCE(214);
      if (lookahead == 'h') ADVANCE(91);
      if (lookahead == 'i') ADVANCE(168);
      if (lookahead == 'k') ADVANCE(79);
      if (lookahead == 'l') ADVANCE(317);
      if (lookahead == 'm') ADVANCE(18);
      if (lookahead == 'n') ADVANCE(19);
      if (lookahead == 'o') ADVANCE(163);
      if (lookahead == 'p') ADVANCE(27);
      if (lookahead == 'q') ADVANCE(162);
      if (lookahead == 'r') ADVANCE(20);
      if (lookahead == 's') ADVANCE(17);
      if (lookahead == 't') ADVANCE(21);
      if (lookahead == 'u') ADVANCE(123);
      if (lookahead == 'v') ADVANCE(22);
      if (lookahead == 'w') ADVANCE(24);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(14)
      END_STATE();
    case 15:
      if (lookahead == 'a') ADVANCE(316);
      if (lookahead == 'b') ADVANCE(315);
      if (lookahead == 'c') ADVANCE(318);
      if (lookahead == 'd') ADVANCE(77);
      if (lookahead == 'e') ADVANCE(324);
      if (lookahead == 'f') ADVANCE(172);
      if (lookahead == 'g') ADVANCE(214);
      if (lookahead == 'h') ADVANCE(91);
      if (lookahead == 'i') ADVANCE(168);
      if (lookahead == 'k') ADVANCE(79);
      if (lookahead == 'l') ADVANCE(317);
      if (lookahead == 'm') ADVANCE(18);
      if (lookahead == 'n') ADVANCE(19);
      if (lookahead == 'o') ADVANCE(163);
      if (lookahead == 'p') ADVANCE(27);
      if (lookahead == 'q') ADVANCE(162);
      if (lookahead == 'r') ADVANCE(20);
      if (lookahead == 's') ADVANCE(17);
      if (lookahead == 't') ADVANCE(21);
      if (lookahead == 'u') ADVANCE(123);
      if (lookahead == 'v') ADVANCE(22);
      if (lookahead == 'w') ADVANCE(24);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(15)
      END_STATE();
    case 16:
      if (lookahead == 'a') ADVANCE(316);
      if (lookahead == 'b') ADVANCE(315);
      if (lookahead == 'c') ADVANCE(318);
      if (lookahead == 'd') ADVANCE(77);
      if (lookahead == 'e') ADVANCE(322);
      if (lookahead == 'f') ADVANCE(172);
      if (lookahead == 'g') ADVANCE(214);
      if (lookahead == 'h') ADVANCE(91);
      if (lookahead == 'i') ADVANCE(168);
      if (lookahead == 'k') ADVANCE(79);
      if (lookahead == 'l') ADVANCE(317);
      if (lookahead == 'm') ADVANCE(18);
      if (lookahead == 'n') ADVANCE(19);
      if (lookahead == 'o') ADVANCE(163);
      if (lookahead == 'p') ADVANCE(27);
      if (lookahead == 'q') ADVANCE(162);
      if (lookahead == 'r') ADVANCE(20);
      if (lookahead == 's') ADVANCE(17);
      if (lookahead == 't') ADVANCE(21);
      if (lookahead == 'u') ADVANCE(123);
      if (lookahead == 'v') ADVANCE(22);
      if (lookahead == 'w') ADVANCE(24);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(16)
      END_STATE();
    case 17:
      if (lookahead == 'a') ADVANCE(310);
      if (lookahead == 'e') ADVANCE(60);
      if (lookahead == 'i') ADVANCE(177);
      if (lookahead == 't') ADVANCE(33);
      if (lookahead == 'u') ADVANCE(285);
      END_STATE();
    case 18:
      if (lookahead == 'a') ADVANCE(62);
      if (lookahead == 'o') ADVANCE(68);
      END_STATE();
    case 19:
      if (lookahead == 'a') ADVANCE(169);
      if (lookahead == 'e') ADVANCE(276);
      if (lookahead == 'o') ADVANCE(249);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(273);
      if (lookahead == 'e') ADVANCE(30);
      if (lookahead == 'o') ADVANCE(272);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(53);
      if (lookahead == 'i') ADVANCE(257);
      if (lookahead == 'm' ||
          lookahead == 't') ADVANCE(314);
      if (lookahead == 'y') ADVANCE(207);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(147);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(55);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(216);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(233);
      END_STATE();
    case 26:
      if (lookahead == 'a') ADVANCE(113);
      END_STATE();
    case 27:
      if (lookahead == 'a') ADVANCE(113);
      if (lookahead == 'r') ADVANCE(80);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(232);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(164);
      if (lookahead == 't') ADVANCE(103);
      END_STATE();
    case 30:
      if (lookahead == 'a') ADVANCE(72);
      if (lookahead == 'i') ADVANCE(167);
      if (lookahead == 'l') ADVANCE(41);
      if (lookahead == 'q') ADVANCE(266);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(59);
      END_STATE();
    case 32:
      if (lookahead == 'a') ADVANCE(274);
      END_STATE();
    case 33:
      if (lookahead == 'a') ADVANCE(220);
      END_STATE();
    case 34:
      if (lookahead == 'a') ADVANCE(64);
      END_STATE();
    case 35:
      if (lookahead == 'a') ADVANCE(158);
      END_STATE();
    case 36:
      if (lookahead == 'a') ADVANCE(56);
      END_STATE();
    case 37:
      if (lookahead == 'a') ADVANCE(159);
      if (lookahead == 'd') ADVANCE(81);
      END_STATE();
    case 38:
      if (lookahead == 'a') ADVANCE(148);
      END_STATE();
    case 39:
      if (lookahead == 'a') ADVANCE(141);
      END_STATE();
    case 40:
      if (lookahead == 'a') ADVANCE(217);
      END_STATE();
    case 41:
      if (lookahead == 'a') ADVANCE(254);
      END_STATE();
    case 42:
      if (lookahead == 'a') ADVANCE(74);
      END_STATE();
    case 43:
      if (lookahead == 'a') ADVANCE(115);
      END_STATE();
    case 44:
      if (lookahead == 'a') ADVANCE(61);
      END_STATE();
    case 45:
      if (lookahead == 'a') ADVANCE(146);
      END_STATE();
    case 46:
      if (lookahead == 'a') ADVANCE(255);
      END_STATE();
    case 47:
      if (lookahead == 'a') ADVANCE(155);
      END_STATE();
    case 48:
      if (lookahead == 'a') ADVANCE(117);
      END_STATE();
    case 49:
      if (lookahead == 'a') ADVANCE(160);
      END_STATE();
    case 50:
      if (lookahead == 'a') ADVANCE(54);
      END_STATE();
    case 51:
      if (lookahead == 'a') ADVANCE(260);
      END_STATE();
    case 52:
      if (lookahead == 'a') ADVANCE(261);
      END_STATE();
    case 53:
      if (lookahead == 'b') ADVANCE(153);
      if (lookahead == 'r') ADVANCE(116);
      END_STATE();
    case 54:
      if (lookahead == 'b') ADVANCE(149);
      END_STATE();
    case 55:
      if (lookahead == 'b') ADVANCE(156);
      END_STATE();
    case 56:
      if (lookahead == 'c') ADVANCE(121);
      END_STATE();
    case 57:
      if (lookahead == 'c') ADVANCE(192);
      END_STATE();
    case 58:
      if (lookahead == 'c') ADVANCE(189);
      END_STATE();
    case 59:
      if (lookahead == 'c') ADVANCE(78);
      END_STATE();
    case 60:
      if (lookahead == 'c') ADVANCE(252);
      END_STATE();
    case 61:
      if (lookahead == 'c') ADVANCE(240);
      END_STATE();
    case 62:
      if (lookahead == 'c') ADVANCE(222);
      END_STATE();
    case 63:
      if (lookahead == 'c') ADVANCE(46);
      END_STATE();
    case 64:
      if (lookahead == 'd') ADVANCE(310);
      END_STATE();
    case 65:
      if (lookahead == 'd') ADVANCE(144);
      if (lookahead == 'u') ADVANCE(161);
      END_STATE();
    case 66:
      if (lookahead == 'd') ADVANCE(211);
      END_STATE();
    case 67:
      if (lookahead == 'd') ADVANCE(213);
      if (lookahead == 'u') ADVANCE(161);
      END_STATE();
    case 68:
      if (lookahead == 'd') ADVANCE(268);
      END_STATE();
    case 69:
      if (lookahead == 'd') ADVANCE(78);
      END_STATE();
    case 70:
      if (lookahead == 'd') ADVANCE(154);
      if (lookahead == 'u') ADVANCE(161);
      END_STATE();
    case 71:
      if (lookahead == 'd') ADVANCE(58);
      END_STATE();
    case 72:
      if (lookahead == 'd') ADVANCE(195);
      END_STATE();
    case 73:
      if (lookahead == 'd') ADVANCE(229);
      END_STATE();
    case 74:
      if (lookahead == 'd') ADVANCE(98);
      END_STATE();
    case 75:
      if (lookahead == 'd') ADVANCE(251);
      if (lookahead == 'u') ADVANCE(161);
      END_STATE();
    case 76:
      if (lookahead == 'd') ADVANCE(157);
      if (lookahead == 'u') ADVANCE(161);
      END_STATE();
    case 77:
      if (lookahead == 'e') ADVANCE(205);
      END_STATE();
    case 78:
      if (lookahead == 'e') ADVANCE(310);
      END_STATE();
    case 79:
      if (lookahead == 'e') ADVANCE(278);
      END_STATE();
    case 80:
      if (lookahead == 'e') ADVANCE(150);
      if (lookahead == 'o') ADVANCE(212);
      END_STATE();
    case 81:
      if (lookahead == 'e') ADVANCE(110);
      END_STATE();
    case 82:
      if (lookahead == 'e') ADVANCE(37);
      END_STATE();
    case 83:
      if (lookahead == 'e') ADVANCE(325);
      END_STATE();
    case 84:
      if (lookahead == 'e') ADVANCE(298);
      END_STATE();
    case 85:
      if (lookahead == 'e') ADVANCE(299);
      END_STATE();
    case 86:
      if (lookahead == 'e') ADVANCE(302);
      END_STATE();
    case 87:
      if (lookahead == 'e') ADVANCE(303);
      END_STATE();
    case 88:
      if (lookahead == 'e') ADVANCE(326);
      END_STATE();
    case 89:
      if (lookahead == 'e') ADVANCE(232);
      END_STATE();
    case 90:
      if (lookahead == 'e') ADVANCE(218);
      END_STATE();
    case 91:
      if (lookahead == 'e') ADVANCE(42);
      END_STATE();
    case 92:
      if (lookahead == 'e') ADVANCE(236);
      END_STATE();
    case 93:
      if (lookahead == 'e') ADVANCE(238);
      END_STATE();
    case 94:
      if (lookahead == 'e') ADVANCE(64);
      END_STATE();
    case 95:
      if (lookahead == 'e') ADVANCE(63);
      END_STATE();
    case 96:
      if (lookahead == 'e') ADVANCE(66);
      END_STATE();
    case 97:
      if (lookahead == 'e') ADVANCE(230);
      END_STATE();
    case 98:
      if (lookahead == 'e') ADVANCE(215);
      END_STATE();
    case 99:
      if (lookahead == 'e') ADVANCE(243);
      if (lookahead == 'o') ADVANCE(68);
      END_STATE();
    case 100:
      if (lookahead == 'e') ADVANCE(240);
      END_STATE();
    case 101:
      if (lookahead == 'e') ADVANCE(179);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(101)
      END_STATE();
    case 102:
      if (lookahead == 'e') ADVANCE(245);
      END_STATE();
    case 103:
      if (lookahead == 'e') ADVANCE(221);
      END_STATE();
    case 104:
      if (lookahead == 'e') ADVANCE(227);
      END_STATE();
    case 105:
      if (lookahead == 'e') ADVANCE(239);
      END_STATE();
    case 106:
      if (lookahead == 'e') ADVANCE(128);
      END_STATE();
    case 107:
      if (lookahead == 'e') ADVANCE(231);
      END_STATE();
    case 108:
      if (lookahead == 'e') ADVANCE(119);
      END_STATE();
    case 109:
      if (lookahead == 'e') ADVANCE(119);
      if (lookahead == 'i') ADVANCE(237);
      END_STATE();
    case 110:
      if (lookahead == 'f') ADVANCE(310);
      END_STATE();
    case 111:
      if (lookahead == 'g') ADVANCE(214);
      if (lookahead == 'h') ADVANCE(97);
      if (lookahead == 'l') ADVANCE(124);
      if (lookahead == 'm') ADVANCE(190);
      if (lookahead == 'q') ADVANCE(166);
      if (lookahead == 't') ADVANCE(107);
      END_STATE();
    case 112:
      if (lookahead == 'g') ADVANCE(310);
      END_STATE();
    case 113:
      if (lookahead == 'g') ADVANCE(78);
      END_STATE();
    case 114:
      if (lookahead == 'g') ADVANCE(47);
      END_STATE();
    case 115:
      if (lookahead == 'g') ADVANCE(83);
      END_STATE();
    case 116:
      if (lookahead == 'g') ADVANCE(100);
      END_STATE();
    case 117:
      if (lookahead == 'g') ADVANCE(88);
      END_STATE();
    case 118:
      if (lookahead == 'g') ADVANCE(185);
      END_STATE();
    case 119:
      if (lookahead == 'g') ADVANCE(49);
      END_STATE();
    case 120:
      if (lookahead == 'h') ADVANCE(191);
      END_STATE();
    case 121:
      if (lookahead == 'h') ADVANCE(96);
      END_STATE();
    case 122:
      if (lookahead == 'i') ADVANCE(118);
      END_STATE();
    case 123:
      if (lookahead == 'i') ADVANCE(57);
      END_STATE();
    case 124:
      if (lookahead == 'i') ADVANCE(184);
      END_STATE();
    case 125:
      if (lookahead == 'i') ADVANCE(81);
      END_STATE();
    case 126:
      if (lookahead == 'i') ADVANCE(242);
      END_STATE();
    case 127:
      if (lookahead == 'i') ADVANCE(170);
      END_STATE();
    case 128:
      if (lookahead == 'i') ADVANCE(171);
      END_STATE();
    case 129:
      if (lookahead == 'i') ADVANCE(176);
      END_STATE();
    case 130:
      if (lookahead == 'i') ADVANCE(246);
      END_STATE();
    case 131:
      if (lookahead == 'i') ADVANCE(28);
      END_STATE();
    case 132:
      if (lookahead == 'i') ADVANCE(237);
      END_STATE();
    case 133:
      if (lookahead == 'i') ADVANCE(194);
      END_STATE();
    case 134:
      if (lookahead == 'i') ADVANCE(149);
      END_STATE();
    case 135:
      if (lookahead == 'i') ADVANCE(228);
      END_STATE();
    case 136:
      if (lookahead == 'i') ADVANCE(197);
      END_STATE();
    case 137:
      if (lookahead == 'i') ADVANCE(186);
      END_STATE();
    case 138:
      if (lookahead == 'i') ADVANCE(199);
      END_STATE();
    case 139:
      if (lookahead == 'i') ADVANCE(200);
      END_STATE();
    case 140:
      if (lookahead == 'i') ADVANCE(50);
      END_STATE();
    case 141:
      if (lookahead == 'l') ADVANCE(310);
      END_STATE();
    case 142:
      if (lookahead == 'l') ADVANCE(314);
      END_STATE();
    case 143:
      if (lookahead == 'l') ADVANCE(311);
      END_STATE();
    case 144:
      if (lookahead == 'l') ADVANCE(109);
      if (lookahead == 'q') ADVANCE(270);
      if (lookahead == 't') ADVANCE(23);
      END_STATE();
    case 145:
      if (lookahead == 'l') ADVANCE(277);
      END_STATE();
    case 146:
      if (lookahead == 'l') ADVANCE(265);
      END_STATE();
    case 147:
      if (lookahead == 'l') ADVANCE(265);
      if (lookahead == 'r') ADVANCE(140);
      END_STATE();
    case 148:
      if (lookahead == 'l') ADVANCE(210);
      END_STATE();
    case 149:
      if (lookahead == 'l') ADVANCE(78);
      END_STATE();
    case 150:
      if (lookahead == 'l') ADVANCE(127);
      if (lookahead == 'v') ADVANCE(133);
      END_STATE();
    case 151:
      if (lookahead == 'l') ADVANCE(165);
      END_STATE();
    case 152:
      if (lookahead == 'l') ADVANCE(201);
      END_STATE();
    case 153:
      if (lookahead == 'l') ADVANCE(84);
      END_STATE();
    case 154:
      if (lookahead == 'l') ADVANCE(132);
      END_STATE();
    case 155:
      if (lookahead == 'l') ADVANCE(93);
      END_STATE();
    case 156:
      if (lookahead == 'l') ADVANCE(85);
      END_STATE();
    case 157:
      if (lookahead == 'l') ADVANCE(108);
      END_STATE();
    case 158:
      if (lookahead == 'l') ADVANCE(267);
      END_STATE();
    case 159:
      if (lookahead == 'l') ADVANCE(131);
      END_STATE();
    case 160:
      if (lookahead == 'l') ADVANCE(105);
      END_STATE();
    case 161:
      if (lookahead == 'm') ADVANCE(310);
      END_STATE();
    case 162:
      if (lookahead == 'm') ADVANCE(143);
      if (lookahead == 'u') ADVANCE(193);
      END_STATE();
    case 163:
      if (lookahead == 'm') ADVANCE(126);
      if (lookahead == 'v') ADVANCE(90);
      END_STATE();
    case 164:
      if (lookahead == 'm') ADVANCE(209);
      END_STATE();
    case 165:
      if (lookahead == 'm') ADVANCE(190);
      END_STATE();
    case 166:
      if (lookahead == 'm') ADVANCE(151);
      END_STATE();
    case 167:
      if (lookahead == 'm') ADVANCE(204);
      END_STATE();
    case 168:
      if (lookahead == 'm') ADVANCE(43);
      if (lookahead == 'n') ADVANCE(111);
      END_STATE();
    case 169:
      if (lookahead == 'm') ADVANCE(92);
      END_STATE();
    case 170:
      if (lookahead == 'm') ADVANCE(137);
      END_STATE();
    case 171:
      if (lookahead == 'm') ADVANCE(48);
      END_STATE();
    case 172:
      if (lookahead == 'n') ADVANCE(310);
      END_STATE();
    case 173:
      if (lookahead == 'n') ADVANCE(287);
      END_STATE();
    case 174:
      if (lookahead == 'n') ADVANCE(304);
      END_STATE();
    case 175:
      if (lookahead == 'n') ADVANCE(305);
      END_STATE();
    case 176:
      if (lookahead == 'n') ADVANCE(112);
      END_STATE();
    case 177:
      if (lookahead == 'n') ADVANCE(59);
      END_STATE();
    case 178:
      if (lookahead == 'n') ADVANCE(263);
      END_STATE();
    case 179:
      if (lookahead == 'n') ADVANCE(73);
      END_STATE();
    case 180:
      if (lookahead == 'n') ADVANCE(145);
      END_STATE();
    case 181:
      if (lookahead == 'n') ADVANCE(129);
      END_STATE();
    case 182:
      if (lookahead == 'n') ADVANCE(259);
      END_STATE();
    case 183:
      if (lookahead == 'n') ADVANCE(38);
      END_STATE();
    case 184:
      if (lookahead == 'n') ADVANCE(106);
      END_STATE();
    case 185:
      if (lookahead == 'n') ADVANCE(39);
      END_STATE();
    case 186:
      if (lookahead == 'n') ADVANCE(40);
      END_STATE();
    case 187:
      if (lookahead == 'o') ADVANCE(310);
      END_STATE();
    case 188:
      if (lookahead == 'o') ADVANCE(264);
      END_STATE();
    case 189:
      if (lookahead == 'o') ADVANCE(69);
      END_STATE();
    case 190:
      if (lookahead == 'o') ADVANCE(68);
      END_STATE();
    case 191:
      if (lookahead == 'o') ADVANCE(64);
      END_STATE();
    case 192:
      if (lookahead == 'o') ADVANCE(182);
      END_STATE();
    case 193:
      if (lookahead == 'o') ADVANCE(253);
      END_STATE();
    case 194:
      if (lookahead == 'o') ADVANCE(269);
      END_STATE();
    case 195:
      if (lookahead == 'o') ADVANCE(180);
      END_STATE();
    case 196:
      if (lookahead == 'o') ADVANCE(219);
      END_STATE();
    case 197:
      if (lookahead == 'o') ADVANCE(173);
      END_STATE();
    case 198:
      if (lookahead == 'o') ADVANCE(142);
      END_STATE();
    case 199:
      if (lookahead == 'o') ADVANCE(174);
      END_STATE();
    case 200:
      if (lookahead == 'o') ADVANCE(175);
      END_STATE();
    case 201:
      if (lookahead == 'o') ADVANCE(34);
      END_STATE();
    case 202:
      if (lookahead == 'o') ADVANCE(212);
      END_STATE();
    case 203:
      if (lookahead == 'o') ADVANCE(262);
      END_STATE();
    case 204:
      if (lookahead == 'p') ADVANCE(310);
      END_STATE();
    case 205:
      if (lookahead == 'p') ADVANCE(224);
      END_STATE();
    case 206:
      if (lookahead == 'p') ADVANCE(78);
      END_STATE();
    case 207:
      if (lookahead == 'p') ADVANCE(82);
      END_STATE();
    case 208:
      if (lookahead == 'p') ADVANCE(31);
      END_STATE();
    case 209:
      if (lookahead == 'p') ADVANCE(149);
      END_STATE();
    case 210:
      if (lookahead == 'p') ADVANCE(26);
      END_STATE();
    case 211:
      if (lookahead == 'p') ADVANCE(223);
      if (lookahead == 's') ADVANCE(122);
      END_STATE();
    case 212:
      if (lookahead == 'p') ADVANCE(104);
      END_STATE();
    case 213:
      if (lookahead == 'q') ADVANCE(270);
      END_STATE();
    case 214:
      if (lookahead == 'r') ADVANCE(188);
      END_STATE();
    case 215:
      if (lookahead == 'r') ADVANCE(312);
      END_STATE();
    case 216:
      if (lookahead == 'r') ADVANCE(181);
      END_STATE();
    case 217:
      if (lookahead == 'r') ADVANCE(277);
      END_STATE();
    case 218:
      if (lookahead == 'r') ADVANCE(152);
      END_STATE();
    case 219:
      if (lookahead == 'r') ADVANCE(64);
      END_STATE();
    case 220:
      if (lookahead == 'r') ADVANCE(248);
      END_STATE();
    case 221:
      if (lookahead == 'r') ADVANCE(183);
      END_STATE();
    case 222:
      if (lookahead == 'r') ADVANCE(187);
      END_STATE();
    case 223:
      if (lookahead == 'r') ADVANCE(202);
      END_STATE();
    case 224:
      if (lookahead == 'r') ADVANCE(95);
      END_STATE();
    case 225:
      if (lookahead == 'r') ADVANCE(198);
      END_STATE();
    case 226:
      if (lookahead == 'r') ADVANCE(44);
      END_STATE();
    case 227:
      if (lookahead == 'r') ADVANCE(247);
      END_STATE();
    case 228:
      if (lookahead == 'r') ADVANCE(94);
      END_STATE();
    case 229:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 230:
      if (lookahead == 'r') ADVANCE(130);
      END_STATE();
    case 231:
      if (lookahead == 'r') ADVANCE(185);
      END_STATE();
    case 232:
      if (lookahead == 's') ADVANCE(310);
      END_STATE();
    case 233:
      if (lookahead == 's') ADVANCE(232);
      END_STATE();
    case 234:
      if (lookahead == 's') ADVANCE(250);
      END_STATE();
    case 235:
      if (lookahead == 's') ADVANCE(210);
      END_STATE();
    case 236:
      if (lookahead == 's') ADVANCE(208);
      END_STATE();
    case 237:
      if (lookahead == 's') ADVANCE(244);
      END_STATE();
    case 238:
      if (lookahead == 's') ADVANCE(86);
      END_STATE();
    case 239:
      if (lookahead == 's') ADVANCE(87);
      END_STATE();
    case 240:
      if (lookahead == 't') ADVANCE(310);
      END_STATE();
    case 241:
      if (lookahead == 't') ADVANCE(296);
      END_STATE();
    case 242:
      if (lookahead == 't') ADVANCE(271);
      END_STATE();
    case 243:
      if (lookahead == 't') ADVANCE(120);
      END_STATE();
    case 244:
      if (lookahead == 't') ADVANCE(297);
      END_STATE();
    case 245:
      if (lookahead == 't') ADVANCE(279);
      END_STATE();
    case 246:
      if (lookahead == 't') ADVANCE(232);
      END_STATE();
    case 247:
      if (lookahead == 't') ADVANCE(277);
      END_STATE();
    case 248:
      if (lookahead == 't') ADVANCE(210);
      END_STATE();
    case 249:
      if (lookahead == 't') ADVANCE(78);
      END_STATE();
    case 250:
      if (lookahead == 't') ADVANCE(226);
      END_STATE();
    case 251:
      if (lookahead == 't') ADVANCE(23);
      END_STATE();
    case 252:
      if (lookahead == 't') ADVANCE(136);
      END_STATE();
    case 253:
      if (lookahead == 't') ADVANCE(51);
      END_STATE();
    case 254:
      if (lookahead == 't') ADVANCE(89);
      END_STATE();
    case 255:
      if (lookahead == 't') ADVANCE(94);
      END_STATE();
    case 256:
      if (lookahead == 't') ADVANCE(36);
      END_STATE();
    case 257:
      if (lookahead == 't') ADVANCE(149);
      END_STATE();
    case 258:
      if (lookahead == 't') ADVANCE(256);
      END_STATE();
    case 259:
      if (lookahead == 't') ADVANCE(225);
      END_STATE();
    case 260:
      if (lookahead == 't') ADVANCE(138);
      END_STATE();
    case 261:
      if (lookahead == 't') ADVANCE(139);
      END_STATE();
    case 262:
      if (lookahead == 't') ADVANCE(52);
      END_STATE();
    case 263:
      if (lookahead == 'u') ADVANCE(161);
      END_STATE();
    case 264:
      if (lookahead == 'u') ADVANCE(204);
      END_STATE();
    case 265:
      if (lookahead == 'u') ADVANCE(78);
      END_STATE();
    case 266:
      if (lookahead == 'u') ADVANCE(135);
      END_STATE();
    case 267:
      if (lookahead == 'u') ADVANCE(102);
      END_STATE();
    case 268:
      if (lookahead == 'u') ADVANCE(149);
      END_STATE();
    case 269:
      if (lookahead == 'u') ADVANCE(235);
      END_STATE();
    case 270:
      if (lookahead == 'u') ADVANCE(203);
      END_STATE();
    case 271:
      if (lookahead == 'v') ADVANCE(45);
      END_STATE();
    case 272:
      if (lookahead == 'w') ADVANCE(310);
      END_STATE();
    case 273:
      if (lookahead == 'w') ADVANCE(300);
      END_STATE();
    case 274:
      if (lookahead == 'w') ADVANCE(301);
      END_STATE();
    case 275:
      if (lookahead == 'w') ADVANCE(196);
      END_STATE();
    case 276:
      if (lookahead == 'x') ADVANCE(248);
      END_STATE();
    case 277:
      if (lookahead == 'y') ADVANCE(310);
      END_STATE();
    case 278:
      if (lookahead == 'y') ADVANCE(275);
      END_STATE();
    case 279:
      if (lookahead == 'y') ADVANCE(206);
      END_STATE();
    case 280:
      if (lookahead == '{') ADVANCE(284);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(280)
      if (lookahead != 0 &&
          lookahead != '\\' &&
          lookahead != '}') ADVANCE(341);
      END_STATE();
    case 281:
      if (lookahead == '}') ADVANCE(332);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(281);
      END_STATE();
    case 282:
      if (lookahead == '}') ADVANCE(329);
      if (lookahead != 0) ADVANCE(282);
      END_STATE();
    case 283:
      if (lookahead == '}') ADVANCE(328);
      if (lookahead != 0) ADVANCE(283);
      END_STATE();
    case 284:
      if (lookahead == '}') ADVANCE(340);
      if (lookahead != 0) ADVANCE(284);
      END_STATE();
    case 285:
      if (lookahead == 'b' ||
          lookahead == 'p') ADVANCE(314);
      END_STATE();
    case 286:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(286)
      if (lookahead != 0) ADVANCE(327);
      END_STATE();
    case 287:
      if (('1' <= lookahead && lookahead <= '4')) ADVANCE(310);
      END_STATE();
    case 288:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 289:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(281);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(anon_sym_SLASH_STAR_BANG);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(anon_sym_STAR_SLASH);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(anon_sym_STAR_SLASH);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(339);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(339);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(anon_sym_list);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(anon_sym_endlist);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(anon_sym_table);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(anon_sym_endtable);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(anon_sym_raw);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(anon_sym_endraw);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(anon_sym_legalese);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(anon_sym_endlegalese);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(anon_sym_quotation);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(anon_sym_endquotation);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(sym_raw_content_chunk);
      if (lookahead == '\\') ADVANCE(282);
      if (lookahead == '}') ADVANCE(329);
      if (lookahead != 0) ADVANCE(306);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(sym_raw_content_chunk);
      if (lookahead == '{') ADVANCE(306);
      if (lookahead == '}') ADVANCE(309);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(307);
      if (lookahead != 0 &&
          lookahead != '\\') ADVANCE(331);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(sym_raw_content_chunk);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(308);
      if (lookahead != 0 &&
          lookahead != '\\') ADVANCE(309);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(sym_raw_content_chunk);
      if (lookahead != 0 &&
          lookahead != '\\') ADVANCE(309);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(sym_command_name);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 'a') ADVANCE(258);
      if (lookahead == 'e') ADVANCE(178);
      if (lookahead == 'm') ADVANCE(99);
      if (lookahead == 'p') ADVANCE(223);
      if (lookahead == 's') ADVANCE(122);
      if (lookahead == 't') ADVANCE(279);
      if (lookahead == 'v') ADVANCE(35);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 'f') ADVANCE(134);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 's') ADVANCE(241);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(sym_inline_command_name);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'a') ADVANCE(71);
      if (lookahead == 'r') ADVANCE(125);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'b') ADVANCE(234);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'e') ADVANCE(114);
      if (lookahead == 'i') ADVANCE(313);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'l') ADVANCE(25);
      if (lookahead == 'o') ADVANCE(69);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'n') ADVANCE(65);
      if (lookahead == 'x') ADVANCE(29);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'n') ADVANCE(70);
      if (lookahead == 'x') ADVANCE(29);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'n') ADVANCE(67);
      if (lookahead == 'x') ADVANCE(29);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'n') ADVANCE(75);
      if (lookahead == 'x') ADVANCE(29);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'n') ADVANCE(263);
      if (lookahead == 'x') ADVANCE(29);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'n') ADVANCE(76);
      if (lookahead == 'x') ADVANCE(29);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(anon_sym_image);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(anon_sym_inlineimage);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(sym_image_content);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\\') ADVANCE(327);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(sym_image_alt);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(sym_block_argument);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(sym_block_argument);
      if (lookahead == '*') ADVANCE(331);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '\\' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(330);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(sym_block_argument);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '\\' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(331);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(sym_cell_span);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == ',') ADVANCE(337);
      if (lookahead == '*' ||
          lookahead == '\\') ADVANCE(339);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(348);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(333);
      if (lookahead != 0) ADVANCE(338);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == '/') ADVANCE(293);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(339);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == '}') ADVANCE(332);
      if (lookahead == '*' ||
          lookahead == '\\') ADVANCE(339);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(348);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(335);
      if (lookahead != 0) ADVANCE(338);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == '*' ||
          lookahead == '\\') ADVANCE(339);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(348);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(333);
      if (lookahead != 0) ADVANCE(338);
      END_STATE();
    case 337:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == '*' ||
          lookahead == '\\') ADVANCE(339);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(348);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(335);
      if (lookahead != 0) ADVANCE(338);
      END_STATE();
    case 338:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == '*' ||
          lookahead == '\\') ADVANCE(339);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(348);
      if (lookahead != 0) ADVANCE(338);
      END_STATE();
    case 339:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(339);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(sym_inline_text);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(sym_inline_text);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '\\' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(341);
      END_STATE();
    case 342:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '*') ADVANCE(331);
      if (lookahead == '{') ADVANCE(345);
      if (lookahead == '}') ADVANCE(348);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(342);
      if (lookahead != 0 &&
          lookahead != '\\') ADVANCE(330);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '{') ADVANCE(336);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(343);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(338);
      END_STATE();
    case 344:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '{') ADVANCE(346);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(344);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(348);
      END_STATE();
    case 345:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '}') ADVANCE(329);
      if (lookahead == '*' ||
          lookahead == '\\') ADVANCE(282);
      if (lookahead != 0) ADVANCE(345);
      END_STATE();
    case 346:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '}') ADVANCE(328);
      if (lookahead == '*' ||
          lookahead == '\\') ADVANCE(283);
      if (lookahead != 0) ADVANCE(346);
      END_STATE();
    case 347:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(347);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(348);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(sym_text);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(348);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 3},
  [3] = {.lex_state = 3},
  [4] = {.lex_state = 5},
  [5] = {.lex_state = 5},
  [6] = {.lex_state = 3},
  [7] = {.lex_state = 3},
  [8] = {.lex_state = 3},
  [9] = {.lex_state = 3},
  [10] = {.lex_state = 3},
  [11] = {.lex_state = 3},
  [12] = {.lex_state = 3},
  [13] = {.lex_state = 3},
  [14] = {.lex_state = 3},
  [15] = {.lex_state = 3},
  [16] = {.lex_state = 3},
  [17] = {.lex_state = 3},
  [18] = {.lex_state = 13},
  [19] = {.lex_state = 14},
  [20] = {.lex_state = 15},
  [21] = {.lex_state = 16},
  [22] = {.lex_state = 13},
  [23] = {.lex_state = 16},
  [24] = {.lex_state = 16},
  [25] = {.lex_state = 16},
  [26] = {.lex_state = 13},
  [27] = {.lex_state = 15},
  [28] = {.lex_state = 14},
  [29] = {.lex_state = 13},
  [30] = {.lex_state = 12},
  [31] = {.lex_state = 12},
  [32] = {.lex_state = 6},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 10},
  [36] = {.lex_state = 2},
  [37] = {.lex_state = 7},
  [38] = {.lex_state = 3},
  [39] = {.lex_state = 11},
  [40] = {.lex_state = 3},
  [41] = {.lex_state = 3},
  [42] = {.lex_state = 3},
  [43] = {.lex_state = 3},
  [44] = {.lex_state = 3},
  [45] = {.lex_state = 3},
  [46] = {.lex_state = 11},
  [47] = {.lex_state = 11},
  [48] = {.lex_state = 3},
  [49] = {.lex_state = 3},
  [50] = {.lex_state = 3},
  [51] = {.lex_state = 11},
  [52] = {.lex_state = 3},
  [53] = {.lex_state = 3},
  [54] = {.lex_state = 3},
  [55] = {.lex_state = 3},
  [56] = {.lex_state = 3},
  [57] = {.lex_state = 3},
  [58] = {.lex_state = 3},
  [59] = {.lex_state = 3},
  [60] = {.lex_state = 3},
  [61] = {.lex_state = 3},
  [62] = {.lex_state = 3},
  [63] = {.lex_state = 3},
  [64] = {.lex_state = 3},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 286},
  [69] = {.lex_state = 280},
  [70] = {.lex_state = 101},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 280},
  [73] = {.lex_state = 101},
  [74] = {.lex_state = 101},
  [75] = {.lex_state = 101},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_SLASH_STAR_BANG] = ACTIONS(1),
    [anon_sym_STAR_SLASH] = ACTIONS(1),
    [anon_sym_BSLASH] = ACTIONS(1),
    [anon_sym_list] = ACTIONS(1),
    [anon_sym_endlist] = ACTIONS(1),
    [anon_sym_table] = ACTIONS(1),
    [anon_sym_endtable] = ACTIONS(1),
    [anon_sym_raw] = ACTIONS(1),
    [anon_sym_legalese] = ACTIONS(1),
    [anon_sym_endlegalese] = ACTIONS(1),
    [anon_sym_quotation] = ACTIONS(1),
    [anon_sym_endquotation] = ACTIONS(1),
    [sym_command_name] = ACTIONS(1),
    [sym_inline_command_name] = ACTIONS(1),
    [anon_sym_image] = ACTIONS(1),
    [anon_sym_inlineimage] = ACTIONS(1),
    [sym_cell_span] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(71),
    [sym_comment] = STATE(34),
    [sym_block_comment] = STATE(67),
    [aux_sym_source_file_repeat1] = STATE(34),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_SLASH_STAR_BANG] = ACTIONS(5),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 6,
    ACTIONS(7), 1,
      anon_sym_STAR_SLASH,
    ACTIONS(9), 1,
      anon_sym_BSLASH,
    ACTIONS(11), 1,
      sym_text,
    STATE(3), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [28] = 6,
    ACTIONS(9), 1,
      anon_sym_BSLASH,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(13), 1,
      anon_sym_STAR_SLASH,
    STATE(6), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [56] = 6,
    ACTIONS(15), 1,
      anon_sym_BSLASH,
    ACTIONS(17), 1,
      sym_block_argument,
    ACTIONS(19), 1,
      sym_text,
    STATE(14), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [84] = 6,
    ACTIONS(19), 1,
      sym_text,
    ACTIONS(21), 1,
      anon_sym_BSLASH,
    ACTIONS(23), 1,
      sym_block_argument,
    STATE(12), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [112] = 6,
    ACTIONS(25), 1,
      anon_sym_STAR_SLASH,
    ACTIONS(27), 1,
      anon_sym_BSLASH,
    ACTIONS(30), 1,
      sym_text,
    STATE(6), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [140] = 5,
    ACTIONS(30), 1,
      sym_text,
    ACTIONS(33), 1,
      anon_sym_BSLASH,
    STATE(7), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [165] = 5,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(36), 1,
      anon_sym_BSLASH,
    STATE(7), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [190] = 5,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(38), 1,
      anon_sym_BSLASH,
    STATE(7), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [215] = 5,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(40), 1,
      anon_sym_BSLASH,
    STATE(7), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [240] = 5,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(42), 1,
      anon_sym_BSLASH,
    STATE(7), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [265] = 5,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(44), 1,
      anon_sym_BSLASH,
    STATE(7), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [290] = 5,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(46), 1,
      anon_sym_BSLASH,
    STATE(11), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [315] = 5,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(48), 1,
      anon_sym_BSLASH,
    STATE(7), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [340] = 5,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(50), 1,
      anon_sym_BSLASH,
    STATE(8), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [365] = 5,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(52), 1,
      anon_sym_BSLASH,
    STATE(10), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [390] = 5,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(54), 1,
      anon_sym_BSLASH,
    STATE(9), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(50), 5,
      sym_block_command,
      sym_command,
      sym_inline_command,
      sym_image_command,
      sym_inlineimage_command,
    STATE(62), 5,
      sym_list_block,
      sym_table_block,
      sym_raw_block,
      sym_legalese_block,
      sym_quotation_block,
  [415] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(58), 1,
      anon_sym_endlist,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
  [446] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(76), 1,
      anon_sym_endquotation,
  [477] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(78), 1,
      anon_sym_endlegalese,
  [508] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(80), 1,
      anon_sym_endtable,
  [539] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(82), 1,
      anon_sym_endlist,
  [570] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(84), 1,
      anon_sym_endtable,
  [601] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(86), 1,
      anon_sym_endtable,
  [632] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(88), 1,
      anon_sym_endtable,
  [663] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(90), 1,
      anon_sym_endlist,
  [694] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(92), 1,
      anon_sym_endlegalese,
  [725] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(94), 1,
      anon_sym_endquotation,
  [756] = 10,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(96), 1,
      anon_sym_endlist,
  [787] = 9,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(68), 1,
      sym_command_name,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
  [815] = 9,
    ACTIONS(56), 1,
      anon_sym_list,
    ACTIONS(60), 1,
      anon_sym_table,
    ACTIONS(62), 1,
      anon_sym_raw,
    ACTIONS(64), 1,
      anon_sym_legalese,
    ACTIONS(66), 1,
      anon_sym_quotation,
    ACTIONS(70), 1,
      sym_inline_command_name,
    ACTIONS(72), 1,
      anon_sym_image,
    ACTIONS(74), 1,
      anon_sym_inlineimage,
    ACTIONS(98), 1,
      sym_command_name,
  [843] = 3,
    ACTIONS(102), 1,
      sym_cell_span,
    ACTIONS(104), 1,
      sym_command_argument,
    ACTIONS(100), 3,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
      sym_text,
  [855] = 4,
    ACTIONS(106), 1,
      ts_builtin_sym_end,
    ACTIONS(108), 1,
      anon_sym_SLASH_STAR_BANG,
    STATE(67), 1,
      sym_block_comment,
    STATE(33), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [869] = 4,
    ACTIONS(5), 1,
      anon_sym_SLASH_STAR_BANG,
    ACTIONS(111), 1,
      ts_builtin_sym_end,
    STATE(67), 1,
      sym_block_comment,
    STATE(33), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [883] = 4,
    ACTIONS(113), 1,
      anon_sym_BSLASH,
    ACTIONS(115), 1,
      sym_raw_content_chunk,
    ACTIONS(117), 1,
      sym_block_argument,
    STATE(46), 1,
      aux_sym_raw_block_repeat1,
  [896] = 2,
    ACTIONS(121), 1,
      sym_image_alt,
    ACTIONS(119), 3,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
      sym_text,
  [905] = 3,
    ACTIONS(102), 1,
      sym_cell_span,
    ACTIONS(104), 1,
      sym_command_argument,
    ACTIONS(100), 2,
      anon_sym_BSLASH,
      sym_text,
  [916] = 2,
    ACTIONS(125), 1,
      sym_text,
    ACTIONS(123), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [924] = 3,
    ACTIONS(127), 1,
      anon_sym_BSLASH,
    ACTIONS(129), 1,
      sym_raw_content_chunk,
    STATE(39), 1,
      aux_sym_raw_block_repeat1,
  [934] = 2,
    ACTIONS(134), 1,
      sym_text,
    ACTIONS(132), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [942] = 2,
    ACTIONS(138), 1,
      sym_text,
    ACTIONS(136), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [950] = 2,
    ACTIONS(142), 1,
      sym_text,
    ACTIONS(140), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [958] = 2,
    ACTIONS(146), 1,
      sym_text,
    ACTIONS(144), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [966] = 2,
    ACTIONS(150), 1,
      sym_text,
    ACTIONS(148), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [974] = 2,
    ACTIONS(154), 1,
      sym_text,
    ACTIONS(152), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [982] = 3,
    ACTIONS(156), 1,
      anon_sym_BSLASH,
    ACTIONS(158), 1,
      sym_raw_content_chunk,
    STATE(39), 1,
      aux_sym_raw_block_repeat1,
  [992] = 3,
    ACTIONS(160), 1,
      anon_sym_BSLASH,
    ACTIONS(162), 1,
      sym_raw_content_chunk,
    STATE(51), 1,
      aux_sym_raw_block_repeat1,
  [1002] = 2,
    ACTIONS(166), 1,
      sym_text,
    ACTIONS(164), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1010] = 2,
    ACTIONS(170), 1,
      sym_text,
    ACTIONS(168), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1018] = 2,
    ACTIONS(174), 1,
      sym_text,
    ACTIONS(172), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1026] = 3,
    ACTIONS(158), 1,
      sym_raw_content_chunk,
    ACTIONS(176), 1,
      anon_sym_BSLASH,
    STATE(39), 1,
      aux_sym_raw_block_repeat1,
  [1036] = 2,
    ACTIONS(180), 1,
      sym_text,
    ACTIONS(178), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1044] = 2,
    ACTIONS(184), 1,
      sym_text,
    ACTIONS(182), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1052] = 2,
    ACTIONS(188), 1,
      sym_text,
    ACTIONS(186), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1060] = 2,
    ACTIONS(192), 1,
      sym_text,
    ACTIONS(190), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1068] = 2,
    ACTIONS(196), 1,
      sym_text,
    ACTIONS(194), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1076] = 2,
    ACTIONS(200), 1,
      sym_text,
    ACTIONS(198), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1084] = 2,
    ACTIONS(204), 1,
      sym_text,
    ACTIONS(202), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1092] = 2,
    ACTIONS(208), 1,
      sym_text,
    ACTIONS(206), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1100] = 2,
    ACTIONS(212), 1,
      sym_text,
    ACTIONS(210), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1108] = 2,
    ACTIONS(216), 1,
      sym_text,
    ACTIONS(214), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1116] = 2,
    ACTIONS(220), 1,
      sym_text,
    ACTIONS(218), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1124] = 2,
    ACTIONS(224), 1,
      sym_text,
    ACTIONS(222), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1132] = 2,
    ACTIONS(228), 1,
      sym_text,
    ACTIONS(226), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [1140] = 1,
    ACTIONS(230), 2,
      ts_builtin_sym_end,
      anon_sym_SLASH_STAR_BANG,
  [1145] = 1,
    ACTIONS(232), 2,
      ts_builtin_sym_end,
      anon_sym_SLASH_STAR_BANG,
  [1150] = 1,
    ACTIONS(234), 2,
      ts_builtin_sym_end,
      anon_sym_SLASH_STAR_BANG,
  [1155] = 1,
    ACTIONS(236), 1,
      sym_image_content,
  [1159] = 1,
    ACTIONS(238), 1,
      sym_inline_text,
  [1163] = 1,
    ACTIONS(240), 1,
      anon_sym_endraw,
  [1167] = 1,
    ACTIONS(242), 1,
      ts_builtin_sym_end,
  [1171] = 1,
    ACTIONS(244), 1,
      sym_inline_text,
  [1175] = 1,
    ACTIONS(246), 1,
      anon_sym_endraw,
  [1179] = 1,
    ACTIONS(248), 1,
      anon_sym_endraw,
  [1183] = 1,
    ACTIONS(250), 1,
      anon_sym_endraw,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 28,
  [SMALL_STATE(4)] = 56,
  [SMALL_STATE(5)] = 84,
  [SMALL_STATE(6)] = 112,
  [SMALL_STATE(7)] = 140,
  [SMALL_STATE(8)] = 165,
  [SMALL_STATE(9)] = 190,
  [SMALL_STATE(10)] = 215,
  [SMALL_STATE(11)] = 240,
  [SMALL_STATE(12)] = 265,
  [SMALL_STATE(13)] = 290,
  [SMALL_STATE(14)] = 315,
  [SMALL_STATE(15)] = 340,
  [SMALL_STATE(16)] = 365,
  [SMALL_STATE(17)] = 390,
  [SMALL_STATE(18)] = 415,
  [SMALL_STATE(19)] = 446,
  [SMALL_STATE(20)] = 477,
  [SMALL_STATE(21)] = 508,
  [SMALL_STATE(22)] = 539,
  [SMALL_STATE(23)] = 570,
  [SMALL_STATE(24)] = 601,
  [SMALL_STATE(25)] = 632,
  [SMALL_STATE(26)] = 663,
  [SMALL_STATE(27)] = 694,
  [SMALL_STATE(28)] = 725,
  [SMALL_STATE(29)] = 756,
  [SMALL_STATE(30)] = 787,
  [SMALL_STATE(31)] = 815,
  [SMALL_STATE(32)] = 843,
  [SMALL_STATE(33)] = 855,
  [SMALL_STATE(34)] = 869,
  [SMALL_STATE(35)] = 883,
  [SMALL_STATE(36)] = 896,
  [SMALL_STATE(37)] = 905,
  [SMALL_STATE(38)] = 916,
  [SMALL_STATE(39)] = 924,
  [SMALL_STATE(40)] = 934,
  [SMALL_STATE(41)] = 942,
  [SMALL_STATE(42)] = 950,
  [SMALL_STATE(43)] = 958,
  [SMALL_STATE(44)] = 966,
  [SMALL_STATE(45)] = 974,
  [SMALL_STATE(46)] = 982,
  [SMALL_STATE(47)] = 992,
  [SMALL_STATE(48)] = 1002,
  [SMALL_STATE(49)] = 1010,
  [SMALL_STATE(50)] = 1018,
  [SMALL_STATE(51)] = 1026,
  [SMALL_STATE(52)] = 1036,
  [SMALL_STATE(53)] = 1044,
  [SMALL_STATE(54)] = 1052,
  [SMALL_STATE(55)] = 1060,
  [SMALL_STATE(56)] = 1068,
  [SMALL_STATE(57)] = 1076,
  [SMALL_STATE(58)] = 1084,
  [SMALL_STATE(59)] = 1092,
  [SMALL_STATE(60)] = 1100,
  [SMALL_STATE(61)] = 1108,
  [SMALL_STATE(62)] = 1116,
  [SMALL_STATE(63)] = 1124,
  [SMALL_STATE(64)] = 1132,
  [SMALL_STATE(65)] = 1140,
  [SMALL_STATE(66)] = 1145,
  [SMALL_STATE(67)] = 1150,
  [SMALL_STATE(68)] = 1155,
  [SMALL_STATE(69)] = 1159,
  [SMALL_STATE(70)] = 1163,
  [SMALL_STATE(71)] = 1167,
  [SMALL_STATE(72)] = 1171,
  [SMALL_STATE(73)] = 1175,
  [SMALL_STATE(74)] = 1179,
  [SMALL_STATE(75)] = 1183,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(66),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [25] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_block_comment_repeat1, 2),
  [27] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_comment_repeat1, 2), SHIFT_REPEAT(31),
  [30] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_comment_repeat1, 2), SHIFT_REPEAT(50),
  [33] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_comment_repeat1, 2), SHIFT_REPEAT(30),
  [36] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [38] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [40] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [42] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [44] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [46] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [48] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [50] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [52] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [54] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [56] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [60] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [64] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [68] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [70] = {.entry = {.count = 1, .reusable = false}}, SHIFT(69),
  [72] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [74] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [78] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [80] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [82] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [84] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [88] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [90] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [92] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [94] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [96] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [98] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [100] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 2),
  [102] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [104] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [108] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(2),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [113] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [115] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [117] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [119] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_inlineimage_command, 3, .production_id = 3),
  [121] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [123] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_quotation_block, 4),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_quotation_block, 4),
  [127] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_raw_block_repeat1, 2),
  [129] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_raw_block_repeat1, 2), SHIFT_REPEAT(39),
  [132] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_quotation_block, 5),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_quotation_block, 5),
  [136] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list_block, 4),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_block, 4),
  [140] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_inline_command, 3),
  [142] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_inline_command, 3),
  [144] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3),
  [146] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3),
  [148] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, .production_id = 1),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, .production_id = 1),
  [152] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_table_block, 4),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_block, 4),
  [156] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [160] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [164] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_legalese_block, 5),
  [166] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_legalese_block, 5),
  [168] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_raw_block, 4),
  [170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_raw_block, 4),
  [172] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_markup, 1),
  [174] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_markup, 1),
  [176] = {.entry = {.count = 1, .reusable = false}}, SHIFT(70),
  [178] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_raw_block, 6, .production_id = 5),
  [180] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_raw_block, 6, .production_id = 5),
  [182] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list_block, 6, .production_id = 5),
  [184] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_block, 6, .production_id = 5),
  [186] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_legalese_block, 4),
  [188] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_legalese_block, 4),
  [190] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_raw_block, 5),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_raw_block, 5),
  [194] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_table_block, 6, .production_id = 5),
  [196] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_block, 6, .production_id = 5),
  [198] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_image_command, 3, .production_id = 2),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_image_command, 3, .production_id = 2),
  [202] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_inlineimage_command, 4, .production_id = 4),
  [204] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_inlineimage_command, 4, .production_id = 4),
  [206] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list_block, 5, .production_id = 5),
  [208] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_block, 5, .production_id = 5),
  [210] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list_block, 5),
  [212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_block, 5),
  [214] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_table_block, 5, .production_id = 5),
  [216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_block, 5, .production_id = 5),
  [218] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_command, 1),
  [220] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_command, 1),
  [222] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_table_block, 5),
  [224] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_table_block, 5),
  [226] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_raw_block, 5, .production_id = 5),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_raw_block, 5, .production_id = 5),
  [230] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_comment, 3),
  [232] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_comment, 2),
  [234] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 1),
  [236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [240] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [242] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_qdoc(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
