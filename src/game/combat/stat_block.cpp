//
// Created by minal on 1/8/2019.
//

#include <cmath>
#include "stat_block.h"
#include "../npc.h"

int get_mod(int stat) {
    return (int)floorf((stat - 10.f) / 2.f);
}

StatBlock::StatBlock(NPC *npc) {
    this->npc = npc;

    strength = 10;
    dexterity = 10;
    vitality = 10;
    intelligence = 10;
    wisdom = 10;
    charisma = 10;
    luck = 10;

    base_attack_bonus = 0;
    size_mod = 0;
    natural_armor = 0;

    base_fort_save = 0;
    base_reflex_save = 0;
    base_will_save = 0;

    max_health = health = 10;

    calculate_stats();
}
void StatBlock::calculate_stats() {
    auto npc_equipment = npc->get_equipment();

    total_str  = strength + npc_equipment->get_total_str_bonus();
    total_dex  = dexterity + npc_equipment->get_total_dex_bonus();
    total_vit  = vitality + npc_equipment->get_total_vit_bonus();
    total_int  = intelligence + npc_equipment->get_total_int_bonus();
    total_wis  = wisdom + npc_equipment->get_total_wis_bonus();
    total_cha  = charisma + npc_equipment->get_total_cha_bonus();
    total_luck = luck + npc_equipment->get_total_luck_bonus();

    str_mod = get_mod(total_str);
    dex_mod = get_mod(total_dex);
    vit_mod = get_mod(total_vit);
    int_mod = get_mod(total_int);
    wis_mod = get_mod(total_wis);
    cha_mod = get_mod(total_cha);
    luck_mod = get_mod(total_luck);

    ac = 10 + dex_mod + size_mod + natural_armor + npc_equipment->get_total_ac_bonus();
    touch_ac = 10 + dex_mod + size_mod;
    ff_ac = 10 + size_mod + natural_armor;

    initiative = dex_mod;
    fort_save = base_fort_save + vit_mod;
    reflex_save = base_reflex_save + dex_mod;
    will_save = base_will_save + wis_mod;

    cmb = base_attack_bonus + str_mod + size_mod;
    cmd = 10 + base_attack_bonus + str_mod + dex_mod + size_mod;
}