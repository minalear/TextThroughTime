//
// Created by Trevor Fisher on 10/11/2018.
//

#include "room.h"

// Constructors/Destructor
Room::Room(const std::string &id) {
    this->id = id;
    set_name("[ROOM]");
    set_description("[DESCRIPTION]");
}
Room::Room(const std::string &id, const std::string &name, const std::string &description, Map *map) {
    this->id = id;
    this->game_map = map;
    set_name(name);
    set_description(description);
}
Room::~Room() { }

// Public functions
const char* Room::s_get_id() {
    return id.c_str();
}
const char* Room::s_get_name() {
    return name.c_str();
}
void Room::s_set_name(const char *name) {
    set_name(std::string(name));
}
void Room::s_set_description(const char *desc) {
    set_description(std::string(desc));
}
void Room::s_append_description(const char *desc) {
    set_description(description + "\n" + std::string(desc));
}
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
    room_inventory.remove_item(item_id);
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
bool Room::s_has_property(const char *prop) {
    const std::string property = std::string(prop);
    for (const auto &x : properties) {
        if (property == x) return true;
    }

    return false;
}
void Room::s_add_property(const char *property) {
    properties.emplace_back(std::string(property));
}
void Room::s_remove_property(const char *prop) {
    const std::string property = std::string(prop);
    for (int i = 0; i < properties.size(); i++) {
        if (property == properties[i]) {
            properties.erase(properties.begin() + i);
        }
    }
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

std::string Room::get_id() {
    return id;
}
std::string Room::get_name() {
    return name;
}
std::string Room::get_description() {
    return description;
}
std::string Room::get_full_description() {
    return get_description() + room_inventory.get_room_descriptions() + npcs.get_room_descriptions();
}
void Room::set_name(const std::string& name) {
    this->name = name;
}
void Room::set_description(const std::string& desc) {
    this->description = desc;
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
