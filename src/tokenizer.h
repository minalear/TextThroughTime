//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_TOKENIZER_H
#define TEXTTHROUGHTIME_TOKENIZER_H

#include <iostream>
#include <vector>

struct TokenGroup {
    std::string *tokens;
    int n_tokens;

    TokenGroup();
    ~TokenGroup();

    std::string& operator[](int index) const;
};

TokenGroup tokenize(const std::string &str);
std::string to_caps(const std::string &str);

template <class T>
bool contains(const T &item, const std::vector<T> &item_list) {
    for (const auto &x : item_list) {
        if (item == x) return true;
    }
    return false;
}

#endif //TEXTTHROUGHTIME_TOKENIZER_H
