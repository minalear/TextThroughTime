DEBUG_001_SCRIPTS = {
	OnPickup = function()
		Manager:CreatePrompt("What is your favorite color?", "DEBUG_001_SCRIPTS", "PickupPromptCallback")
		AppendPromptResponses({"Red", "Blue", "Purple", "Green"})
		Manager:DisplayPrompt()
	end,
	OnDrop = function() end,
	PickupPromptCallback = function(reply)
		if (Contains({"1", "2", "3", "4"}, reply)) then
			return true
		else
			Manager:CreatePrompt("How dare you pick such a foul color!  Have at you!!", "DEBUG_001_SCRIPTS", "FailedPromptCallback")
			AppendPromptResponses({"Sorry for picking such a foul color", "Fuck you, bitch"})
			--Manager:DisplayPrompt()
			return false
		end
	end,
	FailedPromptCallback = function(reply)
		if reply == "1" then
			Manager:Print("Sensible decision.  Off you go!")
			return true
		elseif reply == "2" then 
			Manager:Print("Buffer off you!")
			return true
		else
			return false
		end
	end
}

CELL_DOOR_SCRIPTS = {
	OnInteract = function(action)
		if action == "OPEN" then
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
		if Contains({"PRESS", "PUSH"}, action) then
			Manager:Print("You press the brick, pushing it inwards into the wall.  "..
						  "A small doorway opens up hidden away revealing a secret passage!")
			DUNG_CELL:ConnectRooms("DUNG_SECRET_PASSAGE", "East")
			DUNG_CELL:AppendDescription("A secret passage way out of sight of the guards leads into darkness.")
			DUNG_CELL:RemoveItem("CELL_BRICK")
		end
	end
}

SEWER_ROCK_SLIDE_SCRIPTS = {
	OnInteract = function(action)
		if Contains({"CLEAR", "CLEAN", "REMOVE"}, action) then 
			Manager:Print("After an extended period of effort, you manage to clear a passage through the rocks.")
			SEWER_SE:ConnectRooms("SEWER_HIDEOUT", "South")
			SEWER_ROCK_SLIDE:SetDescription("A pile of rocks with a passageway cleared through it.")
			SEWER_SE:RemoveItem("SEWER_ROCK_SLIDE")
		end
	end
}

SEWER_GRATE_BOTTOM_SCRIPTS = {
	OnInteract = function(action)
		if Contains({"OPEN", "ENTER"}, action) then 
			Manager:Print("You wait until there is no one around and slip through the grate to the city above.")
			Manager:SetCurrentRoom("CITY_STREET")
		end
	end
}

SEWER_GRATE_TOP_SCRIPTS = {
	OnInteract = function(action)
		if Contains({"OPEN", "ENTER"}, action) then 
			Manager:Print("You wait until there is no one around and slip through the grate to the sewers beneath.")
			Manager:SetCurrentRoom("SEWER_NE")
		end
	end
}

SEWER_CHEST_SCRIPTS = {
	OnInteract = function(action)
		if action == "OPEN" then
			Manager:Print("The chest is locked tight and you cannot open it.")
		end
	end
}

CITY_GARDEN_TREE_SCRIPTS = {
	OnInteract = function(action)
		if action == "SEARCH" then
			Manager:Print("You find a small satchel of gold pieces (not yet implemented.")
		end
	end
}