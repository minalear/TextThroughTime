-- To add rooms use Manager::AddRoom("UNIQUE_ID", "Room Name", "Room description")
-- Adding a room makes a global variable under UNIQUE_ID
-- To attach rooms to other rooms use BASE_ID:AttachRoom("OTHER_ROOM_ID", "Direction")

Manager:AddRoom("HH_LIVING_ROOM", "Living Room", "")
Manager:AddRoom("HH_KITCHEN", "Kitchen", "")
Manager:AddRoom("HH_PANTRY", "Pantry", "")
Manager:AddRoom("HH_LAWN", "Front Lawn", "")
Manager:AddRoom("SHIRE_LANE", "Wumdledon Lane", "")
Manager:AddRoom("SHIRE_MAIN", "Shire Main Street", "")


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
	"A kitchen")
HH_PANTRY:SetDescription(
	"A pretty small pantry.")
HH_LAWN:SetDescription(
	"Gross as dead lawn.")