//
// Created by minal on 12/19/2018.
//

#ifndef TEXTTHROUGHTIME_ITEM_H
#define TEXTTHROUGHTIME_ITEM_H

#include <string>

class Item {
    std::string name, description;

public:
    Item();
    Item(const std::string &name, const std::string desc);
    ~Item();

    std::string get_name();
    std::string get_description();

    void set_name(const std::string &name);
    void set_description(const std::string &desc);
};

#endif //TEXTTHROUGHTIME_ITEM_H
