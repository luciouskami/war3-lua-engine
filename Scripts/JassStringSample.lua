local CJassObject = CJass()
local CGameObject = CGame()
local GameState = nil

CJassObject:Initialize()

while true do
	GameState = CGameObject:GetGameState()

	if GameState == GS.INGAME then
		local hPlayer = CJassObject:GetLocalPlayer()
		local sPlayerName = CJassObject:GetPlayerName(hPlayer)
		CJassObject:DisplayTimedTextToPlayer(hPlayer, 0, 0, 10, "Local player name is " .. sPlayerName)
		break
	end
	
	Sleep(100)
end