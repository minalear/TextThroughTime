//
// Created by minal on 1/5/2019.
//

#ifndef TEXTTHROUGHTIME_NPC_H
#define TEXTTHROUGHTIME_NPC_H

#include <string>
#include <vector>
#include "game_variable_map.h"

class NPC; // C++ >.>

struct DialogState {
    std::string id;
    std::string dialog_text;
    std::vector<std::string> dialog_options;
    NPC *owner;

    DialogState(const std::string &unique_id, NPC *owner);
};

class NPC {
    std::string id;
    std::string name;
    std::string description;
    std::string room_description;
    std::string current_state;
    std::vector<std::string> aliases;

    std::vector<std::string> properties;
    GameVariableMap<std::string> string_variables;
    GameVariableMap<int>         int_variables;

    std::string dialog_script;
    std::string current_dialog_state;
    std::vector<DialogState*> dialog_states;

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
    bool        s_has_property(const char *property);

    void s_set_name(const char *name);
    void s_set_description(const char *desc);
    void s_set_room_description(const char *desc);
    void s_set_state(const char *state);
    void s_add_alias(const char *alias);
    void s_set_str_variable(const char *key, const char *value);
    void s_set_int_variable(const char *key, int value);
    void s_add_property(const char *property);
    void s_remove_property(const char *property);

    // Dialog centric scripting functions
    void s_set_dialog_script(const char *table_name);
    void s_create_dialog_state(const char *state);
    void s_set_dialog_state(const char *state);
    void s_set_dialog_string(const char *state, const char *str);
    void s_add_dialog_option(const char *state, const char *str);
    const char* s_get_dialog_state();

    // Getters/Setters
    std::string get_id();
    std::string get_name();
    std::string get_description();
    std::string get_room_description();
    std::string get_state();
    std::string get_dialog_state();
    std::string get_dialog_script();
    bool get_dialog_state(const std::string &id, DialogState *&state);
    void set_name(const std::string &name);
    void set_description(const std::string &desc);
    void set_room_description(const std::string &desc);
    void set_state(const std::string &state);

    bool check_name(const std::string &name);
};

#endif //TEXTTHROUGHTIME_NPC_H
