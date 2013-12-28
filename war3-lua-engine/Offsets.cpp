#include "stdafx.h"
#include "Offsets.h"

DWORD GameBase = 0;

DWORD GetGameBase()
{
	if (!GameBase)
		return (GameBase = (DWORD)GetModuleHandle("Game.dll"));
	return GameBase;
}
