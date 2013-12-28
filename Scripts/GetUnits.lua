local CGameObject = CGame()

function Check()
	local hUnits = CGameObject:GetDotaUnits()

	for _,creep in ipairs(hUnits) do
		-- Do anything you want with "creep"
	end

end

while true do
	local GameState = CGameObject:GetGameState()
	
	if GameState == GS.INGAME then
		Check()
	end
	
	Sleep(100)
end