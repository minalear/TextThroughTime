//
// Created by Trevor Fisher on 12/25/2018.
//

#include "command_parser.h"

Command::Command() {
    type = COMMAND_TYPES::NONE;
    args = nullptr;
    n_args = 0;
}
Command::~Command() {
    delete [] args;
}

Command process_input(const TokenGroup &tokens) {
    typedef const std::vector<std::string> word_list; // Typedef for cleaner code
    word_list superfluous_words = {"THE", "IN", "INTO", "A", "AN", "AT"};
    word_list move_words        = {"MOVE", "GO", "TRAVEL", "ENTER"};
    word_list drop_words        = {"DROP", "REMOVE"};
    word_list pickup_words      = {"PICKUP", "TAKE", "GRAB"};
    word_list place_words       = {"PLACE", "PUT", "SET"};
    word_list examine_words     = {"LOOK", "EXAMINE", "INSPECT", "VIEW"};
    word_list direction_words   = {"NORTH", "SOUTH", "EAST", "WEST"};

    // Filter out (hopefully) unnecessary words from our input
    std::string token_buffer[100];
    int n = 0;
    for (int i = 0; i < tokens.n_tokens; i++) {
        if (!contains<std::string>(tokens[i], superfluous_words))
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
    if (contains(command.primary, move_words)) {
        command.type = COMMAND_TYPES::MOVE;
    }
    else if (contains(command.primary, drop_words)) {
        command.type = COMMAND_TYPES::DROP;
    }
    else if (contains(command.primary, pickup_words)) {
        command.type = COMMAND_TYPES::PICKUP;
    }
    else if (contains(command.primary, place_words)) {
        command.type = COMMAND_TYPES::PLACE;
    }
    else if (contains(command.primary, examine_words)) {
        command.type = COMMAND_TYPES::EXAMINE;
    }
    else if (command.primary == "CLEAR") {
        command.type = COMMAND_TYPES::CLEAR_SCREEN;
    }
    else if (command.primary == "DEBUG") {
        command.type = COMMAND_TYPES::DEBUG;
    }
    else if (command.primary == "HELP") {
        command.type = COMMAND_TYPES::HELP;
    }

    // Special circumstances
    // Clearing away an item rather than meaning to clear the screen
    if (command.type == COMMAND_TYPES::CLEAR_SCREEN && command.n_args > 0 && command.args[0] != "SCREEN") {
        command.type = COMMAND_TYPES::INTERACTION;
    }
    // Attempting to move an item rather than move to a location
    else if (command.type == COMMAND_TYPES::MOVE && command.n_args > 0) {
        if (!contains(command.args[0], direction_words)) {
            command.type = COMMAND_TYPES::INTERACTION;
        }
    }

    return command;
}