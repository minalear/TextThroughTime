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
DUNG_SECRET_PASSAGE:AttachRoom("SEWER_SE", "East")

CASTLE:AttachRoom("DUNG_ENTRANCE", "West")
CASTLE:AttachRoom("CITY_MERCHANT", "East")

SEWER_SE:AttachRoom("DUNG_SECRET_PASSAGE", "West")
SEWER_SE:AttachRoom("SEWER_NE", "North")
SEWER_NE:AttachRoom("SEWER_SE", "South")
SEWER_NE:AttachRoom("SEWER_NW", "West")
SEWER_SW:AttachRoom("SEWER_HIDEOUT", "South")
SEWER_SW:AttachRoom("SEWER_NW", "North")
SEWER_NW:AttachRoom("SEWER_NE", "West")

-- Starting Room --
Manager:SetCurrentRoom("DUNG_CELL")

-- Room Descriptions --
HH_LIVING_ROOM:SetDescription(
	"A quaint little abode settled partially underground, furnished to the brim with antiques acquired from your family.  "..
	"A small round door leads to your front lawn while an archway leads to your kitchen behind you.  A end table sits next to your leather couch "..
	"which you tend to store important trinkets lies closed as well.")
HH_KITCHEN:SetDescription(
	"A kitchen set against the back of the house with your basic array of cooking appliances; a stove, sink, and various storage bins.  "..
	"A door leading to your expansive pantry is also located to the side here.")
HH_PANTRY:SetDescription(
	"A very spacious pantry cut into the heart of the hill, making it much cooler than the other rooms in the house, allowing  "..
	"for storage of food.")
HH_LAWN:SetDescription(
	"Your spacious lawn sprawls out in front of you, with your garden stretching out to your right.  The surrounding hills are very green for this "..
	"time of year.  Various noises can be heard from down the lane, nothing too out of the ordinary.")
HH_SECRET_ROOM:SetDescription(
	"A secret room with secret stuff.")
	
-- Items for the Hobbit Hole
Manager:CreateItem("SMOKE_PIPE", "Pipe", "A luxuriously crafted wooden pipe, carved with various designs from the Ancient Kingdom.  It is loaded with some Deborah's famous Kush.")
Manager:CreateItem("CHEESE_WHEEL", "Cheese Wheel", "A very rotund piece of cheddar cheese.")
Manager:CreateItem("JOURNAL", "Journal", "Your personal journal where you keep notes about that one book you're writing about the Dark Lord and stuff.")
Manager:CreateItem("THE_RING", "Ring", "A small golden ring.")
Manager:CreateItem("THE_LIAR", "Khajiit Statue", "A strange looking statue of a Khajiit.  Inscribed on the bottom is the name \"M'aiq the Liar.\"")

HH_LIVING_ROOM:AddItem("JOURNAL")
HH_LIVING_ROOM:AddItem("THE_RING")
HH_KITCHEN:AddItem("SMOKE_PIPE")
HH_PANTRY:AddItem("CHEESE_WHEEL")
HH_SECRET_ROOM:AddItem("THE_LIAR")

require("scripts.room_scripts")