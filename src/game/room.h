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

    Map *game_map;

public:
    Room();
    Room(Map *map, const std::string &name, const std::string &description);
    ~Room();

    void s_attach_room(const char* room_id, const char* direction);
    void s_set_description(const char* desc);
    void attach_room(Room* room, Directions direction);

    Room* get_room(Directions direction);
    bool can_move(Directions direction);
    bool can_move(const std::string &direction);
    bool can_move(const std::string &direction_str, Directions &direction);

    std::string get_name();
    std::string get_description();

    void set_name(const std::string& name);
    void set_description(const std::string& desc);
    void set_map(Map *map);
};

#endif //TEXTTHROUGHTIME_ROOM_H
