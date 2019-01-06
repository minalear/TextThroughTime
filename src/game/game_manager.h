//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_GAME_MANAGER_H
#define TEXTTHROUGHTIME_GAME_MANAGER_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include "map.h"
#include "room.h"
#include "npc.h"
#include "../window_manager.h"
#include "inventory.h"
#include "command_parser.h"
#include "game_variable_map.h"

class lua_State;

struct Prompt {
    std::string message;
    const char *table_name, *callback_function;

    std::vector<std::string> responses;
};

enum struct GAME_STATES {
    TRAVEL, PROMPT, DIALOG
};

class GameManager {
    WindowManager *window_manager;
    Map game_map;
    Room *current_room;
    Inventory player_inventory;

    lua_State* L;

    Prompt current_prompt;
    GAME_STATES current_state;

    GameVariableMap<std::string> global_str_variables;
    GameVariableMap<int>         global_int_variables;

    // Scripting functions
    void s_print(const char *msg);
    void s_progress_time(int amount, char type);
    void s_set_current_room(const char *id);
    void s_create_room(const char *room_id, const char *name);
    void s_create_item(const char *item_id, const char *name);
    void s_create_static_item(const char *item_id, const char *name);
    void s_create_npc(const char *npc_id, const char *name);
    void s_player_add_item(const char *item_id);
    void s_player_add_items(const char *item_id, int quantity);
    bool s_player_remove_item(const char *item_id);
    bool s_player_remove_items(const char *item_id, int quantity);
    bool s_player_has_item(const char* item_id);
    void s_create_prompt(const char *message, const char *table_name, const char* callback_function);
    void s_add_prompt_response(const char* response);
    void s_display_prompt();
    void s_set_str_variable(const char *key, const char *value);
    void s_set_int_variable(const char *key, int value);
    const char* s_get_str_variable(const char *key);
    int         s_get_int_variable(const char *key);

    // Command functions
    void c_help(const Command &command);
    void c_debug(const Command &command);
    void c_clear(const Command &command);
    void c_move(const Command &command);
    void c_examine_room(const Command &command);
    void c_examine_object(const Command &command);
    void c_pickup(const Command &command);
    void c_drop(const Command &command);
    void c_inventory(const Command &command);
    void c_talk(const Command &command);
    void c_interaction(const Command &command);

    void display_room();
    void display_prompt();
    void set_current_room(Room* new_room);

public:
    GameManager(WindowManager *window_manager);
    ~GameManager();

    void initialize_game();
    void handle_input(const std::string &input);
};




#endif //TEXTTHROUGHTIME_GAME_MANAGER_H
