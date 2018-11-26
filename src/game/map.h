//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_MAP_H
#define TEXTTHROUGHTIME_MAP_H

#include <map>
#include <string>

class Room;
typedef std::pair<std::string, Room*> RoomIndex;

enum struct Directions {
    North, South, East, West, None
};

class Map {
private:
    std::map<std::string, Room*> game_map;

public:
    Directions str_to_direction(const std::string &text);
    Room* add_room(
            const std::string &unique_id,
            const std::string &name,
            const std::string &description);
    void attach_room(
            const std::string &target_id,
            const std::string &base_id,
            const std::string &direction);
    Room* get_room(const std::string &id);
};

#endif //TEXTTHROUGHTIME_MAP_H
