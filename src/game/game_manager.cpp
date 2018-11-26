//
// Created by Trevor Fisher on 10/11/2018.
//

#include "game_manager.h"
#include <lua.hpp>
#include <LuaBridge.h>

using namespace luabridge;

GameManager::GameManager(WindowManager *window_manager) {
    this->window_manager = window_manager;

    L = luaL_newstate();
    luaL_openlibs(L);
    getGlobalNamespace(L)
    .beginClass<GameManager>("GameManager")
        .addFunction("AddRoom", &GameManager::s_add_room)
        .addFunction("AttachRoom", &GameManager::s_attach_room)
        .addFunction("SetCurrentRoom", &GameManager::s_set_current_room)
        .addFunction("Print", &GameManager::print)
    .endClass();
    push(L, this);
    lua_setglobal(L, "Manager");

    luaL_dofile(L, "scripts/init.lua");
    lua_pcall(L, 0, 0, 0);

    initialize_game();
}
void GameManager::print(const char *line) {
    window_manager->print_to_log(std::string(line));
}

GameManager::~GameManager() { }

void GameManager::initialize_game() {
    //current_room = &rooms[0];
    window_manager->set_title(current_room->get_name());
    window_manager->print_to_log(current_room->get_description());
    window_manager->print_to_log("\n");
}

void GameManager::process_input(const std::string &input) {
    // Tokenize player input
    auto tokenized_input = tokenize(input);

    // Commands
    if (tokenized_input.command == "help") {
        c_help();
    }
    else if (tokenized_input.command == "clear") {
        c_clear();
    }
    else if (tokenized_input.command == "move") {
        c_move(tokenized_input);
    }
    else if (tokenized_input.command == "look") {
        c_look(tokenized_input);
    }
    else if (tokenized_input.command == "go") {
        c_suicide(tokenized_input);
    }

    // No valid input
    else {
        window_manager->print_to_log("Please input a valid command.  Type 'help' for a complete list.");
    }
}

// Scripting Functions
void GameManager::s_set_current_room(const char *id) {
    current_room = game_map.get_room(std::string(id));
}
void GameManager::s_add_room(const char *unique_id, const char *name, const char *desc) {
    game_map.add_room(std::string(unique_id), std::string(name), std::string(desc));
}
void GameManager::s_attach_room(const char *target_id, const char *base_id, const char *dir) {
    game_map.attach_room(std::string(target_id), std::string(base_id), std::string(dir));

}

// Command Functions
void GameManager::c_help() {
    window_manager->print_to_log("This is a helpful response.");
}
void GameManager::c_clear() {
    window_manager->clear_log();
}
void GameManager::c_move(const TokenGroup &tokens) {
    // Test for valid number of args
    if (tokens.n_tokens != 1) {
        window_manager->print_to_log("Please input the correct number of arguments (move [direction]).");
        return;
    }

    // Check for valid direction
    std::string direction = tokens.tokens[0];
    if (!current_room->can_move(direction)) {
        window_manager->print_to_log("You cannot travel in that direction!");
        return;
    }

    // Move the character in the desired direction
    if (direction == "north") {
        window_manager->print_to_log("You move towards the north.");
        current_room = current_room->get_room(Directions::North);
    }
    else if (direction == "south") {
        window_manager->print_to_log("You move towards the south.");
        current_room = current_room->get_room(Directions::South);
    }
    else if (direction == "east") {
        window_manager->print_to_log("You move towards the east.");
        current_room = current_room->get_room(Directions::East);
    }
    else if (direction == "west") {
        window_manager->print_to_log("You move towards the west.");
        current_room = current_room->get_room(Directions::West);
    }

    window_manager->set_title(current_room->get_name());
    window_manager->print_to_log(current_room->get_description() + "\n");
}
void GameManager::c_look(const TokenGroup &tokens) {
    if (tokens.n_tokens == 0) {
        window_manager->print_to_log(current_room->get_description() + "\n");
    }
}
void GameManager::c_suicide(const TokenGroup &tokens) {
    if (tokens.tokens[0] == "commit" && tokens.tokens[1] == "die") {
        window_manager->print_to_log("You can't do that yet boi.\n");
    }
}