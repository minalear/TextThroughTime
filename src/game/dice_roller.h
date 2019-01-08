//
// Created by minal on 1/8/2019.
//

#ifndef TEXTTHROUGHTIME_DICE_ROLLER_H
#define TEXTTHROUGHTIME_DICE_ROLLER_H

#include <string>

struct DiceRoller {
    int s_roll_dice(const char *dice);
    int roll_dice(const std::string &dice);
};

#endif //TEXTTHROUGHTIME_DICE_ROLLER_H
