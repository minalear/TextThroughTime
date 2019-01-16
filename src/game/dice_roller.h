//
// Created by minal on 1/8/2019.
//

#ifndef TEXTTHROUGHTIME_DICE_ROLLER_H
#define TEXTTHROUGHTIME_DICE_ROLLER_H

#include <string>

class StatBlock;
enum struct ROLL_RESULTS {
    SUCCESS, CRITICAL_SUCCESS,
    FAIL, CRITICAL_FAIL,
    LUCK_SUCCESS
};

struct DiceRoller {
    const int DC_INCREASE = 5;

    int s_roll_dice(const char *dice);
    int roll_dice(const std::string &dice);

    ROLL_RESULTS luck_check(StatBlock *stat_block, int dc);
    ROLL_RESULTS roll_check(const std::string &roll, int mod);

    ROLL_RESULTS strength_check(StatBlock *stat_block, int dc);
    ROLL_RESULTS dexterity_check(StatBlock *stat_block, int dc);
    ROLL_RESULTS vitality_check(StatBlock *stat_block, int dc);
    ROLL_RESULTS intelligence_check(StatBlock *stat_block, int dc);
    ROLL_RESULTS wisdom_check(StatBlock *stat_block, int dc);
    ROLL_RESULTS charisma_check(StatBlock *stat_block, int dc);

    ROLL_RESULTS fort_save(StatBlock *stat_block, int dc);
    ROLL_RESULTS reflex_save(StatBlock *stat_block, int dc);
    ROLL_RESULTS will_save(StatBlock *stat_block, int dc);

    int initiative(StatBlock *stat_block);
};

#endif //TEXTTHROUGHTIME_DICE_ROLLER_H
