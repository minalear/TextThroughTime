Manager:CreateEquipment("OFFICER_HEAD", "Officer Helmet", "HEAD")
AppendItemAlias(OFFICER_HEAD, {"helmet"})
OFFICER_HEAD:SetACBonus(1)

Manager:CreateEquipment("OFFICER_GEAR", "Officer Armor", "ARMOR")
AppendItemAlias(OFFICER_GEAR, {"armor"})
OFFICER_GEAR:SetACBonus(1)
OFFICER_GEAR:SetVitalityBonus(2)

Manager:CreateEquipment("OFFICER_CLOAK", "Insignia Cloak", "CLOAK")
AppendItemAlias(OFFICER_CLOAK, {"cloak"})
OFFICER_GEAR:SetDexterityBonus(1)

Manager:CreateEquipment("HP_REGEN_NECK", "Necklace of Regeneration", "NECK")
AppendItemAlias(HP_REGEN_NECK, {"necklace", "neck", "regen neck"})
HP_REGEN_NECK_SCRIPTS = {
	OnCombatRound = function(entity) {
		entity:Heal(1)
	}
}

Manager:CreateEquipment("STONESKIN_RING", "Ring of Stoneskin", "RING")
AppendItemAlias(STONESKIN_RING, {"ring", "stoneskin"})

Manager:CreateEquipment("STRENGTH_RING", "Ring of Brute Strength", "RING")
AppendItemAlias(STRENGTH_RING, {"ring", "strength"})

Manager:CreateEquipment("SPEED_TRINKET", "Trinket of Swiftness", "TRINKET")
AppendItemAlias(SPEED_TRINKET, {"swiftness", "trinket"})

Manager:CreateEquipment("WRATH_SWORD", "Sword of Wrath", "MAIN_HAND")
AppendItemAlias(WRATH_SWORD, {"sword", "wrath sword"})

Manager:CreateEquipment("OFFICER_BUCKLER", "Buckler of Justice", "OFF_HAND")
AppendItemAlias(OFFICER_BUCKLER, {"buckler", "shield"})

Manager:CreateEquipment("OFFICER_DEFENDER", "Defender of Justice", "OFF_HAND")
AppendItemAlias(OFFICER_DEFENDER, {"defender"})

Manager:CreateEquipment("FINCH_KNUCKLES", "Knuckle Dusters of Finch", "MAIN_HAND")
AppendItemAlias(FINCH_KNUCKLES, {"knuckles", "dusters"})
FINCH_KNUCKLES:SetDescription("The weapons of choice of a muscle wizard.")
FINCH_KNUCKLES:SetDamage("500d1000+2")
FINCH_KNUCKLES:SetAttackBonus(5)

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