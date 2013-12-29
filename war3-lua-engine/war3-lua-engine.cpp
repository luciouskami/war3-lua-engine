// war3-lua-engine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <TlHelp32.h>
#include <vector>
#include "war3_lua_engine.h"
#include "Jass.h"
#include "Game.h"
#include "Offsets.h"
#include "Scripts.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Advapi32.lib")

Unit* GlobalUnits[1000];
int GlobalUnitsCount = 1;
Location GlobalLocations[1000];
int GlobalLocationsCount = 0;

namespace War3LuaEngine
{

CScripts Scripts;

using namespace std;
using namespace luabridge;

// traceback function, adapted from lua.c
// when a runtime error occurs, this will append the call stack to the error message
//
static int traceback (lua_State* L)
{
  // look up Lua's 'debug.traceback' function
  lua_getglobal(L, "debug");
  if (!lua_istable(L, -1))
  {
    lua_pop(L, 1);
    return 1;
  }
  lua_getfield(L, -1, "traceback");
  if (!lua_isfunction(L, -1))
  {
    lua_pop(L, 2);
    return 1;
  }
  lua_pushvalue(L, 1); /* pass error message */
  lua_pushinteger(L, 2); /* skip this function and traceback */
  lua_call(L, 2, 1); /* call debug.traceback */
  return 1;
}

int addTraceback (lua_State* L)
{
  lua_pushcfunction (L, &traceback);
  return luaL_ref (L, LUA_REGISTRYINDEX);
}

//==============================================================================

// add our own functions and classes to a Lua environment

#pragma region JassDefinitions
pGetLocalPlayer				GetLocalPlayer;
pDisplayTimedTextToPlayer	DisplayTimedTextToPlayer;
pChangeLevel				ChangeLevel;
pPingMinimap				PingMinimap;
pPingMinimapEx				PingMinimapEx;
pIsUnitVisible				IsUnitVisible;
pSelectUnit					SelectUnit;
pClearSelection				ClearSelection;
pGetTriggerUnit				GetTriggerUnit;
pGetOwningPlayer			GetOwningPlayer;
pGetPlayerColor				GetPlayerColor;
pDialogCreate				DialogCreate;
pDialogDisplay				DialogDisplay;
pDialogSetMessage			DialogSetMessage;
pDialogAddQuitButton		DialogAddQuitButton;
pDialogAddButton			DialogAddButton;
pClearTextMessages			ClearTextMessages;
pCreateTextTag				CreateTextTag;
pSetTextTagText				SetTextTagText;
pSetTextTagPosUnit			SetTextTagPosUnit;
pSetTextTagColor			SetTextTagColor;
pSetTextTagVelocity			SetTextTagVelocity;
pSetTextTagFadepoint		SetTextTagFadepoint;
pSetTextTagLifespan			SetTextTagLifespan;
pSetTextTagPermanent		SetTextTagPermanent;
pSetTextTagVisibility		SetTextTagVisibility;
pPauseGame					PauseGame;
pGetHeroLevel				GetHeroLevel;
pGetUnitX					GetUnitX;
pGetUnitY					GetUnitY;
pGetPlayerId				GetPlayerId;
pIsUnitAlly					IsUnitAlly;
pIsUnitEnemy				IsUnitEnemy;
pIsPlayerAlly				IsPlayerAlly;
pIsPlayerEnemy				IsPlayerEnemy;
pIsPlayerObserver			IsPlayerObserver;
pPlayer						Player;
pGetPlayerRace				GetPlayerRace;
pDoNotSaveReplay			DoNotSaveReplay;
pGetPlayerState				GetPlayerState;
pGetPlayerScore				GetPlayerScore;
pIsVisibleToPlayer			IsVisibleToPlayer;
pIsFoggedToPlayer			IsFoggedToPlayer;
pIsMaskedToPlayer			IsMaskedToPlayer;
pConvertRace				ConvertRace;
pConvertPlayerState			ConvertPlayerState;
pConvertPlayerScore			ConvertPlayerScore;
pGetPlayerSlotState			GetPlayerSlotState;
pConvertPlayerSlotState		ConvertPlayerSlotState;
pConvertUnitState			ConvertUnitState;
pGetUnitState				GetUnitState;
pGetUnitTypeId				GetUnitTypeId;
pGetPlayerName				GetPlayerName;
pGetUnitName				GetUnitName;
pGetItemName				GetItemName;
pGetItemCharges				GetItemCharges;
#pragma endregion

static void GetJassString(char *szString, CJassString *String)
{
	DWORD Module = (DWORD)GetModuleHandle("Game.dll");
	DWORD Address = Module + 0x011300;

	__asm
	{
		PUSH szString;
		MOV ECX, String;
		CALL Address;
	}

}
static void ShowMessage(const char* Message)
{
	HWND hwnd = FindWindow("Warcraft III", NULL);
	MessageBox(hwnd,Message,"Warcraft Lua Engine",MB_OK|MB_ICONINFORMATION);
}
static void Debug(int Value)
{
	char Output[128];
	sprintf_s(Output, "Return Code : %i", Value);
	MessageBox(NULL,Output,"Debug",MB_OK|MB_ICONINFORMATION);
}
const CHAR* GetStringFromJSID(HJSSTRING JSID)
{
	const CHAR* cRet;

	__asm
	{
		push JSID;
		mov ecx, 1;
		call _GetCurrentJassEnv;
		mov ecx, eax;
		call _JSIDToPointer;
		mov ecx,dword ptr ds:[eax+0x08]; // Pointer to second structure
		mov eax,dword ptr ds:[ecx+0x1C]; // Pointer to string array
		mov cRet, eax;
	}

	return cRet;
}

class CJass{
public:

void Initialize()
{
	GetLocalPlayer 				= (pGetLocalPlayer)					(_GetLocalPlayer);
	DisplayTimedTextToPlayer	= (pDisplayTimedTextToPlayer)		(_DisplayTimedTextToPlayer);
	ChangeLevel					= (pChangeLevel)					(_ChangeLevel);
	PingMinimap					= (pPingMinimap)					(_PingMinimap);
	PingMinimapEx				= (pPingMinimapEx)					(_PingMinimapEx);
	IsUnitVisible 				= (pIsUnitVisible)					(_IsUnitVisible);
	SelectUnit 					= (pSelectUnit)						(_SelectUnit);
	ClearSelection 				= (pClearSelection)					(_ClearSelection);
	GetTriggerUnit				= (pGetTriggerUnit)					(_GetTriggerUnit);
	GetOwningPlayer				= (pGetOwningPlayer)				(_GetOwningPlayer);
	GetPlayerColor				= (pGetPlayerColor)					(_GetPlayerColor);
	CreateTextTag				= (pCreateTextTag)					(_CreateTextTag);
	SetTextTagText				= (pSetTextTagText)					(_SetTextTagText);
	SetTextTagPosUnit			= (pSetTextTagPosUnit)				(_SetTextTagPosUnit);
	SetTextTagColor				= (pSetTextTagColor)				(_SetTextTagColor);
	SetTextTagVelocity			= (pSetTextTagVelocity)				(_SetTextTagVelocity);
	SetTextTagFadepoint			= (pSetTextTagFadepoint)			(_SetTextTagFadepoint);
	SetTextTagLifespan			= (pSetTextTagLifespan)				(_SetTextTagLifespan);
	SetTextTagPermanent			= (pSetTextTagPermanent)			(_SetTextTagPermanent);
	SetTextTagVisibility		= (pSetTextTagVisibility)			(_SetTextTagVisibility);
	DialogCreate				= (pDialogCreate)					(_DialogCreate);
	DialogDisplay				= (pDialogDisplay)					(_DialogDisplay);
	DialogSetMessage			= (pDialogSetMessage)				(_DialogSetMessage);
	DialogAddQuitButton			= (pDialogAddQuitButton)			(_DialogAddQuitButton);
	DialogAddButton				= (pDialogAddButton)				(_DialogAddButton);
	ClearTextMessages			= (pClearTextMessages)				(_ClearTextMessages);
	PauseGame					= (pPauseGame)						(_JPauseGame);
	GetHeroLevel				= (pGetHeroLevel)					(_GetHeroLevel);
	GetUnitX					= (pGetUnitX)						(_GetUnitX);
	GetUnitY					= (pGetUnitY)						(_GetUnitY);
	GetPlayerId					= (pGetPlayerId)					(_GetPlayerId);
	IsUnitAlly					= (pIsUnitAlly)						(_IsUnitAlly);
	IsUnitEnemy					= (pIsUnitEnemy)					(_IsUnitEnemy);
	IsPlayerAlly				= (pIsPlayerAlly)					(_IsPlayerAlly);
	IsPlayerEnemy				= (pIsPlayerEnemy)					(_IsPlayerEnemy);
	IsPlayerObserver			= (pIsPlayerObserver)				(_IsPlayerObserver);
	Player						= (pPlayer)							(_Player);
	GetPlayerRace				= (pGetPlayerRace)					(_GetPlayerRace);
	DoNotSaveReplay				= (pDoNotSaveReplay)				(_DoNotSaveReplay);
	GetPlayerState				= (pGetPlayerState)					(_GetPlayerState);
	GetPlayerScore				= (pGetPlayerScore)					(_GetPlayerScore);
	IsVisibleToPlayer			= (pIsVisibleToPlayer)				(_IsVisibleToPlayer);
	IsFoggedToPlayer			= (pIsFoggedToPlayer)				(_IsFoggedToPlayer);
	IsMaskedToPlayer			= (pIsMaskedToPlayer)				(_IsMaskedToPlayer);
	ConvertRace					= (pConvertRace)					(_ConvertRace);
	ConvertPlayerState			= (pConvertPlayerState)				(_ConvertPlayerState);
	ConvertPlayerScore			= (pConvertPlayerScore)				(_ConvertPlayerScore);
	GetPlayerSlotState			= (pGetPlayerSlotState)				(_GetPlayerSlotState);
	ConvertPlayerSlotState		= (pConvertPlayerSlotState)			(_ConvertPlayerSlotState);
	ConvertUnitState			= (pConvertUnitState)				(_ConvertUnitState);
	GetUnitState				= (pGetUnitState)					(_GetUnitState);
	GetUnitTypeId				= (pGetUnitTypeId)					(_GetUnitTypeId);
	GetPlayerName				= (pGetPlayerName)					(_GetPlayerName);
	GetUnitName					= (pGetUnitName)					(_GetUnitName);
	GetItemName					= (pGetItemName)					(_GetItemName);
	GetItemCharges				= (pGetItemCharges)					(_GetItemCharges);
}

void MyDisplayTimedTextToPlayer (HPLAYER hPlayer, float x, float y, float Duration, const char* Text)
{
	CJassString JSMessage;
	char* NewText = _strdup(Text);
	GetJassString(NewText ,&JSMessage);
	DisplayTimedTextToPlayer(hPlayer, &x, &y, &Duration, &JSMessage);
}
HPLAYER MyGetLocalPlayer ()
{
	return GetLocalPlayer();
}
void MyChangeLevel(const char* newLevel, bool doScoreScreen)
{
	CJassString JSnewLevel;
	char* NewText = _strdup(newLevel);
	GetJassString(NewText ,&JSnewLevel);
	ChangeLevel(&JSnewLevel, doScoreScreen);
}
void MyPingMinimap(float x, float y, float duration)
{
	PingMinimap(&x, &y, &duration);
}
void MyPingMinimapEx(float x, float y, float duration, int red, int green, int blue, bool extraEffects)
{
	PingMinimapEx(&x, &y, &duration, red, green, blue, extraEffects);
}
bool MyIsUnitVisible(HUNIT hUnit, HPLAYER hPlayer)
{
	return IsUnitVisible(hUnit, hPlayer);
}
void MySelectUnit(HUNIT hUnit, bool flag)
{
	SelectUnit(hUnit, flag);
}
HUNIT MyGetTriggerUnit()
{
	return GetTriggerUnit();
}
HPLAYER MyGetOwningPlayer(HUNIT hUnit)
{
	return GetOwningPlayer(hUnit);
}
HPLAYERCOLOR MyGetPlayerColor(HPLAYER hPlayer)
{
	return GetPlayerColor(hPlayer);
}
HDIALOG MyDialogCreate()
{
	return DialogCreate();
}
void MyDialogDisplay(HPLAYER hPlayer , HDIALOG hDialog , bool flag)
{
	DialogDisplay(hPlayer, hDialog, flag);
}
void MyDialogSetMessage(HDIALOG hDialog , const char *Message)
{
	CJassString JSMessage;
	char* NewText = _strdup(Message);
	GetJassString(NewText ,&JSMessage);
	DialogSetMessage(hDialog, &JSMessage);
}
HBUTTON MyDialogAddButton(HDIALOG hDialog , const char *ButtonText , int Hotkey)
{
	CJassString JSButtonText;
	char* NewText = _strdup(ButtonText);
	GetJassString(NewText ,&JSButtonText);
	return DialogAddButton(hDialog, &JSButtonText, Hotkey);
}
HBUTTON MyDialogAddQuitButton(HDIALOG hDialog , bool ShowScoreScreen , const char *ButtonText , int Hotkey)
{
	CJassString JSButtonText;
	char* NewText = _strdup(ButtonText);
	GetJassString(NewText ,&JSButtonText);
	return DialogAddQuitButton(hDialog, ShowScoreScreen, &JSButtonText, Hotkey);
}
void MyClearTextMessages()
{
	ClearTextMessages();
}
HTEXTTAG MyCreateTextTag()
{
	return CreateTextTag();
}
void MySetTextTagText(HTEXTTAG hTextTag, const char *Text, float height)
{
	CJassString JSTest;
	char* NewText = _strdup(Text);
	GetJassString(NewText ,&JSTest);
	SetTextTagText(hTextTag, &JSTest, &height);
}
void MySetTextTagPosUnit(HTEXTTAG hTextTag, int hUnit, float heightOffset)
{
	SetTextTagPosUnit(hTextTag, hUnit, &heightOffset);
}
void MySetTextTagColor(HTEXTTAG hTextTag, int red, int green, int blue, int alpha)
{
	SetTextTagColor(hTextTag, red, green, blue, alpha);
}
void MySetTextTagVelocity(HTEXTTAG hTextTag, float xvel, float yvel)
{
	SetTextTagVelocity(hTextTag, &xvel, &yvel);
}
void MySetTextTagFadepoint(HTEXTTAG hTextTag, float fadepoint)
{
	SetTextTagFadepoint(hTextTag, &fadepoint);
}
void MySetTextTagLifespan(HTEXTTAG hTextTag, float lifespan)
{
	SetTextTagLifespan(hTextTag, &lifespan);
}
void MySetTextTagPermanent(HTEXTTAG hTextTag, bool flag)
{
	SetTextTagPermanent(hTextTag, flag);
}
void MySetTextTagVisibility(HTEXTTAG hTextTag, bool flag)
{
	SetTextTagVisibility(hTextTag, flag);
}
void MyClearSelection()
{
	ClearSelection();
}
void MyPauseGame(bool flag)
{
	PauseGame(flag);
}
int MyGetHeroLevel(HUNIT hUnit)
{
	return GetHeroLevel(hUnit);
}
float MyGetUnitX(HUNIT hUnit)
{
	return GetUnitX(hUnit).fl;
}
float MyGetUnitY(HUNIT hUnit)
{
	return GetUnitY(hUnit).fl;
}
int MyGetPlayerId(HPLAYER hPlayer)
{
	return GetPlayerId(hPlayer);
}
bool MyIsUnitAlly(HUNIT hUnit, HPLAYER hPlayer)
{
	return IsUnitAlly(hUnit, hPlayer);
}
bool MyIsUnitEnemy(HUNIT hUnit, HPLAYER hPlayer)
{
	return IsUnitEnemy(hUnit, hPlayer);
}
bool MyIsPlayerAlly(HPLAYER hPlayer1, HPLAYER hPlayer2)
{
	return IsPlayerAlly(hPlayer1, hPlayer1);
}
bool MyIsPlayerEnemy(HPLAYER hPlayer1, HPLAYER hPlayer2)
{
	return IsPlayerEnemy(hPlayer1, hPlayer1);
}
bool MyIsPlayerObserver(HPLAYER hPlayer)
{
	return IsPlayerObserver(hPlayer);
}
HPLAYER MyPlayer(int Index)
{
	return Player(Index);
}
HRACE MyGetPlayerRace(HPLAYER hPlayer)
{
	return GetPlayerRace(hPlayer);
}
void MyDoNotSaveReplay()
{
	DoNotSaveReplay();
}
int MyGetPlayerState(HPLAYER hPlayer, HPLAYERSTATE hPlayerState)
{
	return GetPlayerState(hPlayer, hPlayerState);
}
int MyGetPlayerScore(HPLAYER hPlayer, HPLAYERSCORE hPlayerState)
{
	return GetPlayerScore(hPlayer, hPlayerState);
}
bool MyIsVisibleToPlayer(float x, float y, HPLAYER hPlayer)
{
	return IsVisibleToPlayer(&x, &y, hPlayer);
}
bool MyIsFoggedToPlayer(float x, float y, HPLAYER hPlayer)
{
	return IsFoggedToPlayer(&x, &y, hPlayer);
}
bool MyIsMaskedToPlayer(float x, float y, HPLAYER hPlayer)
{
	return IsMaskedToPlayer(&x, &y, hPlayer);
}
HRACE MyConvertRace(int i)
{
	return ConvertRace(i);
}
HPLAYERSTATE MyConvertPlayerState(int i)
{
	return ConvertPlayerState(i);
}
HPLAYERSCORE MyConvertPlayerScore(int i)
{
	return ConvertPlayerScore(i);
}
HPLAYERSLOTSTATE MyGetPlayerSlotState(HPLAYER hPlayer)
{
	return GetPlayerSlotState(hPlayer);
}
HPLAYERSLOTSTATE MyConvertPlayerSlotState(int i)
{
	return ConvertPlayerSlotState(i);
}
HUNITSTATE MyConvertUnitState(int i)
{
	return ConvertUnitState(i);
}
float MyGetUnitState(HUNIT hUnit, HUNITSTATE hUnitState)
{
	return GetUnitState(hUnit, hUnitState).fl;
}
int MyGetUnitTypeId(HUNIT hUnit)
{
	return GetUnitTypeId(hUnit);
}
const char* MyGetPlayerName(HPLAYER hPlayer)
{
	HJSSTRING PlayerName = GetPlayerName(hPlayer);
	return GetStringFromJSID(PlayerName);
}
const char* MyGetUnitName(HUNIT hUnit)
{
	HJSSTRING UnitName = GetUnitName(hUnit);
	return GetStringFromJSID(UnitName);
}
const char* MyGetItemName(HITEM hItem)
{
	HJSSTRING ItemName = GetItemName(hItem);
	return GetStringFromJSID(ItemName);
}
int MyGetItemCharges(HITEM hItem)
{
	return GetItemCharges(hItem);
}

};

class CGame{
public:

