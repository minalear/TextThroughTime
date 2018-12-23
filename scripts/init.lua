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
--DUNG_CELL:AttachRoom("DUNG_SECRET_PASSAGE", "East")
--DUNG_CELL:AttachRoom("DUNG_HALLWAY", "North")
--UNG_HALLWAY:AttachRoom("DUNG_CELL", "South")
DUNG_HALLWAY:AttachRoom("DUNG_ENTRANCE", "North")
DUNG_ENTRANCE:AttachRoom("DUNG_HALLWAY", "South")
DUNG_ENTRANCE:AttachRoom("CASTLE", "East")
--DUNG_SECRET_PASSAGE:AttachRoom("DUNG_CELL", "West")
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
DUNG_CELL:SetDescription("")
DUNG_HALLWAY:SetDescription("")
DUNG_ENTRANCE:SetDescription("")
DUNG_SECRET_PASSAGE:SetDescription("")
CASTLE:SetDescription("")
SEWER_NW:SetDescription("")
SEWER_SW:SetDescription("")
SEWER_SE:SetDescription("")
SEWER_NE:SetDescription("")
SEWER_HIDEOUT:SetDescription("")
CITY_STREET:SetDescription("")
CITY_STREET_NORTH:SetDescription("")
CITY_MERCHANT:SetDescription("")
CITY_GARDEN:SetDescription("")
CITY_CLOTHING:SetDescription("")
CITY_GATE:SetDescription("")
VICTORY:SetDescription("")
	
-- Items for the Hobbit Hole
Manager:CreateItem("DISGUISE", "Disguise", "A set of clothing designed to conceal your identity discreetly.", false)
Manager:CreateItem("CELL_DOOR", 
	"Cell Door", "A wrought iron fence that has degraded slightly due to the moist environment of the dungeon.  "..
	"It looks very heavy and is locked with a fairly primitive locking mechanism.", true)
Manager:CreateItem("CELL_KEYS",
	"Keys", "Set of bronze keys that look like they could unlock a certain cell door.", false)
Manager:CreateItem("CELL_BRICK",
	"False Brick", "A peculiar looking brick that seems to be offset from the rest.  Perhaps I should press it?", true)

CITY_CLOTHING:AddItem("DISGUISE")
DUNG_CELL:AddItem("CELL_DOOR")
DUNG_CELL:AddItem("CELL_KEYS")
DUNG_CELL:AddItem("CELL_BRICK")
DUNG_HALLWAY:AddItem("CELL_DOOR")

--[[HH_LIVING_ROOM:AddItem("JOURNAL")
HH_LIVING_ROOM:AddItem("THE_RING")
HH_KITCHEN:AddItem("SMOKE_PIPE")
HH_PANTRY:AddItem("CHEESE_WHEEL")
HH_SECRET_ROOM:AddItem("THE_LIAR")]]--

require("scripts.room_scripts")
require("scripts.item_scripts")