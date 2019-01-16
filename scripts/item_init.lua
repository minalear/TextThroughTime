Manager:CreateEquipment("SWORD", "Longsword", "MAIN_HAND")
AppendItemAlias(SWORD, {"sword"})
SWORD:SetDescription("A well worn, but reliable, iron longsword.")
SWORD:SetDamage("1d8")

Manager:CreateEquipment("MAGIC_SWORD", "Magic Longsword+1", "MAIN_HAND")
AppendItemAlias(MAGIC_SWORD, {"sword", "magic sword"})
MAGIC_SWORD:SetDescription("An enchanted iron longsword.")
MAGIC_SWORD:SetDamage("1d8+1")
MAGIC_SWORD:SetAttackBonus(1)

Manager:CreateEquipment("GAFF", "Boarding Gaff", "MAIN_HAND")
AppendItemAlias(GAFF, {"gaff"})
GAFF:SetDescription("A long wooden pole with a metal hook at the end designed for dock work.")
GAFF:SetDamage("1d6")

Manager:CreateEquipment("COIF", "Leather Coif", "HEAD")
AppendItemAlias(COIF, {"coif"})
COIF:SetDescription("A small leather cap that wraps around the head to give moderate protection.")
COIF:SetACBonus(1)

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