	CGame()
	{
		GetTlsValue();
	}

	int GetGameState()
	{
		DWORD rt;
		if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)(TlsValue + 4 * 0x0D), (LPVOID)&rt, 4, NULL))
			return -1;
		if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)(rt + 0x10), (LPVOID)&rt, 4, NULL))
			return -1;
		if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)(rt + 0x8), (LPVOID)&rt, 4, NULL))
			return -1;
		if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)(rt + 0x278), (LPVOID)&rt, 4, NULL))
			return -1;

		return rt;
	}
	float GetUnitStat(int unitID, DWORD statNum)
	{
		Unit* unit = GlobalUnits[unitID];
		float result = 0;

		__asm
		{
			PUSH statNum;
			LEA EAX,result
			PUSH EAX
			MOV ECX,unit
			CALL _GetFloatStat
		}
		return result;
	}
	int GetUnitLocation(int unitID)
	{
		Unit* unit = GlobalUnits[unitID];
		Location loc =	{ 0, 0, 0 };

		if (GlobalLocationsCount >= 1000) GlobalLocationsCount = 0;

		if (!unit)
			return 0;

		__asm
		{
			PUSHAD;
			MOV EAX,unit;
			MOV EDX, DWORD PTR DS:[EAX];
			LEA ECX,loc;
			PUSH ECX;
			MOV ECX,EAX;
			MOV EAX,DWORD PTR DS:[EDX+0xB8];
			CALL EAX;
			MOV ECX,EAX;
			CALL _GetLocation;
			POPAD;
		}
		GlobalLocationsCount++;
		GlobalLocations[GlobalLocationsCount] = loc;
		return GlobalLocationsCount;
	}
	int GetSelectedUnit()
	{
		HPLAYER plr = gGetLocalPlayer();
		HUNIT rt;

		if (GlobalUnitsCount >= 1000) GlobalUnitsCount = 1;

		__asm
		{
			MOV EAX,plr;
			MOV ECX,DWORD PTR DS:[EAX+0x34];
			MOV EAX,DWORD PTR DS:[ECX+0x1E0];
			MOV rt,EAX;
		}
		GlobalUnitsCount++;
		GlobalUnits[GlobalUnitsCount] = (Unit*)rt;
		return GlobalUnitsCount;
	}
	float Distance(int one, int two)
	{
		Location LOne = GlobalLocations[one];
		Location LTwo = GlobalLocations[two];
		float A = (LOne.X - LTwo.X);
		float B = (LOne.Y - LTwo.Y);
		float C = (LOne.Z - LTwo.Z);
		return sqrtf(A * A + B * B + C * C);
	}
	void PauseGame()
	{
		__asm
		{
			PUSHAD;
			MOV EAX,_PauseGameConst;
			MOV BYTE PTR SS:[ESP+0x20],1;
			MOV DWORD PTR SS:[ESP+0xC],EAX;
			XOR EDX,EDX;
			LEA ECX,DWORD PTR SS:[ESP+0xC];
			CALL _PauseGame;
			POPAD;
		}
	}
	void ResumeGame()
	{
		__asm
		{
			PUSHAD;
			MOV EAX,_ResumeGameConst;
			MOV BYTE PTR SS:[ESP+0x20],2;
			MOV DWORD PTR SS:[ESP+0xC],EAX;
			XOR EDX,EDX;
			LEA ECX,DWORD PTR SS:[ESP+0xC];
			CALL _ResumeGame;
			POPAD;
			}
	}
	void gSelectUnit(int unitID)
	{
		Unit* unit = GlobalUnits[unitID];

		__asm
		{
			ADDR(_W3XGlobalClass,EAX)
			MOV ESI, DWORD PTR DS:[EAX+0x24C];
			PUSH 0;
			PUSH 0;
			PUSH 0;
			PUSH unit;
			MOV ECX,ESI;
			CALL _UnitSelect;
		}
	}
	void SendCommand(int unitID, DWORD cmdId, float X, float Y, int targetID)
	{	
		int unt = GetSelectedUnit();
		Unit* unit = GlobalUnits[unitID];

		if (unit)
			gSelectUnit(unitID);

		if (targetID == 0)
		{
			__asm
			{
				PUSH 0
				PUSH 6
				PUSH 0
				ADDR(_W3XGlobalClass,ECX)
				MOV ECX, DWORD PTR DS:[ECX+0x1B4];
				PUSH Y
				PUSH X
				PUSH 0
				PUSH cmdId
				CALL _MoveAttackCmd
			}
		}
		else
		{
			Unit* target = GlobalUnits[targetID];
			__asm
			{
				PUSH 0
				PUSH 4
				PUSH target
				PUSH 0
				PUSH cmdId
				ADDR(_W3XGlobalClass,ECX)
				MOV ECX, DWORD PTR DS:[ECX+0x1B4];
				CALL _MoveTargetCmd
			}
		}
		if (unt && !IsDead(unt))
			gSelectUnit(unt);
	}
	DWORD GetPlayerNumber()
	{
		DWORD rt;

		__asm
		{
			ADDR(_W3XPlayerData,EAX)
			TEST EAX,EAX;
			JE err;
			MOVZX EAX,WORD PTR DS:[EAX+0x28];
			MOV rt,EAX;
		}
		return (DWORD)rt;
	err:
		return 0;
	}
	DWORD GetPlayerByNumber(DWORD plNum)
	{
		DWORD rt = 0;

		__asm
		{
			ADDR(_W3XPlayerData,ECX)
			PUSH plNum;
			CALL _GetHPlayerByNumber;
			MOV rt,EAX;
		}
		return rt;
	}
	DWORD gGetLocalPlayer()
	{
		return GetPlayerByNumber(GetPlayerNumber());
	}
	bool IsHero(int unitID)
	{
		Unit* unit = GlobalUnits[unitID];

		__asm
		{
			MOV EAX,unit
			CALL _IsUnitHero
		}
	}
	bool IsUnitOwnedByPlayer(DWORD plr, int unitID)
	{
		DWORD rt;
		Unit* unit = GlobalUnits[unitID];

		if (!unit)
			return false;

		__asm
		{
			MOV ESI,unit;
			MOV EAX,plr;
			PUSH -1;
			MOVZX EDI,BYTE PTR DS:[EAX+0x30];
			MOV EAX,DWORD PTR DS:[ESI];
			MOV EDX,DWORD PTR DS:[EAX+0xEC];
			MOV ECX,ESI;
			CALL EDX;
			XOR ECX,ECX;
			CMP EDI,EAX;
			SETE CL;
			MOV EAX,ECX;
			MOV rt,EAX;
		}
		return rt > 0;
	}
	bool IsDead(int unitID)
	{
		Unit* unit = GlobalUnits[unitID];

		__asm
		{
			MOV ECX,unit;
			TEST DWORD PTR DS:[ECX+0x5C],FLAG_DEAD;
			JE endlbl;
		}
		return true;
	endlbl:
		return false;
	}
	LuaRef GetAllUnits(lua_State *L)
	{
		LuaRef Table = newTable(L);
		int count = 1;
		DWORD len = 0;
		DWORD arr = GetUnitArray(len);

		if (GlobalUnitsCount >= 1000) GlobalUnitsCount = 1;

		for (DWORD i = 0; i < len; i++)
		{
			GlobalUnits[GlobalUnitsCount] = (Unit*)*(DWORD*)(arr + i * 4);

			if (!IsValidUnitPtr(GlobalUnits[GlobalUnitsCount]))
				continue;

				Table[count] = GlobalUnitsCount;
				count++;

			GlobalUnitsCount++;
		}
		return Table;
		
	}
	LuaRef GetDotaUnits(lua_State *L)
	{
		LuaRef Table = newTable(L);
		int UnitClassID = 0;
		int count = 1;
		DWORD len = 0;
		DWORD arr = GetUnitArray(len);

		if (GlobalUnitsCount >= 1000) GlobalUnitsCount = 1;

		for (DWORD i = 0; i < len; i++)
		{
			GlobalUnits[GlobalUnitsCount] = (Unit*)*(DWORD*)(arr + i * 4);

			if (!IsValidUnitPtr(GlobalUnits[GlobalUnitsCount]))
				continue;

			UnitClassID = (int)GlobalUnits[GlobalUnitsCount]->dwClassId;

			if (UnitClassID == 1702061422 || UnitClassID == 1701081721 || UnitClassID == 1969711215 || UnitClassID == 1970169187 || UnitClassID == 1700946284 || UnitClassID == 1970107511)
			{
				Table[count] = GlobalUnitsCount;
				count++;
			}
			GlobalUnitsCount++;
		}
		return Table;
		
	}

