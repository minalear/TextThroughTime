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

    std::string& operator[](int index) const;
};

TokenGroup tokenize(const std::string &str);
std::string to_caps(const std::string &str);

#endif //TEXTTHROUGHTIME_TOKENIZER_H
