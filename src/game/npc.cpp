//
// Created by minal on 1/5/2019.
//

#include "npc.h"
#include "../tokenizer.h"

DialogState::DialogState(const std::string &unique_id, NPC *owner) {
    this->id = unique_id;
    this->owner = owner;
}

NPC::NPC(Map *map, const std::string &id) : GameObject(map, id) {
    inventory = new Inventory();
    equipment = new Equipment(this);
    stat_block = new StatBlock(this);
    s_set_melee_damage("1d4");
}
NPC::NPC(Map *map, const std::string &id, const std::string &name, const std::string &desc) : GameObject(map, id, name, desc) {
    inventory = new Inventory();
    equipment = new Equipment(this);
    stat_block = new StatBlock(this);
    s_set_melee_damage("1d4");
}

void NPC::s_equip_item(const char *item_id) {
    InventorySlot *slot = nullptr;
    if (game_map->get_inventory()->get_item(item_id, slot)) {
        equipment->equip_item(slot->item);
       stat_block->calculate_stats();
    }
}

void NPC::s_set_str(int str) {
    stat_block->strength = str;
    stat_block->calculate_stats();
}
void NPC::s_set_dex(int dex) {
    stat_block->dexterity = dex;
    stat_block->calculate_stats();
}
void NPC::s_set_vit(int vit) {
    stat_block->vitality = vit;
    stat_block->calculate_stats();
}
void NPC::s_set_int(int intl) {
    stat_block->intelligence = intl;
    stat_block->calculate_stats();
}
void NPC::s_set_wis(int wis) {
    stat_block->wisdom = wis;
    stat_block->calculate_stats();
}
void NPC::s_set_cha(int cha) {
    stat_block->charisma = cha;
    stat_block->calculate_stats();
}
void NPC::s_set_luck(int luck) {
    stat_block->luck = luck;
    stat_block->calculate_stats();
}
void NPC::s_set_melee_damage(const char *damage) {
    this->melee_damage = std::string(damage);
}
void NPC::s_set_dialog_script(const char *table_name) {
    this->dialog_script = std::string(table_name);
}
void NPC::s_create_dialog_state(const char *state_id) {
    auto new_state = new DialogState(std::string(state_id), this);
    dialog_states.emplace_back(new_state);
}
void NPC::s_set_dialog_state(const char *state) {
    current_dialog_state = std::string(state);
}
void NPC::s_set_dialog_string(const char *id, const char *str) {
    DialogState *state;
    if (get_dialog_state(std::string(id), state)) {
        state->dialog_text = std::string(str);
    }
}
void NPC::s_add_dialog_option(const char *id, const char *str) {
    DialogState *state;
    if (get_dialog_state(std::string(id), state)) {
        state->dialog_options.emplace_back(std::string(str));
    }
}
const char* NPC::s_get_dialog_state() {
    return current_dialog_state.c_str();
}
std::string NPC::get_dialog_state() {
    return this->current_dialog_state;
}
std::string NPC::get_dialog_script() {
    return this->dialog_script;
}
std::string NPC::get_melee_damage() {
    return this->melee_damage;
}
bool NPC::get_dialog_state(const std::string &id, DialogState *&state) {
    for (auto &x : dialog_states) {
        if (id == x->id) {
            state = x;
            return true;
        }
    }

    return false;
}

void NPC::heal(int amount) {
    stat_block->health += amount;
    if (stat_block->health > stat_block->max_health)
        stat_block->health = stat_block->max_health;
}

Inventory *NPC::get_inventory() {
    return inventory;
}
Equipment *NPC::get_equipment() {
    return equipment;
}
StatBlock *NPC::get_statblock() {
    return stat_block;
}