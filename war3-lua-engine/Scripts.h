#pragma once

#pragma region Definitions

#define NONEMOD			0
#define ALTMOD			1
#define SHIFTMOD		2
#define CTRLMOD			4
#define LWINMOD			8
#define ALTPERMMOD		16
#define SHIFTPERMMOD	32
#define CTRLPERMMOD		64
#define LWINPERMMOD		128
#define RWINPERMMOD		256
#define RESETMOD		ALTPERMMOD+CTRLPERMMOD+SHIFTPERMMOD+LWINPERMMOD+RWINPERMMOD

#define NUMKEYS 93
typedef enum {CTRLDOWN, CTRLUP, ALTDOWN, ALTUP, SHIFTDOWN, SHIFTUP,
				LWINDOWN, LWINUP, RWINDOWN, RWINUP, ASC, NUMPADENTER, ALT} SK_SpecialKeys;

#define SK_LOOKUP	0
#define SK_SPECIAL	1


#define IsPhysicallyDown(vk) ( (GetAsyncKeyState(vk) & 0x80000000) || ((GetKeyState(vk) & 0x8000)) )

#define MAXHOTKEYS 64

#pragma endregion

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CScripts
{
public:
	CScripts(void);
	~CScripts(void);

	static int MouseClick(const char* Button, int x = -1, int y = -1, int Clicks = 1, int Speed = 10);
	static int HotKeySet(const char* Key, luabridge::LuaRef Func, lua_State* L);
	static void Util_Sleep(int nTimeOut);
	static void KeyPress(const char *szSendKeys);
	static bool HandleHotKey(void);

private:
	static void ConvertCoords(int nCoordMode, POINT &pt);
	static void MouseMoveExecute(int x, int y, int nSpeed);
	static void Util_RegReadString(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwBufLen, char *szValue);
	static int Util_MouseDown(const char *szButton);
	static int Util_MouseUp(const char *szButton);
	static bool SetToggleState(UINT vk, bool bState);
	static int ReadToChar(char ch, const char *szLine, char *szResult, int &nPos);
	static bool IsVKExtended(UINT key);
	static void SimKeyDown(UINT vk, bool bForceExtended = false);
	static void SimKeyUp(UINT vk, bool bForceExtended = false);
	static void ResolveKeyModifiers(UINT vkres);
	static void SimModsDown(void);
	static void SimModsUp(void);
	static void SimKeystroke(UINT vk, bool bForceExtended = false);
	static void SendVk(UINT vk, int nRep, bool bExtended = false);
	static void SendCh(char ch, int nRep);
	static void SendSpecial(char *szTemp);
	static void SendSpecialCh(char ch);
	static bool GetSingleVKandMods(const char *szString, UINT &vk, bool &bShift, bool &bControl, bool &bAlt, bool &bWin);
	static void Initialize(void);

};

struct HotKeyDetails {
    WPARAM  wParam;                             // Hotkey ID
    LPARAM  lParam;                             // Key and modifiers (control, alt, etc)
    luabridge::LuaRef *lFunction;               // Function to call

    HotKeyDetails(): wParam(NULL), lParam(NULL), lFunction(NULL) {}
};

	
extern HotKeyDetails	*m_HotKeyDetails[64];	// Array for tracking hotkey details
extern int				m_nHotKeyQueuePos;				// Position in the global hotkey queue
extern bool				Initialized;