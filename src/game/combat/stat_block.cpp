//
// Created by minal on 1/8/2019.
//

#include <cmath>
#include "stat_block.h"

int get_mod(int stat) {
    return (stat - 10) / 2;
}

StatBlock::StatBlock() {
    strength = 10;
    dexterity = 10;
    vitality = 10;
    intelligence = 10;
    wisdom = 10;
    charisma = 10;
    luck = 10;

    base_attack_bonus = 0;
    size_mod = 0;

    base_fort_save = 0;
    base_reflex_save = 0;
    base_will_save = 0;
}
void StatBlock::calculate_stats() {
    str_mod = get_mod(strength);
    dex_mod = get_mod(dexterity);
    vit_mod = get_mod(vitality);
    int_mod = get_mod(intelligence);
    wis_mod = get_mod(wisdom);
    cha_mod = get_mod(charisma);
    luck_mod = get_mod(luck);

    ac = 10 + dex_mod + size_mod + natural_armor;
    touch_ac = 10 + dex_mod + size_mod;
    ff_ac = 10 + size_mod + natural_armor;

    initiative = dex_mod;
    fort_save = base_fort_save + vit_mod;
    reflex_save = base_reflex_save + dex_mod;
    will_save = base_will_save + wis_mod;

    cmb = base_attack_bonus + str_mod + size_mod;
    cmd = 10 + base_attack_bonus + str_mod + dex_mod + size_mod;
}