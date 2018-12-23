CELL_DOOR_SCRIPTS = {
	OnInteract = function(action)
		if action == "open" then
			if Manager:PlayerHasItem("CELL_KEYS") then
				DUNG_CELL:AttachRoom("DUNG_HALLWAY", "North")
				DUNG_HALLWAY:AttachRoom("DUNG_CELL", "South")
				Manager:Print("You unlocked the cell door!")
			else
				Manager:Print("You have no way to unlock the cell door.")
			end
		end
	end
}