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
void Room::s_attach_room(const char *room_id, const char *direction) {
    auto room = game_map->get_room(std::string(room_id));
    auto dir  = game_map->str_to_direction(std::string(direction));

    attach_room(room, dir);
}
void Room::s_set_description(const char* desc) {
    set_description(std::string(desc));
}
void Room::s_add_item(const char *item_id) {
    Item *item = nullptr;
    if (game_map->get_inventory()->get_item(std::string(item_id), item)) {
        room_inventory.add_item(item);
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