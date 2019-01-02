//
// Created by Trevor Fisher on 10/11/2018.
//

#include <lua.hpp>
#include <LuaBridge.h>
#include "game_manager.h"
#include "../core/math_utils.h"

using namespace luabridge;

GameManager::GameManager(WindowManager *window_manager) {
    this->window_manager = window_manager;
    current_room = nullptr;

    L = luaL_newstate();
    luaL_openlibs(L);

    getGlobalNamespace(L)
        .addFunction("Rand", minalear::rand_int)
    .beginClass<GameManager>("GameManager")
        .addFunction("Print", &GameManager::s_print)
        .addFunction("ProgressTime", &GameManager::s_progress_time)
        .addFunction("SetCurrentRoom", &GameManager::s_set_current_room)

        .addFunction("CreateRoom", &GameManager::s_create_room)
        .addFunction("CreateItem", &GameManager::s_create_item)
        .addFunction("CreateStaticItem", &GameManager::s_create_static_item)

        .addFunction("PlayerAddItem", &GameManager::s_player_add_item)
        .addFunction("PlayerAddItems", &GameManager::s_player_add_items)
        .addFunction("PlayerRemoveItem", &GameManager::s_player_remove_item)
        .addFunction("PlayerRemoveItems", &GameManager::s_player_remove_items)
        .addFunction("PlayerHasItem", &GameManager::s_player_has_item)

        .addFunction("CreatePrompt", &GameManager::s_create_prompt)
        .addFunction("AddPromptResponse", &GameManager::s_add_prompt_response)
        .addFunction("DisplayPrompt", &GameManager::s_display_prompt)
    .endClass()
    .beginClass<Room>("Room")
        .addFunction("GetID", &Room::s_get_id)
        .addFunction("GetName", &Room::s_get_name)
        .addFunction("SetName", &Room::s_set_name)
        .addFunction("SetDescription", &Room::s_set_description)
        .addFunction("AppendDescription", &Room::s_append_description)
        .addFunction("AttachRoom", &Room::s_attach_room)
        .addFunction("ConnectRooms", &Room::s_connect_rooms)
        .addFunction("AddItem", &Room::s_add_item)
        .addFunction("AddItems", &Room::s_add_items)
        .addFunction("RemoveItem", &Room::s_remove_item)
        .addFunction("RemoveItems", &Room::s_remove_items)
    .endClass()
    .beginClass<Item>("Item")
        .addFunction("GetID", &Item::s_get_id)
        .addFunction("GetName", &Item::s_get_name)
        .addFunction("SetName", &Item::s_set_name)
        .addFunction("SetDescription", &Item::s_set_description)
        .addFunction("AppendDescription", &Item::s_append_description)
        .addFunction("IsStatic", &Item::get_is_static)
        .addFunction("SetIsStatic", &Item::set_is_static)
        .addFunction("AddAlias", &Item::s_add_alias)
    .endClass();

    push(L, this);
    lua_setglobal(L, "Manager");

    luaL_dofile(L, "scripts/init.lua");
    lua_pcall(L, 0, 0, 0);

    initialize_game();
}
GameManager::~GameManager() { }

void GameManager::initialize_game() {
    current_state = GAME_STATES::TRAVEL;
    display_room();
}

void GameManager::handle_input(const std::string &input) {
    // Process player input into a Command
    auto command = process_input(tokenize(input));

    if (current_state == GAME_STATES::TRAVEL) {
        if (command.type == COMMAND_TYPES::NONE) {
            window_manager->print_to_log("The input does not appear to be valid.  Double check your spelling.  Type 'help' for a complete list.");
        } else if (command.type == COMMAND_TYPES::DEBUG) {
            c_debug(command);
        } else if (command.type == COMMAND_TYPES::HELP) {
            c_help(command);
        } else if (command.type == COMMAND_TYPES::CLEAR_SCREEN) {
            c_clear(command);
        } else if (command.type == COMMAND_TYPES::MOVE) {
            c_move(command);
        } else if (command.type == COMMAND_TYPES::DROP) {
            c_drop(command);
        } else if (command.type == COMMAND_TYPES::PICKUP) {
            c_pickup(command);
        } else if (command.type == COMMAND_TYPES::PLACE) {
            // c_place(command);
        } else if (command.type == COMMAND_TYPES::EXAMINE_ROOM) {
            c_examine_room(command);
        } else if (command.type == COMMAND_TYPES::EXAMINE_ITEM) {
            c_examine_item(command);
        } else if (command.type == COMMAND_TYPES::INTERACTION) {
            c_interaction(command);
        }
    } else if (current_state == GAME_STATES::PROMPT) {
        LuaRef prompt_callback = getGlobal(L, current_prompt.table_name)[current_prompt.callback_function];
        if (prompt_callback(command.primary)) {
            current_state = GAME_STATES::TRAVEL;
            window_manager->print_to_log("\n\n");
            display_room();
        } else {
            window_manager->print_to_log("Invalid response.\n\n");
            display_prompt();
        }

        // TODO: Do better error checking
        // just calling prompt_callback could be an error if the script isn't function correctly
    }
}

