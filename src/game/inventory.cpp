//
// Created by minal on 12/19/2018.
//

#include "inventory.h"
#include "../tokenizer.h"

void Inventory::add_item(Item *item) {
    items.push_back(item);
}
bool Inventory::remove_item(const std::string &unique_id) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->get_id() == unique_id) {
            items.erase(items.begin() + i);
            return true;
        }
    }

    return false;
}
bool Inventory::remove_item(const std::string &unique_id, Item *&item) {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->get_id() == unique_id) {
            item = items[i];
            items.erase(items.begin() + i);
            return true;
        }
    }

    return false;
}
bool Inventory::get_item(const std::string &unique_id, Item *&item) {
    // Loop through each item in the inventory, if we find the id, set item to it and return true
    for (const auto &x : items) {
        if (x->get_id() == unique_id) {
            item = x;
            return true;
        }
    }

    return false;
}
bool Inventory::get_item_by_name(const std::string &name, Item *&item) {
    // Convert name to all caps
    std::string name_caps = to_caps(name);
    for (const auto &x : items) {
        if (to_caps(x->get_name()) == name_caps) {
            item = x;
            return true;
        }
    }

    return false;
}

std::string Inventory::get_item_list() {
    std::string buffer;
    for (const auto &x : items) {
        buffer += x->get_name() + "\n";
    }

    return buffer;
}
void Inventory::delete_items() {
    for (int i = 0; i < items.size(); i++) {
        delete items[i];
    }
    items.clear();
}