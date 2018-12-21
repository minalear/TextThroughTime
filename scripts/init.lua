-- To add rooms use Manager::AddRoom("UNIQUE_ID", "Room Name", "Room description")
-- Adding a room makes a global variable under UNIQUE_ID
-- To attach rooms to other rooms use BASE_ID:AttachRoom("OTHER_ROOM_ID", "Direction")

Manager:AddRoom("HH_LIVING_ROOM", "Living Room", "")
Manager:AddRoom("HH_KITCHEN", "Kitchen", "")
Manager:AddRoom("HH_PANTRY", "Pantry", "")
Manager:AddRoom("HH_LAWN", "Front Lawn", "")
Manager:AddRoom("SHIRE_LANE", "Wumdledon Lane", "")
Manager:AddRoom("SHIRE_MAIN", "Shire Main Street", "")
Manager:AddRoom("HH_SECRET_ROOM", "Secret Hobbit Room", "")


HH_LIVING_ROOM:AttachRoom("HH_KITCHEN", "South")
HH_LIVING_ROOM:AttachRoom("HH_LAWN", "North")
HH_KITCHEN:AttachRoom("HH_LIVING_ROOM", "North")
HH_KITCHEN:AttachRoom("HH_PANTRY", "West")
HH_PANTRY:AttachRoom("HH_KITCHEN", "East")
HH_LAWN:AttachRoom("HH_LIVING_ROOM", "South")

Manager:SetCurrentRoom("HH_LIVING_ROOM")

-- Room Descriptions
HH_LIVING_ROOM:SetDescription(
	"A quaint little abode settled partially underground, furnished to the brim with antiques acquired from your family.  "..
	"A small round door leads to your front lawn while an archway leads to your kitchen behind you.  A end table sits next to your leather couch "..
	"which you tend to store important trinkets lies closed as well.")
HH_KITCHEN:SetDescription(
	"A kitchen set against the back of the house with your basic array of cooking appliances; a stove, sink, and various storage bins.  "..
	"A door leading to your expansive pantry is also located to the side here.")
HH_PANTRY:SetDescription(
	"A very spacious pantry cut into the heart of the hill, making it much cooler than the other rooms in the house, allowing  "..
	"for storage of food.")
HH_LAWN:SetDescription(
	"Your spacious lawn sprawls out in front of you, with your garden stretching out to your right.  The surrounding hills are very green for this "..
	"time of year.  Various noises can be heard from down the lane, nothing too out of the ordinary.")
HH_SECRET_ROOM:SetDescription(
	"A secret room with secret stuff.")
	
-- Items for the Hobbit Hole
Manager:CreateItem("SMOKE_PIPE", "Pipe", "A luxuriously crafted wooden pipe, carved with various designs from the Ancient Kingdom.  It is loaded with some Deborah's famous Kush.")
Manager:CreateItem("CHEESE_WHEEL", "Cheese Wheel", "A very rotund piece of cheddar cheese.")
Manager:CreateItem("JOURNAL", "Journal", "Your personal journal where you keep notes about that one book you're writing about the Dark Lord and stuff.")
Manager:CreateItem("THE_RING", "Ring", "A small golden ring.")
Manager:CreateItem("THE_LIAR", "Khajiit Statue", "A strange looking statue of a Khajiit.  Inscribed on the bottom is the name \"M'aiq the Liar.\"")

HH_LIVING_ROOM:AddItem("JOURNAL")
HH_LIVING_ROOM:AddItem("THE_RING")
HH_KITCHEN:AddItem("SMOKE_PIPE")
HH_PANTRY:AddItem("CHEESE_WHEEL")

-- Room Functions
HH_PANTRY_FUNCTIONS = {
	OnItemDrop = function (item)
		if item:GetName() == "Journal" then
			HH_PANTRY:AppendDescription("The journal has manifested itself into a doorway into another dimension.")
			HH_PANTRY:RemoveItem("JOURNAL")
			HH_PANTRY:AttachRoom("HH_SECRET_ROOM", "West")
			HH_SECRET_ROOM:AttachRoom("HH_PANTRY", "East")
		end
	end
}