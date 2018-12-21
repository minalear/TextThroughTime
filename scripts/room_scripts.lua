--[[ITEM_ID_SCRIPTS = {
	OnEnter = function() end,
	OnExit = function() return true end,
	OnItemPickup = function(item) end,
	OnItemDrop = function(item) end,
	OnLook = function(item) end
}]]--

-- Room Scripts
HH_LIVING_ROOM_SCRIPTS = {
	OnEnter = function() end,
	OnExit = function() return true end,
	OnItemPickup = function(item) end,
	OnItemDrop = function(item) end,
	OnLook = function(item) end
}

HH_KITCHEN_SCRIPTS = {
	OnEnter = function() end,
	OnExit = function() return true end,
	OnItemPickup = function(item) end,
	OnItemDrop = function(item) end,
	OnLook = function(item) end
}

HH_PANTRY_SCRIPTS = {
	OnEnter = function() end,
	OnExit = function() return true end,
	OnItemPickup = function(item) end,
	OnItemDrop = function(item) 
		if item:GetID() == "THE_RING" then
			-- Display a message to the player about the ring opening up a portal
			HH_PANTRY:AppendDescription("A portal to a secret room is open on the opposite side of the room")
			HH_PANTRY:RemoveItem("THE_RING")
			HH_PANTRY:AttachRoom("HH_SECRET_ROOM", "West")
			HH_SECRET_ROOM:AttachRoom("HH_PANTRY", "East")
		end
	end,
	OnLook = function(item) end
}

HH_LAWN_SCRIPTS = {
	OnEnter = function() end,
	OnExit = function() return true end,
	OnItemPickup = function(item) end,
	OnItemDrop = function(item) end,
	OnLook = function(item) end
}

HH_SECRET_ROOM_SCRIPTS = {
	OnEnter = function() end,
	OnExit = function() 
		return Manager:PlayerHasItem("THE_LIAR")
	end,
	OnItemPickup = function(item) end,
	OnItemDrop = function(item) end,
	OnLook = function(item) end
}