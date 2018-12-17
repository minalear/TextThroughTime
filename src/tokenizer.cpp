//
// Created by Trevor Fisher on 10/11/2018.
//

#include "tokenizer.h"

TokenGroup::TokenGroup() {
    n_tokens = 0;
    tokens = nullptr;
}
TokenGroup::~TokenGroup() {
    delete[] tokens;
}

TokenGroup tokenize(const std::string &str) {
    std::string buffer;
    std::string temp_tokens[100];
    TokenGroup token_group;
    token_group.n_tokens = 0;

    bool ignore_spaces = false;

    // Parse insput string and split it up via spaces
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

    // Place tokenized input into a TokenGroup and return it
    token_group.tokens = new std::string[token_group.n_tokens-1];
    token_group.command = temp_tokens[0];
    for (int i = 1; i < token_group.n_tokens; i++) {
        token_group.tokens[i-1] = temp_tokens[i];
    }
    token_group.n_tokens -= 1; // Don't count the command as a token

    return token_group;
}