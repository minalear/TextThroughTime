//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_GAME_MANAGER_H
#define TEXTTHROUGHTIME_GAME_MANAGER_H

#include <cstdlib>
#include <ctime>
#include "map.h"
#include "room.h"
#include "../window_manager.h"
#include "inventory.h"
#include "command_parser.h"

class lua_State;

class GameManager {
    WindowManager *window_manager;
    Map game_map;
    Room *current_room;
    Inventory player_inventory;

    lua_State* L;

    // Scripting functions
    void s_set_current_room(const char* id);
    void s_add_room(const char* unique_id, const char* name, const char* desc);
    void s_create_item(const char* item_id, const char* name, const char* desc, bool is_static);
    bool s_player_has_item(const char* item_id);
    bool s_remove_item(const char* item_id);
    void s_print(const char* line);

    // Command functions
    void c_help(const Command &command);
    void c_debug(const Command &command);
    void c_clear(const Command &command);
    void c_move(const Command &command);
    void c_examine(const Command &command);
    void c_pickup(const Command &command);
    void c_drop(const Command &command);
    void c_inventory(const Command &command);
    void c_interaction(const Command &command);

    void display_room();
    void set_current_room(Room* new_room);

public:
    GameManager(WindowManager *window_manager);
    ~GameManager();

    void initialize_game();
    void handle_input(const std::string &input);
};


#endif //TEXTTHROUGHTIME_GAME_MANAGER_H