private:
	void GetTlsValue()
	{
		TlsIndex = *(DWORD*)(_W3XTlsIndex);
		LPVOID tls = (LPVOID)GetW3TlsForIndex(TlsIndex);
		TlsSetValue(TlsIndex, tls);
		TlsValue = (DWORD)tls;
	}
	DWORD GetW3TlsForIndex(DWORD index)
{
	DWORD pid = GetCurrentProcessId();
	THREADENTRY32 te32;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
	te32.dwSize = sizeof(THREADENTRY32);

	if (Thread32First(hSnap, &te32))
	{
		do
		{
			if (te32.th32OwnerProcessID == pid)
			{
				HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, false, te32.th32ThreadID);
				CONTEXT ctx =				{ CONTEXT_SEGMENTS };
				LDT_ENTRY ldt;
				GetThreadContext(hThread, &ctx);
				GetThreadSelectorEntry(hThread, ctx.SegFs, &ldt);
				DWORD dwThreadBase = ldt.BaseLow | (ldt.HighWord.Bytes.BaseMid <<
													16) | (ldt.HighWord.Bytes.BaseHi << 24);
				CloseHandle(hThread);
				if (dwThreadBase == NULL)
					continue;
				DWORD* dwTLS = *(DWORD**)(dwThreadBase + 0xE10 + 4 * index);
				if (dwTLS == NULL)
					continue;
				printf("Found => Thread: %X , TLS for index %X : %X\n", te32.th32ThreadID, index, (DWORD)dwTLS);
				return (DWORD)dwTLS;
			}
		} while (Thread32Next(hSnap, &te32));
	}

	return NULL;
}
	DWORD GetUnitArray(DWORD& Sz)
	{
		__asm
		{
			ADDR(_W3XGlobalClass,EAX)
			MOV EAX,DWORD PTR DS:[EAX+0x3BC]
			PUSH 0 // if 0 here it will just return the pointer if 1 it will update the array
			MOV ECX,EAX
			CALL _GetUnitArrayPtr
			MOV ECX,DWORD PTR DS:[EAX+4]
			MOV EDX,DWORD PTR DS:[Sz]
			MOV DWORD PTR DS:[EDX], ECX
			MOV EAX,DWORD PTR DS:[EAX+8]
		}
	}
	bool IsValidUnitPtr(Unit* ptr)
	{
		return IsValidUnitPtr((DWORD)ptr);
	}
	bool IsValidUnitPtr(DWORD ptr)
	{
		DWORD test;

		if (!ptr)
			return false;
		if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)ptr, &test, sizeof(test), NULL))
			return false;
		if (test != _UnitClass)
			return false;
		return true;
	}

	DWORD TlsValue, TlsIndex;
};


