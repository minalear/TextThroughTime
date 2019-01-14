//
// Created by minal on 1/10/2019.
//

#include <string>
#include "combat_manager.h"
#include "../npc.h"
#include "../command_parser.h"
#include "../game_manager.h"

CombatManager::CombatManager(GameManager *game_manager, NPC *player) {
    this->game_manager = game_manager;
    this->player = player;
    enemy = nullptr;
}

void CombatManager::set_enemy(NPC *enemy) {
    this->enemy = enemy;
}

std::string append_to_dice(const std::string &dice, int amount) {
    return dice + ((amount >= 0) ? "+" + std::to_string(amount) : std::to_string(amount));
}
void CombatManager::do_combat_round(const Command &player_input) {
    int  pc_attack  = player->get_statblock()->get_attack_bonus();
    int  pc_damage  = player->get_statblock()->str_mod;
    int  pc_luck    = player->get_statblock()->luck_mod;
    int  pc_ac      = player->get_statblock()->ac;
    int  pc_luck_ac = (pc_ac + 4) * 5; // Convert the d20 AC to a harder percentile DC (20 * 5 == 100)
    auto pc_weapon  = player->get_equipment()->get_equipment_slot(EQUIPMENT_SLOTS::MAIN_HAND);
    auto pc_weapon_damage = (pc_weapon->equipped) ? pc_weapon->equipment->get_damage() : player->get_melee_damage(); // 1d4 being unarmed damage

    int  enemy_attack  = enemy->get_statblock()->get_attack_bonus();
    int  enemy_damage  = enemy->get_statblock()->str_mod;
    int  enemy_luck    = enemy->get_statblock()->luck_mod;
    int  enemy_ac      = enemy->get_statblock()->ac;
    int  enemy_luck_ac = (enemy_ac + 4) * 5;
    auto enemy_weapon  = enemy->get_equipment()->get_equipment_slot(EQUIPMENT_SLOTS::MAIN_HAND);
    auto enemy_weapon_damage = (enemy_weapon->equipped) ? enemy_weapon->equipment->get_damage() : enemy->get_melee_damage();

    // Do player combat
    int attack_roll = dice_roller.roll_dice(append_to_dice("1d20", pc_attack));
    int luck_roll   = dice_roller.roll_dice(append_to_dice("1d100", pc_luck));
    
    if (attack_roll >= enemy_ac) {
        // Regular attack vs ac roll
        game_manager->print_to_log("You hit " + enemy->get_name() + " (" + append_to_dice("1d20", pc_attack) + " = " + std::to_string(attack_roll) + ")!");
        int damage_dealt = dice_roller.roll_dice(append_to_dice(pc_weapon_damage, pc_damage));
        enemy->get_statblock()->health -= damage_dealt;
        game_manager->print_to_log("You dealt " + std::to_string(damage_dealt) + " damage.\n\n");
    } else if (luck_roll >= enemy_luck_ac) {
        // Extra check with luck ac to attack
        game_manager->print_to_log("You lucked out and hit " + enemy->get_name() + " (" + append_to_dice("1d100", pc_luck) + " = " + std::to_string(luck_roll) + ")!");
        int damage_dealt = dice_roller.roll_dice(append_to_dice(pc_weapon_damage, pc_damage));
        enemy->get_statblock()->health -= damage_dealt;
        game_manager->print_to_log("You dealt " + std::to_string(damage_dealt) + " damage.\n\n");
    } else {
        game_manager->print_to_log("You were unable to land a hit on your opponent (" + append_to_dice("1d20", pc_attack) + " = " + std::to_string(attack_roll) + ")!");
    }

    // Do enemy combat
    attack_roll = dice_roller.roll_dice(append_to_dice("1d20", enemy_attack));
    luck_roll   = dice_roller.roll_dice(append_to_dice("1d100", enemy_luck));
    if (attack_roll >= pc_ac) {
        // Regular attack vs ac roll
        game_manager->print_to_log("They were able to hit you (" + append_to_dice("1d20", enemy_attack) + " = " + std::to_string(attack_roll) + ")!");
        int damage_dealt = dice_roller.roll_dice(append_to_dice(enemy_weapon_damage, enemy_damage));
        player->get_statblock()->health -= damage_dealt;
        game_manager->print_to_log("They dealt " + std::to_string(damage_dealt) + " damage to you.\n\n");
    } else if (luck_roll >= pc_luck_ac) {
        // Extra check with luck ac to attack
        game_manager->print_to_log("They lucked out and hit you (" + append_to_dice("1d100", enemy_luck) + " = " + std::to_string(luck_roll) + ")!");
        int damage_dealt = dice_roller.roll_dice(append_to_dice(enemy_weapon_damage, enemy_damage));
        player->get_statblock()->health -= damage_dealt;
        game_manager->print_to_log("They dealt " + std::to_string(damage_dealt) + " damage to you.\n\n");
    } else {
        game_manager->print_to_log("They were unable to land a hit on you (" + append_to_dice("1d20", enemy_attack) + " = " + std::to_string(attack_roll) + ")!");
    }
}
