//
// Created by minal on 1/8/2019.
//

#include "dice_roller.h"
#include "../core/math_utils.h"

int DiceRoller::s_roll_dice(const char *dice) {
    return roll_dice(std::string(dice));
}

int DiceRoller::roll_dice(const std::string &dice) {
    std::string buffer;

    uint32_t i = 0;
    for (; i < dice.length(); i++) {
        if (dice[i] == 'd' || dice[i] == 'D') break;
        buffer += dice[i];
    }
    const int num_dice = std::stoi(buffer);
    const int dice_sides = std::stoi(dice.substr(i + 1, dice.size() - i - 1));

    int total = 0;
    for (i = 0; i < num_dice; i++) {
        total += minalear::rand_int(1, dice_sides+1);
    }

    return total;
}
