//
// Created by minal on 1/5/2019.
//

#include "npc_container.h"
#include "npc.h"

void NPCContainer::add_npc(NPC *npc) {
    npcs.emplace_back(npc);
}
bool NPCContainer::remove_npc(const std::string &unique_id) {
    for (int i = 0; i < npcs.size(); i++) {
        if (npcs[i]->get_id() == unique_id) {
            npcs.erase(npcs.begin() + i);
            return true;
        }
    }

    return false;
}

bool NPCContainer::get_npc(const std::string &unique_id, NPC *&npc) {
    for (const auto &x : npcs) {
        if (x->get_id() == unique_id) {
            npc = x;
            return true;
        }
    }

    return false;
}

bool NPCContainer::get_npc_by_name(const std::string &name, NPC *&npc) {
    for (const auto &x : npcs) {
        if (x->check_name(name)) {
            npc = x;
            return true;
        }
    }

    return false;
}

std::string NPCContainer::get_npc_list() {
    std::string buffer;
    for (const auto &npc : npcs) {
        buffer += npc->get_name() + "\n";
    }

    return buffer;
}

std::string NPCContainer::get_room_descriptions() {
    std::string desc_buffer;
    for (const auto &npc : npcs) {
        auto x_room_desc = npc->get_room_description();

        if (!x_room_desc.empty()) {
            desc_buffer += "  " + npc->get_room_description();
        }
    }

    return desc_buffer;
}

void NPCContainer::delete_npcs() {
    for (int i = 0; i < npcs.size(); i++) {
        delete npcs[i];
    }
    npcs.clear();
}
