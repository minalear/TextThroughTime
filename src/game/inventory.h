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
    Item* remove_item(const std::string &unique_id);
};

#endif //TEXTTHROUGHTIME_INVENTORY_H
