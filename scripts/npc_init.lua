Manager:CreateNPC("DEBUG_SANTA", "Santa Claus")
AppendNPCAlias(DEBUG_SANTA, {"SANTA", "CLAUS", "JOLLY MAN", "JOLLY LOOKING MAN"})

DEBUG_SANTA:SetDescription("He appears to be a jolly looking man in a bright red coat, currently carrying large canvas sack full of rectangular objects.  Perhaps this is the legendary Santa Claus???")
DEBUG_SANTA:SetRoomDescription("A jolly looking man stands near the corner.")

--DEBUG_SANTA:CreateDialogState("INTRO")
--DEBUG_SANTA:SetDialogString("INTRO", "Hello there!  How may I help you?")
--DEBUG_SANTA:AddDialogOption("INTRO", "You can bugger off old man.")
--DEBUG_SANTA:AddDialogOption("INTRO", "Can you give me some presents?")
--DEBUG_SANTA:AddDialogOption("INTRO", "Goodbye!")

--DEBUG_SANTA:CreateDialogState("GIFT_GIVEN")
--DEBUG_SANTA:CreateDialogString("GIFT_GIVEN", "Scram kid, you already got your present.")

--DEBUG_SANTA:SetDialogState("INTRO")


DEBUG_SANTA:SetDialogTable("DEBUG_SANTA_DIALOG")
DEBUG_SANTA:CreateDialogState("INTRO")
DEBUG_SANTA:SetDialogString("INTRO", "Hello there!  How may I help you?")
DEBUG_SANTA:AddDialogOption("INTRO", "You can bugger off old man!")
DEBUG_SANTA:AddDialogOption("INTRO", "Can you give me some presents?")
DEBUG_SANTA:AddDialogOption("INTRO", "Goodbye.")

DEBUG_SANTA:CreateDialogState("GIFT_GIVEN")
DEBUG_SANTA:SetDialogString("Scram kid, you already got your present.")
DEBUG_SANTA:AddDialogOption("GIFT_GIVEN", "Goodbye.")

DEBUG_SANTA_DIALOG = {
	OnTalk = function() 
		Manager:ShowDialog("DEBUG_SANTA", "INTRO")
	end
	OnReply = function(reply)
		if DEBUG_SANTA:GetDialogState() == "INTRO" then
			if reply 
			DEBUG_SANTA:SetDialogState("GIFT_GIVEN")
		elseif DEBUG_SANTA:GetDialogState() == "GIFT_GIVEN" then
		
		elseif 
	end
}