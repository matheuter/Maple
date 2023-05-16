/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */
 //
 //  RustLexerBase.h
 //
 //  dev: jcju
 //
#pragma once

#include "antlr4-runtime.h"
using namespace antlr4;

    class RustLexerBase : public antlr4::Lexer {
    public:
        antlr4::CharStream* _input; // Pure reference, usually from statically allocated instance.

    protected:
        RustLexerBase(antlr4::CharStream* input)
            : Lexer(input) {
            _input = input;
        }
    public:
        std::unique_ptr<Token> lt1;
        std::unique_ptr<Token> lt2;
    public:
        std::unique_ptr<Token> NextToken()
        {
            // Get the next token.
            std::unique_ptr<Token> next = Lexer::nextToken();

            if (next->getChannel() == DEFAULT_TOKEN_CHANNEL)
            {
                // Keep track of the last token on the default channel.
                lt2 = std::move(lt1);
                lt1 = std::move(next);
            }
            return next;
        }
    public:
        bool SOF() {
            return _input->LA(-1) <= 0;
        }
    public:
        bool next(char expect) {
            return _input->LA(1) == expect;
        }

    public:
        bool floatDotPossible() {
            int next = _input->LA(1);
            // only block . _ identifier after float
            if (next == '.' || next == '_')
                return false;
            if (next == 'f') {
                // 1.f32
                if (_input->LA(2) == '3' && _input->LA(3) == '2')
                    return true;
                //1.f64
                if (_input->LA(2) == '6' && _input->LA(3) == '4')
                    return true;
                return false;
            }
            if (next >= 'a' && next <= 'z')
                return false;
            if (next >= 'A' && next <= 'Z')
                return false;
            return true;
        }
        enum {
            KW_AS = 1, KW_BREAK = 2, KW_CONST = 3, KW_CONTINUE = 4, KW_CRATE = 5,
            KW_ELSE = 6, KW_ENUM = 7, KW_EXTERN = 8, KW_FALSE = 9, KW_FN = 10, KW_FOR = 11,
            KW_IF = 12, KW_IMPL = 13, KW_IN = 14, KW_LET = 15, KW_LOOP = 16, KW_MATCH = 17,
            KW_MOD = 18, KW_MOVE = 19, KW_MUT = 20, KW_PUB = 21, KW_REF = 22, KW_RETURN = 23,
            KW_SELFVALUE = 24, KW_SELFTYPE = 25, KW_STATIC = 26, KW_STRUCT = 27,
            KW_SUPER = 28, KW_TRAIT = 29, KW_TRUE = 30, KW_TYPE = 31, KW_UNSAFE = 32,
            KW_USE = 33, KW_WHERE = 34, KW_WHILE = 35, KW_ASYNC = 36, KW_AWAIT = 37,
            KW_DYN = 38, KW_ABSTRACT = 39, KW_BECOME = 40, KW_BOX = 41, KW_DO = 42,
            KW_FINAL = 43, KW_MACRO = 44, KW_OVERRIDE = 45, KW_PRIV = 46, KW_TYPEOF = 47,
            KW_UNSIZED = 48, KW_VIRTUAL = 49, KW_YIELD = 50, KW_TRY = 51, KW_UNION = 52,
            KW_STATICLIFETIME = 53, KW_MACRORULES = 54, KW_UNDERLINELIFETIME = 55,
            KW_DOLLARCRATE = 56, NON_KEYWORD_IDENTIFIER = 57, RAW_IDENTIFIER = 58,
            LINE_COMMENT = 59, BLOCK_COMMENT = 60, INNER_LINE_DOC = 61, INNER_BLOCK_DOC = 62,
            OUTER_LINE_DOC = 63, OUTER_BLOCK_DOC = 64, BLOCK_COMMENT_OR_DOC = 65,
            SHEBANG = 66, WHITESPACE = 67, NEWLINE = 68, CHAR_LITERAL = 69, STRING_LITERAL = 70,
            RAW_STRING_LITERAL = 71, BYTE_LITERAL = 72, BYTE_STRING_LITERAL = 73,
            RAW_BYTE_STRING_LITERAL = 74, INTEGER_LITERAL = 75, DEC_LITERAL = 76,
            HEX_LITERAL = 77, OCT_LITERAL = 78, BIN_LITERAL = 79, FLOAT_LITERAL = 80,
            LIFETIME_OR_LABEL = 81, PLUS = 82, MINUS = 83, STAR = 84, SLASH = 85,
            PERCENT = 86, CARET = 87, NOT = 88, AND = 89, OR = 90, ANDAND = 91,
            OROR = 92, PLUSEQ = 93, MINUSEQ = 94, STAREQ = 95, SLASHEQ = 96, PERCENTEQ = 97,
            CARETEQ = 98, ANDEQ = 99, OREQ = 100, SHLEQ = 101, SHREQ = 102, EQ = 103,
            EQEQ = 104, NE = 105, GT = 106, LT = 107, GE = 108, LE = 109, AT = 110,
            UNDERSCORE = 111, DOT = 112, DOTDOT = 113, DOTDOTDOT = 114, DOTDOTEQ = 115,
            COMMA = 116, SEMI = 117, COLON = 118, PATHSEP = 119, RARROW = 120, FATARROW = 121,
            POUND = 122, DOLLAR = 123, QUESTION = 124, LCURLYBRACE = 125, RCURLYBRACE = 126,
            LSQUAREBRACKET = 127, RSQUAREBRACKET = 128, LPAREN = 129, RPAREN = 130
        };
    public:
        bool floatLiteralPossible() {
            if (this->lt1 == nullptr || this->lt2 == nullptr)
                return true;
            if (this->lt1->getType() != DOT)
                return true;
            switch (this->lt2->getType()) {
            case CHAR_LITERAL:
            case STRING_LITERAL:
            case RAW_STRING_LITERAL:
            case BYTE_LITERAL:
            case BYTE_STRING_LITERAL:
            case RAW_BYTE_STRING_LITERAL:
            case INTEGER_LITERAL:
            case DEC_LITERAL:
            case HEX_LITERAL:
            case OCT_LITERAL:
            case BIN_LITERAL:

            case KW_SUPER:
            case KW_SELFVALUE:
            case KW_SELFTYPE:
            case KW_CRATE:
            case KW_DOLLARCRATE:

            case GT:
            case RCURLYBRACE:
            case RSQUAREBRACKET:
            case RPAREN:

            case KW_AWAIT:

            case NON_KEYWORD_IDENTIFIER:
            case RAW_IDENTIFIER:
            case KW_MACRORULES:
                return false;
            default:
                return true;
            }
        }
    };
