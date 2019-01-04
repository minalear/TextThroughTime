//
// Created by minal on 12/19/2018.
//

#include "item.h"
#include "../tokenizer.h"

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

// Scripting specific functions
const char* Item::s_get_id() {
    return id.c_str();
}
const char* Item::s_get_name() {
    return name.c_str();
}
const char* Item::s_get_state() {
    return current_state.c_str();
}
const char* Item::s_get_str_variable(const char *key) {
    return string_variables.get_variable(std::string(key)).c_str();
}
int Item::s_get_int_variable(const char *key) {
    return int_variables.get_variable(std::string(key));
}
void Item::s_set_name(const char *name) {
    set_name(std::string(name));
}
void Item::s_set_description(const char *desc) {
    set_description(std::string(desc));
}
void Item::s_append_description(const char *desc) {
    set_description(description + "\n" + std::string(desc));
}
void Item::s_set_room_description(const char *desc) {
    set_room_description(std::string(desc));
}
void Item::s_set_state(const char *state) {
    set_state(std::string(state));
}
void Item::s_add_alias(const char *alias) {
    aliases.push_back(std::string(alias));
}
void Item::s_set_str_variable(const char *key, const char *value) {
    string_variables.set_variable(std::string(key), std::string(value));
}
void Item::s_set_int_variable(const char *key, int value) {
    int_variables.set_variable(std::string(key), value);
}

std::string Item::get_id() {
    return this->id;
}
std::string Item::get_name() {
    return this->name;
}
std::string Item::get_description() {
    return this->description;
}
std::string Item::get_room_description() {
    return this->room_description;
}
std::string Item::get_state() {
    return this->current_state;
}
bool Item::get_is_static() {
    return this->is_static;
}

void Item::set_name(const std::string &name) {
    this->name = name;
}
void Item::set_description(const std::string &desc) {
    this->description = desc;
}
void Item::set_room_description(const std::string &desc) {
    this->room_description = desc;
}
void Item::set_is_static(bool value) {
    this->is_static = value;
}
void Item::set_state(const std::string &state) {
    this->current_state = state;
}
bool Item::check_name(const std::string &test) {
    const std::string caps_test = to_caps(test);
    if (to_caps(name) == caps_test) return true;
    for (const auto &x : aliases) {
        if (to_caps(x) == caps_test) return true;
    }

    return false;
}
