Manager:AddRoom("ROOM_001", "Yellow Room", "This room is very yellow.")
Manager:AddRoom("ROOM_002", "Green Room", "Turns out, this room is pretty green.")

Manager:AttachRoom("ROOM_001", "ROOM_002", "North")
Manager:AttachRoom("ROOM_002", "ROOM_001", "South")

Manager:SetCurrentRoom("ROOM_001")