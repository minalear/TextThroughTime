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
    int num_dice = 0;
    int dice_sides = 0;
    int modifier = 0;

    uint32_t i = 0;
    for (; i < dice.size(); i++) {
        if (dice[i] == 'd' || dice[i] == 'D') break;
        buffer += dice[i];
    }
    num_dice = std::stoi(buffer);
    buffer.clear();

    char mod_symbol = ' ';
    for (i = i+1; i < dice.size(); i++) {
        if (dice [i] == '+' || dice[i] == '-') {
            mod_symbol = dice[i];
            break;
        }
        buffer += dice[i];
    }

    dice_sides = std::stoi(buffer);
    if (mod_symbol == '+') {
        modifier = std::stoi(dice.substr(i + 1, dice.size() - i - 1));
    } else if (mod_symbol == '-') {
        modifier = -std::stoi(dice.substr(i+1, dice.size() - i - 1));
    }

    int total = 0;
    for (i = 0; i < num_dice; i++) {
        total += minalear::rand_int(1, dice_sides+1);
    }

    return total + modifier;
}
