//
// Created by minal on 1/5/2019.
//

#include "npc.h"
#include "../tokenizer.h"

DialogState::DialogState(const std::string &unique_id, NPC *owner) {
    this->id = unique_id;
    this->owner = owner;
}

NPC::NPC(const std::string &id, Map *map) {
    this->id = id;
    this->game_map = map;
    set_name("[NPC NAME]");
    set_description("[NPC DESCRIPTION]");

    inventory = new Inventory();
    equipment = new Equipment(this);
    stat_block = new StatBlock(this);
    s_set_melee_damage("1d4");
}
NPC::NPC(const std::string &id, const std::string &name, const std::string &desc, Map *map) {
    this->id = id;
    this->game_map = map;
    set_name(name);
    set_description(desc);

    inventory = new Inventory();
    equipment = new Equipment(this);
    stat_block = new StatBlock(this);
    s_set_melee_damage("1d4");
}
NPC::~NPC() {
    for (auto &x : dialog_states) {
        delete x;
    }
    dialog_states.clear();
}

const char *NPC::s_get_id() {
    return this->id.c_str();
}
const char *NPC::s_get_name() {
    return this->name.c_str();
}
const char *NPC::s_get_description() {
    return this->description.c_str();
}
const char *NPC::s_get_room_description() {
    return this->room_description.c_str();
}
const char *NPC::s_get_state() {
    return this->current_state.c_str();
}
const char *NPC::s_get_str_variable(const char *key) {
    return string_variables.get_variable(std::string(key)).c_str();
}
int NPC::s_get_int_variable(const char *key) {
    return int_variables.get_variable(std::string(key));
}
bool NPC::s_has_property(const char *prop) {
    const std::string property = std::string(prop);
    for (const auto &x : properties) {
        if (property == x) return true;
    }

    return false;
}

void NPC::s_set_name(const char *name) {
    set_name(std::string(name));
}
void NPC::s_set_description(const char *desc) {
    set_description(std::string(desc));
}
void NPC::s_set_room_description(const char *desc) {
    set_room_description(std::string(desc));
}
void NPC::s_set_state(const char *state) {
    set_state(std::string(state));
}
void NPC::s_add_alias(const char *alias) {
    aliases.emplace_back(std::string(alias));
}
void NPC::s_set_str_variable(const char *key, const char *value) {
    string_variables.set_variable(std::string(key), std::string(value));
}
void NPC::s_set_int_variable(const char *key, int value) {
    int_variables.set_variable(std::string(key), value);
}
void NPC::s_add_property(const char *property) {
    properties.emplace_back(std::string(property));
}
void NPC::s_remove_property(const char *prop) {
    const std::string property = std::string(prop);
    for (int i = 0; i < properties.size(); i++) {
        if (property == properties[i]) {
            properties.erase(properties.begin() + i);
        }
    }
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

std::string NPC::get_id() {
    return this->id;
}
std::string NPC::get_name() {
    return this->name;
}
std::string NPC::get_description() {
    return this->description;
}
std::string NPC::get_room_description() {
    return this->room_description;
}
std::string NPC::get_state() {
    return this->current_state;
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
void NPC::set_name(const std::string &name) {
    this->name = name;
}
void NPC::set_description(const std::string &desc) {
    this->description = desc;
}
void NPC::set_room_description(const std::string &desc) {
    this->room_description = desc;
}
void NPC::set_state(const std::string &state) {
    this->current_state = state;
}
bool NPC::check_name(const std::string &name) {
    // Check the name and all aliases to see if it matches the provided name
    const std::string caps_test = to_caps(name);
    if (to_caps(name) == caps_test) return true;
    for (const auto &x : aliases) {
        if (to_caps(x) == caps_test) return true;
    }

    return false;
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