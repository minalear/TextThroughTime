CELL_DOOR_SCRIPTS = {
	OnInteract = function(action)
		if action == "open" then
			if Manager:PlayerHasItem("CELL_KEYS") then
				DUNG_CELL:AttachRoom("DUNG_HALLWAY", "North")
				DUNG_HALLWAY:AttachRoom("DUNG_CELL", "South")
				Manager:Print("You unlocked the cell door with the keys!")
			else
				Manager:Print("You have no way to unlock the cell door.")
			end
		end
	end
}

CELL_BRICK_SCRIPTS = {
	OnInteract = function(action)
		if action == "press" then 
			Manager:Print("You press the brick, pushing it inwards into the wall.  "..
						  "A small doorway opens up hidden away revealing a secret passage!")
			DUNG_CELL:AttachRoom("DUNG_SECRET_PASSAGE", "East")
			DUNG_SECRET_PASSAGE:AttachRoom("DUNG_CELL", "West")
		end
	end
}