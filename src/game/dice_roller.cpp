//
// Created by minal on 1/8/2019.
//

#include "dice_roller.h"
#include "../core/math_utils.h"
#include "combat/stat_block.h"

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

ROLL_RESULTS DiceRoller::roll_check(const std::string &roll, int mod) {
    return ROLL_RESULTS::FAIL;
}

ROLL_RESULTS DiceRoller::strength_check(StatBlock *stat_block, int dc) {
    int roll = roll_dice("1d20");
    if (roll == 1)  return ROLL_RESULTS::CRITICAL_FAIL;
    if (roll == 20) return ROLL_RESULTS::CRITICAL_SUCCESS;
    if (roll + stat_block->str_mod >= dc) return ROLL_RESULTS::SUCCESS;

    return ROLL_RESULTS::FAIL;
}
ROLL_RESULTS DiceRoller::dexterity_check(StatBlock *stat_block, int dc) {
    int roll = roll_dice("1d20");
    if (roll == 1)  return ROLL_RESULTS::CRITICAL_FAIL;
    if (roll == 20) return ROLL_RESULTS::CRITICAL_SUCCESS;
    if (roll + stat_block->dex_mod >= dc) return ROLL_RESULTS::SUCCESS;

    return ROLL_RESULTS::FAIL;
}
ROLL_RESULTS DiceRoller::vitality_check(StatBlock *stat_block, int dc) {
    int roll = roll_dice("1d20");
    if (roll == 1)  return ROLL_RESULTS::CRITICAL_FAIL;
    if (roll == 20) return ROLL_RESULTS::CRITICAL_SUCCESS;
    if (roll + stat_block->vit_mod >= dc) return ROLL_RESULTS::SUCCESS;

    return ROLL_RESULTS::FAIL;
}
ROLL_RESULTS DiceRoller::intelligence_check(StatBlock *stat_block, int dc) {
    int roll = roll_dice("1d20");
    if (roll == 1)  return ROLL_RESULTS::CRITICAL_FAIL;
    if (roll == 20) return ROLL_RESULTS::CRITICAL_SUCCESS;
    if (roll + stat_block->int_mod >= dc) return ROLL_RESULTS::SUCCESS;

    return ROLL_RESULTS::FAIL;
}
ROLL_RESULTS DiceRoller::wisdom_check(StatBlock *stat_block, int dc) {
    int roll = roll_dice("1d20");
    if (roll == 1)  return ROLL_RESULTS::CRITICAL_FAIL;
    if (roll == 20) return ROLL_RESULTS::CRITICAL_SUCCESS;
    if (roll + stat_block->wis_mod >= dc) return ROLL_RESULTS::SUCCESS;

    return ROLL_RESULTS::FAIL;
}
ROLL_RESULTS DiceRoller::charisma_check(StatBlock *stat_block, int dc) {
    int roll = roll_dice("1d20");
    if (roll == 1)  return ROLL_RESULTS::CRITICAL_FAIL;
    if (roll == 20) return ROLL_RESULTS::CRITICAL_SUCCESS;
    if (roll + stat_block->cha_mod >= dc) return ROLL_RESULTS::SUCCESS;

    return ROLL_RESULTS::FAIL;
}
ROLL_RESULTS DiceRoller::luck_check(StatBlock *stat_block, int dc) {
    int roll = roll_dice("1d20");
    if (roll == 1)  return ROLL_RESULTS::CRITICAL_FAIL;
    if (roll == 20) return ROLL_RESULTS::CRITICAL_SUCCESS;
    if (roll + stat_block->luck_mod >= dc) return ROLL_RESULTS::SUCCESS;

    return ROLL_RESULTS::FAIL;
}
ROLL_RESULTS DiceRoller::fort_save(StatBlock *stat_block, int dc) {
    int roll = roll_dice("1d20");
    if (roll == 1)  return ROLL_RESULTS::CRITICAL_FAIL;
    if (roll == 20) return ROLL_RESULTS::CRITICAL_SUCCESS;
    if (roll + stat_block->fort_save >= dc) return ROLL_RESULTS::SUCCESS;

    return ROLL_RESULTS::FAIL;
}
ROLL_RESULTS DiceRoller::reflex_save(StatBlock *stat_block, int dc) {
    int roll = roll_dice("1d20");
    if (roll == 1)  return ROLL_RESULTS::CRITICAL_FAIL;
    if (roll == 20) return ROLL_RESULTS::CRITICAL_SUCCESS;
    if (roll + stat_block->reflex_save >= dc) return ROLL_RESULTS::SUCCESS;

    return ROLL_RESULTS::FAIL;
}
ROLL_RESULTS DiceRoller::will_save(StatBlock *stat_block, int dc) {
    int roll = roll_dice("1d20");
    if (roll == 1)  return ROLL_RESULTS::CRITICAL_FAIL;
    if (roll == 20) return ROLL_RESULTS::CRITICAL_SUCCESS;
    if (roll + stat_block->will_save >= dc) return ROLL_RESULTS::SUCCESS;

    return ROLL_RESULTS::FAIL;
}

int DiceRoller::initiative(StatBlock *stat_block) {
    return roll_dice("1d20") + stat_block->initiative;
}
