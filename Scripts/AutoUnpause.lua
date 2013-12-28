local CurrentState = 0
local CGameObject = CGame()

while true do
	CurrentState = CGameObject:GetGameState()
	
	if CurrentState == GS.PAUSED then -- Someone paused the game --
		Sleep(3000) -- Wait 3 seconds before unpause --
		
		-- Check if it's still paused --
		CurrentState = CGameObject:GetGameState()
		
		if CurrentState == GS.PAUSED then
		CGameObject:ResumeGame()
		end
	end

	Sleep(100)
end
