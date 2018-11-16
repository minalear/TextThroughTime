//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_ROOM_H
#define TEXTTHROUGHTIME_ROOM_H

#include <string>
#include "map.h"

class Room {
    std::map<Directions, Room*> connected_rooms;
    std::string name, description;

public:
    Room();
    Room(const std::string &name, const std::string &description);
    ~Room();

    void attach_room(Room* room, Directions direction);
    Room* get_room(Directions direction);
    bool can_move(Directions direction);
    bool can_move(std::string direction);

    std::string get_name();
    std::string get_description();

    void set_name(const std::string& name);
    void set_description(const std::string& desc);
};

#endif //TEXTTHROUGHTIME_ROOM_H
