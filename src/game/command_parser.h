//
// Created by Trevor Fisher on 12/25/2018.
//

#ifndef TEXTTHROUGHTIME_COMMAND_PARSER_H
#define TEXTTHROUGHTIME_COMMAND_PARSER_H

#include "../tokenizer.h"

enum struct COMMAND_TYPES {
    DEBUG, HELP, CLEAR_SCREEN, MOVE, DROP, PICKUP, PLACE, EXAMINE_ITEM, EXAMINE_ROOM, INTERACTION, NONE
};

struct Command {
    COMMAND_TYPES type;
    std::string primary;
    std::string *args;
    int n_args;

    Command();
    ~Command();


};

Command process_input(const TokenGroup &tokens);

#endif //TEXTTHROUGHTIME_COMMAND_PARSER_H
