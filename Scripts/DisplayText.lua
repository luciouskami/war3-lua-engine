local CurrentState = 0
local PreviousState = 0
local hPlayer = nil
local CGameObject = CGame()
local CJassObject = CJass()

CJassObject:Initialize()

while true do
	CurrentState = CGameObject:GetGameState()
	
	if CurrentState == GS.INGAME then -- We Are In Game --
		Sleep(1000)
		hPlayer = CJassObject:GetLocalPlayer()
		CJassObject:DisplayTimedTextToPlayer(hPlayer, 0, 0, 10, "We are sending this text with |CFF8989DEWarcraft Lua Engine|R")
		break
	end

	Sleep(100)
end