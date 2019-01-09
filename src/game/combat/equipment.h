//
// Created by Trevor Fisher on 1/8/2019.
//

#ifndef TEXTTHROUGHTIME_EQUIPMENT_H
#define TEXTTHROUGHTIME_EQUIPMENT_H

#include "../item.h"

struct EquipmentSlot {
    Item *equipment = nullptr;
    bool equipped = false;
};
struct Equipment {
    NPC *npc;

    // Armor slots
    EquipmentSlot headwear;
    EquipmentSlot armor;
    EquipmentSlot cloak;

    // Jewelry
    EquipmentSlot neckpiece;
    EquipmentSlot ring01;
    EquipmentSlot ring02;
    EquipmentSlot trinket;

    // Weapons/Shields
    EquipmentSlot main_hand;
    EquipmentSlot off_hand;

    Equipment(NPC *npc);
    int calculate_ac();
    void equip_item(Item *equipment);
    EquipmentSlot *get_slot()
};


#endif //TEXTTHROUGHTIME_EQUIPMENT_H
