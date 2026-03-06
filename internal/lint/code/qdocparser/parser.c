#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 19
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 18
#define ALIAS_COUNT 0
#define TOKEN_COUNT 10
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  anon_sym_SLASH_STAR_BANG = 1,
  anon_sym_STAR_SLASH = 2,
  anon_sym_BSLASH = 3,
  sym_command_name = 4,
  sym_inline_command_name = 5,
  sym_command_argument = 6,
  sym_description = 7,
  sym_inline_text = 8,
  sym_text = 9,
  sym_source_file = 10,
  sym_comment = 11,
  sym_block_comment = 12,
  sym_markup = 13,
  sym_command = 14,
  sym_inline_command = 15,
  aux_sym_source_file_repeat1 = 16,
  aux_sym_block_comment_repeat1 = 17,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_SLASH_STAR_BANG] = "/*!",
  [anon_sym_STAR_SLASH] = "*/",
  [anon_sym_BSLASH] = "\\",
  [sym_command_name] = "command_name",
  [sym_inline_command_name] = "inline_command_name",
  [sym_command_argument] = "command_argument",
  [sym_description] = "description",
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
  [sym_description] = sym_description,
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
  [sym_description] = {
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
  [17] = 17,
  [18] = 18,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(218);
      ADVANCE_MAP(
        '*', 6,
        '/', 5,
        '\\', 223,
        'a', 233,
        'b', 232,
        'c', 234,
        'd', 53,
        'e', 235,
        'f', 124,
        'g', 159,
        'h', 62,
        'i', 125,
        'k', 55,
        'l', 228,
        'm', 8,
        'n', 9,
        'o', 116,
        'p', 16,
        'q', 115,
        'r', 56,
        's', 7,
        't', 10,
        'u', 87,
        'v', 11,
        'w', 13,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(246);
      if (lookahead == '*') ADVANCE(237);
      if (lookahead == '\\') ADVANCE(224);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(240);
      if (lookahead != 0) ADVANCE(236);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(247);
      if (lookahead == '*') ADVANCE(242);
      if (lookahead == '\\') ADVANCE(225);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(241);
      if (lookahead != 0) ADVANCE(239);
      END_STATE();
    case 3:
      if (lookahead == '!') ADVANCE(219);
      END_STATE();
    case 4:
      if (lookahead == '*') ADVANCE(6);
      if (lookahead == '\\') ADVANCE(223);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(248);
      if (lookahead != 0) ADVANCE(249);
      END_STATE();
    case 5:
      if (lookahead == '*') ADVANCE(3);
      END_STATE();
    case 6:
      if (lookahead == '/') ADVANCE(220);
      END_STATE();
    case 7:
      if (lookahead == 'a') ADVANCE(226);
      if (lookahead == 'e') ADVANCE(43);
      if (lookahead == 'i') ADVANCE(128);
      if (lookahead == 't') ADVANCE(21);
      if (lookahead == 'u') ADVANCE(216);
      END_STATE();
    case 8:
      if (lookahead == 'a') ADVANCE(44);
      if (lookahead == 'o') ADVANCE(48);
      END_STATE();
    case 9:
      if (lookahead == 'a') ADVANCE(121);
      if (lookahead == 'e') ADVANCE(210);
      if (lookahead == 'o') ADVANCE(190);
      END_STATE();
    case 10:
      if (lookahead == 'a') ADVANCE(37);
      if (lookahead == 'i') ADVANCE(186);
      if (lookahead == 'y') ADVANCE(154);
      if (lookahead == 'm' ||
          lookahead == 't') ADVANCE(231);
      END_STATE();
    case 11:
      if (lookahead == 'a') ADVANCE(107);
      END_STATE();
    case 12:
      if (lookahead == 'a') ADVANCE(36);
      END_STATE();
    case 13:
      if (lookahead == 'a') ADVANCE(162);
      END_STATE();
    case 14:
      if (lookahead == 'a') ADVANCE(177);
      END_STATE();
    case 15:
      if (lookahead == 'a') ADVANCE(79);
      END_STATE();
    case 16:
      if (lookahead == 'a') ADVANCE(79);
      if (lookahead == 'r') ADVANCE(57);
      END_STATE();
    case 17:
      if (lookahead == 'a') ADVANCE(176);
      END_STATE();
    case 18:
      if (lookahead == 'a') ADVANCE(117);
      if (lookahead == 't') ADVANCE(73);
      END_STATE();
    case 19:
      if (lookahead == 'a') ADVANCE(51);
      if (lookahead == 'i') ADVANCE(120);
      if (lookahead == 'l') ADVANCE(29);
      if (lookahead == 'q') ADVANCE(204);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(42);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(165);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(46);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(113);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(38);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(112);
      if (lookahead == 'd') ADVANCE(58);
      END_STATE();
    case 26:
      if (lookahead == 'a') ADVANCE(105);
      END_STATE();
    case 27:
      if (lookahead == 'a') ADVANCE(100);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(161);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(195);
      END_STATE();
    case 30:
      if (lookahead == 'a') ADVANCE(52);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(40);
      END_STATE();
    case 32:
      if (lookahead == 'a') ADVANCE(111);
      END_STATE();
    case 33:
      if (lookahead == 'a') ADVANCE(106);
      END_STATE();
    case 34:
      if (lookahead == 'a') ADVANCE(194);
      END_STATE();
    case 35:
      if (lookahead == 'a') ADVANCE(196);
      END_STATE();
    case 36:
      if (lookahead == 'b') ADVANCE(108);
      END_STATE();
    case 37:
      if (lookahead == 'b') ADVANCE(108);
      if (lookahead == 'r') ADVANCE(81);
      END_STATE();
    case 38:
      if (lookahead == 'c') ADVANCE(84);
      END_STATE();
    case 39:
      if (lookahead == 'c') ADVANCE(141);
      END_STATE();
    case 40:
      if (lookahead == 'c') ADVANCE(182);
      END_STATE();
    case 41:
      if (lookahead == 'c') ADVANCE(137);
      END_STATE();
    case 42:
      if (lookahead == 'c') ADVANCE(54);
      END_STATE();
    case 43:
      if (lookahead == 'c') ADVANCE(192);
      END_STATE();
    case 44:
      if (lookahead == 'c') ADVANCE(167);
      END_STATE();
    case 45:
      if (lookahead == 'c') ADVANCE(35);
      END_STATE();
    case 46:
      if (lookahead == 'd') ADVANCE(226);
      END_STATE();
    case 47:
      if (lookahead == 'd') ADVANCE(157);
      END_STATE();
    case 48:
      if (lookahead == 'd') ADVANCE(201);
      END_STATE();
    case 49:
      if (lookahead == 'd') ADVANCE(54);
      END_STATE();
    case 50:
      if (lookahead == 'd') ADVANCE(41);
      END_STATE();
    case 51:
      if (lookahead == 'd') ADVANCE(144);
      END_STATE();
    case 52:
      if (lookahead == 'd') ADVANCE(70);
      END_STATE();
    case 53:
      if (lookahead == 'e') ADVANCE(152);
      END_STATE();
    case 54:
      if (lookahead == 'e') ADVANCE(226);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(212);
      END_STATE();
    case 56:
      if (lookahead == 'e') ADVANCE(19);
      if (lookahead == 'o') ADVANCE(208);
      END_STATE();
    case 57:
      if (lookahead == 'e') ADVANCE(104);
      if (lookahead == 'o') ADVANCE(158);
      END_STATE();
    case 58:
      if (lookahead == 'e') ADVANCE(76);
      END_STATE();
    case 59:
      if (lookahead == 'e') ADVANCE(25);
      END_STATE();
    case 60:
      if (lookahead == 'e') ADVANCE(176);
      END_STATE();
    case 61:
      if (lookahead == 'e') ADVANCE(163);
      END_STATE();
    case 62:
      if (lookahead == 'e') ADVANCE(30);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(181);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(182);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(180);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(46);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(45);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(47);
      END_STATE();
    case 69:
      if (lookahead == 'e') ADVANCE(174);
      END_STATE();
    case 70:
      if (lookahead == 'e') ADVANCE(160);
      END_STATE();
    case 71:
      if (lookahead == 'e') ADVANCE(184);
      if (lookahead == 'o') ADVANCE(48);
      END_STATE();
    case 72:
      if (lookahead == 'e') ADVANCE(185);
      END_STATE();
    case 73:
      if (lookahead == 'e') ADVANCE(166);
      END_STATE();
    case 74:
      if (lookahead == 'e') ADVANCE(172);
      END_STATE();
    case 75:
      if (lookahead == 'e') ADVANCE(175);
      END_STATE();
    case 76:
      if (lookahead == 'f') ADVANCE(226);
      END_STATE();
    case 77:
      if (lookahead == 'g') ADVANCE(159);
      if (lookahead == 'h') ADVANCE(69);
      if (lookahead == 'm') ADVANCE(139);
      if (lookahead == 'q') ADVANCE(119);
      if (lookahead == 't') ADVANCE(75);
      END_STATE();
    case 78:
      if (lookahead == 'g') ADVANCE(226);
      END_STATE();
    case 79:
      if (lookahead == 'g') ADVANCE(54);
      END_STATE();
    case 80:
      if (lookahead == 'g') ADVANCE(32);
      END_STATE();
    case 81:
      if (lookahead == 'g') ADVANCE(64);
      END_STATE();
    case 82:
      if (lookahead == 'g') ADVANCE(133);
      END_STATE();
    case 83:
      if (lookahead == 'h') ADVANCE(140);
      END_STATE();
    case 84:
      if (lookahead == 'h') ADVANCE(68);
      END_STATE();
    case 85:
      if (lookahead == 'i') ADVANCE(108);
      END_STATE();
    case 86:
      if (lookahead == 'i') ADVANCE(82);
      END_STATE();
    case 87:
      if (lookahead == 'i') ADVANCE(39);
      END_STATE();
    case 88:
      if (lookahead == 'i') ADVANCE(58);
      END_STATE();
    case 89:
      if (lookahead == 'i') ADVANCE(183);
      END_STATE();
    case 90:
      if (lookahead == 'i') ADVANCE(122);
      END_STATE();
    case 91:
      if (lookahead == 'i') ADVANCE(127);
      END_STATE();
    case 92:
      if (lookahead == 'i') ADVANCE(12);
      END_STATE();
    case 93:
      if (lookahead == 'i') ADVANCE(135);
      END_STATE();
    case 94:
      if (lookahead == 'i') ADVANCE(187);
      END_STATE();
    case 95:
      if (lookahead == 'i') ADVANCE(17);
      END_STATE();
    case 96:
      if (lookahead == 'i') ADVANCE(142);
      END_STATE();
    case 97:
      if (lookahead == 'i') ADVANCE(173);
      END_STATE();
    case 98:
      if (lookahead == 'i') ADVANCE(146);
      END_STATE();
    case 99:
      if (lookahead == 'i') ADVANCE(134);
      END_STATE();
    case 100:
      if (lookahead == 'l') ADVANCE(226);
      END_STATE();
    case 101:
      if (lookahead == 'l') ADVANCE(231);
      END_STATE();
    case 102:
      if (lookahead == 'l') ADVANCE(227);
      END_STATE();
    case 103:
      if (lookahead == 'l') ADVANCE(211);
      END_STATE();
    case 104:
      if (lookahead == 'l') ADVANCE(90);
      if (lookahead == 'v') ADVANCE(96);
      END_STATE();
    case 105:
      if (lookahead == 'l') ADVANCE(155);
      END_STATE();
    case 106:
      if (lookahead == 'l') ADVANCE(203);
      END_STATE();
    case 107:
      if (lookahead == 'l') ADVANCE(203);
      if (lookahead == 'r') ADVANCE(92);
      END_STATE();
    case 108:
      if (lookahead == 'l') ADVANCE(54);
      END_STATE();
    case 109:
      if (lookahead == 'l') ADVANCE(118);
      END_STATE();
    case 110:
      if (lookahead == 'l') ADVANCE(148);
      END_STATE();
    case 111:
      if (lookahead == 'l') ADVANCE(65);
      END_STATE();
    case 112:
      if (lookahead == 'l') ADVANCE(95);
      END_STATE();
    case 113:
      if (lookahead == 'l') ADVANCE(205);
      END_STATE();
    case 114:
      if (lookahead == 'm') ADVANCE(226);
      END_STATE();
    case 115:
      if (lookahead == 'm') ADVANCE(102);
      if (lookahead == 'u') ADVANCE(143);
      END_STATE();
    case 116:
      if (lookahead == 'm') ADVANCE(89);
      if (lookahead == 'v') ADVANCE(61);
      END_STATE();
    case 117:
      if (lookahead == 'm') ADVANCE(151);
      END_STATE();
    case 118:
      if (lookahead == 'm') ADVANCE(139);
      END_STATE();
    case 119:
      if (lookahead == 'm') ADVANCE(109);
      END_STATE();
    case 120:
      if (lookahead == 'm') ADVANCE(150);
      END_STATE();
    case 121:
      if (lookahead == 'm') ADVANCE(63);
      END_STATE();
    case 122:
      if (lookahead == 'm') ADVANCE(99);
      END_STATE();
    case 123:
      if (lookahead == 'n') ADVANCE(200);
      END_STATE();
    case 124:
      if (lookahead == 'n') ADVANCE(226);
      END_STATE();
    case 125:
      if (lookahead == 'n') ADVANCE(77);
      END_STATE();
    case 126:
      if (lookahead == 'n') ADVANCE(217);
      END_STATE();
    case 127:
      if (lookahead == 'n') ADVANCE(78);
      END_STATE();
    case 128:
      if (lookahead == 'n') ADVANCE(42);
      END_STATE();
    case 129:
      if (lookahead == 'n') ADVANCE(103);
      END_STATE();
    case 130:
      if (lookahead == 'n') ADVANCE(91);
      END_STATE();
    case 131:
      if (lookahead == 'n') ADVANCE(199);
      END_STATE();
    case 132:
      if (lookahead == 'n') ADVANCE(26);
      END_STATE();
    case 133:
      if (lookahead == 'n') ADVANCE(27);
      END_STATE();
    case 134:
      if (lookahead == 'n') ADVANCE(28);
      END_STATE();
    case 135:
      if (lookahead == 'o') ADVANCE(124);
      END_STATE();
    case 136:
      if (lookahead == 'o') ADVANCE(226);
      END_STATE();
    case 137:
      if (lookahead == 'o') ADVANCE(49);
      END_STATE();
    case 138:
      if (lookahead == 'o') ADVANCE(202);
      END_STATE();
    case 139:
      if (lookahead == 'o') ADVANCE(48);
      END_STATE();
    case 140:
      if (lookahead == 'o') ADVANCE(46);
      END_STATE();
    case 141:
      if (lookahead == 'o') ADVANCE(131);
      END_STATE();
    case 142:
      if (lookahead == 'o') ADVANCE(206);
      END_STATE();
    case 143:
      if (lookahead == 'o') ADVANCE(193);
      END_STATE();
    case 144:
      if (lookahead == 'o') ADVANCE(129);
      END_STATE();
    case 145:
      if (lookahead == 'o') ADVANCE(164);
      END_STATE();
    case 146:
      if (lookahead == 'o') ADVANCE(126);
      END_STATE();
    case 147:
      if (lookahead == 'o') ADVANCE(101);
      END_STATE();
    case 148:
      if (lookahead == 'o') ADVANCE(22);
      END_STATE();
    case 149:
      if (lookahead == 'o') ADVANCE(158);
      END_STATE();
    case 150:
      if (lookahead == 'p') ADVANCE(226);
      END_STATE();
    case 151:
      if (lookahead == 'p') ADVANCE(108);
      END_STATE();
    case 152:
      if (lookahead == 'p') ADVANCE(169);
      END_STATE();
    case 153:
      if (lookahead == 'p') ADVANCE(54);
      END_STATE();
    case 154:
      if (lookahead == 'p') ADVANCE(59);
      END_STATE();
    case 155:
      if (lookahead == 'p') ADVANCE(15);
      END_STATE();
    case 156:
      if (lookahead == 'p') ADVANCE(20);
      END_STATE();
    case 157:
      if (lookahead == 'p') ADVANCE(168);
      if (lookahead == 's') ADVANCE(86);
      END_STATE();
    case 158:
      if (lookahead == 'p') ADVANCE(74);
      END_STATE();
    case 159:
      if (lookahead == 'r') ADVANCE(138);
      END_STATE();
    case 160:
      if (lookahead == 'r') ADVANCE(229);
      END_STATE();
    case 161:
      if (lookahead == 'r') ADVANCE(211);
      END_STATE();
    case 162:
      if (lookahead == 'r') ADVANCE(130);
      END_STATE();
    case 163:
      if (lookahead == 'r') ADVANCE(110);
      END_STATE();
    case 164:
      if (lookahead == 'r') ADVANCE(46);
      END_STATE();
    case 165:
      if (lookahead == 'r') ADVANCE(189);
      END_STATE();
    case 166:
      if (lookahead == 'r') ADVANCE(132);
      END_STATE();
    case 167:
      if (lookahead == 'r') ADVANCE(136);
      END_STATE();
    case 168:
      if (lookahead == 'r') ADVANCE(149);
      END_STATE();
    case 169:
      if (lookahead == 'r') ADVANCE(67);
      END_STATE();
    case 170:
      if (lookahead == 'r') ADVANCE(31);
      END_STATE();
    case 171:
      if (lookahead == 'r') ADVANCE(147);
      END_STATE();
    case 172:
      if (lookahead == 'r') ADVANCE(188);
      END_STATE();
    case 173:
      if (lookahead == 'r') ADVANCE(66);
      END_STATE();
    case 174:
      if (lookahead == 'r') ADVANCE(94);
      END_STATE();
    case 175:
      if (lookahead == 'r') ADVANCE(133);
      END_STATE();
    case 176:
      if (lookahead == 's') ADVANCE(226);
      END_STATE();
    case 177:
      if (lookahead == 's') ADVANCE(176);
      END_STATE();
    case 178:
      if (lookahead == 's') ADVANCE(191);
      END_STATE();
    case 179:
      if (lookahead == 's') ADVANCE(155);
      END_STATE();
    case 180:
      if (lookahead == 's') ADVANCE(54);
      END_STATE();
    case 181:
      if (lookahead == 's') ADVANCE(156);
      END_STATE();
    case 182:
      if (lookahead == 't') ADVANCE(226);
      END_STATE();
    case 183:
      if (lookahead == 't') ADVANCE(207);
      END_STATE();
    case 184:
      if (lookahead == 't') ADVANCE(83);
      END_STATE();
    case 185:
      if (lookahead == 't') ADVANCE(213);
      END_STATE();
    case 186:
      if (lookahead == 't') ADVANCE(108);
      END_STATE();
    case 187:
      if (lookahead == 't') ADVANCE(176);
      END_STATE();
    case 188:
      if (lookahead == 't') ADVANCE(211);
      END_STATE();
    case 189:
      if (lookahead == 't') ADVANCE(155);
      END_STATE();
    case 190:
      if (lookahead == 't') ADVANCE(54);
      END_STATE();
    case 191:
      if (lookahead == 't') ADVANCE(170);
      END_STATE();
    case 192:
      if (lookahead == 't') ADVANCE(98);
      END_STATE();
    case 193:
      if (lookahead == 't') ADVANCE(34);
      END_STATE();
    case 194:
      if (lookahead == 't') ADVANCE(93);
      END_STATE();
    case 195:
      if (lookahead == 't') ADVANCE(60);
      END_STATE();
    case 196:
      if (lookahead == 't') ADVANCE(66);
      END_STATE();
    case 197:
      if (lookahead == 't') ADVANCE(24);
      END_STATE();
    case 198:
      if (lookahead == 't') ADVANCE(197);
      END_STATE();
    case 199:
      if (lookahead == 't') ADVANCE(171);
      END_STATE();
    case 200:
      if (lookahead == 'u') ADVANCE(114);
      END_STATE();
    case 201:
      if (lookahead == 'u') ADVANCE(108);
      END_STATE();
    case 202:
      if (lookahead == 'u') ADVANCE(150);
      END_STATE();
    case 203:
      if (lookahead == 'u') ADVANCE(54);
      END_STATE();
    case 204:
      if (lookahead == 'u') ADVANCE(97);
      END_STATE();
    case 205:
      if (lookahead == 'u') ADVANCE(72);
      END_STATE();
    case 206:
      if (lookahead == 'u') ADVANCE(179);
      END_STATE();
    case 207:
      if (lookahead == 'v') ADVANCE(33);
      END_STATE();
    case 208:
      if (lookahead == 'w') ADVANCE(226);
      END_STATE();
    case 209:
      if (lookahead == 'w') ADVANCE(145);
      END_STATE();
    case 210:
      if (lookahead == 'x') ADVANCE(189);
      END_STATE();
    case 211:
      if (lookahead == 'y') ADVANCE(226);
      END_STATE();
    case 212:
      if (lookahead == 'y') ADVANCE(209);
      END_STATE();
    case 213:
      if (lookahead == 'y') ADVANCE(153);
      END_STATE();
    case 214:
      if (lookahead == '{') ADVANCE(215);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(214);
      if (lookahead != 0 &&
          lookahead != '\\' &&
          lookahead != '}') ADVANCE(245);
      END_STATE();
    case 215:
      if (lookahead == '}') ADVANCE(244);
      if (lookahead != 0) ADVANCE(215);
      END_STATE();
    case 216:
      if (lookahead == 'b' ||
          lookahead == 'p') ADVANCE(231);
      END_STATE();
    case 217:
      if (('1' <= lookahead && lookahead <= '4')) ADVANCE(226);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(anon_sym_SLASH_STAR_BANG);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(anon_sym_STAR_SLASH);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(anon_sym_STAR_SLASH);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(243);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead)) ADVANCE(238);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(anon_sym_STAR_SLASH);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(243);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(243);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead)) ADVANCE(238);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(anon_sym_BSLASH);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(243);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(sym_command_name);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 'a') ADVANCE(198);
      if (lookahead == 'e') ADVANCE(123);
      if (lookahead == 'm') ADVANCE(71);
      if (lookahead == 'p') ADVANCE(168);
      if (lookahead == 's') ADVANCE(86);
      if (lookahead == 't') ADVANCE(213);
      if (lookahead == 'v') ADVANCE(23);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 'e') ADVANCE(80);
      if (lookahead == 'i') ADVANCE(230);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 'f') ADVANCE(85);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(sym_command_name);
      if (lookahead == 's') ADVANCE(182);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(sym_inline_command_name);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'a') ADVANCE(50);
      if (lookahead == 'r') ADVANCE(88);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'b') ADVANCE(178);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'l') ADVANCE(14);
      if (lookahead == 'o') ADVANCE(49);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(sym_inline_command_name);
      if (lookahead == 'n') ADVANCE(200);
      if (lookahead == 'x') ADVANCE(18);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == '\n') ADVANCE(249);
      if (lookahead == '*' ||
          lookahead == '\\') ADVANCE(238);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(239);
      if (lookahead != 0) ADVANCE(236);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == '/') ADVANCE(221);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(243);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead)) ADVANCE(238);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(sym_command_argument);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(243);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead)) ADVANCE(238);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(sym_description);
      if (lookahead == '\n') ADVANCE(249);
      if (lookahead == '*' ||
          lookahead == '\\') ADVANCE(243);
      if (lookahead != 0) ADVANCE(239);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(sym_description);
      if (lookahead == '\n') ADVANCE(246);
      if (lookahead == '*') ADVANCE(237);
      if (lookahead == '\\') ADVANCE(224);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(240);
      if (lookahead != 0) ADVANCE(236);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(sym_description);
      if (lookahead == '\n') ADVANCE(247);
      if (lookahead == '*') ADVANCE(242);
      if (lookahead == '\\') ADVANCE(225);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(241);
      if (lookahead != 0) ADVANCE(239);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(sym_description);
      if (lookahead == '/') ADVANCE(222);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(243);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(sym_description);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(243);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(sym_inline_text);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(sym_inline_text);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ' &&
          lookahead != '\\' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(245);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '\n') ADVANCE(246);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(240);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(236);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(sym_text);
      if (lookahead == '\n') ADVANCE(247);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(241);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(239);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(sym_text);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(248);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(249);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(sym_text);
      if (lookahead != 0 &&
          lookahead != '*' &&
          lookahead != '\\') ADVANCE(249);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 4},
  [3] = {.lex_state = 4},
  [4] = {.lex_state = 4},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 1},
  [8] = {.lex_state = 2},
  [9] = {.lex_state = 4},
  [10] = {.lex_state = 4},
  [11] = {.lex_state = 4},
  [12] = {.lex_state = 4},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 214},
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
    [sym_source_file] = STATE(17),
    [sym_comment] = STATE(5),
    [sym_block_comment] = STATE(13),
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
    STATE(9), 2,
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
    STATE(9), 2,
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
    STATE(9), 2,
      sym_command,
      sym_inline_command,
  [54] = 4,
    ACTIONS(5), 1,
      anon_sym_SLASH_STAR_BANG,
    ACTIONS(23), 1,
      ts_builtin_sym_end,
    STATE(13), 1,
      sym_block_comment,
    STATE(6), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [68] = 4,
    ACTIONS(25), 1,
      ts_builtin_sym_end,
    ACTIONS(27), 1,
      anon_sym_SLASH_STAR_BANG,
    STATE(13), 1,
      sym_block_comment,
    STATE(6), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [82] = 3,
    ACTIONS(32), 1,
      sym_command_argument,
    ACTIONS(34), 1,
      sym_description,
    ACTIONS(30), 3,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
      sym_text,
  [94] = 2,
    ACTIONS(38), 1,
      sym_description,
    ACTIONS(36), 3,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
      sym_text,
  [103] = 2,
    ACTIONS(42), 1,
      sym_text,
    ACTIONS(40), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [111] = 2,
    ACTIONS(44), 1,
      sym_text,
    ACTIONS(36), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [119] = 2,
    ACTIONS(48), 1,
      sym_text,
    ACTIONS(46), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [127] = 2,
    ACTIONS(52), 1,
      sym_text,
    ACTIONS(50), 2,
      anon_sym_STAR_SLASH,
      anon_sym_BSLASH,
  [135] = 1,
    ACTIONS(54), 2,
      ts_builtin_sym_end,
      anon_sym_SLASH_STAR_BANG,
  [140] = 1,
    ACTIONS(56), 2,
      ts_builtin_sym_end,
      anon_sym_SLASH_STAR_BANG,
  [145] = 2,
    ACTIONS(58), 1,
      sym_command_name,
    ACTIONS(60), 1,
      sym_inline_command_name,
  [152] = 1,
    ACTIONS(62), 2,
      ts_builtin_sym_end,
      anon_sym_SLASH_STAR_BANG,
  [157] = 1,
    ACTIONS(64), 1,
      ts_builtin_sym_end,
  [161] = 1,
    ACTIONS(66), 1,
      sym_inline_text,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 18,
  [SMALL_STATE(4)] = 36,
  [SMALL_STATE(5)] = 54,
  [SMALL_STATE(6)] = 68,
  [SMALL_STATE(7)] = 82,
  [SMALL_STATE(8)] = 94,
  [SMALL_STATE(9)] = 103,
  [SMALL_STATE(10)] = 111,
  [SMALL_STATE(11)] = 119,
  [SMALL_STATE(12)] = 127,
  [SMALL_STATE(13)] = 135,
  [SMALL_STATE(14)] = 140,
  [SMALL_STATE(15)] = 145,
  [SMALL_STATE(16)] = 152,
  [SMALL_STATE(17)] = 157,
  [SMALL_STATE(18)] = 161,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [15] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_block_comment_repeat1, 2, 0, 0),
  [17] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_comment_repeat1, 2, 0, 0), SHIFT_REPEAT(15),
  [20] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_comment_repeat1, 2, 0, 0), SHIFT_REPEAT(9),
  [23] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [27] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(2),
  [30] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 2, 0, 0),
  [32] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [34] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [36] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 3, 0, 0),
  [38] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [40] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_markup, 1, 0, 0),
  [42] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_markup, 1, 0, 0),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 3, 0, 0),
  [46] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_inline_command, 3, 0, 0),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_inline_command, 3, 0, 0),
  [50] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_command, 4, 0, 0),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_command, 4, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 1, 0, 0),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_comment, 2, 0, 0),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [60] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [62] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block_comment, 3, 0, 0),
  [64] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_qdoc(void) {
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
