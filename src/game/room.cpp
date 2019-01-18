//
// Created by Trevor Fisher on 10/11/2018.
//

#include "room.h"

// Constructors/Destructor
Room::Room(Map *map, const std::string &id) : GameObject(map, id) { }
Room::Room(Map *map, const std::string &id, const std::string &name, const std::string &desc) : GameObject(map, id, name, desc) { }

// Public functions
void Room::s_attach_room(const char *room_id, const char *direction) {
    auto room = game_map->get_room(std::string(room_id));
    auto dir  = game_map->str_to_direction(std::string(direction));

    attach_room(room, dir);
}
void Room::s_connect_rooms(const char *room_id, const char *direction) {
    auto room = game_map->get_room(std::string(room_id));
    auto dir  = game_map->str_to_direction(std::string(direction));

    attach_room(room, dir);
    room->attach_room(this, game_map->get_opposite_direction(dir));
}
void Room::s_add_item(const char *item_id) {
    InventorySlot *item_slot = nullptr;
    if (game_map->get_inventory()->get_item(std::string(item_id), item_slot)) {
        room_inventory.add_item(item_slot->item, 1);
    }
}
void Room::s_add_items(const char *item_id, int quantity) {
    InventorySlot *item_slot = nullptr;
    if (game_map->get_inventory()->get_item(std::string(item_id), item_slot)) {
        room_inventory.add_item(item_slot->item, quantity);
    }

    // TODO: Add error checking for invalid Item ID
}
void Room::s_remove_item(const char *item_id) {
    room_inventory.remove_item(item_id);
}
void Room::s_remove_items(const char *item_id, int quantity) {
    room_inventory.remove_item(item_id, quantity);
}
void Room::s_add_npc(const char *npc_id) {
    NPC *npc = nullptr;
    if (game_map->get_npc_container()->get_npc(std::string(npc_id), npc)) {
        npcs.add_npc(npc);
    }

    // TODO: Add error checking for invalid NPC ID
}
void Room::s_remove_npc(const char *npc_id) {
    npcs.remove_npc(std::string(npc_id));
}

void Room::attach_room(Room *room, Directions direction) {
    if (connected_rooms.count(direction) == 0) {
        connected_rooms.insert(std::pair<Directions, Room*>(direction, room));
    }
}
bool Room::can_move(Directions direction) {
    return (connected_rooms.count(direction) > 0);
}
bool Room::can_move(const std::string &direction) {
    return can_move(game_map->str_to_direction(direction));
}
bool Room::can_move(const std::string &direction_str, Directions &direction) {
    direction = game_map->str_to_direction(direction_str);
    return can_move(direction);
}

std::string Room::get_full_description() {
    return get_description() + room_inventory.get_room_descriptions() + npcs.get_room_descriptions();
}
void Room::set_map(Map *map) {
    this->game_map = map;
}

Room *Room::get_room(Directions direction) {
    return connected_rooms[direction];
}
Inventory* Room::get_inventory() {
    return &room_inventory;
}
NPCContainer *Room::get_npc_container() {
    return &npcs;
}
