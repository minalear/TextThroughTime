//
// Created by Trevor Fisher on 10/11/2018.
//

#include "map.h"
#include "room.h"
#include <cassert>
#include <string>

Directions str_to_direction(const std::string &text) {
    // Set text to all caps
    std::string buffer;
    for (int i = 0; i < text.size(); i++) {
        buffer += (char)std::toupper(text[i]);
    }
    if (buffer == "NORTH") return Directions::North;
    if (buffer == "SOUTH") return Directions::South;
    if (buffer == "EAST")  return Directions::East;
    if (buffer == "WEST")  return Directions::West;

    return Directions::None;
}

void Map::add_room(const std::string &unique_id, const std::string &name, const std::string &description) {
    // Ensure that there is only one room with that unique id
    assert(game_map.find(unique_id) == game_map.end());
    auto new_room = new Room(name, description);
    game_map.insert(RoomIndex(unique_id, new_room));
}

void Map::attach_room(const std::string &target_id, const std::string &base_id, const std::string &dir) {
    auto base_room = game_map[base_id];
    auto next_room = game_map[target_id];
    auto direction = str_to_direction(dir);

    assert(direction != Directions::None);
    base_room->attach_room(next_room, direction);
}

Room *Map::get_room(const std::string &id) {
    return game_map[id];
}
