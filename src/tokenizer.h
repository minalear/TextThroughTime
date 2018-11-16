//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_TOKENIZER_H
#define TEXTTHROUGHTIME_TOKENIZER_H

#include <iostream>

struct TokenGroup {
    std::string command;
    std::string *tokens;
    int n_tokens;

    TokenGroup();
    ~TokenGroup();
};

TokenGroup tokenize(const std::string &str);

#endif //TEXTTHROUGHTIME_TOKENIZER_H
