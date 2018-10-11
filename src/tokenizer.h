//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_TOKENIZER_H
#define TEXTTHROUGHTIME_TOKENIZER_H

#include <iostream>

struct TokenGroup {
    std::string *tokens;
    int n_tokens;

    TokenGroup() {
        n_tokens = 0;
        tokens = nullptr;
    }
    ~TokenGroup() {
        delete [] tokens;
    }
};

TokenGroup tokenize(const std::string &str) {
    std::string buffer;
    auto temp_tokens = new std::string[100];
    TokenGroup token_group;
    token_group.n_tokens = 0;

    bool ignore_spaces = false;

    for (auto& x : str) {
        if (x == ' ' && !ignore_spaces) {
            temp_tokens[token_group.n_tokens] = buffer;
            token_group.n_tokens++;
            buffer.clear();
        } else if (x == '"') {
            ignore_spaces = !ignore_spaces;
        } else {
            buffer += x;
        }
    }
    if (!buffer.empty()) {
        temp_tokens[token_group.n_tokens] = buffer;
        token_group.n_tokens++;
    }

    token_group.tokens = new std::string[token_group.n_tokens];
    for (int i = 0; i < token_group.n_tokens; i++) {
        token_group.tokens[i] = temp_tokens[i];
    }
    delete [] temp_tokens;

    return token_group;
}

#endif //TEXTTHROUGHTIME_TOKENIZER_H
