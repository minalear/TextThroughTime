//
// Created by minal on 12/19/2018.
//

#ifndef TEXTTHROUGHTIME_INVENTORY_H
#define TEXTTHROUGHTIME_INVENTORY_H

#include <vector>
#include <string>

class Item;

struct InventorySlot {
    Item *item;
    int quantity;

    InventorySlot(Item* item, int quantity);
};

class Inventory {
    std::vector<InventorySlot*> items;

public:
    void add_item(Item* item);
    void add_item(Item* item, int quantity);
    bool remove_item(const std::string &unique_id);
    bool remove_item(const std::string &unique_id, int quantity);
    bool get_item(const std::string &unique_id, InventorySlot *&item);
    bool get_item_by_name(const std::string &name, InventorySlot *&item);

    std::string get_item_list(bool ignore_static = true);
    std::string get_room_descriptions();
    void delete_items();
};

#endif //TEXTTHROUGHTIME_INVENTORY_H