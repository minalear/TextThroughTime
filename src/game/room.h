//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_ROOM_H
#define TEXTTHROUGHTIME_ROOM_H

#include <string>
#include "map.h"
#include "npc.h"
#include "inventory.h"
#include "npc_container.h"

class Room {
    std::map<Directions, Room*> connected_rooms;
    std::string id, name, description;
    Inventory room_inventory;
    NPCContainer npcs;

    Map *game_map;

    std::vector<std::string> properties;

public:
    Room(const std::string &id);
    Room(const std::string &id, const std::string &name, const std::string &description, Map *map);
    ~Room();

    const char* s_get_id();
    const char* s_get_name();
    void s_set_name(const char *name);
    void s_set_description(const char *desc);
    void s_append_description(const char *desc);
    void s_attach_room(const char *room_id, const char *direction);
    void s_connect_rooms(const char *room_id, const char *direction);
    void s_add_item(const char *item_id);
    void s_add_items(const char *item_id, int quantity);
    void s_remove_item(const char *item_id);
    void s_remove_items(const char *item_id, int quantity);
    void s_add_npc(const char *npc_id);
    void s_remove_npc(const char *npc_id);
    bool s_has_property(const char *property);
    void s_add_property(const char *property);
    void s_remove_property(const char *property);

    void attach_room(Room* room, Directions direction);

    Room* get_room(Directions direction);
    bool can_move(Directions direction);
    bool can_move(const std::string &direction);
    bool can_move(const std::string &direction_str, Directions &direction);

    std::string get_id();
    std::string get_name();
    std::string get_description();
    std::string get_full_description();

    void set_name(const std::string& name);
    void set_description(const std::string& desc);
    void set_map(Map *map);

    Inventory* get_inventory();
    NPCContainer* get_npc_container();
};

#endif //TEXTTHROUGHTIME_ROOM_H
