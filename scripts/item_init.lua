-- Dungeon Cell --
Manager:CreateStaticItem("CELL_BED", "Bed")
CELL_BED:SetDescription("A flat of wood with hay strewn about can hardly be called a bed, but this is all that you have.")
CELL_BED:SetRoomDescription("A small cot lies in the corner of the room, covered in a thin fabric for a blanket and some hay for cushioning.")
AppendItemAlias(CELL_BED, {"BUNK", "COT", "HAY"})
CELL_BED_SCRIPTS = {
	OnInteract = function(action)
		if action == "SLEEP" then
			Manager:Print("You sleep for a bit on the uncomfortable cot.")
			Manager:ProgressTime(8, "H")
		elseif action == "SEARCH" then
			Manager:Print("Digging through the thin fabric, you find a single lockpick!  Perhaps you could pick the cell door?")
			Manager:PlayerAddItems("LOCKPICK", 1)
		end
	end
}

Manager:CreateItem("CELL_BUCKET", "Poo Pale")
CELL_BUCKET:SetDescription("A bucket that prisoners defecate into.  You'll be lucky if the guard changes it out weekly.")
CELL_BUCKET:SetRoomDescription("A nasty looking, wooden bucket resides on the floor.  A horrendous stench wafts towards you that reminds you of excrement.")
AppendItemAlias(CELL_BUCKET, {"bucket", "pale"})
CELL_BUCKET_SCRIPTS = {
	OnInteract = function(action)
		if Contains({"SNIFF", "SMELL"}, action) then
			Manager:Print("It does not smell pleasant.  What do you expect?")
		elseif Contains({"USE", "POOP", "SHIT", "PISS", "PEE", "DEFECATE", "RELIEVE"}, action) then
			Manager:Print("You relieve yourself into the pale.")
		end
	end,
	OnPickup = function()
		Manager:Print("You pickup the shit bucket... for some reason.")
	end
}

Manager:CreateStaticItem("CELL_DOOR", "Cell Door")
CELL_DOOR:SetDescription("A wrought iron fence that has degraded slightly due to the moist environment of the dungeon.  It looks very heavy and is locked with a fairly primitive locking mechanism.")
CELL_DOOR:SetRoomDescription("A single, heavy iron door blocks your way to freedom.")

AppendItemAlias(CELL_DOOR, {"door", "gate"})
CELL_DOOR_SCRIPTS = {
	OnInteract = function(action)
		if Contains({"PUSH", "PULL", "OPEN"}, action) then
			Manager:Print("You attempt to open the gate.  It is obviously locked and does not budge.")
		elseif Contains({"PICK", "UNLOCK"}, action) then 
			if Manager:PlayerHasItem("CELL_KEYS") then
				DUNG_CELL:ConnectRooms("DUNG_HALLWAY", "North")
				Manager:Print("You unlocked the cell door with the keys!")
			elseif Manager:PlayerHasItem("LOCKPICK") then
				Manager:Print("You attempt to pick the lock when no one is looking...")
				Manager:Print("You saddly break the pick in the process.")
				Manager:PlayerRemoveItems("LOCKPICK", 1)
			end
		end
	end
}

Manager:CreateItem("CELL_KEYS", "Keys")
CELL_KEYS:SetDescription("Set of bronze keys that look like they could unlock a certain cell door.")

Manager:CreateStaticItem("CELL_BRICK", "False Brick")
CELL_BRICK:SetDescription("There seems to be a single brick offset from the rest.  Perhaps I should press it?")

AppendItemAlias(CELL_BRICK, {"brick", "stone", "slab", "wall"})
CELL_BRICK_SCRIPTS = {
	OnInteract = function(action)
		if Contains({"PRESS", "PUSH"}, action) then
			-- TODO: Have the player examine the wall first, otherwise they just press against the wall doing nothing.
			Manager:Print("You press the brick, pushing it into the wall.  A small doorway opens up hidden away revealing a secret passage!")
			DUNG_CELL:ConnectRooms("DUNG_SECRET_PASSAGE", "East")
			DUNG_CELL:AppendDescription("A secret passage way out of sight of the guards leads into darkness.")
			DUNG_CELL:RemoveItem("CELL_BRICK") -- TODO: Replace this with item states
		end
	end
}

