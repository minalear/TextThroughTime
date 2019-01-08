Manager:CreateItem("SWORD", "Longsword")
AppendItemAlias(SWORD, {"sword"})
SWORD:SetDescription("A well worn, but reliable, iron longsword.")

Manager:CreateStaticContainer("ARENA_ARMORY", "Armory")
AppendItemAlias(ARENA_ARMORY, {"cabinet", "wardrobe"})
ARENA_ARMORY:SetDescription("A tall, mahogany cabinet used to house equipment used by the gladiators.  It is currently locked.")
ARENA_ARMORY:SetRoomDescription("A tall cabinet sits in the far corner, surounded by various gladiators.")

ARENA_ARMORY:AddItem("SWORD")

-- Lock the armory
ARENA_ARMORY:AddProperty("LOCKED")

-- Armory scripts
ARENA_ARMORY_SCRIPTS = {
	OnInteract = function(action)
		if action == "UNLOCK" then
			ARENA_ARMORY:RemoveProperty("LOCKED")
			Manager:Print("You unlock the armory.")
			ARENA_ARMORY:SetDescription("A tall, mahogany cabinet used to house equipment used by the gladiators.  It is currently unlocked.")
		elseif action == "LOCK" then
			ARENA_ARMORY:AddProperty("LOCKED")
			Manager:Print("You lock the armory.")
			ARENA_ARMORY:SetDescription("A tall, mahogany cabinet used to house equipment used by the gladiators.  It is currently locked.")
		end
	end
}