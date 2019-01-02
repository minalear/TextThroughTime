-- Shared Functions --
function imprison_player()
	Manager:Print("The guards notice you and aprehend you before you could escape!  They drag you back to your cell.")
	Manager:SetCurrentRoom("DUNG_CELL")
end

-- Dungeon Cell --
Manager:CreateRoom("DUNG_CELL", "Dungeon Cell")
DUNG_CELL:SetDescription("A cramped, damp dungeon cell surrounds you.  The cell seems to be carved out of natural stone, however a seemingly out of place brick wall makes up the right hand side of the cell.  A small bed sits in the corner while a smelly shit bucket resides next to it.  It is very dark in the cell, with whatever light present illuminating from the distant hallway through the cell door.  Trying to make out details is impossible, however, on the brick wall, there seems to be a single brick standing out from the rest.")
DUNG_CELL:AddItem("CELL_BED")
DUNG_CELL:AddItem("CELL_BUCKET")
DUNG_CELL:AddItem("CELL_DOOR")
DUNG_CELL:AddItem("CELL_BRICK")

-- Dungeon Hallway --
Manager:CreateRoom("DUNG_HALLWAY", "Dungeon Hallway")
DUNG_HALLWAY:SetDescription("The hallway leads down towards a number of cells, all currently vacant.  The door that attracts your attention the most is the solid iron door of your cell.  Nothing much else catches your attention.")
DUNG_HALLWAY:AddItem("CELL_DOOR")


Manager:CreateRoom("DUNG_ENTRANCE", "Dungeon Entrance")
Manager:CreateRoom("DUNG_SECRET_PASSAGE", "Secret Passage")


Manager:CreateRoom("CASTLE", "Castle Courtyard")
CASTLE_SCRIPTS = {
	OnEnter = function() 
		if not Manager:PlayerHasItem("DISGUISE") then
			imprison_player()
		end
	end
}


-- Sewer Rooms --
Manager:CreateRoom("SEWER_SE", "South-East Sewer")
SEWER_SE:AddItem("SEWER_ROCK_SLIDE")


Manager:CreateRoom("SEWER_NE", "North-East Sewer")
SEWER_NE:AddItem("SEWER_GRATE_BOTTOM")


Manager:CreateRoom("SEWER_SW", "South-West Sewer")
Manager:CreateRoom("SEWER_NW", "North-West Sewer")


Manager:CreateRoom("SEWER_HIDEOUT", "Secret Hideout")
SEWER_HIDEOUT:AddItem("SEWER_CHEST")


-- City Rooms --
Manager:CreateRoom("CITY_STREET", "Main Avenue")
CITY_STREET:AddItem("SEWER_GRATE_TOP")


Manager:CreateRoom("CITY_MERCHANT", "Merchant Quarter")
CITY_MERCHANT:AddItem("CITY_FOUNTAIN")


Manager:CreateRoom("CITY_GARDEN", "Memorial Garden")
CITY_GARDEN:AddItem("CITY_GARDEN_TREE")


Manager:CreateRoom("CITY_CLOTHING", "Clothing Shoppe")
CITY_CLOTHING:AddItem("DISGUISE")


Manager:CreateRoom("CITY_GATE", "Main Gate")
CITY_GATE_SCRIPTS = {
	OnEnter = function() 
		if not Manager:PlayerHasItem("DISGUISE") then
			imprison_player()
		end
	end
}

Manager:CreateRoom("CITY_STREET_NORTH", "North Main Avenue")
Manager:CreateRoom("VICTORY", "Outside")

-- Room Connections --
DUNG_HALLWAY:ConnectRooms("DUNG_ENTRANCE", "North")
DUNG_ENTRANCE:ConnectRooms("CASTLE", "East")
CASTLE:ConnectRooms("CITY_MERCHANT", "East")
CITY_MERCHANT:ConnectRooms("CITY_CLOTHING", "North")
CITY_MERCHANT:ConnectRooms("CITY_STREET", "East")
CITY_STREET:ConnectRooms("CITY_STREET_NORTH", "North")
CITY_STREET:ConnectRooms("CITY_GARDEN", "East")
CITY_STREET_NORTH:ConnectRooms("CITY_GATE", "North")
CITY_GATE:ConnectRooms("VICTORY", "North")
DUNG_SECRET_PASSAGE:ConnectRooms("SEWER_SW", "East")
SEWER_SW:ConnectRooms("SEWER_NW", "North")
SEWER_NW:ConnectRooms("SEWER_NE", "East")
SEWER_NE:ConnectRooms("SEWER_SE", "South")