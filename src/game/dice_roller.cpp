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

    // Format [NUM_DICE]D[NUM_SIDES](+-)[MODIFIERS]

    // First seek until we find D, then set that to num_dice
    int i = 0;
    for (; i < dice.size(); i++) {
        if (dice[i] == 'd' || dice[i] == 'D') break;
        buffer += dice[i];
    }
    i++; // Skip the D

    // Convert the buffer to the number of dice
    int num_dice = std::stoi(buffer);
    buffer.clear();

    // Now seek until the end or until we hit a + or -
    int current_sign = 1; // Used to do negative/positive modifier math
    for (; i < dice.size(); i++) {
        if (dice[i] == '+' || dice[i] == '-') {
            if (dice[i] == '+') current_sign =  1;
            else                current_sign = -1;

            break;
        }
        buffer += dice[i];
    }
    i++; // Skip the first sign since we just set it

    // Convert the buffer to the number of sides on each dice
    int num_sides = std::stoi(buffer);
    buffer.clear();

    // Process any modifiers that are left (the loop will skip if there are none and we'll just be adding 0)
    int total_mod = 0;
    for (; i < dice.size(); i++) {
        if (dice[i] == '+') {
            // Add the buffer
            if (!buffer.empty()) {
                int bti = std::stoi(buffer);
                total_mod += bti * current_sign;
                buffer.clear();
            }
            current_sign = 1;
        } else if (dice[i] == '-') {
            // Subtract the buffer
            if (!buffer.empty()) {
                int bti = std::stoi(buffer);
                total_mod += bti * current_sign;
                buffer.clear();
            }
            current_sign = -1;
        } else {
            buffer += dice[i];
        }
    }

    // The final modifier will be stuck in the buffer, so calculate that
    if (!buffer.empty()) {
        total_mod += std::stoi(buffer) * current_sign;
        buffer.clear();
    }

    // Roll the dice and add up the totals
    int total = 0;
    for (i = 0; i < num_dice; i++) {
        total += minalear::rand_int(1, num_sides + 1);
    }

    // Return the total rolls with the modifiers
    return total + total_mod;
}
