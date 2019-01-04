-- Shared Functions --
function imprison_player()
	Manager:Print("The guards notice you and aprehend you before you could escape!  They drag you back to your cell.")
	Manager:SetCurrentRoom("DUNG_CELL")
end

-- Dungeon Cell --
Manager:CreateRoom("DUNG_CELL", "Dungeon Cell")
DUNG_CELL:SetDescription("A damp dungeon cell surrounds you.  Most of the cell seems to be carved out of the mountain side, with the eastern wall being comprised of brick.  Due to the lack of illumination, it's hard to make out any details on anything.")

DUNG_CELL:AddItem("CELL_BRICK")
DUNG_CELL:AddItem("CELL_DOOR")
DUNG_CELL:AddItem("CELL_BED")
DUNG_CELL:AddItem("CELL_BUCKET")
DUNG_CELL:AddItem("DEBUG_ITEM_001")

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