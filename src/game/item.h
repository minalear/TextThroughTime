//
// Created by minal on 12/19/2018.
//

#ifndef TEXTTHROUGHTIME_ITEM_H
#define TEXTTHROUGHTIME_ITEM_H

#include <string>
#include <vector>

class Item {
    std::string id; // The unique ID of the item
    std::string name; // The name that appears in the inventory
    std::string description; // The description of the item when examined
    std::string room_description; // The description of the item while it's in the room.  Appears when the room is examined.
    std::string current_state; // Used to define different behaviors depending on the item's current state

    std::vector<std::string> aliases;
    bool is_static = false;

public:
    Item(const std::string &id);
    Item(const std::string &id, const std::string &name, const std::string &desc);
    ~Item();

    const char* s_get_id();
    const char* s_get_name();
    const char* s_get_state();

    void s_set_name(const char *name);
    void s_set_description(const char *desc);
    void s_append_description(const char *desc);
    void s_set_room_description(const char *desc);
    void s_set_state(const char *state);
    void s_add_alias(const char *alias);

    std::string get_id();
    std::string get_name();
    std::string get_description();
    std::string get_room_description();
    std::string get_state();
    bool get_is_static();

    void set_name(const std::string &name);
    void set_description(const std::string &desc);
    void set_room_description(const std::string &desc);
    void set_is_static(bool value);
    void set_state(const std::string &state);
    bool check_name(const std::string &name);
};

#endif //TEXTTHROUGHTIME_ITEM_H
