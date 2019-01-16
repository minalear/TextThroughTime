//
// Created by minal on 12/19/2018.
//

#ifndef TEXTTHROUGHTIME_ITEM_H
#define TEXTTHROUGHTIME_ITEM_H

#include <string>
#include <vector>
#include "game_variable_map.h"
#include "inventory.h"
#include "map.h"

class Item {
    std::string id; // The unique ID of the item
    std::string name; // The name that appears in the inventory
    std::string description; // The description of the item when examined
    std::string room_description; // The description of the item while it's in the room.  Appears when the room is examined.
    std::string current_state; // Used to define different behaviors depending on the item's current state

    std::vector<std::string> aliases; // Alternative short names that can be used to refer to this item
    std::vector<std::string> properties;

    GameVariableMap<std::string> string_variables;
    GameVariableMap<int>         int_variables;
    Inventory container_items;

    Map *game_map;

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
    Item(const std::string &id, Map *map);
    Item(const std::string &id, const std::string &name, const std::string &desc, Map *map);
    ~Item();

    const char* s_get_id();
    const char* s_get_name();
    const char* s_get_state();
    const char* s_get_str_variable(const char *key);
    int s_get_int_variable(const char *key);

    void s_set_name(const char *name);
    void s_set_description(const char *desc);
    void s_append_description(const char *desc);
    void s_set_room_description(const char *desc);
    void s_set_state(const char *state);
    void s_add_alias(const char *alias);
    void s_set_str_variable(const char *key, const char *value);
    void s_set_int_variable(const char *key, int value);
    bool s_has_property(const char *property);
    void s_add_property(const char *property);
    void s_remove_property(const char *property);
    void s_add_item(const char *item_id);
    void s_add_items(const char *item_id, int quantity);
    void s_remove_item(const char *item_id);
    void s_remove_items(const char *item_id, int quantity);
    void s_set_damage(const char *damage);

    std::string get_id();
    std::string get_name();
    std::string get_description();
    std::string get_room_description();
    std::string get_state();
    std::string get_damage();

    void set_name(const std::string &name);
    void set_description(const std::string &desc);
    void set_room_description(const std::string &desc);
    void set_state(const std::string &state);
    bool check_name(const std::string &name);

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
