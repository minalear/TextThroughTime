//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_ROOM_H
#define TEXTTHROUGHTIME_ROOM_H

#include <string>
#include "map.h"
#include "inventory.h"

class Room {
    std::map<Directions, Room*> connected_rooms;
    std::string id, name, description;
    Inventory room_inventory;

    Map *game_map;

public:
    Room(const std::string &id);
    Room(const std::string &id, const std::string &name, const std::string &description, Map *map);
    ~Room();

    void s_attach_room(const char* room_id, const char* direction);
    void s_set_description(const char* desc);
    void s_add_item(const char* item_id);
    void attach_room(Room* room, Directions direction);

    Room* get_room(Directions direction);
    bool can_move(Directions direction);
    bool can_move(const std::string &direction);
    bool can_move(const std::string &direction_str, Directions &direction);

    std::string get_id();
    std::string get_name();
    std::string get_description();

    void set_name(const std::string& name);
    void set_description(const std::string& desc);
    void set_map(Map *map);

    Inventory* get_inventory();
};

#endif //TEXTTHROUGHTIME_ROOM_H
