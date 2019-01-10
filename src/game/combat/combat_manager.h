//
// Created by minal on 1/10/2019.
//

#ifndef TEXTTHROUGHTIME_COMBAT_MANAGER_H
#define TEXTTHROUGHTIME_COMBAT_MANAGER_H

#include "../dice_roller.h"

class NPC;
class GameManager;
struct Command;

class CombatManager {
    GameManager *game_manager;
    NPC *player;
    NPC *enemy;

    DiceRoller dice_roller;

public:
    CombatManager(GameManager *game_manager, NPC *player);
    void set_enemy(NPC *enemy);

    void do_combat_round(const Command &player_input);
};


#endif //TEXTTHROUGHTIME_COMBAT_MANAGER_H
