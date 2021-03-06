//
// Created by Trevor Fisher on 12/25/2018.
//

#ifndef TEXTTHROUGHTIME_COMMAND_PARSER_H
#define TEXTTHROUGHTIME_COMMAND_PARSER_H

#include "../tokenizer.h"

enum struct COMMAND_TYPES {
    DEBUG, HELP, CLEAR_SCREEN, MOVE,
    DROP, PICKUP, TAKE, PLACE, EXAMINE_ROOM,
    EXAMINE_OBJECT, INVENTORY, INTERACTION,
    TALK, NONE
};

struct Command {
    COMMAND_TYPES type;
    std::string primary;
    std::string *args;
    int n_args;

    Command();
    ~Command();
};

void init_lists();
Command process_input(const TokenGroup &tokens);

#endif //TEXTTHROUGHTIME_COMMAND_PARSER_H
