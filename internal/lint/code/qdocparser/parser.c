#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 17
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 17
#define ALIAS_COUNT 0
#define TOKEN_COUNT 9
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 3
#define PRODUCTION_ID_COUNT 1

enum {
  anon_sym_SLASH_STAR_BANG = 1,
  anon_sym_STAR_SLASH = 2,
  anon_sym_BSLASH = 3,
  sym_command_name = 4,
  sym_inline_command_name = 5,
  sym_command_argument = 6,
  sym_inline_text = 7,
  sym_text = 8,
  sym_source_file = 9,
  sym_comment = 10,
  sym_block_comment = 11,
  sym_markup = 12,
  sym_command = 13,
  sym_inline_command = 14,
  aux_sym_source_file_repeat1 = 15,
  aux_sym_block_comment_repeat1 = 16,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_SLASH_STAR_BANG] = "/*!",
  [anon_sym_STAR_SLASH] = "*/",
  [anon_sym_BSLASH] = "\\",
  [sym_command_name] = "command_name",
  [sym_inline_command_name] = "inline_command_name",
  [sym_command_argument] = "command_argument",
  [sym_inline_text] = "inline_text",
  [sym_text] = "text",
  [sym_source_file] = "source_file",
  [sym_comment] = "comment",
  [sym_block_comment] = "block_comment",
  [sym_markup] = "markup",
  [sym_command] = "command",
  [sym_inline_command] = "inline_command",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_block_comment_repeat1] = "block_comment_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_SLASH_STAR_BANG] = anon_sym_SLASH_STAR_BANG,
  [anon_sym_STAR_SLASH] = anon_sym_STAR_SLASH,
  [anon_sym_BSLASH] = anon_sym_BSLASH,
  [sym_command_name] = sym_command_name,
  [sym_inline_command_name] = sym_inline_command_name,
  [sym_command_argument] = sym_command_argument,
  [sym_inline_text] = sym_inline_text,
  [sym_text] = sym_text,
  [sym_source_file] = sym_source_file,
  [sym_comment] = sym_comment,
  [sym_block_comment] = sym_block_comment,
  [sym_markup] = sym_markup,
  [sym_command] = sym_command,
  [sym_inline_command] = sym_inline_command,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_block_comment_repeat1] = aux_sym_block_comment_repeat1,
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
  [sym_command_name] = {
    .visible = true,
    .named = true,
  },
  [sym_inline_command_name] = {
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
  [sym_command] = {
    .visible = true,
    .named = true,
  },
  [sym_inline_command] = {
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
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(217);
      if (lookahead == '*') ADVANCE(5);
      if (lookahead == '/') ADVANCE(3);
      if (lookahead == '\\') ADVANCE(221);
      if (lookahead == 'a') ADVANCE(230);
      if (lookahead == 'b') ADVANCE(229);
      if (lookahead == 'c') ADVANCE(231);
      if (lookahead == 'd') ADVANCE(52);
      if (lookahead == 'e') ADVANCE(232);
      if (lookahead == 'f') ADVANCE(123);
      if (lookahead == 'g') ADVANCE(158);
      if (lookahead == 'h') ADVANCE(61);
      if (lookahead == 'i') ADVANCE(124);
      if (lookahead == 'k') ADVANCE(54);
      if (lookahead == 'l') ADVANCE(225);
      if (lookahead == 'm') ADVANCE(7);
      if (lookahead == 'n') ADVANCE(8);
      if (lookahead == 'o') ADVANCE(115);
      if (lookahead == 'p') ADVANCE(15);
      if (lookahead == 'q') ADVANCE(114);
      if (lookahead == 'r') ADVANCE(55);
      if (lookahead == 's') ADVANCE(6);
      if (lookahead == 't') ADVANCE(9);
      if (lookahead == 'u') ADVANCE(86);
      if (lookahead == 'v') ADVANCE(10);
      if (lookahead == 'w') ADVANCE(12);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == '!') ADVANCE(218);
      END_STATE();
    case 2:
      if (lookahead == '*') ADVANCE(5);
      if (lookahead == '\\') ADVANCE(221);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(238);
      if (lookahead != 0) ADVANCE(240);
      END_STATE();
    case 3:
      if (lookahead == '*') ADVANCE(1);
      END_STATE();
    case 4:
      if (lookahead == '*') ADVANCE(233);
      if (lookahead == '\\') ADVANCE(222);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(239);
      if (lookahead != 0) ADVANCE(234);
      END_STATE();
    case 5:
      if (lookahead == '/') ADVANCE(219);
      END_STATE();
    case 6:
      if (lookahead == 'a') ADVANCE(223);
      if (lookahead == 'e') ADVANCE(42);
      if (lookahead == 'i') ADVANCE(127);
      if (lookahead == 't') ADVANCE(20);
      if (lookahead == 'u') ADVANCE(215);
      END_STATE();
    case 7:
      if (lookahead == 'a') ADVANCE(43);
      if (lookahead == 'o') ADVANCE(47);
      END_STATE();
    case 8:
      if (lookahead == 'a') ADVANCE(120);
      if (lookahead == 'e') ADVANCE(209);
      if (lookahead == 'o') ADVANCE(189);
      END_STATE();
    case 9:
      if (lookahead == 'a') ADVANCE(36);
      if (lookahead == 'i') ADVANCE(185);
      if (lookahead == 'm' ||
          lookahead == 't') ADVANCE(228);
      if (lookahead == 'y') ADVANCE(153);
      END_STATE();
    case 10:
      if (lookahead == 'a') ADVANCE(106);
      END_STATE();
    case 11:
      if (lookahead == 'a') ADVANCE(35);
      END_STATE();
    case 12:
      if (lookahead == 'a') ADVANCE(161);
      END_STATE();
    case 13:
      if (lookahead == 'a') ADVANCE(176);
      END_STATE();
    case 14:
      if (lookahead == 'a') ADVANCE(78);
      END_STATE();
    case 15:
      if (lookahead == 'a') ADVANCE(78);
      if (lookahead == 'r') ADVANCE(56);
      END_STATE();
    case 16:
      if (lookahead == 'a') ADVANCE(175);
      END_STATE();
    case 17:
      if (lookahead == 'a') ADVANCE(116);
      if (lookahead == 't') ADVANCE(72);
      END_STATE();
    case 18:
      if (lookahead == 'a') ADVANCE(50);
      if (lookahead == 'i') ADVANCE(119);
      if (lookahead == 'l') ADVANCE(28);
      if (lookahead == 'q') ADVANCE(203);
      END_STATE();
    case 19:
      if (lookahead == 'a') ADVANCE(41);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(164);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(45);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(112);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(37);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(111);
      if (lookahead == 'd') ADVANCE(57);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(104);
      END_STATE();
    case 26:
      if (lookahead == 'a') ADVANCE(99);
      END_STATE();
    case 27:
      if (lookahead == 'a') ADVANCE(160);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(194);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(51);
      END_STATE();
    case 30:
      if (lookahead == 'a') ADVANCE(39);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(110);
      END_STATE();
    case 32:
      if (lookahead == 'a') ADVANCE(105);
      END_STATE();
    case 33:
      if (lookahead == 'a') ADVANCE(193);
      END_STATE();
    case 34:
      if (lookahead == 'a') ADVANCE(195);
      END_STATE();
    case 35:
      if (lookahead == 'b') ADVANCE(107);
      END_STATE();
    case 36:
      if (lookahead == 'b') ADVANCE(107);
      if (lookahead == 'r') ADVANCE(80);
      END_STATE();
    case 37:
      if (lookahead == 'c') ADVANCE(83);
      END_STATE();
    case 38:
      if (lookahead == 'c') ADVANCE(140);
      END_STATE();
    case 39:
      if (lookahead == 'c') ADVANCE(181);
      END_STATE();
    case 40:
      if (lookahead == 'c') ADVANCE(136);
      END_STATE();
    case 41:
      if (lookahead == 'c') ADVANCE(53);
      END_STATE();
    case 42:
      if (lookahead == 'c') ADVANCE(191);
      END_STATE();
    case 43:
      if (lookahead == 'c') ADVANCE(166);
      END_STATE();
    case 44:
      if (lookahead == 'c') ADVANCE(34);
      END_STATE();
    case 45:
      if (lookahead == 'd') ADVANCE(223);
      END_STATE();
    case 46:
      if (lookahead == 'd') ADVANCE(156);
      END_STATE();
    case 47:
      if (lookahead == 'd') ADVANCE(200);
      END_STATE();
    case 48:
      if (lookahead == 'd') ADVANCE(53);
      END_STATE();
    case 49:
      if (lookahead == 'd') ADVANCE(40);
      END_STATE();
    case 50:
      if (lookahead == 'd') ADVANCE(143);
      END_STATE();
    case 51:
      if (lookahead == 'd') ADVANCE(69);
      END_STATE();
    case 52:
      if (lookahead == 'e') ADVANCE(151);
      END_STATE();
    case 53:
      if (lookahead == 'e') ADVANCE(223);
      END_STATE();
    case 54:
      if (lookahead == 'e') ADVANCE(211);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(18);
      if (lookahead == 'o') ADVANCE(207);
      END_STATE();
    case 56:
      if (lookahead == 'e') ADVANCE(103);
      if (lookahead == 'o') ADVANCE(157);
      END_STATE();
    case 57:
      if (lookahead == 'e') ADVANCE(75);
      END_STATE();
    case 58:
      if (lookahead == 'e') ADVANCE(24);
      END_STATE();
    case 59:
      if (lookahead == 'e') ADVANCE(175);
      END_STATE();
    case 60:
      if (lookahead == 'e') ADVANCE(162);
      END_STATE();
    case 61:
      if (lookahead == 'e') ADVANCE(29);
      END_STATE();
    case 62:
      if (lookahead == 'e') ADVANCE(180);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(181);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(179);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(45);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(44);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(46);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(173);
      END_STATE();
    case 69:
      if (lookahead == 'e') ADVANCE(159);
      END_STATE();
    case 70:
      if (lookahead == 'e') ADVANCE(183);
      if (lookahead == 'o') ADVANCE(47);
      END_STATE();
    case 71:
      if (lookahead == 'e') ADVANCE(184);
      END_STATE();
    case 72:
      if (lookahead == 'e') ADVANCE(165);
      END_STATE();
    case 73:
      if (lookahead == 'e') ADVANCE(171);
      END_STATE();
    case 74:
      if (lookahead == 'e') ADVANCE(174);
      END_STATE();
    case 75:
      if (lookahead == 'f') ADVANCE(223);
      END_STATE();
    case 76:
      if (lookahead == 'g') ADVANCE(158);
      if (lookahead == 'h') ADVANCE(68);
      if (lookahead == 'm') ADVANCE(138);
      if (lookahead == 'q') ADVANCE(118);
      if (lookahead == 't') ADVANCE(74);
      END_STATE();
    case 77:
      if (lookahead == 'g') ADVANCE(223);
      END_STATE();
    case 78:
      if (lookahead == 'g') ADVANCE(53);
      END_STATE();
    case 79:
      if (lookahead == 'g') ADVANCE(31);
      END_STATE();
    case 80:
      if (lookahead == 'g') ADVANCE(63);
      END_STATE();
    case 81:
      if (lookahead == 'g') ADVANCE(132);
      END_STATE();
    case 82:
      if (lookahead == 'h') ADVANCE(139);
      END_STATE();
    case 83:
      if (lookahead == 'h') ADVANCE(67);
      END_STATE();
    case 84:
      if (lookahead == 'i') ADVANCE(107);
      END_STATE();
    case 85:
      if (lookahead == 'i') ADVANCE(81);
      END_STATE();
    case 86:
      if (lookahead == 'i') ADVANCE(38);
      END_STATE();
    case 87:
      if (lookahead == 'i') ADVANCE(57);
      END_STATE();
    case 88:
      if (lookahead == 'i') ADVANCE(182);
      END_STATE();
    case 89:
      if (lookahead == 'i') ADVANCE(121);
      END_STATE();
    case 90:
      if (lookahead == 'i') ADVANCE(126);
      END_STATE();
    case 91:
      if (lookahead == 'i') ADVANCE(11);
      END_STATE();
    case 92:
      if (lookahead == 'i') ADVANCE(134);
      END_STATE();
    case 93:
      if (lookahead == 'i') ADVANCE(186);
      END_STATE();
    case 94:
      if (lookahead == 'i') ADVANCE(16);
      END_STATE();
    case 95:
      if (lookahead == 'i') ADVANCE(141);
      END_STATE();
    case 96:
      if (lookahead == 'i') ADVANCE(172);
      END_STATE();
    case 97:
      if (lookahead == 'i') ADVANCE(145);
      END_STATE();
    case 98:
      if (lookahead == 'i') ADVANCE(133);
      END_STATE();
    case 99:
      if (lookahead == 'l') ADVANCE(223);
      END_STATE();
    case 100:
      if (lookahead == 'l') ADVANCE(228);
      END_STATE();
    case 101:
      if (lookahead == 'l') ADVANCE(224);
      END_STATE();
    case 102:
      if (lookahead == 'l') ADVANCE(210);
      END_STATE();
    case 103:
      if (lookahead == 'l') ADVANCE(89);
      if (lookahead == 'v') ADVANCE(95);
      END_STATE();
    case 104:
      if (lookahead == 'l') ADVANCE(154);
      END_STATE();
    case 105:
      if (lookahead == 'l') ADVANCE(202);
      END_STATE();
    case 106:
      if (lookahead == 'l') ADVANCE(202);
      if (lookahead == 'r') ADVANCE(91);
      END_STATE();
    case 107:
      if (lookahead == 'l') ADVANCE(53);
      END_STATE();
    case 108:
      if (lookahead == 'l') ADVANCE(117);
      END_STATE();
    case 109:
      if (lookahead == 'l') ADVANCE(147);
      END_STATE();
    case 110:
      if (lookahead == 'l') ADVANCE(64);
      END_STATE();
    case 111:
      if (lookahead == 'l') ADVANCE(94);
      END_STATE();
    case 112:
      if (lookahead == 'l') ADVANCE(204);
      END_STATE();
    case 113:
      if (lookahead == 'm') ADVANCE(223);
      END_STATE();
    case 114:
      if (lookahead == 'm') ADVANCE(101);
      if (lookahead == 'u') ADVANCE(142);
      END_STATE();
    case 115:
      if (lookahead == 'm') ADVANCE(88);
      if (lookahead == 'v') ADVANCE(60);
      END_STATE();
    case 116:
      if (lookahead == 'm') ADVANCE(150);
      END_STATE();
    case 117:
      if (lookahead == 'm') ADVANCE(138);
      END_STATE();
    case 118:
      if (lookahead == 'm') ADVANCE(108);
      END_STATE();
    case 119:
      if (lookahead == 'm') ADVANCE(149);
      END_STATE();
    case 120:
      if (lookahead == 'm') ADVANCE(62);
      END_STATE();
    case 121:
      if (lookahead == 'm') ADVANCE(98);
      END_STATE();
    case 122:
      if (lookahead == 'n') ADVANCE(199);
      END_STATE();
    case 123:
      if (lookahead == 'n') ADVANCE(223);
      END_STATE();
    case 124:
      if (lookahead == 'n') ADVANCE(76);
      END_STATE();
    case 125:
      if (lookahead == 'n') ADVANCE(216);
      END_STATE();
    case 126:
      if (lookahead == 'n') ADVANCE(77);
      END_STATE();
    case 127:
      if (lookahead == 'n') ADVANCE(41);
      END_STATE();
    case 128:
      if (lookahead == 'n') ADVANCE(102);
      END_STATE();
    case 129:
      if (lookahead == 'n') ADVANCE(90);
      END_STATE();
    case 130:
      if (lookahead == 'n') ADVANCE(198);
      END_STATE();
    case 131:
      if (lookahead == 'n') ADVANCE(25);
      END_STATE();
    case 132:
      if (lookahead == 'n') ADVANCE(26);
      END_STATE();
    case 133:
      if (lookahead == 'n') ADVANCE(27);
      END_STATE();
    case 134:
      if (lookahead == 'o') ADVANCE(123);
      END_STATE();
    case 135:
      if (lookahead == 'o') ADVANCE(223);
      END_STATE();
    case 136:
      if (lookahead == 'o') ADVANCE(48);
      END_STATE();
    case 137:
      if (lookahead == 'o') ADVANCE(201);
      END_STATE();
    case 138:
      if (lookahead == 'o') ADVANCE(47);
      END_STATE();
    case 139:
      if (lookahead == 'o') ADVANCE(45);
      END_STATE();
    case 140:
      if (lookahead == 'o') ADVANCE(130);
      END_STATE();
    case 141:
      if (lookahead == 'o') ADVANCE(205);
      END_STATE();
    case 142:
      if (lookahead == 'o') ADVANCE(192);
      END_STATE();
    case 143:
      if (lookahead == 'o') ADVANCE(128);
      END_STATE();
    case 144:
      if (lookahead == 'o') ADVANCE(163);
      END_STATE();
    case 145:
      if (lookahead == 'o') ADVANCE(125);
      END_STATE();
    case 146:
      if (lookahead == 'o') ADVANCE(100);
      END_STATE();
    case 147:
      if (lookahead == 'o') ADVANCE(21);
      END_STATE();
    case 148:
      if (lookahead == 'o') ADVANCE(157);
      END_STATE();
    case 149:
      if (lookahead == 'p') ADVANCE(223);
      END_STATE();
    case 150:
      if (lookahead == 'p') ADVANCE(107);
      END_STATE();
    case 151:
      if (lookahead == 'p') ADVANCE(168);
      END_STATE();
    case 152:
      if (lookahead == 'p') ADVANCE(53);
      END_STATE();
    case 153:
      if (lookahead == 'p') ADVANCE(58);
      END_STATE();
    case 154:
      if (lookahead == 'p') ADVANCE(14);
      END_STATE();
    case 155:
      if (lookahead == 'p') ADVANCE(19);
      END_STATE();
    case 156:
      if (lookahead == 'p') ADVANCE(167);
      if (lookahead == 's') ADVANCE(85);
      END_STATE();
    case 157:
      if (lookahead == 'p') ADVANCE(73);
      END_STATE();
    case 158:
      if (lookahead == 'r') ADVANCE(137);
      END_STATE();
    case 159:
      if (lookahead == 'r') ADVANCE(226);
      END_STATE();
    case 160:
      if (lookahead == 'r') ADVANCE(210);
      END_STATE();
    case 161:
      if (lookahead == 'r') ADVANCE(129);
      END_STATE();
    case 162:
      if (lookahead == 'r') ADVANCE(109);
      END_STATE();
    case 163:
      if (lookahead == 'r') ADVANCE(45);
      END_STATE();
    case 164:
      if (lookahead == 'r') ADVANCE(188);
      END_STATE();
    case 165:
      if (lookahead == 'r') ADVANCE(131);
      END_STATE();
    case 166:
      if (lookahead == 'r') ADVANCE(135);
      END_STATE();
    case 167:
      if (lookahead == 'r') ADVANCE(148);
      END_STATE();
    case 168:
      if (lookahead == 'r') ADVANCE(66);
      END_STATE();
    case 169:
      if (lookahead == 'r') ADVANCE(30);
      END_STATE();
    case 170:
      if (lookahead == 'r') ADVANCE(146);
      END_STATE();
    case 171:
      if (lookahead == 'r') ADVANCE(187);
      END_STATE();
    case 172:
      if (lookahead == 'r') ADVANCE(65);
      END_STATE();
    case 173:
      if (lookahead == 'r') ADVANCE(93);
      END_STATE();
    case 174:
      if (lookahead == 'r') ADVANCE(132);
      END_STATE();
    case 175:
      if (lookahead == 's') ADVANCE(223);
      END_STATE();
    case 176:
      if (lookahead == 's') ADVANCE(175);
      END_STATE();
    case 177:
      if (lookahead == 's') ADVANCE(190);
      END_STATE();
    case 178:
      if (lookahead == 's') ADVANCE(154);
      END_STATE();
    case 179:
      if (lookahead == 's') ADVANCE(53);
      END_STATE();
    case 180:
      if (lookahead == 's') ADVANCE(155);
      END_STATE();
    case 181:
      if (lookahead == 't') ADVANCE(223);
      END_STATE();
    case 182:
      if (lookahead == 't') ADVANCE(206);
      END_STATE();
    case 183:
      if (lookahead == 't') ADVANCE(82);
      END_STATE();
    case 184:
      if (lookahead == 't') ADVANCE(212);
      END_STATE();
    case 185:
      if (lookahead == 't') ADVANCE(107);
      END_STATE();
    case 186:
      if (lookahead == 't') ADVANCE(175);
      END_STATE();
    case 187:
      if (lookahead == 't') ADVANCE(210);
      END_STATE();
    case 188:
      if (lookahead == 't') ADVANCE(154);
      END_STATE();
    case 189:
      if (lookahead == 't') ADVANCE(53);
      END_STATE();
    case 190:
      if (lookahead == 't') ADVANCE(169);
      END_STATE();
    case 191:
      if (lookahead == 't') ADVANCE(97);
      END_STATE();
    case 192:
      if (lookahead == 't') ADVANCE(33);
      END_STATE();
    case 193:
      if (lookahead == 't') ADVANCE(92);
      END_STATE();
    case 194:
      if (lookahead == 't') ADVANCE(59);
      END_STATE();
    case 195:
      if (lookahead == 't') ADVANCE(65);
      END_STATE();
    case 196:
      if (lookahead == 't') ADVANCE(23);
      END_STATE();
    case 197:
      if (lookahead == 't') ADVANCE(196);
      END_STATE();
    case 198:
      if (lookahead == 't') ADVANCE(170);
      END_STATE();
    case 199:
      if (lookahead == 'u') ADVANCE(113);
      END_STATE();
    case 200:
      if (lookahead == 'u') ADVANCE(107);
      END_STATE();
    case 201:
      if (lookahead == 'u') ADVANCE(149);
      END_STATE();
    case 202:
      if (lookahead == 'u') ADVANCE(53);
      END_STATE();
    case 203:
      if (lookahead == 'u') ADVANCE(96);
      END_STATE();
    case 204:
      if (lookahead == 'u') ADVANCE(71);
      END_STATE();
    case 205:
      if (lookahead == 'u') ADVANCE(178);
      END_STATE();
    case 206:
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 207:
      if (lookahead == 'w') ADVANCE(223);
      END_STATE();
    case 208:
      if (lookahead == 'w') ADVANCE(144);
      END_STATE();
    case 209:
      if (lookahead == 'x') ADVANCE(188);
      END_STATE();
    case 210:
      if (lookahead == 'y') ADVANCE(223);
      END_STATE();
    case 211:
      if (lookahead == 'y') ADVANCE(208);
      END_STATE();
    case 212:
      if (lookahead == 'y') ADVANCE(152);
      END_STATE();
    case 213:
      if (lookahead == '{') ADVANCE(214);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(213)
      if (lookahead != 0 &&
          lookahead != '\\' &&
          lookahead != '}') ADVANCE(237);
      END_STATE();
    case 214:
      if (lookahead == '}') ADVANCE(236);
      if (lookahead != 0) ADVANCE(214);
      END_STATE();
    case 215:
      if (lookahead == 'b' ||
          lookahead == 'p') ADVANCE(228);
      END_STATE();
    case 216:
      if (('1' <= lookahead && lookahead <= '4')) ADVANCE(223);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_SLASH_STAR_BANG);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(anon_sym_STAR_SLASH);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(anon_sym_STAR_SLASH);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(235);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(235);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(sym_command_name);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 'a') ADVANCE(197);
      if (lookahead == 'e') ADVANCE(122);
      if (lookahead == 'm') ADVANCE(70);
      if (lookahead == 'p') ADVANCE(167);
      if (lookahead == 's') ADVANCE(85);
      if (lookahead == 't') ADVANCE(212);
      if (lookahead == 'v') ADVANCE(22);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 'e') ADVANCE(79);
      if (lookahead == 'i') ADVANCE(227);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 'f') ADVANCE(84);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 's') ADVANCE(181);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(sym_inline_command_name);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'a') ADVANCE(49);
      if (lookahead == 'r') ADVANCE(87);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'b') ADVANCE(177);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'l') ADVANCE(13);
      if (lookahead == 'o') ADVANCE(48);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'n') ADVANCE(199);
      if (lookahead == 'x') ADVANCE(17);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == '/') ADVANCE(220);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(235);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == '*' ||
          lookahead == '\\') ADVANCE(235);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(240);
      if (lookahead != 0) ADVANCE(234);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ') ADVANCE(235);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(sym_inline_text);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(sym_inline_text);
      if (lookahead != 0 &&
          lookahead != '\t' &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ' ' &&
          lookahead != '\\' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(237);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(238);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(240);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(239);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(234);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(sym_text);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(240);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 2},
  [3] = {.lex_state = 2},
  [4] = {.lex_state = 2},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 4},
  [8] = {.lex_state = 2},
  [9] = {.lex_state = 2},
  [10] = {.lex_state = 2},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 213},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_SLASH_STAR_BANG] = ACTIONS(1),
    [anon_sym_STAR_SLASH] = ACTIONS(1),
    [anon_sym_BSLASH] = ACTIONS(1),
    [sym_command_name] = ACTIONS(1),
    [sym_inline_command_name] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(15),
    [sym_comment] = STATE(5),
    [sym_block_comment] = STATE(11),
    [aux_sym_source_file_repeat1] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_SLASH_STAR_BANG] = ACTIONS(5),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 5,
    ACTIONS(7), 1,
      anon_sym_STAR_SLASH,
    ACTIONS(9), 1,
      anon_sym_BSLASH,
    ACTIONS(11), 1,
      sym_text,
    STATE(3), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(8), 2,
      sym_command,
      sym_inline_command,
  [18] = 5,
    ACTIONS(9), 1,
      anon_sym_BSLASH,
    ACTIONS(11), 1,
      sym_text,
    ACTIONS(13), 1,
      anon_sym_STAR_SLASH,
    STATE(4), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(8), 2,
      sym_command,
      sym_inline_command,
  [36] = 5,
    ACTIONS(15), 1,
      anon_sym_STAR_SLASH,
    ACTIONS(17), 1,
      anon_sym_BSLASH,
    ACTIONS(20), 1,
      sym_text,
    STATE(4), 2,
      sym_markup,
      aux_sym_block_comment_repeat1,
    STATE(8), 2,
      sym_command,
      sym_inline_command,
  [54] = 4,
    ACTIONS(5), 1,
      anon_sym_SLASH_STAR_BANG,
    ACTIONS(23), 1,
      ts_builtin_sym_end,
    STATE(11), 1,
      sym_block_comment,
    STATE(6), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [68] = 4,
    ACTIONS(25), 1,
      ts_builtin_sym_end,
    ACTIONS(27), 1,
      anon_sym_SLASH_STAR_BANG,
    STATE(11), 1,
      sym_block_comment,
    STATE(6), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [82] = 2,
    ACTIONS(32), 1,
      sym_command_argument,
    ACTIONS(30), 3,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
      sym_text,
  [91] = 2,
    ACTIONS(36), 1,
      sym_text,
    ACTIONS(34), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [99] = 2,
    ACTIONS(40), 1,
      sym_text,
    ACTIONS(38), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [107] = 2,
    ACTIONS(44), 1,
      sym_text,
    ACTIONS(42), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [115] = 1,
    ACTIONS(46), 2,
      ts_builtin_sym_end,
      anon_sym_SLASH_STAR_BANG,
  [120] = 1,
    ACTIONS(48), 2,
      ts_builtin_sym_end,
      anon_sym_SLASH_STAR_BANG,
  [125] = 2,
    ACTIONS(50), 1,
      sym_command_name,
    ACTIONS(52), 1,
      sym_inline_command_name,
  [132] = 1,
    ACTIONS(54), 2,
      ts_builtin_sym_end,
      anon_sym_SLASH_STAR_BANG,
  [137] = 1,
    ACTIONS(56), 1,
      ts_builtin_sym_end,
  [141] = 1,
    ACTIONS(58), 1,
      sym_inline_text,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 18,
  [SMALL_STATE(4)] = 36,
  [SMALL_STATE(5)] = 54,
  [SMALL_STATE(6)] = 68,
  [SMALL_STATE(7)] = 82,
  [SMALL_STATE(8)] = 91,
  [SMALL_STATE(9)] = 99,
  [SMALL_STATE(10)] = 107,
  [SMALL_STATE(11)] = 115,
  [SMALL_STATE(12)] = 120,
  [SMALL_STATE(13)] = 125,
  [SMALL_STATE(14)] = 132,
  [SMALL_STATE(15)] = 137,
  [SMALL_STATE(16)] = 141,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [15] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_block_comment_repeat1, 2),
  [17] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_comment_repeat1, 2), SHIFT_REPEAT(13),
  [20] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_comment_repeat1, 2), SHIFT_REPEAT(8),
  [23] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [27] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(2),
  [30] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 2),
  [32] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [34] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_markup, 1),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_markup, 1),
  [38] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3),
  [40] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3),
  [42] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_inline_command, 3),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_inline_command, 3),
  [46] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 1),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_comment, 2),
  [50] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [52] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_comment, 3),
  [56] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
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