// Scripting Functions
void GameManager::s_print(const char *line) {
    window_manager->print_to_log(std::string(line));
}
void GameManager::s_progress_time(int amount, char type) {
    // TODO: Implement TIME
}
void GameManager::s_set_current_room(const char *id) {
    set_current_room(game_map.get_room(std::string(id)));
}
void GameManager::s_create_room(const char *unique_id, const char *name) {
    // Add the room to the game map
    auto new_room = game_map.add_room(std::string(unique_id), std::string(name), "NULL DESCRIPTION");

    // Make the room available in the init script
    push(L, new_room);
    lua_setglobal(L, unique_id);

    LuaRef room_table = getGlobal(L, unique_id);
}
void GameManager::s_create_item(const char *item_id, const char *name) {
    // Create the item
    auto new_item = new Item(std::string(item_id), std::string(name), "NULL DESCRIPTION");
    new_item->set_is_static(false);
    game_map.get_inventory()->add_item(new_item);

    // Make the item available in the init script
    push(L, new_item);
    lua_setglobal(L, item_id);
}
void GameManager::s_create_static_item(const char *item_id, const char *name) {
    // Create the item
    auto new_item = new Item(std::string(item_id), std::string(name), "NULL DESCRIPTION");
    new_item->set_is_static(true);
    game_map.get_inventory()->add_item(new_item);

    // Make the item available in the init script
    push(L, new_item);
    lua_setglobal(L, item_id);
}
void GameManager::s_player_add_item(const char *item_id) {
    Item *item;
    game_map.get_inventory()->get_item(item_id, item);
    player_inventory.add_item(item);
}
void GameManager::s_player_add_items(const char *item_id, int quantity) {
    Item *item;
    game_map.get_inventory()->get_item(item_id, item);
    player_inventory.add_item(item);
    // TODO: Implement item quantities
}
bool GameManager::s_player_remove_item(const char *item_id) {
    return player_inventory.remove_item(item_id);
}
bool GameManager::s_player_remove_items(const char *item_id) {
    return player_inventory.remove_item(item_id);
}
bool GameManager::s_player_has_item(const char *item_id) {
    Item *item;
    return player_inventory.get_item(item_id, item);
}

void GameManager::s_create_prompt(const char *message, const char *table_name, const char* callback_function) {
    current_prompt.message = std::string(message);
    current_prompt.table_name = table_name;
    current_prompt.callback_function = callback_function;
    current_prompt.responses.clear();
}
void GameManager::s_add_prompt_response(const char* response) {
    current_prompt.responses.emplace_back(std::string(response));
}
void GameManager::s_display_prompt() {
    display_prompt();
}

