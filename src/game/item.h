//
// Created by minal on 12/19/2018.
//

#ifndef TEXTTHROUGHTIME_ITEM_H
#define TEXTTHROUGHTIME_ITEM_H

#include "game_object.h"
#include "inventory.h"

class Item : public GameObject {
    Inventory container_items;

    // Equipment stats
    std::string damage; // dice roll [1d6]
    int attack_bonus;
    int ac_bonus;
    int str_bonus;
    int dex_bonus;
    int vit_bonus;
    int int_bonus;
    int wis_bonus;
    int cha_bonus;
    int luck_bonus;

public:
    Item(Map *map, const std::string &id);
    Item(Map *map, const std::string &id, const std::string &name, const std::string &desc);

    void s_add_item(const char *item_id);
    void s_add_items(const char *item_id, int quantity);
    void s_remove_item(const char *item_id);
    void s_remove_items(const char *item_id, int quantity);
    void s_set_damage(const char *damage);

    std::string get_damage();
    std::string get_description() override;

    int get_attack_bonus();
    int get_ac_bonus();
    int get_str_bonus();
    int get_dex_bonus();
    int get_vit_bonus();
    int get_int_bonus();
    int get_wis_bonus();
    int get_cha_bonus();
    int get_luck_bonus();

    void set_attack_bonus(int bonus);
    void set_ac_bonus(int bonus);
    void set_str_bonus(int bonus);
    void set_dex_bonus(int bonus);
    void set_vit_bonus(int bonus);
    void set_int_bonus(int bonus);
    void set_wis_bonus(int bonus);
    void set_cha_bonus(int bonus);
    void set_luck_bonus(int bonus);

    Inventory* get_inventory();
};

#endif //TEXTTHROUGHTIME_ITEM_H
