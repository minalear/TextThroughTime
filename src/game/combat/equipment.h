//
// Created by Trevor Fisher on 1/8/2019.
//

#ifndef TEXTTHROUGHTIME_EQUIPMENT_H
#define TEXTTHROUGHTIME_EQUIPMENT_H

#include "../item.h"

enum struct EQUIPMENT_SLOTS {
    HEAD = 0,
    ARMOR = 1,
    CLOAK = 2,
    NECK = 3,
    RING_01 = 4,
    RING_02 = 5,
    TRINKET = 6,
    MAIN_HAND = 7,
    OFF_HAND = 8,
    NONE = -1
};

struct EquipmentSlot {
    Item *equipment = nullptr;
    bool equipped = false;
};
struct Equipment {
    NPC *npc;

    const static int NUM_SLOTS = 9;
    EquipmentSlot slots[NUM_SLOTS];

    Equipment(NPC *npc);
    int calculate_ac();
    void equip_item(Item *equipment);
    EquipmentSlot *get_equipment_slot(EQUIPMENT_SLOTS slot);
};


#endif //TEXTTHROUGHTIME_EQUIPMENT_H
