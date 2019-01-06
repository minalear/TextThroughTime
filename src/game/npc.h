//
// Created by minal on 1/5/2019.
//

#ifndef TEXTTHROUGHTIME_NPC_H
#define TEXTTHROUGHTIME_NPC_H

#include <string>
#include <vector>
#include "game_variable_map.h"

class NPC {
    std::string id;
    std::string name;
    std::string description;
    std::string room_description;
    std::string current_state;

    std::vector<std::string> aliases;

    GameVariableMap<std::string> string_variables;
    GameVariableMap<int>         int_variables;

public:

    NPC(const std::string &id);
    NPC(const std::string &id, const std::string &name, const std::string &desc);
    ~NPC();

    //Script functions
    const char* s_get_id();
    const char* s_get_name();
    const char* s_get_description();
    const char* s_get_room_description();
    const char* s_get_state();
    const char* s_get_str_variable(const char *key);
    int         s_get_int_variable(const char *key);

    void s_set_name(const char *name);
    void s_set_description(const char *desc);
    void s_set_room_description(const char *desc);
    void s_set_state(const char *state);
    void s_add_alias(const char *alias);
    void s_set_str_variable(const char *key, const char *value);
    void s_set_int_variable(const char *key, int value);

    // Getters/Setters
    std::string get_id();
    std::string get_name();
    std::string get_description();
    std::string get_room_description();
    std::string get_state();
    void set_name(const std::string &name);
    void set_description(const std::string &desc);
    void set_room_description(const std::string &desc);
    void set_state(const std::string &state);

    bool check_name(const std::string &name);
};

#endif //TEXTTHROUGHTIME_NPC_H
