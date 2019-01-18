//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_ROOM_H
#define TEXTTHROUGHTIME_ROOM_H

#include "game_object.h"
#include "map.h"
#include "npc.h"
#include "inventory.h"
#include "npc_container.h"

class Room : public GameObject {
    std::map<Directions, Room*> connected_rooms;
    Inventory room_inventory;
    NPCContainer npcs;

public:
    Room(Map *map, const std::string &id);
    Room(Map *map, const std::string &id, const std::string &name, const std::string &desc);

    void s_attach_room(const char *room_id, const char *direction);
    void s_connect_rooms(const char *room_id, const char *direction);
    void s_add_item(const char *item_id);
    void s_add_items(const char *item_id, int quantity);
    void s_remove_item(const char *item_id);
    void s_remove_items(const char *item_id, int quantity);
    void s_add_npc(const char *npc_id);
    void s_remove_npc(const char *npc_id);

    void attach_room(Room* room, Directions direction);

    Room* get_room(Directions direction);
    bool can_move(Directions direction);
    bool can_move(const std::string &direction);
    bool can_move(const std::string &direction_str, Directions &direction);

    std::string get_full_description();
    void set_map(Map *map);

    Inventory* get_inventory();
    NPCContainer* get_npc_container();
};

#endif //TEXTTHROUGHTIME_ROOM_H
