//
// Created by Trevor Fisher on 1/8/2019.
//

#include "equipment.h"

Equipment::Equipment(NPC *npc) {
    this->npc = npc;
}

int Equipment::calculate_ac() {
    int total = 0;
    total += (headwear.equipped)  ? headwear.equipment->get_ac_bonus() : 0;
    total += (armor.equipped)     ? armor.equipment->get_ac_bonus() : 0;
    total += (cloak.equipped)     ? cloak.equipment->get_ac_bonus() : 0;

    total += (neckpiece.equipped) ? neckpiece.equipment->get_ac_bonus() : 0;
    total += (ring01.equipped)    ? ring01.equipment->get_ac_bonus() : 0;
    total += (ring02.equipped)    ? ring02.equipment->get_ac_bonus() : 0;
    total += (trinket.equipped)   ? trinket.equipment->get_ac_bonus() : 0;

    total += (main_hand.equipped) ? main_hand.equipment->get_ac_bonus() : 0;
    total += (off_hand.equipped)  ? off_hand.equipment->get_ac_bonus() : 0;

    return total;
}
void Equipment::equip_item(Item *equipment) {
    if (!equipment->s_has_property("EQUIPMENT")) return;
    const std::string slot = equipment->s_get_str_variable("EQUIPMENT_SLOT");
}
EquipmentSlot *Equipment::get_slot() {
    return nullptr;
}
