//
// Created by minal on 12/19/2018.
//

#ifndef TEXTTHROUGHTIME_INVENTORY_H
#define TEXTTHROUGHTIME_INVENTORY_H

#include <vector>
#include <string>
#include "item.h"

class Inventory {
    std::vector<Item*> items;

public:
    void add_item(Item* item);
    bool remove_item(const std::string &unique_id);
    bool remove_item(const std::string &unique_id, Item *&item);
    bool get_item(const std::string &unique_id, Item *&item);
    bool get_item_by_name(const std::string &name, Item *&item);

    std::string get_item_list();
    void delete_items();
};

#endif //TEXTTHROUGHTIME_INVENTORY_H