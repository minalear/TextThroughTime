//
// Created by minal on 1/5/2019.
//

#ifndef TEXTTHROUGHTIME_NPC_CONTAINER_H
#define TEXTTHROUGHTIME_NPC_CONTAINER_H

#include <vector>
#include <string>

class NPC;
class NPCContainer {
    std::vector<NPC*> npcs;

public:
    void add_npc(NPC* npc);
    bool remove_npc(const std::string &unique_id);
    bool get_npc(const std::string &unique_id, NPC *&npc);
    bool get_npc_by_name(const std::string &name, NPC *&npc);

    std::string get_npc_list();
    std::string get_room_descriptions();

    void delete_npcs();
};


#endif //TEXTTHROUGHTIME_NPC_CONTAINER_H
