//
// Created by Trevor Fisher on 10/11/2018.
//

#include "room.h"

// Constructors/Destructor
Room::Room(Map *map, const std::string &name, const std::string &description) {
    this->game_map = map;
    this->name = name;
    this->description = description;
}
Room::Room() {
    this->name = "[ROOM]";
    this->description = "[DESCRIPTION]";
}
Room::~Room() { }

// Public functions
void Room::s_attach_room(const char *room_id, const char *direction) {
    auto room = game_map->get_room(std::string(room_id));
    auto dir  = game_map->str_to_direction(std::string(direction));

    attach_room(room, dir);
}
void Room::attach_room(Room *room, Directions direction) {
    if (connected_rooms.count(direction) == 0) {
        connected_rooms.insert(std::pair<Directions, Room*>(direction, room));
    }
}
bool Room::can_move(Directions direction) {
    return (connected_rooms.count(direction) > 0);
}
bool Room::can_move(std::string direction) {
    return can_move(game_map->str_to_direction(direction));
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
