-- To add rooms use Manager::AddRoom("UNIQUE_ID", "Room Name", "Room description")
-- Adding a room makes a global variable under UNIQUE_ID
-- To attach rooms to other rooms use BASE_ID:AttachRoom("OTHER_ROOM_ID", "Direction")

-- Room Creation --
Manager:AddRoom("DUNG_CELL", "Dungeon Cell", "")
Manager:AddRoom("DUNG_HALLWAY", "Dungeon Hallway", "")
Manager:AddRoom("DUNG_ENTRANCE", "Dungeon Entrance", "")
Manager:AddRoom("DUNG_SECRET_PASSAGE", "Secret Passage", "")

Manager:AddRoom("CASTLE", "Castle Courtyard", "")

Manager:AddRoom("SEWER_SE", "South-East Sewer", "")
Manager:AddRoom("SEWER_NE", "North-East Sewer", "")
Manager:AddRoom("SEWER_SW", "South-West Sewer", "")
Manager:AddRoom("SEWER_NW", "North-West Sewer", "")
Manager:AddRoom("SEWER_HIDEOUT", "Secret Hideout", "")

Manager:AddRoom("CITY_STREET", "Main Avenue", "")
Manager:AddRoom("CITY_STREET_NORTH", "North Main Avenue", "")
Manager:AddRoom("CITY_MERCHANT", "Merchant Quarter", "")
Manager:AddRoom("CITY_GARDEN", "Memorial Garden", "")
Manager:AddRoom("CITY_CLOTHING", "Clothing Shoppe", "")
Manager:AddRoom("CITY_GATE", "Main Gate", "")

Manager:AddRoom("VICTORY", "Outside", "")

-- Room Attachments --
DUNG_CELL:AttachRoom("DUNG_SECRET_PASSAGE", "East")
DUNG_CELL:AttachRoom("DUNG_HALLWAY", "North")
DUNG_HALLWAY:AttachRoom("DUNG_CELL", "South")
DUNG_HALLWAY:AttachRoom("DUNG_ENTRANCE", "North")
DUNG_ENTRANCE:AttachRoom("DUNG_HALLWAY", "South")
DUNG_ENTRANCE:AttachRoom("CASTLE", "East")
DUNG_SECRET_PASSAGE:AttachRoom("DUNG_CELL", "West")
DUNG_SECRET_PASSAGE:AttachRoom("SEWER_SW", "East")

CASTLE:AttachRoom("DUNG_ENTRANCE", "West")
CASTLE:AttachRoom("CITY_MERCHANT", "East")

SEWER_SW:AttachRoom("DUNG_SECRET_PASSAGE", "West")
SEWER_SW:AttachRoom("SEWER_NW", "North")
SEWER_NW:AttachRoom("SEWER_SW", "South")
SEWER_NW:AttachRoom("SEWER_NE", "East")
SEWER_NE:AttachRoom("SEWER_NW", "West")
SEWER_NE:AttachRoom("CITY_STREET", "North")
SEWER_NE:AttachRoom("SEWER_SE", "South")
SEWER_SE:AttachRoom("SEWER_NE", "North")
SEWER_SE:AttachRoom("SEWER_HIDEOUT", "South")
SEWER_HIDEOUT:AttachRoom("SEWER_SE", "North")

CITY_STREET:AttachRoom("CITY_STREET_NORTH", "North")
CITY_STREET:AttachRoom("SEWER_NW", "South")
CITY_STREET:AttachRoom("CITY_GARDEN", "East")
CITY_STREET:AttachRoom("CITY_MERCHANT", "West")
CITY_STREET_NORTH:AttachRoom("CITY_GATE", "North")
CITY_STREET_NORTH:AttachRoom("CITY_STREET", "South")
CITY_MERCHANT:AttachRoom("CITY_CLOTHING", "North")
CITY_MERCHANT:AttachRoom("CITY_STREET", "East")
CITY_MERCHANT:AttachRoom("CASTLE", "West")
CITY_GARDEN:AttachRoom("CITY_STREET", "West")
CITY_CLOTHING:AttachRoom("CITY_MERCHANT", "South")
CITY_GATE:AttachRoom("VICTORY", "North")
CITY_GATE:AttachRoom("CITY_STREET_NORTH", "South")

VICTORY:AttachRoom("CITY_GATE", "South")

-- Starting Room --
Manager:SetCurrentRoom("DUNG_CELL")

-- Room Descriptions --

	
-- Items for the Hobbit Hole
Manager:CreateItem("SMOKE_PIPE", "Pipe", "A luxuriously crafted wooden pipe, carved with various designs from the Ancient Kingdom.  It is loaded with some Deborah's famous Kush.")
Manager:CreateItem("CHEESE_WHEEL", "Cheese Wheel", "A very rotund piece of cheddar cheese.")
Manager:CreateItem("JOURNAL", "Journal", "Your personal journal where you keep notes about that one book you're writing about the Dark Lord and stuff.")
Manager:CreateItem("THE_RING", "Ring", "A small golden ring.")
Manager:CreateItem("THE_LIAR", "Khajiit Statue", "A strange looking statue of a Khajiit.  Inscribed on the bottom is the name \"M'aiq the Liar.\"")

--[[HH_LIVING_ROOM:AddItem("JOURNAL")
HH_LIVING_ROOM:AddItem("THE_RING")
HH_KITCHEN:AddItem("SMOKE_PIPE")
HH_PANTRY:AddItem("CHEESE_WHEEL")
HH_SECRET_ROOM:AddItem("THE_LIAR")]]--

require("scripts.room_scripts")