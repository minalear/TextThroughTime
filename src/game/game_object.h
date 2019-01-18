//
// Created by minal on 1/17/2019.
//

#ifndef TEXTTHROUGHTIME_GAME_OBJECT_H
#define TEXTTHROUGHTIME_GAME_OBJECT_H

#include <string>
#include <vector>
#include "game_variable_map.h"
#include "map.h"

class GameObject {
protected:
    std::string id; // The unique ID of the item
    std::string name; // The name that appears in the inventory
    std::string description; // The description of the item when examined
    std::string room_description; // The description of the item while it's in the room.  Appears when the room is examined.
    std::string current_state; // Used to define different behaviors depending on the item's current state

    std::vector<std::string> aliases; // Alternative short names that can be used to refer to this item
    std::vector<std::string> properties;

    GameVariableMap<std::string> string_variables;
    GameVariableMap<int>         int_variables;

    Map *game_map;

public:
    GameObject(Map *map, const std::string& id);
    GameObject(Map *map, const std::string& id, const std::string& name, const std::string& desc);

    // Scripting specific functions
    const char* s_get_id();
    const char* s_get_name();
    const char* s_get_description();
    const char* s_get_room_description();
    const char* s_get_state();
    const char* s_get_str_variable(const char *key);
    int s_get_int_variable(const char *key);
    bool s_has_variable(const char *key);
    bool s_has_property(const char *property);

    void s_set_name(const char *name);
    void s_set_description(const char *desc);
    void s_set_room_description(const char *desc);
    void s_set_state(const char *state);
    void s_add_alias(const char *alias);
    void s_set_str_variable(const char *key, const char *value);
    void s_set_int_variable(const char *key, int value);
    void s_add_property(const char *property);
    void s_remove_property(const char *property);

    // Normal functions
    virtual std::string get_id();
    virtual std::string get_name();
    virtual std::string get_description();
    virtual std::string get_room_description();
    virtual std::string get_state();

    void set_id(const std::string &id);
    void set_name(const std::string &name);
    void set_description(const std::string &desc);
    void set_room_description(const std::string &desc);
    void set_state(const std::string &desc);

    bool check_name(const std::string &value);
};

#endif //TEXTTHROUGHTIME_GAME_OBJECT_H