// Command Functions
void GameManager::c_help(const Command &command) {
    window_manager->print_to_log("This is a helpful response.");
}
void GameManager::c_debug(const Command &command) {
    if (command.args[0] == "inventory") {
        window_manager->print_to_log("== Current Player Inventory (Debug) ==");
        window_manager->print_to_log(player_inventory.get_item_list(false));
        window_manager->print_to_log("\n== Current Room Inventory (Debug) ==");
        window_manager->print_to_log(current_room->get_inventory()->get_item_list(false));
    }
    else if (command.args[0] == "move") {
        auto next_room = game_map.get_room(command.args[1]);
        set_current_room(next_room);
    }
    else if (command.args[0] == "additem") {
        Item *item = nullptr;
        if (game_map.get_inventory()->get_item(command.args[1], item)) {
            player_inventory.add_item(item);
        }
    }
}
void GameManager::c_clear(const Command &command) {
    window_manager->clear_log();
}
void GameManager::c_move(const Command &command) {
    // Test for valid number of args
    if (command.n_args != 1) {
        window_manager->print_to_log("Please input the correct number of arguments (move [direction]).");
        return;
    }

    // Check for valid direction
    Directions direction = Directions::None;
    if (!current_room->can_move(command.args[0], direction)) {
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
void GameManager::c_examine_room(const Command &command) {
    display_room();

    // Execute the OnLook trigger
    std::string script_table_name = current_room->get_id() + "_SCRIPTS";
    LuaRef room_scripts = getGlobal(L, script_table_name.c_str());
    if (!room_scripts.isNil() && !room_scripts["OnLook"].isNil()) {
        room_scripts["OnLook"]();
    }
}
void GameManager::c_examine_item(const Command &command) {
    Item *item = nullptr;
    if (player_inventory.get_item_by_name(command.args[0], item)) {
        window_manager->print_to_log(item->get_description() + "\n\n");
    }
    else if (current_room->get_inventory()->get_item_by_name(command.args[0], item)) {
        window_manager->print_to_log(item->get_description() + "\n\n");
    }
}
void GameManager::c_pickup(const Command &command) {
    Item *item = nullptr;
    if (current_room->get_inventory()->get_item_by_name(command.args[0], item)) {
        if (item->get_is_static()) {
            // We cannot pickup static items.
            window_manager->print_to_log("You cannot pick that up!");
        }
        else {
            // We can pickup non-static items.
            current_room->get_inventory()->remove_item(item->get_id());
            player_inventory.add_item(item);
            window_manager->print_to_log("You pick up " + item->get_name() + " and add it to your knapsack.\n");

            // Execute the room's OnItemPickup trigger
            std::string script_table_name = current_room->get_id() + "_SCRIPTS";
            LuaRef room_scripts = getGlobal(L, script_table_name.c_str());
            if (!room_scripts.isNil() && !room_scripts["OnItemPickup"].isNil()) {
                room_scripts["OnItemPickup"](item);
            }

            // Execute the items's OnPickup trigger
            script_table_name = "DEBUG_001_SCRIPTS";
            LuaRef item_scripts = getGlobal(L, script_table_name.c_str());
            if (!item_scripts.isNil() && !item_scripts["OnPickup"].isNil()) {
                item_scripts["OnPickup"]();
            }
        }
    }
    else {
        window_manager->print_to_log("There is no item to pickup by that name.\n");
    }
}
void GameManager::c_drop(const Command &command) {
    Item *item = nullptr;
    if (player_inventory.get_item_by_name(command.args[0], item)) {
        player_inventory.remove_item(item->get_id());
        current_room->get_inventory()->add_item(item);
        window_manager->print_to_log("You remove " + item->get_name() + " from your knapsack and place it on the floor.\n");

        // Execute the room's OnItemDrop trigger
        std::string script_table_name = current_room->get_id() + "_SCRIPTS";
        LuaRef room_scripts = getGlobal(L, script_table_name.c_str());
        if (!room_scripts.isNil() && !room_scripts["OnItemDrop"].isNil()) {
            room_scripts["OnItemDrop"](item);
        }

        // Execute the items's OnDrop trigger
        script_table_name = item->get_id() + "_SCRIPTS";
        LuaRef item_scripts = getGlobal(L, script_table_name.c_str());
        if (!item_scripts.isNil() && !item_scripts["OnDrop"].isNil()) {
            item_scripts["OnDrop"]();
        }
    }
    else {
        window_manager->print_to_log("There is no item to drop by that name.\n");
    }
}
void GameManager::c_inventory(const Command &command) {
    window_manager->print_to_log("== Current Inventory ==");
    window_manager->print_to_log(player_inventory.get_item_list());
}

void GameManager::c_interaction(const Command &command) {
    Item *item = nullptr;
    if (current_room->get_inventory()->get_item_by_name(command.args[0], item)) {
        // Execute the OnInteract item trigger
        std::string script_table_name = item->get_id() + "_SCRIPTS";
        LuaRef item_scripts = getGlobal(L, script_table_name.c_str());
        if (!item_scripts.isNil() && !item_scripts["OnInteract"].isNil()) {
            item_scripts["OnInteract"](command.primary);
        }
    }
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
void GameManager::display_prompt() {
    current_state = GAME_STATES::PROMPT;

    window_manager->print_to_log(current_prompt.message);
    int i = 1;
    for (const auto &x : current_prompt.responses) {
        window_manager->print_to_log(std::to_string(i++) + ") " + x);
    }
}
void GameManager::set_current_room(Room *new_room){
    bool canMove = true; // Set this to the OnExit script function which either allows or disallows the movement of the player

    // Trigger the OnExit function on the current room and the OnEnter function on the new room
    if (current_room != nullptr) {
        std::string old_room_table = current_room->get_id() + "_SCRIPTS";
        LuaRef old_room_scripts = getGlobal(L, old_room_table.c_str());
        if (!old_room_scripts.isNil() && !old_room_scripts["OnExit"].isNil()) {
            canMove = old_room_scripts["OnExit"]();
        }
    }

    if (canMove) {
        current_room = new_room;

        std::string script_table_name = current_room->get_id() + "_SCRIPTS";
        LuaRef room_scripts = getGlobal(L, script_table_name.c_str());
        if (!room_scripts.isNil() && !room_scripts["OnEnter"].isNil()) {
            room_scripts["OnEnter"]();
        }
        window_manager->print_to_log("You enter " + current_room->get_name());
    }
}