//
// Created by minal on 12/19/2018.
//

#ifndef TEXTTHROUGHTIME_ITEM_H
#define TEXTTHROUGHTIME_ITEM_H

#include <string>

class Item {
    std::string id, name, description;
    bool is_static = false;

public:
    Item(const std::string &id);
    Item(const std::string &id, const std::string &name, const std::string &desc);
    ~Item();

    std::string get_id();
    std::string get_name();
    std::string get_description();
    bool get_is_static();

    void set_name(const std::string &name);
    void set_description(const std::string &desc);
    void set_is_static(bool value);

    void s_set_description(const char* desc);
    const char* s_get_id();
    const char* s_get_name();
};

#endif //TEXTTHROUGHTIME_ITEM_H