void addToState (lua_State *L)
{

	getGlobalNamespace (L) //Global Functions
		.addFunction ("ShowMessage", &ShowMessage)
		.addFunction ("Sleep", &Scripts.Util_Sleep)
		.addFunction ("Debug", &Debug)
		.addFunction ("MouseClick", &Scripts.MouseClick)
		.addFunction ("KeyPress", &Scripts.KeyPress)
		.addFunction ("HotKeySet", &Scripts.HotKeySet);

	getGlobalNamespace (L)
		.beginNamespace("GS")
			.addVariable("NOTHING",&GS_NOTHING,false)
			.addVariable("LOBBY",&GS_LOBBY,false)
			.addVariable("LOADING",&GS_LOADING,false)
			.addVariable("INGAME",&GS_INGAME,false)
			.addVariable("PAUSED",&GS_PAUSED,false)
		.endNamespace();

	getGlobalNamespace (L)
		.beginNamespace("STAT")
			.addVariable("HP",&STAT_HP,false)
			.addVariable("MAXHP",&STAT_MAXHP,false)
			.addVariable("MANA",&STAT_MANA,false)
			.addVariable("MAXMANA",&STAT_MAXMANA,false)
		.endNamespace();

	getGlobalNamespace (L)
		.beginNamespace("CMD")
			.addVariable("MOVE",&CMD_MOVE,false)
			.addVariable("ATTACK",&CMD_ATTACK,false)
			.addVariable("HOLD",&CMD_HOLD,false)
			.addVariable("STOP",&CMD_STOP,false)
		.endNamespace();

	getGlobalNamespace (L)
		.beginClass<CJass>("CJass")
		.addConstructor<void (*) (void)> ()
			.addFunction("Initialize",&CJass::Initialize)
			.addFunction("GetLocalPlayer",&CJass::MyGetLocalPlayer)
			.addFunction("DisplayTimedTextToPlayer",&CJass::MyDisplayTimedTextToPlayer)
			.addFunction("ChangeLevel",&CJass::MyChangeLevel)
			.addFunction("PingMinimap",&CJass::MyPingMinimap)
			.addFunction("PingMinimapEx",&CJass::MyPingMinimapEx)
			.addFunction("IsUnitVisible",&CJass::MyIsUnitVisible)
			.addFunction("SelectUnit",&CJass::MySelectUnit)
			.addFunction("GetTriggerUnit",&CJass::MyGetTriggerUnit)
			.addFunction("GetOwningPlayer",&CJass::MyGetOwningPlayer)
			.addFunction("GetPlayerColor",&CJass::MyGetPlayerColor)
			.addFunction("DialogCreate",&CJass::MyDialogCreate)
			.addFunction("DialogDisplay",&CJass::MyDialogDisplay)
			.addFunction("DialogSetMessage",&CJass::MyDialogSetMessage)
			.addFunction("DialogAddButton",&CJass::MyDialogAddButton)
			.addFunction("DialogAddQuitButton",&CJass::MyDialogAddQuitButton)
			.addFunction("ClearTextMessages",&CJass::MyClearTextMessages)
			.addFunction("CreateTextTag",&CJass::MyCreateTextTag)
			.addFunction("SetTextTagText",&CJass::MySetTextTagText)
			.addFunction("SetTextTagPosUnit",&CJass::MySetTextTagPosUnit)
			.addFunction("SetTextTagColor",&CJass::MySetTextTagColor)
			.addFunction("SetTextTagVelocity",&CJass::MySetTextTagVelocity)
			.addFunction("SetTextTagFadepoint",&CJass::MySetTextTagFadepoint)
			.addFunction("SetTextTagLifespan",&CJass::MySetTextTagLifespan)
			.addFunction("SetTextTagPermanent",&CJass::MySetTextTagPermanent)
			.addFunction("SetTextTagVisibility",&CJass::MySetTextTagVisibility)
			.addFunction("ClearSelection",&CJass::MyClearSelection)
			.addFunction("PauseGame",&CJass::MyPauseGame)	
			.addFunction("GetHeroLevel",&CJass::MyGetHeroLevel)
			.addFunction("GetUnitX",&CJass::MyGetUnitX)
			.addFunction("GetUnitY",&CJass::MyGetUnitY)
			.addFunction("GetPlayerId",&CJass::MyGetPlayerId)
			.addFunction("IsUnitAlly",&CJass::MyIsUnitAlly)
			.addFunction("IsUnitEnemy",&CJass::MyIsUnitEnemy)
			.addFunction("IsPlayerAlly",&CJass::MyIsPlayerAlly)
			.addFunction("IsPlayerEnemy",&CJass::MyIsPlayerEnemy)
			.addFunction("IsPlayerObserver",&CJass::MyIsPlayerObserver)
			.addFunction("Player",&CJass::MyPlayer)
			.addFunction("GetPlayerRace",&CJass::MyGetPlayerRace)
			.addFunction("DoNotSaveReplay",&CJass::MyDoNotSaveReplay)
			.addFunction("GetPlayerState",&CJass::MyGetPlayerState)
			.addFunction("GetPlayerScore",&CJass::MyGetPlayerScore)
			.addFunction("IsVisibleToPlayer",&CJass::MyIsVisibleToPlayer)
			.addFunction("IsFoggedToPlayer",&CJass::MyIsFoggedToPlayer)
			.addFunction("IsMaskedToPlayer",&CJass::MyIsMaskedToPlayer)
			.addFunction("ConvertRace",&CJass::MyConvertRace)
			.addFunction("ConvertPlayerState",&CJass::MyConvertPlayerState)
			.addFunction("ConvertPlayerScore",&CJass::MyConvertPlayerScore)
			.addFunction("GetPlayerSlotState",&CJass::MyGetPlayerSlotState)
			.addFunction("ConvertPlayerSlotState",&CJass::MyConvertPlayerSlotState)
			.addFunction("ConvertUnitState",&CJass::MyConvertUnitState)
			.addFunction("GetUnitState",&CJass::MyGetUnitState)
			.addFunction("GetUnitTypeId",&CJass::MyGetUnitTypeId)
			.addFunction("GetPlayerName",&CJass::MyGetPlayerName)
			.addFunction("GetUnitName",&CJass::MyGetUnitName)
			.addFunction("GetItemName",&CJass::MyGetItemName)
			.addFunction("GetItemCharges",&CJass::MyGetItemCharges)
		.endClass();

	getGlobalNamespace (L)
		.beginClass<CGame>("CGame")
		.addConstructor<void (*) (void)> ()
			.addFunction("GetGameState",&CGame::GetGameState)
			.addFunction("PauseGame",&CGame::PauseGame)
			.addFunction("ResumeGame",&CGame::ResumeGame)
			.addFunction("GetSelectedUnit",&CGame::GetSelectedUnit)
			.addFunction("GetAllUnits",&CGame::GetAllUnits)
			.addFunction("GetDotaUnits",&CGame::GetDotaUnits)
			.addFunction("GetUnitStat",&CGame::GetUnitStat)
			.addFunction("IsDead",&CGame::IsDead)
			.addFunction("SelectUnit",&CGame::gSelectUnit)
			.addFunction("SendCommand",&CGame::SendCommand)
			.addFunction("IsHero",&CGame::IsHero)
			.addFunction("IsUnitOwnedByPlayer",&CGame::IsUnitOwnedByPlayer)
			.addFunction("GetLocalPlayer",&CGame::gGetLocalPlayer)
			.addFunction("GetLocalPlayerNumber",&CGame::GetPlayerNumber)
			.addFunction("GetPlayerByNumber",&CGame::GetPlayerByNumber)
			.addFunction("GetUnitLocation",&CGame::GetUnitLocation)
			.addFunction("Distance",&CGame::Distance)
		.endClass();

}

}
