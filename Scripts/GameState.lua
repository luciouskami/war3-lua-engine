local CurrentState = 0
local PreviousState = 0
local StateName = nil
local CGameObject = CGame()


while true do
	CurrentState = CGameObject:GetGameState()
	
	if		CurrentState == GS.NOTHING	then StateName = "GS_NOTHING"
	elseif	CurrentState == GS.LOBBY	then StateName = "GS_LOBBY"
	elseif	CurrentState == GS.LOADING	then StateName = "GS_LOADING"
	elseif	CurrentState == GS.INGAME	then StateName = "GS_INGAME"
	elseif	CurrentState == GS.PAUSED	then StateName = "GS_PAUSED"
	end
	
	if CurrentState ~= PreviousState then -- State Changed --
		ShowMessage("Game state has been changed to " .. StateName)
	end
	
	PreviousState = CurrentState
	Sleep(100)
end