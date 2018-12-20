//
// Created by minal on 12/19/2018.
//

#include "item.h"

Item::Item(const std::string &id) {
    this->id = id;
    set_name("[ROOM]");
    set_description("[DESCRIPTION]");
}
Item::Item(const std::string &id, const std::string &name, const std::string &desc) {
    this->id = id;
    set_name(name);
    set_description(desc);
}
Item::~Item() { }

std::string Item::get_id() {
    return this->id;
}
std::string Item::get_name() {
    return this->name;
}
std::string Item::get_description() {
    return this->description;
}

void Item::set_name(const std::string &name) {
    this->name = name;
}
void Item::set_description(const std::string &desc) {
    this->description = desc;
}