-- Sewer Items --
Manager:CreateStaticItem("SEWER_ROCK_SLIDE", "Rock Slide")
SEWER_ROCK_SLIDE:SetDescription("A pile of rocks seems to have slipped over a former passageway.  I wonder what lies on the otherside?")
AppendItemAlias(SEWER_ROCK_SLIDE, {"rockslide", "rocks", "rubble", "debris"})
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

Manager:CreateStaticItem("SEWER_GRATE_BOTTOM", "Sewer Grate")
SEWER_GRATE_BOTTOM:SetDescription("A loose sewer grate that seems to lead to the city streets above.")
AppendItemAlias(SEWER_GRATE_BOTTOM, {"grate"})
SEWER_GRATE_BOTTOM_SCRIPTS = {
	OnInteract = function(action)
		if Contains({"OPEN", "ENTER"}, action) then 
			Manager:Print("You wait until there is no one around and slip through the grate to the city above.")
			Manager:SetCurrentRoom("CITY_STREET")
		end
	end
}

Manager:CreateStaticItem("SEWER_GRATE_TOP", "Sewer Grate")
SEWER_GRATE_TOP:SetDescription("The sewer grate that leads down into the sewer.")
AppendItemAlias(SEWER_GRATE_TOP, {"grate"})
SEWER_GRATE_TOP_SCRIPTS = {
	OnInteract = function(action)
		if Contains({"OPEN", "ENTER"}, action) then 
			Manager:Print("You wait until there is no one around and slip through the grate to the sewers beneath.")
			Manager:SetCurrentRoom("SEWER_NE")
		end
	end
}

Manager:CreateStaticItem("SEWER_CHEST", "Chest")
SEWER_CHEST:SetDescription("An old, beaten up chest that seems to not have been opened in awhile.")
SEWER_CHEST_SCRIPTS = {
	OnInteract = function(action)
		if action == "OPEN" then
			Manager:Print("The chest is locked tight and you cannot open it.")
		elseif Contains({"PICK", "UNLOCK"}, action) then 
			if Manager:PlayerHasItem("LOCKPICK") then
				Manager:Print("You attempt to pick the lock when no one is looking...")
				Manager:Print("You unlock the chest and find 15 gold!")
				Manager:PlayerAddItems("GOLD", 15) -- TODO: Replace with item inventories/states
			end
		end
	end
}

-- City Items --
Manager:CreateStaticItem("CITY_GARDEN_TREE", "Old Tree")
CITY_GARDEN_TREE:SetDescription("A large oak tree sits majestically at the center of the city's garden.  Its roots dig deep and its branches reach far.  A knot in the tree seems to hide a nook.  What could it be hinding?")
AppendItemAlias(CITY_GARDEN_TREE, {"tree"})
CITY_GARDEN_TREE_SCRIPTS = {
	OnInteract = function(action)
		if action == "SEARCH" then
			Manager:Print("You find a small satchel of containing 15 gold pieces!")
			Manager:PlayerAddItems("GOLD", 15)
		end
	end
}

Manager:CreateStaticItem("CITY_FOUNTAIN", "Water Fountain")
CITY_FOUNTAIN:SetDescription("A large, overpowering water fountain resides in the center of the merchant district.  It has large oppulent statues depicting a local legend and one of their many adventures.  Shiny coins can be seen at the bottom where locals throw in copper pieces hoping for their wishes to come true.")
AppendItemAlias(CITY_FOUNTAIN, {"fountain"})
CITY_FOUNTAIN_SCRIPTS = {
	OnInteract = function(action)
		if action == "SEARCH" then
			Manager:Print("You dip your hand into the fountain and pull out some gold coins.")
			Manager:PlayerAddItems("GOLD", 3)
		end
	end
}

Manager:CreateItem("GOLD", "Gold Coin")
GOLD:SetDescription("A small golden coin with the likeness of some King on it.")
Manager:CreateItem("LOCKPICK", "Lockpick")
LOCKPICK:SetDescription("A small device used to pick locks.")
Manager:CreateItem("DISGUISE", "Disguise")
DISGUISE:SetDescription("A set of clothing designed to conceal your identity discreetly.")