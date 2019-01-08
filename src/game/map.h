//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_MAP_H
#define TEXTTHROUGHTIME_MAP_H

#include <map>
#include <string>
#include "inventory.h"
#include "npc_container.h"

class Room;
typedef std::pair<std::string, Room*> RoomIndex;

enum struct Directions {
    North, South, East, West, None
};

class Map {
private:
    std::map<std::string, Room*> game_map;
    Inventory all_items; // List of all items in the game
    NPCContainer all_npcs;

public:
    Map();
    ~Map();

    Directions str_to_direction(const std::string &text);
    Directions get_opposite_direction(Directions direction);
    Room* add_room(
            const std::string &unique_id,
            const std::string &name,
            const std::string &description);
    void attach_room(
            const std::string &target_id,
            const std::string &base_id,
            const std::string &direction);
    Room* get_room(const std::string &id);
    Inventory* get_inventory();
    NPCContainer* get_npc_container();
};

#endif //TEXTTHROUGHTIME_MAP_H
