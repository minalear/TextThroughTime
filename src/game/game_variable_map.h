//
// Created by minal on 1/4/2019.
//

#ifndef TEXTTHROUGHTIME_GAMEVARIABLEMAP_H
#define TEXTTHROUGHTIME_GAMEVARIABLEMAP_H

#include <map>
#include <string>
#include <cassert>

template <class T>
class GameVariableMap {
    std::map<std::string, T> map;

public:
    const T& get_variable(const std::string &key);
    void set_variable(const std::string &key, T value);
    bool has_variable(const std::string &key);
};

template <class T>
const T& GameVariableMap<T>::get_variable(const std::string &key) {
    auto find = map.find(key);
    assert(find != map.end()); // TODO: Replace this with try-catch

    return find->second;
}

template <class T>
void GameVariableMap<T>::set_variable(const std::string &key, T value) {
    auto find = map.find(key);
    if (find == map.end()) { // Variable doesn't already exist
        map.insert(std::make_pair(key, value));
    } else {
        find->second = value;
    }
}

template <class T>
bool GameVariableMap<T>::has_variable(const std::string &key) {
    auto find = map.find(key);
    return (find != map.end());
}

#endif //TEXTTHROUGHTIME_GAMEVARIABLEMAP_H
