-- Arena Combatants --
Manager:CreateNPC("ARENA_FRANK", "Frank Shaw")
AppendNPCAlias(ARENA_FRANK, {"frank"})
ARENA_FRANK:SetDescription("A scrawny looking man from the local town wielding a tall spear like weapon.  His stance is weak, his arms look heavy, and there seems to be spaghetti stains on his shirt.")
ARENA_FRANK:SetRoomDescription("A scrawny looking man stands before you, ready for combat.")

ARENA_FRANK:SetStrength(9)
ARENA_FRANK:SetDexterity(12)
ARENA_FRANK:SetVitality(14)
ARENA_FRANK:SetIntelligence(7)
ARENA_FRANK:SetWisdom(8)
ARENA_FRANK:SetCharisma(11)
ARENA_FRANK:SetLuck(16)
ARENA_FRANK:EquipItem("GAFF")
ARENA_FRANK:EquipItem("COIF")

Manager:CreateNPC("ARENA_MARLIN", "Marlin, the Golem")
AppendNPCAlias(ARENA_MARLIN, {"marlin", "golem"})
ARENA_MARLIN:SetDescription("A huge, bronze golem.")
ARENA_MARLIN:SetRoomDescription("A huge, bronze golem is currently trying to kill you.")

ARENA_MARLIN:SetStrength(28)
ARENA_MARLIN:SetDexterity(12)
ARENA_MARLIN:SetVitality(30)
ARENA_MARLIN:SetIntelligence(24)
ARENA_MARLIN:SetWisdom(19)
ARENA_MARLIN:SetCharisma(8)
ARENA_MARLIN:SetLuck(100)
ARENA_MARLIN:SetMeleeDamage("1d12")

Manager:CreateNPC("ETHAN_FINCH", "Ethan the Finch")
AppendNPCAlias(ETHAN_FINCH, {"ethan", "finch"})
ETHAN_FINCH:SetDescription("A muscle wizard.")
ETHAN_FINCH:SetRoomDescription("A strong looking wizard boy stands at attention.")

ETHAN_FINCH:SetStrength(412)
ETHAN_FINCH:SetDexterity(10)
ETHAN_FINCH:SetVitality(10)
ETHAN_FINCH:SetIntelligence(1000)
ETHAN_FINCH:SetWisdom(9)
ETHAN_FINCH:SetCharisma(10)
ETHAN_FINCH:SetLuck(304)
ETHAN_FINCH:SetMeleeDamage("2d12")

ETHAN_FINCH:EquipItem("FINCH_KNUCKLES")

-- Example --
Manager:CreateNPC("DEBUG_SANTA", "Santa Claus")
AppendNPCAlias(DEBUG_SANTA, {"SANTA", "CLAUS", "JOLLY MAN", "JOLLY LOOKING MAN"})

DEBUG_SANTA:SetDescription("He appears to be a jolly looking man in a bright red coat, currently carrying large canvas sack full of rectangular objects.  Perhaps this is the legendary Santa Claus???")
DEBUG_SANTA:SetRoomDescription("A jolly looking man stands near the corner.")

DEBUG_SANTA:SetDialogScript("DEBUG_SANTA_DIALOG")
DEBUG_SANTA:CreateDialogState("INTRO")
DEBUG_SANTA:SetDialogString("INTRO", "Hello there!  How may I help you?")
DEBUG_SANTA:AddDialogOption("INTRO", "You can bugger off old man!")
DEBUG_SANTA:AddDialogOption("INTRO", "Can you give me some presents?")
DEBUG_SANTA:AddDialogOption("INTRO", "Goodbye.")

DEBUG_SANTA:CreateDialogState("GIFT_GIVEN")
DEBUG_SANTA:SetDialogString("GIFT_GIVEN", "Scram kid, you already got your present.")
DEBUG_SANTA:AddDialogOption("GIFT_GIVEN", "Goodbye.")
DEBUG_SANTA:SetDialogState("INTRO")

DEBUG_SANTA_DIALOG = {
	OnTalk = function() 
		Manager:DisplayDialog("DEBUG_SANTA")
	end,
	OnReply = function(reply)
		current_dialog_state = DEBUG_SANTA:GetDialogState()
		if current_dialog_state == "INTRO" then
			if reply == "1" then
				Manager:NPCSpeak("DEBUG_SANTA", "It seems you have been a naughty boy... a very naughty boy UwU")
				Manager:PlayerAddItem("COAL")
				Manager:Print("You received a piece of coal from Santa Claus.")
				Manager:ExitDialog()
				DEBUG_SANTA:SetDialogState("GIFT_GIVEN")
				return true
			elseif reply == "2" then
				Manager:NPCSpeak("DEBUG_SANTA", "Sure, my friend!  Here you go!")
				Manager:PlayerAddItem("PRESENT")
				Manager:Print("You received a magnificiently wrapped present from Santa Claus!")
				Manager:ExitDialog()
				DEBUG_SANTA:SetDialogState("GIFT_GIVEN")
				return true
			else
				Manager:NPCSpeak("DEBUG_SANTA", "Whatever, kid.")
				Manager:ExitDialog()
				return true
			end
		
		elseif current_dialog_state == "GIFT_GIVEN" then
			Manager:ExitDialog()
			return true
		end
		
		return false
	end
}