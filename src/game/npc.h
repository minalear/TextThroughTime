//
// Created by minal on 1/5/2019.
//

#ifndef TEXTTHROUGHTIME_NPC_H
#define TEXTTHROUGHTIME_NPC_H

#include "game_object.h"
#include "inventory.h"
#include "combat/stat_block.h"
#include "combat/equipment.h"

class NPC; // C++ >.>

struct DialogState {
    std::string id;
    std::string dialog_text;
    std::vector<std::string> dialog_options;
    NPC *owner;

    DialogState(const std::string &unique_id, NPC *owner);
};

class NPC : public GameObject {
    std::string dialog_script;
    std::string current_dialog_state;
    std::vector<DialogState*> dialog_states;

    StatBlock *stat_block;
    Inventory *inventory;
    Equipment *equipment;
    std::string melee_damage;

public:
    NPC(Map *map, const std::string &id);
    NPC(Map *map, const std::string &id, const std::string &name, const std::string &desc);

    //Script functions
    void s_equip_item(const char *item_id);

    void s_set_str(int str);
    void s_set_dex(int dex);
    void s_set_vit(int vit);
    void s_set_int(int intl);
    void s_set_wis(int wis);
    void s_set_cha(int cha);
    void s_set_luck(int luck);
    void s_set_melee_damage(const char *damage);

    // Dialog centric scripting functions
    void s_set_dialog_script(const char *table_name);
    void s_create_dialog_state(const char *state);
    void s_set_dialog_state(const char *state);
    void s_set_dialog_string(const char *state, const char *str);
    void s_add_dialog_option(const char *state, const char *str);
    const char* s_get_dialog_state();

    void heal(int amount);

    // Getters/Setters
    std::string get_dialog_state();
    std::string get_dialog_script();
    std::string get_melee_damage();
    bool get_dialog_state(const std::string &id, DialogState *&state);

    Inventory* get_inventory();
    Equipment* get_equipment();
    StatBlock* get_statblock();
};

#endif //TEXTTHROUGHTIME_NPC_H
