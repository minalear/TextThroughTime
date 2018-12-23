--[[ROOM_ID_SCRIPTS = {
	OnEnter = function() end,
	OnExit = function() return true end,
	OnItemPickup = function(item) end,
	OnItemDrop = function(item) end,
	OnLook = function(item) end
}]]--

-- Room Scripts

function imprison_player()
	Manager:SetCurrentRoom("DUNG_CELL")
end

CITY_GATE_SCRIPTS = {
	OnEnter = function() 
		if not Manager:PlayerHasItem("DISGUISE") then
			imprison_player()
		end
	end,
	OnExit = function() return true end,
	OnItemPickup = function(item) end,
	OnItemDrop = function(item) end,
	OnLook = function(item) end
}
CASTLE_SCRIPTS = {
	OnEnter = function() 
		if not Manager:PlayerHasItem("DISGUISE") then
			imprison_player()
		end
	end,
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