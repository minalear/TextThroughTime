//
// Created by Trevor Fisher on 12/25/2018.
//

#include "command_parser.h"

std::vector<std::string> superfluous_list, move_list, drop_list, pickup_list, place_list,
                         examine_list, direction_list, room_list, inventory_list, talk_list;

void init_lists() {
    superfluous_list    = {"THE", "IN", "INTO", "A", "AN", "AT", "OUT", "TO", "WITH"};
    move_list           = {"MOVE", "GO", "TRAVEL", "ENTER"};
    drop_list           = {"DROP", "REMOVE"};
    pickup_list         = {"PICKUP", "TAKE", "GRAB"};
    place_list          = {"PLACE", "PUT", "SET"};
    examine_list        = {"LOOK", "EXAMINE", "INSPECT", "VIEW", "CHECK"};
    direction_list      = {"NORTH", "SOUTH", "EAST", "WEST"};
    room_list           = {"ROOM", "LOCATION", "AREA"};
    inventory_list      = {"INVENTORY"};
    talk_list           = {"TALK", "SPEAK", "CONVERSE"};
}

Command::Command() {
    type = COMMAND_TYPES::NONE;
    args = nullptr;
    n_args = 0;
}
Command::~Command() {
    delete [] args;
}

Command process_input(const TokenGroup &tokens) {
    // Filter out (hopefully) unnecessary words from our input
    std::string token_buffer[100];
    int n = 0;
    for (int i = 0; i < tokens.n_tokens; i++) {
        if (!contains<std::string>(tokens[i], superfluous_list))
            token_buffer[n++] = tokens[i];
    }

    Command command;
    if (n == 0) return command; // If there's no valid input

    // Fill the command's args list with our token_buffer
    command.primary = token_buffer[0];
    command.n_args = n-1;
    command.args = new std::string[command.n_args];
    for (int i = 1; i < n; i++) {
        command.args[i-1] = token_buffer[i];
    }

    command.type = COMMAND_TYPES::INTERACTION; // Defaults to interaction

    // Attempt to figure out the command and set the type
    if (contains(command.primary, move_list)) {
        command.type = COMMAND_TYPES::MOVE;
    } else if (contains(command.primary, drop_list)) {
        command.type = COMMAND_TYPES::DROP;
    } else if (contains(command.primary, pickup_list)) {
        command.type = COMMAND_TYPES::PICKUP;
    } else if (contains(command.primary, place_list)) {
        command.type = COMMAND_TYPES::PLACE;
    } else if (contains(command.primary, examine_list)) {
        // If the player just types "look" or types "inspect area"
        if (command.n_args == 0 || contains<std::string>(command.args[0], room_list)) {
            command.type = COMMAND_TYPES::EXAMINE_ROOM;
        }
        // if the player types something like "inspect inventory"
        else if (contains<std::string>(command.args[0], inventory_list)) {
            command.type = COMMAND_TYPES::INVENTORY;
        }
        // Examine either an item in the room, your inventory, or an NPC
        else {
            command.type = COMMAND_TYPES::EXAMINE_OBJECT;
        }
    } else if (contains(command.primary, inventory_list)) {
        command.type = COMMAND_TYPES::INVENTORY;
    } else if (contains(command.primary, talk_list)) {
        command.type = COMMAND_TYPES::TALK;
    } else if (command.primary == "CLEAR") {
        command.type = COMMAND_TYPES::CLEAR_SCREEN;
    } else if (command.primary == "DEBUG") {
        command.type = COMMAND_TYPES::DEBUG;
    } else if (command.primary == "HELP") {
        command.type = COMMAND_TYPES::HELP;
    }

    // Special circumstances
    // Clearing away an item rather than meaning to clear the screen
    if (command.type == COMMAND_TYPES::CLEAR_SCREEN && command.n_args > 0 && command.args[0] != "SCREEN") {
        command.type = COMMAND_TYPES::INTERACTION;
    }
    // Attempting to move an item rather than move to a location
    else if (command.type == COMMAND_TYPES::MOVE && command.n_args > 0) {
        if (!contains(command.args[0], direction_list)) {
            command.type = COMMAND_TYPES::INTERACTION;
        }
    }

    return command;
}