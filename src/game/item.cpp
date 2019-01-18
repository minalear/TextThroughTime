//
// Created by minal on 12/19/2018.
//

#include "item.h"
#include "../tokenizer.h"

Item::Item(Map *map, const std::string &id) : Item(map, id, "[ITEM]", "[DESCRIPTION]") { }
Item::Item(Map *map, const std::string &id, const std::string &name, const std::string &desc) : GameObject(map, id, name, desc) {
    ac_bonus = 0;
    str_bonus = 0;
    dex_bonus = 0;
    vit_bonus = 0;
    int_bonus = 0;
    wis_bonus = 0;
    cha_bonus = 0;
    luck_bonus = 0;
}

// Scripting specific functions
void Item::s_add_item(const char *item_id) {
    InventorySlot *item_slot = nullptr;
    if (game_map->get_inventory()->get_item(std::string(item_id), item_slot)) {
        container_items.add_item(item_slot->item, 1);
    }
}
void Item::s_add_items(const char *item_id, int quantity) {
    InventorySlot *item_slot = nullptr;
    if (game_map->get_inventory()->get_item(std::string(item_id), item_slot)) {
        container_items.add_item(item_slot->item, quantity);
    }
}
void Item::s_remove_item(const char *item_id) {
    container_items.remove_item(item_id);
}
void Item::s_remove_items(const char *item_id, int quantity) {
    container_items.remove_item(item_id, quantity);
}
void Item::s_set_damage(const char *damage) {
    this->damage = std::string(damage);
}

std::string Item::get_damage() {
    return damage;
}
std::string Item::get_description() {
    std::string description_buffer = this->description + "  ";
    if (s_has_property("CONTAINER") && !s_has_property("LOCKED")) {
        description_buffer += "\n\n== " + name + "'s Inventory ==\n";
        description_buffer += container_items.get_item_list();
    } else if (s_has_property("MAIN_HAND")) {
        description_buffer += "Damage: " + damage;
    }

    return description_buffer;
}
int Item::get_attack_bonus() {
    return attack_bonus;
}
int Item::get_ac_bonus() {
    return ac_bonus;
}
int Item::get_str_bonus() {
    return str_bonus;
}
int Item::get_dex_bonus() {
    return dex_bonus;
}
int Item::get_vit_bonus() {
    return vit_bonus;
}
int Item::get_int_bonus() {
    return int_bonus;
}
int Item::get_wis_bonus() {
    return wis_bonus;
}
int Item::get_cha_bonus() {
    return cha_bonus;
}
int Item::get_luck_bonus() {
    return luck_bonus;
}

void Item::set_attack_bonus(int value) {
    attack_bonus = value;
}
void Item::set_ac_bonus(int value) {
    ac_bonus = value;
}
void Item::set_str_bonus(int bonus) {
    str_bonus = bonus;
}
void Item::set_dex_bonus(int bonus) {
    dex_bonus = bonus;
}
void Item::set_vit_bonus(int bonus) {
    vit_bonus = bonus;
}
void Item::set_int_bonus(int bonus) {
    int_bonus = bonus;
}
void Item::set_wis_bonus(int bonus) {
    wis_bonus = bonus;
}
void Item::set_cha_bonus(int bonus) {
    cha_bonus = bonus;
}
void Item::set_luck_bonus(int bonus) {
    luck_bonus = bonus;
}

Inventory* Item::get_inventory() {
    return &container_items;
}