//
// Created by Trevor Fisher on 10/11/2018.
//

#include "room.h"

Room::Room(const std::string &name, const std::string &description) {
    this->name = name;
    this->description = description;
}
Room::Room() {
    this->name = "[ROOM]";
    this->description = "[DESCRIPTION]";
}
Room::~Room() { }

void Room::attach_room(Room *room, Directions direction) {
    if (connected_rooms.count(direction) == 0) {
        connected_rooms.insert(std::pair<Directions, Room*>(direction, room));
    }
}
bool Room::can_move(Directions direction) {
    return (connected_rooms.count(direction) > 0);
}
bool Room::can_move(std::string direction) {
    if (direction == "north") return can_move(Directions::North);
    if (direction == "south") return can_move(Directions::South);
    if (direction == "east") return can_move(Directions::East);
    if (direction == "west") return can_move(Directions::West);

    return false;
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

Room *Room::get_room(Directions direction) {
    return connected_rooms[direction];
}
