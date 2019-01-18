//
// Created by minal on 1/17/2019.
//

#include "game_object.h"
#include "../tokenizer.h"

GameObject::GameObject(Map *map, const std::string& id) : GameObject(map, id, "[NULL]", "[NULL]") { }
GameObject::GameObject(Map *map, const std::string& id, const std::string& name, const std::string& desc) {
    game_map = map;
    set_id(id);
    set_name(name);
    set_description(desc);
}

// Scripting functions
const char *GameObject::s_get_id() {
    return id.c_str();
}
const char *GameObject::s_get_name() {
    return name.c_str();
}
const char *GameObject::s_get_description() {
    return description.c_str();
}
const char *GameObject::s_get_room_description() {
    return room_description.c_str();
}
const char *GameObject::s_get_state() {
    return current_state.c_str();
}
const char *GameObject::s_get_str_variable(const char *key) {
    return string_variables.get_variable(std::string(key)).c_str();
}
int GameObject::s_get_int_variable(const char *key) {
    return int_variables.get_variable(std::string(key));
}
bool GameObject::s_has_variable(const char *key) {
    auto str_key = std::string(key);
    return (string_variables.has_variable(str_key) || int_variables.has_variable(str_key));
}
bool GameObject::s_has_property(const char *prop) {
    const std::string property = std::string(prop);
    for (const auto &x : properties) {
        if (property == x) return true;
    }

    return false;
}

void GameObject::s_set_name(const char *name) {
    this->name = std::string(name);
}
void GameObject::s_set_description(const char *desc) {
    description = std::string(desc);
}
void GameObject::s_set_room_description(const char *desc) {
    room_description = std::string(desc);
}
void GameObject::s_set_state(const char *state) {
    current_state = std::string(state);
}
void GameObject::s_add_alias(const char *alias) {
    aliases.emplace_back(std::string(alias));
}
void GameObject::s_set_str_variable(const char *key, const char *value) {
    string_variables.set_variable(std::string(key), std::string(value));
}
void GameObject::s_set_int_variable(const char *key, int value) {
    int_variables.set_variable(std::string(key), value);
}
void GameObject::s_add_property(const char *property) {
    properties.emplace_back(std::string(property));
}
void GameObject::s_remove_property(const char *prop) {
    const std::string property = std::string(prop);
    for (int i = 0; i < properties.size(); i++) {
        if (property == properties[i]) {
            properties.erase(properties.begin() + i);
        }
    }
}

// Standard Functions
std::string GameObject::get_id() {
    return id;
}
std::string GameObject::get_name() {
    return name;
}
std::string GameObject::get_description() {
    return description;
}
std::string GameObject::get_room_description() {
    return room_description;
}
std::string GameObject::get_state() {
    return current_state;
}

void GameObject::set_id(const std::string &value) {
    id = value;
}
void GameObject::set_name(const std::string &value) {
    name = value;
}
void GameObject::set_description(const std::string &value) {
    description = value;
}
void GameObject::set_room_description(const std::string &value) {
    room_description = value;
}
void GameObject::set_state(const std::string &value) {
    current_state = value;
}

bool GameObject::check_name(const std::string &value) {
    // Check the name and all aliases to see if it matches the provided name
    const std::string caps_test = to_caps(value);
    if (to_caps(name) == caps_test) return true;
    for (const auto &x : aliases) {
        if (to_caps(x) == caps_test) return true;
    }

    return false;
}

