//
// Created by Trevor Fisher on 1/8/2019.
//

#include "equipment.h"
#include "../npc.h"

EQUIPMENT_SLOTS str_to_slot(const std::string &str) {
    if (str == "HEAD") return EQUIPMENT_SLOTS::HEAD;
    if (str == "ARMOR") return EQUIPMENT_SLOTS::ARMOR;
    if (str == "CLOAK") return EQUIPMENT_SLOTS::CLOAK;
    if (str == "NECK") return EQUIPMENT_SLOTS::NECK;
    if (str == "RING_01") return EQUIPMENT_SLOTS::RING_01;
    if (str == "RING_02") return EQUIPMENT_SLOTS::RING_02;
    if (str == "TRINKET") return EQUIPMENT_SLOTS::TRINKET;
    if (str == "MAIN_HAND") return EQUIPMENT_SLOTS::MAIN_HAND;
    if (str == "OFF_HAND") return EQUIPMENT_SLOTS::OFF_HAND;

    return EQUIPMENT_SLOTS::NONE;
}

Equipment::Equipment(NPC *npc) {
    this->npc = npc;
}

int Equipment::get_total_attack_bonus() {
    int total = 0;
    for (const auto &slot : slots) {
        if (slot.equipped) total += (slot.equipped) ? slot.equipment->get_attack_bonus() : 0;
    }

    return total;
}
int Equipment::get_total_ac_bonus() {
    int total = 0;
    for (const auto &slot : slots) {
        if (slot.equipped) total += (slot.equipped) ? slot.equipment->get_ac_bonus() : 0;
    }

    return total;
}
int Equipment::get_total_str_bonus() {
    int total = 0;
    for (const auto &slot : slots) {
        if (slot.equipped) total += (slot.equipped) ? slot.equipment->get_str_bonus() : 0;
    }

    return total;
}
int Equipment::get_total_dex_bonus() {
    int total = 0;
    for (const auto &slot : slots) {
        if (slot.equipped) total += (slot.equipped) ? slot.equipment->get_dex_bonus() : 0;
    }

    return total;
}
int Equipment::get_total_vit_bonus() {
    int total = 0;
    for (const auto &slot : slots) {
        if (slot.equipped) total += (slot.equipped) ? slot.equipment->get_vit_bonus() : 0;
    }

    return total;
}
int Equipment::get_total_int_bonus() {
    int total = 0;
    for (const auto &slot : slots) {
        if (slot.equipped) total += (slot.equipped) ? slot.equipment->get_int_bonus() : 0;
    }

    return total;
}
int Equipment::get_total_wis_bonus() {
    int total = 0;
    for (const auto &slot : slots) {
        if (slot.equipped) total += (slot.equipped) ? slot.equipment->get_wis_bonus() : 0;
    }

    return total;
}
int Equipment::get_total_cha_bonus() {
    int total = 0;
    for (const auto &slot : slots) {
        if (slot.equipped) total += (slot.equipped) ? slot.equipment->get_cha_bonus() : 0;
    }

    return total;
}
int Equipment::get_total_luck_bonus() {
    int total = 0;
    for (const auto &slot : slots) {
        if (slot.equipped) total += (slot.equipped) ? slot.equipment->get_luck_bonus() : 0;
    }

    return total;
}

void Equipment::equip_item(Item *equipment) {
    if (!equipment->s_has_property("EQUIPMENT")) return;
    auto slot = get_equipment_slot(str_to_slot(equipment->s_get_str_variable("EQUIPMENT_SLOT")));

    // Add the currently equipped item to the NPC's inventory
    if (slot->equipped) {
        npc->get_inventory()->add_item(slot->equipment);
    } else {
        slot->equipped = true;
    }

    slot->equipment = equipment;
}
EquipmentSlot *Equipment::get_equipment_slot(EQUIPMENT_SLOTS slot) {
    return &slots[(int)slot];
}