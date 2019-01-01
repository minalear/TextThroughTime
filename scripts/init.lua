require("scripts.utils") -- Utility script functions

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
DUNG_HALLWAY:ConnectRooms("DUNG_ENTRANCE", "North")
DUNG_ENTRANCE:ConnectRooms("CASTLE", "East")
CASTLE:ConnectRooms("CITY_MERCHANT", "East")
CITY_MERCHANT:ConnectRooms("CITY_CLOTHING", "North")
CITY_MERCHANT:ConnectRooms("CITY_STREET", "East")
CITY_STREET:ConnectRooms("CITY_STREET_NORTH", "North")
--CITY_STREET:ConnectRooms("SEWER_NE", "South")
CITY_STREET:ConnectRooms("CITY_GARDEN", "East")
CITY_STREET_NORTH:ConnectRooms("CITY_GATE", "North")
CITY_GATE:ConnectRooms("VICTORY", "North")
DUNG_SECRET_PASSAGE:ConnectRooms("SEWER_SW", "East")
SEWER_SW:ConnectRooms("SEWER_NW", "North")
SEWER_NW:ConnectRooms("SEWER_NE", "East")
SEWER_NE:ConnectRooms("SEWER_SE", "South")
--SEWER_SE:ConnectRooms("SEWER_HIDEOUT", "South")

-- Starting Room --
Manager:SetCurrentRoom("DUNG_CELL")

-- Room Descriptions --
DUNG_CELL:SetDescription("A cramped, damp dungeon cell surrounds you.  The cell seems to be carved out of natural stone, "..
						 "however a seemingly out of place brick wall makes up the right hand side of the cell.  "..
						 "A small bed sits in the corner while a smelly shit bucket resides next to it.  "..
						 "It is very dark in the cell, with whatever light present illuminating from the distant hallway through the cell door.  "..
						 "Trying to make out details is impossible, however, on the brick wall, there seems to be a single brick standing out from the rest.")
DUNG_HALLWAY:SetDescription("The hallway leads down towards a number of cells, all currently vacant.  The door that attracts your attention the most is "..
							"the solid iron door of your cell.  Nothing much else catches your attention.")
--[[DUNG_ENTRANCE:SetDescription("")
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
VICTORY:SetDescription("")]]--
	
-- Items for the game
-- Dungeon Cell --
Manager:CreateItem("DUNG_BED", "Bed", "A flat of wood with hay strewn about can hardly be called a bed, but this is all that you have.", true)
AppendItemAlias(DUNG_BED, {"bunk", "cot", "hay"})
Manager:CreateItem("DUNG_BUCKET", "Shit Bucket", "A bucket that you use to defecate into.  You're lucky if the guard changes it out weekly.", false)
AppendItemAlias(DUNG_BUCKET, {"bucket", "pale"})
Manager:CreateItem("CELL_DOOR", "Cell Door", "A wrought iron fence that has degraded slightly due to the moist environment of the dungeon.  "..
								"It looks very heavy and is locked with a fairly primitive locking mechanism.", true)
AppendItemAlias(CELL_DOOR, {"door", "gate"})
Manager:CreateItem("CELL_KEYS", "Keys", "Set of bronze keys that look like they could unlock a certain cell door.", false)
Manager:CreateItem("CELL_BRICK", "False Brick", "A peculiar looking brick that seems to be offset from the rest.  Perhaps I should press it?", true)
AppendItemAlias(CELL_BRICK, {"brick", "stone", "slab"})
Manager:CreateItem("DEBUG_001", "Debug Item", "An item for debugging purposes.")
AppendItemAlias(DEBUG_001, {"debug"})

-- Sewer --
Manager:CreateItem("SEWER_ROCK_SLIDE", "Rock Slide", "A pile of rocks seems to have slipped over a former passageway.  I wonder what lies on the otherside?", true)
AppendItemAlias(SEWER_ROCK_SLIDE, {"rockslide", "rocks", "rubble", "debris"})
Manager:CreateItem("SEWER_GRATE_BOTTOM", "Sewer Grate", "A loose sewer grate that seems to lead to the city streets above.", true)
AppendItemAlias(SEWER_GRATE_BOTTOM, {"grate"})
Manager:CreateItem("SEWER_CHEST", "Chest", "An old, beaten up chest that seems to not have been opened in awhile.", true)

-- City --
Manager:CreateItem("SEWER_GRATE_TOP", "Sewer Grate", "The sewer grate that leads down into the sewer.", true)
AppendItemAlias(SEWER_GRATE_BOTTOM, {"grate"})
Manager:CreateItem("CITY_GARDEN_TREE", "Old Tree", "A large oak tree sits majestically at the center of the city's garden.  Its roots dig deep and its branches reach far.  A knot in the tree seems to hide a nook.  What could it be hinding?", true)
AppendItemAlias(SEWER_GRATE_BOTTOM, {"tree"})
Manager:CreateItem("CITY_FOUNTAIN", "Water Fountain", "A large, overpowering water fountain resides in the center of the merchant district.  "..
									"It has large oppulent statues depicting a local legend and one of their many adventures.  "..
									"Shiny coins can be seen at the bottom where locals throw in copper pieces hoping for their wishes to come true.", true)
AppendItemAlias(SEWER_GRATE_BOTTOM, {"fountain"})
Manager:CreateItem("DISGUISE", "Disguise", "A set of clothing designed to conceal your identity discreetly.", false)

DUNG_CELL:AddItem("DUNG_BED")
DUNG_CELL:AddItem("DUNG_BUCKET")
DUNG_CELL:AddItem("CELL_DOOR")
DUNG_CELL:AddItem("CELL_BRICK")
DUNG_CELL:AddItem("DEBUG_001")
DUNG_HALLWAY:AddItem("CELL_DOOR")
SEWER_SE:AddItem("SEWER_ROCK_SLIDE")
SEWER_NE:AddItem("SEWER_GRATE_BOTTOM")
SEWER_HIDEOUT:AddItem("SEWER_CHEST")
CITY_STREET:AddItem("SEWER_GRATE_TOP")
CITY_GARDEN:AddItem("CITY_GARDEN_TREE")
CITY_MERCHANT:AddItem("CITY_FOUNTAIN")
CITY_CLOTHING:AddItem("DISGUISE")

require("scripts.room_scripts")
require("scripts.item_scripts")