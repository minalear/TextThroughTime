Manager:CreateRoom("LOBBY", "Arena Lobby")
LOBBY:SetDescription("The lobby of the arena is cramped and crowded with warriors from around the world.")

LOBBY:AddItem("ARENA_ARMORY")

Manager:CreateRoom("ARENA", "Arena")
ARENA:SetDescription("The roar of the crowd envelopes you as you face off against your opponent.")

ARENA:AddNPC("ARENA_MARLIN")