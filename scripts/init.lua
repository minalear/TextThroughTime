-- To add rooms use Manager::AddRoom("UNIQUE_ID", "Room Name", "Room description")
-- Adding a room makes a global variable under UNIQUE_ID
-- To attach rooms to other rooms use BASE_ID:AttachRoom("OTHER_ROOM_ID", "Direction")

Manager:AddRoom("HOTEL_ENTRANCE", "Hotel Entrance", "The grand entrance to the hotel stands before you.  The red carpet leading up into the double glass doors of the lobby.")
Manager:AddRoom("HOTEL_LOBBY", "Hotel Lobby", "The lobby of the hotel holds the reception desk, several lounging couches and chairs, and a vending machine.\nA lavish staircase leads up towards the rooms while another door leads towards the back behind the desk.")

HOTEL_ENTRANCE:AttachRoom("HOTEL_LOBBY", "North")
HOTEL_LOBBY:AttachRoom("HOTEL_ENTRANCE", "South")

Manager:SetCurrentRoom("HOTEL_ENTRANCE")