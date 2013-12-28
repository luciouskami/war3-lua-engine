#ifndef LUABRIDGE_TESTS_HEADER
#define LUABRIDGE_TESTS_HEADER

#include "stdafx.h"

namespace War3LuaEngine
{

static void SendSpecialCh(char ch);
static void SendSpecial(char *szTemp);
static void SendCh(char ch, int nRep);
static void SendVk(UINT vk, int nRep, bool bExtended = false);
static void SimKeystroke(UINT vk, bool bForceExtended = false);
static void SimModsUp(void);
static void SimModsDown(void);
static void ResolveKeyModifiers(UINT vkres);
static void SimKeyUp(UINT vk, bool bForceExtended = false);
static void SimKeyDown(UINT vk, bool bForceExtended = false);
static bool IsVKExtended(UINT key);
static int ReadToChar(char ch, const char *szLine, char *szResult, int &nPos);
static bool SetToggleState(UINT vk, bool bState);

extern void addToState (lua_State* L);

/**
Returns a registry reference to the message handler to
use in subsequent calls to lua_pcall ().
*/
extern int addTraceback (lua_State* L);


}

#endif