
/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */
 //
 //  RustParserBase.h
 //
 //  dev: jcju
 //
#pragma once

#include "antlr4-runtime.h"
using namespace antlr4;
    class RustParserBase : public Parser {
    public:
        TokenStream* _input;
    protected:
        RustParserBase(antlr4::TokenStream* input)
            : Parser(input) {
            _input = input;
        }
    public:
        bool next(char expect) {
            return _input->LA(1) == expect;
        }
    };
