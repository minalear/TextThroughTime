//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_GAME_MANAGER_H
#define TEXTTHROUGHTIME_GAME_MANAGER_H

#include "map.h"
#include "room.h"
#include "../window_manager.h"
#include <cstdlib>
#include <ctime>

class lua_State;

class GameManager {
    WindowManager *window_manager;
    Map game_map;
    Room *current_room;

    lua_State* L;

    // Scripting functions
    void s_set_current_room(const char* id);
    void s_add_room(const char* unique_id, const char* name, const char* desc);
    void s_attach_room(const char* target_id, const char* base_id, const char* dir);

    void print(const char* line);

public:
    GameManager(WindowManager *window_manager);
    ~GameManager();

    void initialize_game();
    void process_input(const std::string &input);
};


#endif //TEXTTHROUGHTIME_GAME_MANAGER_H
