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
        .addFunction("Print", &GameManager::s_print)
        .addFunction("CreateItem", &GameManager::s_create_item)
        .addFunction("PlayerHasItem", &GameManager::s_player_has_item)
        .addFunction("RemoveItem", &GameManager::s_remove_item)
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
        .addFunction("IsStatic", &Item::get_is_static)
        .addFunction("SetIsStatic", &Item::set_is_static)
    .endClass();

    push(L, this);
    lua_setglobal(L, "Manager");

    luaL_dofile(L, "scripts/init.lua");
    lua_pcall(L, 0, 0, 0);

    initialize_game();
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
    else if (tokenized_input.command == "debug") {
        c_debug(tokenized_input);
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
void GameManager::s_create_item(const char *item_id, const char *name, const char *desc, bool is_static) {
    // Create the item
    auto new_item = new Item(std::string(item_id), std::string(name), std::string(desc));
    new_item->set_is_static(is_static);
    game_map.get_inventory()->add_item(new_item);

    // Make the item available in the init script
    push(L, new_item);
    lua_setglobal(L, item_id);
}
bool GameManager::s_player_has_item(const char* item_id) {
    Item* item;
    return player_inventory.get_item(item_id, item);
}
bool GameManager::s_remove_item(const char* item_id) {
    return player_inventory.remove_item(item_id);
}
void GameManager::s_print(const char *line) {
    window_manager->print_to_log(std::string(line));
}

// Command Functions
void GameManager::c_help() {
    window_manager->print_to_log("This is a helpful response.");
}
void GameManager::c_debug(const TokenGroup &tokens) {
    if (tokens[0] == "inventory") {
        window_manager->print_to_log("== Current Player Inventory (Debug) ==");
        window_manager->print_to_log(player_inventory.get_item_list(false));
        window_manager->print_to_log("\n== Current Room Inventory (Debug) ==");
        window_manager->print_to_log(current_room->get_inventory()->get_item_list(false));
    }
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
        //window_manager->print_to_log("You move towards the north.\n");
        auto next_room = current_room->get_room(Directions::North);
        set_current_room(next_room);
    }
    else if (direction == Directions::South) {
        //window_manager->print_to_log("You move towards the south.\n");
        auto next_room = current_room->get_room(Directions::South);
        set_current_room(next_room);
    }
    else if (direction == Directions::East) {
        //window_manager->print_to_log("You move towards the east.\n");
        auto next_room = current_room->get_room(Directions::East);
        set_current_room(next_room);
    }
    else if (direction == Directions::West) {
        //window_manager->print_to_log("You move towards the west.\n");
        auto next_room = current_room->get_room(Directions::West);
        set_current_room(next_room);
    }

    display_room();
}
void GameManager::c_look(const TokenGroup &tokens) {
    if (tokens.n_tokens == 0) {
        display_room();

        // Execute the OnLook trigger
        std::string script_table_name = current_room->get_id() + "_SCRIPTS";
        LuaRef room_scripts = getGlobal(L, script_table_name.c_str());
        if (!room_scripts.isNil()) {
            room_scripts["OnLook"]();
        }
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
        if (item->get_is_static()) {
            // We cannot pickup static items.
            window_manager->print_to_log("You cannot pick that up!");
        }
        else {
            // We can pickup non-static items.
            current_room->get_inventory()->remove_item(item->get_id());
            player_inventory.add_item(item);
            window_manager->print_to_log("You pick up " + item->get_name() + " and add it to your knapsack.\n");

            // Execute the OnItemPickup trigger
            std::string script_table_name = current_room->get_id() + "_SCRIPTS";
            LuaRef room_scripts = getGlobal(L, script_table_name.c_str());
            if (!room_scripts.isNil()) {
                room_scripts["OnItemPickup"](item);
            }
        }
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

        // Execute the OnItemDrop trigger
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
    bool canMove = true; // Set this to the OnExit script function which either allows or disallows the movement of the player

    // Trigger the OnExit function on the current room and the OnEnter function on the new room
    if (current_room != nullptr) {
        std::string old_room_table = current_room->get_id() + "_SCRIPTS";
        LuaRef old_room_scripts = getGlobal(L, old_room_table.c_str());
        if (!old_room_scripts.isNil()) {
            canMove = old_room_scripts["OnExit"]();
        }
    }

    if (canMove) {
        current_room = new_room;

        std::string script_table_name = current_room->get_id() + "_SCRIPTS";
        LuaRef room_scripts = getGlobal(L, script_table_name.c_str());
        if (!room_scripts.isNil()) {
            room_scripts["OnEnter"]();
        }
        window_manager->print_to_log("You enter " + current_room->get_name());
    }
}