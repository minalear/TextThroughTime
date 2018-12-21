//
// Created by Trevor Fisher on 10/11/2018.
//

#include <lua.hpp>
#include <LuaBridge.h>
#include "game_manager.h"
#include "../core/file_handler.h"

using namespace luabridge;

GameManager::GameManager(WindowManager *window_manager) {
    this->window_manager = window_manager;

    L = luaL_newstate();
    luaL_openlibs(L);

    getGlobalNamespace(L)
    .beginClass<GameManager>("GameManager")
        .addFunction("AddRoom", &GameManager::s_add_room)
        .addFunction("SetCurrentRoom", &GameManager::s_set_current_room)
        .addFunction("Print", &GameManager::print)
        .addFunction("CreateItem", &GameManager::s_create_item)
    .endClass()
    .beginClass<Room>("Room")
        .addFunction("AttachRoom", &Room::s_attach_room)
        .addFunction("SetDescription", &Room::s_set_description)
        .addFunction("AppendDescription", &Room::s_append_description)
        .addFunction("AddItem", &Room::s_add_item)
        .addFunction("RemoveItem", &Room::s_remove_item)
    .endClass()
    .beginClass<Item>("Item")
        .addFunction("SetDescription", &Item::s_set_description)
        .addFunction("GetID", &Item::s_get_id)
        .addFunction("GetName", &Item::s_get_name)
    .endClass();

    push(L, this);
    lua_setglobal(L, "Manager");

    // TODO: Investigate why Lua modules (require()) doesn't seem to work
    // Manually load each script file since require() doesn't work

    std::string game_script = std::string(minalear::read_file("scripts/init.lua"));
    game_script += std::string(minalear::read_file("scripts/room_scripts.lua"));

    //luaL_dofile(L, "scripts/init.lua");
    luaL_dostring(L, game_script.c_str());
    lua_pcall(L, 0, 0, 0);

    initialize_game();
}
void GameManager::print(const char *line) {
    window_manager->print_to_log(std::string(line));
}

GameManager::~GameManager() { }

void GameManager::initialize_game() {
    //current_room = &rooms[0];
    display_room();
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
    else if (tokenized_input.command == "pickup") {
        c_pickup(tokenized_input);
    }
    else if (tokenized_input.command == "drop") {
        c_drop(tokenized_input);
    }
    else if (tokenized_input.command == "inventory") {
        c_inventory(tokenized_input);
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
    // Add the room to the game map
    auto new_room = game_map.add_room(std::string(unique_id), std::string(name), std::string(desc));

    // Make the room available in the init script
    push(L, new_room);
    lua_setglobal(L, unique_id);

    LuaRef room_table = getGlobal(L, unique_id);
}
void GameManager::s_create_item(const char *item_id, const char *name, const char *desc) {
    // Create the item
    auto new_item = new Item(std::string(item_id), std::string(name), std::string(desc));
    game_map.get_inventory()->add_item(new_item);

    // Make the item available in the init script
    push(L, new_item);
    lua_setglobal(L, item_id);
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
    Directions direction = Directions::None;
    if (!current_room->can_move(tokens[0], direction)) {
        window_manager->print_to_log("You cannot travel in that direction!");
        return;
    }

    // Move the character in the desired direction
    if (direction == Directions::North) {
        window_manager->print_to_log("You move towards the north.\n");
        auto next_room = current_room->get_room(Directions::North);
        set_current_room(next_room);
    }
    else if (direction == Directions::South) {
        window_manager->print_to_log("You move towards the south.\n");
        auto next_room = current_room->get_room(Directions::South);
        set_current_room(next_room);
    }
    else if (direction == Directions::East) {
        window_manager->print_to_log("You move towards the east.\n");
        auto next_room = current_room->get_room(Directions::East);
        set_current_room(next_room);
    }
    else if (direction == Directions::West) {
        window_manager->print_to_log("You move towards the west.\n");
        auto next_room = current_room->get_room(Directions::West);
        set_current_room(next_room);
    }

    display_room();
}
void GameManager::c_look(const TokenGroup &tokens) {
    if (tokens.n_tokens == 0) {
        display_room();
    }
    else if (tokens.n_tokens == 1) {
        Item *item = nullptr;
        if (player_inventory.get_item_by_name(tokens[0], item)) {
            window_manager->print_to_log(item->get_description() + "\n\n");
        }
        else if (current_room->get_inventory()->get_item_by_name(tokens[0], item)) {
            window_manager->print_to_log(item->get_description() + "\n\n");
        }
    }
}
void GameManager::c_suicide(const TokenGroup &tokens) {
    if (tokens[0] == "commit" && tokens[1] == "die") {
        window_manager->print_to_log("You can't do that yet boi.\n");
    }
}
void GameManager::c_pickup(const TokenGroup &tokens) {
    Item *item = nullptr;
    if (current_room->get_inventory()->get_item_by_name(tokens[0], item)) {
        current_room->get_inventory()->remove_item(item->get_id());
        player_inventory.add_item(item);
        window_manager->print_to_log("You pick up " + item->get_name() + " and add it to your knapsack.\n");
    }
    else {
        window_manager->print_to_log("There is no item to pickup by that name.\n");
    }
}
void GameManager::c_drop(const TokenGroup &tokens) {
    Item *item = nullptr;
    if (player_inventory.get_item_by_name(tokens[0], item)) {
        player_inventory.remove_item(item->get_id());
        current_room->get_inventory()->add_item(item);
        window_manager->print_to_log("You remove " + item->get_name() + " from your knapsack and place it on the floor.\n");

        std::string script_table_name = current_room->get_id() + "_SCRIPTS";
        LuaRef room_scripts = getGlobal(L, script_table_name.c_str());
        if (!room_scripts.isNil()) {
            room_scripts["OnItemDrop"](item);
        }
    }
    else {
        window_manager->print_to_log("There is no item to drop by that name.\n");
    }
}
void GameManager::c_inventory(const TokenGroup &tokens) {
    window_manager->print_to_log("== Current Inventory ==");
    window_manager->print_to_log(player_inventory.get_item_list());
}

void GameManager::display_room() {
    window_manager->set_title(current_room->get_name());
    window_manager->print_to_log(current_room->get_description() + "\n\n");
    window_manager->print_to_log("== Room Items ==");
    window_manager->print_to_log(current_room->get_inventory()->get_item_list() + "\n");
    window_manager->print_to_log("== Directions ==");
    if (current_room->can_move(Directions::North)) window_manager->print_to_log("- North (" + current_room->get_room(Directions::North)->get_name() + ")");
    if (current_room->can_move(Directions::South)) window_manager->print_to_log("- South (" + current_room->get_room(Directions::South)->get_name() + ")");
    if (current_room->can_move(Directions::East))  window_manager->print_to_log("- East (" + current_room->get_room(Directions::East)->get_name() + ")");
    if (current_room->can_move(Directions::West))  window_manager->print_to_log("- West (" + current_room->get_room(Directions::West)->get_name() + ")");
    window_manager->print_to_log(" ");
}
void GameManager::set_current_room(Room *new_room){
    current_room = new_room;
}