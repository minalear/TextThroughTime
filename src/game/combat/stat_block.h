//
// Created by minal on 1/8/2019.
//

#ifndef TEXTTHROUGHTIME_STAT_BLOCK_H
#define TEXTTHROUGHTIME_STAT_BLOCK_H

struct StatBlock {
    // Set stats
    int strength;
    int dexterity;
    int vitality;
    int intelligence;
    int wisdom;
    int charisma;
    int luck;

    int base_attack_bonus;
    int size_mod;
    int natural_armor;

    int base_fort_save;
    int base_reflex_save;
    int base_will_save;

    // Calculated stats
    int str_mod;
    int dex_mod;
    int vit_mod;
    int int_mod;
    int wis_mod;
    int cha_mod;
    int luck_mod;

    int health, max_health;
    int initiative;

    int ac, touch_ac, ff_ac;

    int fort_save;
    int reflex_save;
    int will_save;

    int cmb, cmd;

    StatBlock();
    void calculate_stats();
};

#endif //TEXTTHROUGHTIME_STAT_BLOCK_H
