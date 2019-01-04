//
// Created by minal on 12/19/2018.
//

#include "inventory.h"
#include "../tokenizer.h"

InventorySlot::InventorySlot(Item* item, int quantity) {
    this->item = item;
    this->quantity = quantity;
}

void Inventory::add_item(Item *item) {
    InventorySlot *slot;
    if (get_item(item->get_id(), slot)) {
        slot->quantity += 1;
    } else {
        slot = new InventorySlot(item, 1);
        items.push_back(slot);
    }
}
void Inventory::add_item(Item *item, int quantity) {
    InventorySlot *slot;
    if (get_item(item->get_id(), slot)) {
        slot->quantity += 1;
    } else {
        slot = new InventorySlot(item, quantity);
        items.push_back(slot);
    }
}
bool Inventory::remove_item(const std::string &unique_id) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->item->get_id() == unique_id) {
            items.erase(items.begin() + i);
            return true;
        }
    }

    return false;
}
bool Inventory::remove_item(const std::string &unique_id, int quantity) {
    for (int i = 0; i < items.size(); i++) {
        const auto slot = items[i];

        if (slot->item->get_id() == unique_id) {
            // You cannot remove more items than the inventory has
            if (quantity > slot->quantity) return false;

            // Decrease the quantity and remove the slot if it is zero or below
            slot->quantity -= quantity;
            if (slot->quantity <= 0) {
                items.erase(items.begin() + i);
                return true;
            }
        }
    }

    return false;
}
bool Inventory::get_item(const std::string &unique_id, InventorySlot *&item) {
    // Loop through each item in the inventory, if we find the id, set item to it and return true
    for (const auto &slot : items) {
        if (slot->item->get_id() == unique_id) {
            item = slot;
            return true;
        }
    }

    return false;
}
bool Inventory::get_item_by_name(const std::string &name, InventorySlot *&item) {
    for (const auto &slot : items) {
        if (slot->item->check_name(name)) {
            item = slot;
            return true;
        }
    }

    return false;
}

std::string Inventory::get_item_list(bool ignore_static) {
    std::string buffer;
    for (const auto &slot : items) {
        if (!ignore_static && slot->item->get_is_static()) {
            buffer += slot->item->get_name() + "(static)\n";
        }
        else if (!slot->item->get_is_static()) {
            buffer += slot->item->get_name() + "  -  " + std::to_string(slot->quantity) + "\n";
        }
    }

    return buffer;
}
std::string Inventory::get_room_descriptions() {
    std::string desc_buffer;
    for (const auto &slot : items) {
        auto x_room_desc = slot->item->get_room_description();

        if (!x_room_desc.empty()) {
            desc_buffer += "  " + slot->item->get_room_description();
        }
    }

    return desc_buffer;
}
void Inventory::delete_items() {
    for (int i = 0; i < items.size(); i++) {
        delete items[i];
    }
    items.clear();
}