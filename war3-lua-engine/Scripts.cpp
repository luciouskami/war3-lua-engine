#include "stdafx.h"
#include "Scripts.h"
#include <process.h>

#pragma region Definitions

int		m_nKeyMod = NONEMOD;

char *g_szKeyTable[NUMKEYS] =
/*1 */	{"ALT", "BACKSPACE", "BS", "DEL", "DELETE", "DOWN", "END", "ENTER",
/*2 */	"ESC", "ESCAPE", "F1", "F2", "F3", "F4", "F5", "F6",
/*3 */	"F7", "F8", "F9", "F10", "F11", "F12", "HOME", "INS",
/*4 */	"INSERT", "LEFT", "PGDN", "PGUP", "RIGHT", "SPACE", "TAB", "UP",
/*5 */	"PRINTSCREEN", "LWIN", "RWIN", "SCROLLLOCK", "NUMLOCK", "CTRLBREAK", "PAUSE", "CAPSLOCK",
/*6 */	"NUMPAD0", "NUMPAD1", "NUMPAD2", "NUMPAD3", "NUMPAD4", "NUMPAD5", "NUMPAD6", "NUMPAD7",
/*7 */	"NUMPAD8", "NUMPAD9", "NUMPADMULT", "NUMPADADD", "NUMPADSUB", "NUMPADDOT", "NUMPADDIV", "APPSKEY",
/*8 */	"LCTRL", "RCTRL", "LALT", "RALT", "LSHIFT", "RSHIFT", "SLEEP", "NUMPADENTER",
/*9 */	"BROWSER_BACK", "BROWSER_FORWARD", "BROWSER_REFRESH", "BROWSER_STOP",
/*10*/	"BROWSER_SEARCH", "BROWSER_FAVORTIES", "BROWSER_HOME", "VOLUME_MUTE",
/*11*/	"VOLUME_DOWN", "VOLUME_UP", "MEDIA_NEXT", "MEDIA_PREV",
/*12*/	"MEDIA_STOP", "MEDIA_PLAY_PAUSE", "LAUNCH_MAIL", "LAUNCH_MEDIA",
/*13*/	"LAUNCH_APP1", "LAUNCH_APP2",
/*14*/	"CTRLDOWN", "CTRLUP",
/*15*/	"ALTDOWN", "ALTUP",
/*16*/	"SHIFTDOWN", "SHIFTUP",
/*17*/	"LWINDOWN", "LWINUP",
/*18*/	"RWINDOWN", "RWINUP",
/*19*/	"ASC"};

// The following must be in the same order as the szKeyTable
char g_cKeyLookupType[NUMKEYS] =
/*1 */	{SK_SPECIAL, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*2 */	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*3 */	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*4 */	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*5 */	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*6 */	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*7 */	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*8 */	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_SPECIAL,
/*9 */	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*10*/	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*11*/	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*12*/	SK_LOOKUP, SK_LOOKUP, SK_LOOKUP, SK_LOOKUP,
/*13*/	SK_LOOKUP, SK_LOOKUP,
/*14 */	SK_SPECIAL, SK_SPECIAL,
/*15*/	SK_SPECIAL, SK_SPECIAL,
/*16*/	SK_SPECIAL, SK_SPECIAL,
/*17*/	SK_SPECIAL, SK_SPECIAL,
/*18*/	SK_SPECIAL, SK_SPECIAL,
/*19*/	SK_SPECIAL};

// The following must be in the same order as the szKeyTable
int g_nKeyCodes[NUMKEYS] =
/*1 */	{ALT, VK_BACK, VK_BACK, VK_DELETE, VK_DELETE, VK_DOWN, VK_END, VK_RETURN,
/*2 */	VK_ESCAPE, VK_ESCAPE, VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6,
/*3 */	VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12, VK_HOME, VK_INSERT,
/*4 */	VK_INSERT, VK_LEFT, VK_NEXT, VK_PRIOR, VK_RIGHT, VK_SPACE, VK_TAB, VK_UP,
/*5 */	VK_SNAPSHOT, VK_LWIN, VK_RWIN, VK_SCROLL, VK_NUMLOCK, VK_CANCEL, VK_PAUSE, VK_CAPITAL,
/*6 */	VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7,
/*7 */	VK_NUMPAD8, VK_NUMPAD9, VK_MULTIPLY, VK_ADD, VK_SUBTRACT, VK_DECIMAL, VK_DIVIDE, VK_APPS,
/*8 */	VK_LCONTROL, VK_RCONTROL, VK_LMENU, VK_RMENU, VK_LSHIFT, VK_RSHIFT, VK_SLEEP, NUMPADENTER,
/*9 */	VK_BROWSER_BACK, VK_BROWSER_FORWARD, VK_BROWSER_REFRESH, VK_BROWSER_STOP,
/*10*/	VK_BROWSER_SEARCH, VK_BROWSER_FAVORITES, VK_BROWSER_HOME, VK_VOLUME_MUTE,
/*11*/	VK_VOLUME_DOWN, VK_VOLUME_UP, VK_MEDIA_NEXT_TRACK, VK_MEDIA_PREV_TRACK,
/*12*/	VK_MEDIA_STOP, VK_MEDIA_PLAY_PAUSE, VK_LAUNCH_MAIL, VK_LAUNCH_MEDIA_SELECT,
/*13*/	VK_LAUNCH_APP1, VK_LAUNCH_APP2,
/*14*/	CTRLDOWN, CTRLUP,
/*15*/	ALTDOWN, ALTUP,
/*16*/	SHIFTDOWN, SHIFTUP,
/*17*/	LWINDOWN, LWINUP,
/*18*/	RWINDOWN, RWINUP,
/*19*/	ASC};

char g_cDiadic [8] = {' ',' ','´','^','~','¨','`',' '};


CScripts *Obj;

HotKeyDetails	*m_HotKeyDetails[MAXHOTKEYS];	// Array for tracking hotkey details
int				m_nHotKeyQueuePos;				// Position in the global hotkey queue

luabridge::LuaRef *rFunc[MAXHOTKEYS];

sCreateHotKey Temp;

bool Initialized;

void WINAPI CreateWndForHotkey(LPVOID);

#pragma endregion

CScripts::CScripts(void)
{
	Obj = (CScripts*) this;

	// Initialise hotkeys to NULL 
	for (int i = 0; i < MAXHOTKEYS; ++i)
		m_HotKeyDetails[i] = NULL;
	m_nHotKeyQueuePos	= 0;
	g_HotKeyNext		= 0;
	bRegisterFinished	= false;
	Initialized = false;
}

CScripts::~CScripts(void)
{
	for (int i = 0; i < MAXHOTKEYS; ++i)
	{
		if (m_HotKeyDetails[i] != NULL)
		{
			UnregisterHotKey(wHandle, (int)m_HotKeyDetails[i]->wParam);
			// Delete memory
			delete rFunc[i];
			delete m_HotKeyDetails[i];
			// Mark as empty
			rFunc[i] = NULL;
			m_HotKeyDetails[i] = NULL;
		}
	}
}

void CScripts::Initialize(void)
{
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CreateWndForHotkey, NULL, 0, NULL);
	SetThreadPriority(hThread, THREAD_PRIORITY_IDLE);
	CloseHandle(hThread);
}

void CScripts::Util_Sleep(int nTimeOut)
{
	// Handle the special cases -1 and 0 first
	if (nTimeOut < 0)
		return;									// No sleep at all for -ve numbers
	else if (nTimeOut == 0)
	{
		::Sleep(0);								// Special case for 0
		return;
	}

	__int64		start, cur, freq;
	double		diff;
	DWORD		dwMin;
	DWORD		dwTimeOut = (DWORD)nTimeOut;

	// Set the minimum Sleep accuracy

		dwMin = 10;

	// If Sleep is >= dwMin or no performance counters are available then use native Sleep()
	if (dwTimeOut >= dwMin || !QueryPerformanceCounter((LARGE_INTEGER *)&start))
	{
		::Sleep(dwTimeOut);
		return;
	}

	// Get frequency
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

	// Note that we must at least do a Sleep(0) once otherwise the SendTo functions get out of
	// sync - especially on 9x/NT4 but also had one report for XP too (seems be on the keydowndelay)
	do
	{
		::Sleep(0);								// Reduce CPU usage - Sleep 0 is special
		QueryPerformanceCounter((LARGE_INTEGER *)&cur);
		diff = ((double)(cur - start) / (double)freq) * 1000.0;

	} while ((DWORD)diff < dwTimeOut);

}
void CScripts::ConvertCoords(int nCoordMode, POINT &pt)
{
	HWND	hFore = GetForegroundWindow();
	RECT	rect;

	if (nCoordMode == 0)
	{
		GetWindowRect(hFore, &rect);
		pt.x = rect.left;
		pt.y = rect.top;
	}
	else if (nCoordMode == 2)
	{
		pt.x = 0;
		pt.y = 0;
		ClientToScreen(hFore, &pt);
	}
	else
	{
		// Screen mode
		pt.x = 0;
		pt.y = 0;
	}

}	// ConvertCoords()
void CScripts::MouseMoveExecute(int x, int y, int nSpeed)
{
	POINT	ptCur, ptOrigin;
	RECT	rect;
	int		xCur, yCur;
	int		delta;
	const	int	nMinSpeed = 32;


	// Convert coords to screen/active window/client
	ConvertCoords(1, ptOrigin);
	x += ptOrigin.x;
	y += ptOrigin.y;

	// Get size of desktop
	GetWindowRect(GetDesktopWindow(), &rect);

	// Sanity check coords - removed so that it works on multiple monitors where -ve values are OK
/*	if (x < 0)
		x = 0;
	else if (x > rect.right)
		x = rect.right;

	if (y < 0)
		y = 0;
	else if (y > rect.bottom)
		y = rect.bottom; */

	// Convert our coords to mouse_event coords
	x = ((65535 * x) / (rect.right-1)) + 1;
	y = ((65535 * y) / (rect.bottom-1)) + 1;


	// Are we slowly moving or insta-moving?
	if (nSpeed == 0)
	{
		mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, x, y, 0, 0);
		Util_Sleep(10);							// Hopefully fixes "clicks before moving" bug
		return;
	}

	// Sanity check for speed
	if (nSpeed < 0 || nSpeed > 100)
		nSpeed = 10;							// Default is speed 10


	// So, it's a more gradual speed that is needed :)
	GetCursorPos(&ptCur);
	xCur = ((ptCur.x * 65535) / (rect.right-1)) + 1;
	yCur = ((ptCur.y * 65535) / (rect.bottom-1)) + 1;

	while (xCur != x || yCur != y)
	{
		if (xCur < x)
		{
			delta = (x - xCur) / nSpeed;
			if (delta == 0 || delta < nMinSpeed)
				delta = nMinSpeed;
			if ((xCur + delta) > x)
				xCur = x;
			else
				xCur += delta;
		}
		else
			if (xCur > x)
			{
				delta = (xCur - x) / nSpeed;
				if (delta == 0 || delta < nMinSpeed)
					delta = nMinSpeed;
				if ((xCur - delta) < x)
					xCur = x;
				else
					xCur -= delta;
			}

		if (yCur < y)
		{
			delta = (y - yCur) / nSpeed;
			if (delta == 0 || delta < nMinSpeed)
				delta = nMinSpeed;
			if ((yCur + delta) > y)
				yCur = y;
			else
				yCur += delta;
		}
		else
			if (yCur > y)
			{
				delta = (yCur - y) / nSpeed;
				if (delta == 0 || delta < nMinSpeed)
					delta = nMinSpeed;
				if ((yCur - delta) < y)
					yCur = y;
				else
					yCur -= delta;
			}

		mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, xCur, yCur, 0, 0);

		Util_Sleep(10);							// 20 ms sleep inbetween moves
	}

} // MouseMoveExecute()
void CScripts::Util_RegReadString(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwBufLen, char *szValue )
{
	HKEY	hRegKey;

	// Make sure the return value is blank just in case we error
	szValue[0] = '\0';

	if (RegOpenKeyEx(hKey, lpSubKey, 0, KEY_QUERY_VALUE, &hRegKey) != ERROR_SUCCESS)
		return;

	RegQueryValueEx(hRegKey, lpValueName, NULL, NULL, (LPBYTE)szValue, &dwBufLen);

	RegCloseKey(hRegKey);

} // Util_RegReadString()
int CScripts::Util_MouseDown(const char *szButton)
{
	char swapped[4];
	DWORD event=0;

	if ( szButton[0] == '\0' || _stricmp(szButton, "LEFT")==0 ) // empty string or "left"
		event = MOUSEEVENTF_LEFTDOWN;
	else if ( _stricmp(szButton,"RIGHT")==0 )
		event = MOUSEEVENTF_RIGHTDOWN;
	else if ( _stricmp(szButton,"MIDDLE")==0 )
		event = MOUSEEVENTF_MIDDLEDOWN;
	else
	{
		Util_RegReadString(HKEY_CURRENT_USER, "Control Panel\\Mouse", "SwapMouseButtons", 4, swapped );
		if ( swapped[0] == '1')	// buttons swapped
		{
			if ( _stricmp(szButton,"MAIN")==0 || _stricmp(szButton, "PRIMARY"))
				event = MOUSEEVENTF_RIGHTDOWN;
			else if ( _stricmp(szButton,"MENU")==0 || _stricmp(szButton, "SECONDARY"))
				event = MOUSEEVENTF_LEFTDOWN;
		}
		else
		{
			if ( _stricmp(szButton,"MAIN")==0 || _stricmp(szButton, "PRIMARY"))
				event = MOUSEEVENTF_LEFTDOWN;
			else if ( _stricmp(szButton,"MENU")==0 || _stricmp(szButton, "SECONDARY"))
				event = MOUSEEVENTF_RIGHTDOWN;
		}
	}
	if (event != 0) {
		mouse_event(event, 0, 0, 0, 0);
		return 1;
	}
	else
		return 0;

} // Util_MouseDown()
int CScripts::Util_MouseUp(const char *szButton)
{
	char swapped[4];
	DWORD event = 0;	// default to 0 in case no strings match

	if ( szButton[0] == '\0' || _stricmp(szButton, "LEFT")==0 ) // empty string or "left"
		event = MOUSEEVENTF_LEFTUP;
	else if ( _stricmp(szButton,"RIGHT")==0 )
		event = MOUSEEVENTF_RIGHTUP;
	else if ( _stricmp(szButton,"MIDDLE")==0 )
		event = MOUSEEVENTF_MIDDLEUP;
	else
	{
		Util_RegReadString(HKEY_CURRENT_USER, "Control Panel\\Mouse", "SwapMouseButtons", 4, swapped );
		if ( swapped[0] = '1')	// buttons swapped
		{
			if ( _stricmp(szButton,"MAIN")==0 || _stricmp(szButton, "PRIMARY"))
				event = MOUSEEVENTF_RIGHTUP;
			else if ( _stricmp(szButton,"MENU")==0 || _stricmp(szButton, "SECONDARY"))
				event = MOUSEEVENTF_LEFTUP;
		}
		else
		{
			if ( _stricmp(szButton,"MAIN")==0 || _stricmp(szButton, "PRIMARY"))
				event = MOUSEEVENTF_LEFTUP;
			else if ( _stricmp(szButton,"MENU")==0 || _stricmp(szButton, "SECONDARY"))
				event = MOUSEEVENTF_RIGHTUP;
		}
	}
	if (event != 0) {
		mouse_event(event, 0, 0, 0, 0);
		return 1;
	}
	else
		return 0;

} // Util_MouseUp()
int CScripts::MouseClick(const char* Button, int x, int y, int Clicks, int Speed)
{
	int		nSpeed = Speed;
	int		nClicks=Clicks, nX=x, nY=y;

	// Check for x without y
	if (nX >= 0 && nY < 0)
	{
		return 0;
	}

		if (nClicks <= 0)
			return 0;	// 0 or less clicks specified


		if (nSpeed < 0)
			return 0;


	// Do we need to move the mouse?
	if (x >= 0)
		MouseMoveExecute(nX, nY, nSpeed);


	for (int i=0; i<nClicks; ++i)
	{
		// Do the click
		if (Util_MouseDown(Button) == 0)
		{
			// not a valid click
			return 0;
		}
		Util_Sleep(10);
		if (Util_MouseUp(Button) == 0) {
			// not a valid click
			return 0;
		}
		Util_Sleep(10);
	}

	return 1;

} // MouseClick()
bool CScripts::SetToggleState(UINT vk, bool bState)
{
	bool	bInitial;

	if (GetKeyState(vk) & 0x01)
		bInitial = true;						// Was on
	else
		bInitial = false;						// Was off


	// Do we need to do anything?
	if (bState == bInitial)
		return bInitial;						// Nope

//	MessageBox(NULL, "Doing Capslock", "", MB_OK);

	keybd_event((BYTE)vk, MapVirtualKey(vk, 0), 0, 0);
	Util_Sleep(1);
	keybd_event((BYTE)vk, MapVirtualKey(vk, 0), KEYEVENTF_KEYUP, 0);
	Util_Sleep(5);

	return bInitial;

} // SetToggleState()
int CScripts::ReadToChar(char ch, const char *szLine, char *szResult, int &nPos)
{
	int		nFlag	= 1;
	int		nResPos	= 0;
	char	cTemp;

	// Find the selected char, and seperate
	while ( ( (cTemp = szLine[nPos]) != '\0') && (nFlag == 1) )
	{
		if (cTemp == ch)
			nFlag = 0;
		else
			szResult[nResPos++] = cTemp;

		nPos++;									// skip to next char

	} // End While


	// End the temp string, whether ch was found or not
	szResult[nResPos] = '\0';

	// if the char to search for was '\0' then it WILL have been found
	if (ch == '\0')
		return 0;
	else
		return nFlag;							// 1 is bad, 0 is good

} // ReadToChar()
bool CScripts::IsVKExtended(UINT key)
{
	if (key == VK_INSERT || key == VK_DELETE || key == VK_END || key == VK_DOWN ||
		key == VK_NEXT || key == VK_LEFT || key == VK_RIGHT || key == VK_HOME || key == VK_UP ||
		key == VK_PRIOR || key == VK_DIVIDE || key == VK_APPS || key == VK_LWIN || key == VK_RWIN ||
		key == VK_RMENU || key == VK_RCONTROL || key == VK_SLEEP || key == VK_BROWSER_BACK ||
		key == VK_BROWSER_FORWARD || key == VK_BROWSER_REFRESH || key == VK_BROWSER_STOP ||
		key == VK_BROWSER_SEARCH || key == VK_BROWSER_FAVORITES || key == VK_BROWSER_HOME ||
		key == VK_VOLUME_MUTE || key == VK_VOLUME_DOWN || key == VK_VOLUME_UP || key == VK_MEDIA_NEXT_TRACK ||
		key == VK_MEDIA_PREV_TRACK || key == VK_MEDIA_STOP || key == VK_MEDIA_PLAY_PAUSE ||
		key == VK_LAUNCH_MAIL || key == VK_LAUNCH_MEDIA_SELECT || key == VK_LAUNCH_APP1 || key == VK_LAUNCH_APP2)
	{
		return true;
	}
	else
		return false;

} // IsVKExtended()
void CScripts::SimKeyDown(UINT vk, bool bForceExtended)
{
	UINT	scan;

	scan = MapVirtualKey(vk, 0);

		if (bForceExtended == true || IsVKExtended(vk) == true)
			keybd_event((BYTE)vk, (BYTE)scan, KEYEVENTF_EXTENDEDKEY, 0);
		else
			keybd_event((BYTE)vk, (BYTE)scan, 0, 0);
	
} // SimKeyDown()
void CScripts::SimKeyUp(UINT vk, bool bForceExtended)
{
	UINT	scan;

	scan = MapVirtualKey(vk, 0);

	// use the keybd_event routines

		if (bForceExtended == true || IsVKExtended(vk) == true)
			keybd_event((BYTE)vk, (BYTE)scan, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		else
			keybd_event((BYTE)vk, (BYTE)scan, KEYEVENTF_KEYUP, 0);

} // SimKeyUp()
void CScripts::ResolveKeyModifiers(UINT vkres)
{
	// Examine the vkres code and see what state modifiers it is requesting
	if ( (vkres & 0x0200)  ) 					// CTRL required?
		m_nKeyMod |= CTRLMOD;

	if ( (vkres & 0x0400) )						// ALT required?
		m_nKeyMod |= ALTMOD;

	if ( (vkres & 0x0100) )						// SHIFT required?
		m_nKeyMod |= SHIFTMOD;

	// if we have permanent key down situation, we don't want to press those
	// keys again so we remove that key!

	if ( (m_nKeyMod & CTRLMOD) && (m_nKeyMod & CTRLPERMMOD) )
		m_nKeyMod ^= CTRLMOD;					// remove ctrl flag

	if ( (m_nKeyMod & ALTMOD) && (m_nKeyMod & ALTPERMMOD) )
		m_nKeyMod ^= ALTMOD;					// remove alt flag

	if ( (m_nKeyMod & SHIFTMOD) && (m_nKeyMod & SHIFTPERMMOD) )
		m_nKeyMod ^= SHIFTMOD;					// remove shift flag

	if ( (m_nKeyMod & LWINMOD) && (m_nKeyMod & LWINPERMMOD) )
		m_nKeyMod ^= LWINMOD;					// remove left win flag

	// Now check the physical state (as best as the buggy API lets us) to see if any
	// of the modifier keys are held down.  If they are - and none of the CTRLPER type
	// flags are used then force them to be released - even if our next keypress is
	// going to use the same modifier - it's just not close to reliable that way
	// This is not perfect, and if the user continues to twat around it will fail


		// keybd_event() mode
		if ( IsPhysicallyDown(VK_CONTROL) && (!(m_nKeyMod & CTRLPERMMOD)) )
		{
			SimKeyUp(VK_CONTROL);
			Util_Sleep(5);
		}

		if ( IsPhysicallyDown(VK_MENU) && (!(m_nKeyMod & ALTPERMMOD)) )
		{
			SimKeyUp(VK_MENU);
			Util_Sleep(5);
		}

		if ( IsPhysicallyDown(VK_SHIFT) && (!(m_nKeyMod & SHIFTPERMMOD)) )
		{
			SimKeyUp(VK_SHIFT);
			Util_Sleep(5);
		}

		if ( IsPhysicallyDown(VK_LWIN) && (!(m_nKeyMod & LWINPERMMOD)) )
		{
			SimKeyUp(VK_LWIN);
			Util_Sleep(5);
		}
	

} // ResolveKeyModifiers()
void CScripts::SimModsDown(void)
{
	UINT m_scanCtrl, m_scanAlt, m_scanShift, m_scanLWin;
	m_scanLWin = MapVirtualKey(VK_LWIN, 0);
	m_scanShift = MapVirtualKey(VK_SHIFT, 0);
	m_scanCtrl = MapVirtualKey(VK_CONTROL, 0);
	m_scanAlt = MapVirtualKey(VK_MENU, 0);

	// If the window is NULL use keybd_event
		if ( m_nKeyMod & LWINMOD ) 				// WIN required?
			keybd_event(VK_LWIN, m_scanLWin, 0, 0);
		if ( m_nKeyMod & SHIFTMOD ) 			// SHIFT required?
			keybd_event(VK_SHIFT, m_scanShift, 0, 0);
		if ( m_nKeyMod & CTRLMOD ) 				// CTRL required?
			keybd_event(VK_CONTROL, m_scanCtrl, 0, 0);
		if ( m_nKeyMod & ALTMOD ) 				// ALT required?
			keybd_event(VK_MENU, m_scanAlt, 0, 0);
	
	// Key down key delay
	Util_Sleep(5);

} // SimModsDown()
void CScripts::SimModsUp(void)
{
	UINT m_scanCtrl, m_scanAlt, m_scanShift, m_scanLWin;
	m_scanLWin = MapVirtualKey(VK_LWIN, 0);
	m_scanShift = MapVirtualKey(VK_SHIFT, 0);
	m_scanCtrl = MapVirtualKey(VK_CONTROL, 0);
	m_scanAlt = MapVirtualKey(VK_MENU, 0);

		// If the window is NULL use keybd_event
		if ( m_nKeyMod & ALTMOD ) 				// ALT required?
			keybd_event(VK_MENU, m_scanAlt, KEYEVENTF_KEYUP, 0);
		if ( m_nKeyMod & CTRLMOD ) 				// CTRL required?
			keybd_event(VK_CONTROL, m_scanCtrl, KEYEVENTF_KEYUP, 0);
		if ( m_nKeyMod & SHIFTMOD ) 			// SHIFT required?
			keybd_event(VK_SHIFT, m_scanShift, KEYEVENTF_KEYUP, 0);
		if ( m_nKeyMod & LWINMOD ) 				// WIN required?
			keybd_event(VK_LWIN, m_scanLWin, KEYEVENTF_KEYUP, 0);

	// Key up keydelay
	Util_Sleep(5);

} // SimModsUp()
void CScripts::SimKeystroke(UINT vk, bool bForceExtended)
{

	SimKeyDown(vk, bForceExtended);
	Util_Sleep(1);							// Hold key down

	SimKeyUp(vk, bForceExtended);
	Util_Sleep(5);							// Delay before next key stroke

} // SimKeystroke()
void CScripts::SendVk(UINT vk, int nRep, bool bExtended)
{
	// NOTE ch is a VK_CODE already

	// Resolve any key modifiers
	ResolveKeyModifiers(NONEMOD);

	SimModsDown();

	while (nRep)
	{
		SimKeystroke(vk, bExtended );			// Do the key(s)
		nRep --;
	}

	SimModsUp();

} // SendVk()
void CScripts::SendCh(char ch, int nRep)
{
	UINT	vkres;

	vkres = VkKeyScan(ch);						// get VK code and modifier info

	// Was a valid code obtained?  If not try and send it using special means
	// In these cases we IGNORE any modifiers as they won't work anyway with
	// the methods we use to send special chars
	if ( (int)vkres == -1)
	{
		SendSpecialCh(ch);
		return;
	}

	// Resolve any key modifiers with perm key downs and merges into m_nKeyMods
	ResolveKeyModifiers(vkres);

	// press the modifier keys required
	SimModsDown();

	while (nRep)
	{
		SimKeystroke((BYTE)(vkres & 0xff));		// Do the key (with automatic key delay)
		nRep--;
	}

	SimModsUp();

} // SendCh
void CScripts::SendSpecial(char *szTemp)
{
	int		nRep;
	int		nPos	= 0;
	int		n		= 0;
	bool	bUp		= false;
	bool	bDown	= false;
	bool	bOn		= false;
	bool	bOff	= false;

	char	*szCmd;
	char	*szRep;

	UINT m_scanCtrl, m_scanAlt, m_scanShift, m_scanLWin;
	m_scanLWin = MapVirtualKey(VK_LWIN, 0);
	m_scanShift = MapVirtualKey(VK_SHIFT, 0);
	m_scanCtrl = MapVirtualKey(VK_CONTROL, 0);
	m_scanAlt = MapVirtualKey(VK_MENU, 0);

	// Allocate temp memory
	szCmd = new char[strlen(szTemp)+1];
	szRep = new char[strlen(szTemp)+1];

	nRep = 1;									// Default number of repeats

	if ( !ReadToChar(' ', szTemp, szCmd, nPos) )
	{
		// Skip spaces to get to the number of repeats or "up", "down"
		while (szTemp[nPos] == ' ' || szTemp[nPos] == '\t')
			nPos++;

		ReadToChar('\0', szTemp, szRep, nPos);

		if (!_stricmp(szRep, "up"))
			bUp = true;
		else if (!_stricmp(szRep, "down"))
			bDown = true;
		else if (!_stricmp(szRep, "on"))
			bOn = true;
		else if (!_stricmp(szRep, "off"))
			bOff = true;
		else
		{
			nRep = atoi(szRep);
			if (nRep <= 0)
				nRep = 1;
		}
	}

	// Look up the index of the key
	while ( (n < NUMKEYS) && (_stricmp(g_szKeyTable[n], szCmd)) )
		n++;

	// if unknown command, send the first letter
	if (n == NUMKEYS)
	{
		if (bDown)
			SimKeyDown(VkKeyScan(szCmd[0]) & 0xff);
		else if (bUp)
			SimKeyUp(VkKeyScan(szCmd[0]) & 0xff);
		else
			SendCh(szCmd[0], nRep);				// unknown command, send first char
	}
	else
	{
		// the command HAS been found if we are here...
		// n is the index
		// check if this is a simple lookup or a special function
		if (g_cKeyLookupType[n] == SK_LOOKUP)
		{
			if (bDown)
				SimKeyDown(g_nKeyCodes[n]);
			else if (bUp)
				SimKeyUp(g_nKeyCodes[n]);
			else if (bOn)
				SetToggleState(g_nKeyCodes[n], true);
			else if (bOff)
				SetToggleState(g_nKeyCodes[n], false);
			else
				SendVk(g_nKeyCodes[n], nRep);
		}
		else
		{
			// Special function
			switch ( g_nKeyCodes[n] )
			{
				case ALT:
					if ( !(m_nKeyMod & ALTPERMMOD) )
					{
						m_nKeyMod |= ALTMOD;// We have to use Mods to get the ALT SYSKEY in SendTo mode

						if (bDown)
							SimKeyDown(VK_MENU);
						else if (bUp)
							SimKeyUp(VK_MENU);
						else
							SimKeystroke(VK_MENU);
					}

					break;

				case NUMPADENTER:
					// This is the same as VK_RETURN but we set the extended key code
					// to indicate that it is on the numpad and not main keyboard
					if (bDown)
						SimKeyDown(VK_RETURN);
					else if (bUp)
						SimKeyUp(VK_RETURN);
					else
						SimKeystroke(VK_RETURN, true);
					break;

				case ALTDOWN:
					if ( !(m_nKeyMod & ALTPERMMOD) )
					{
						m_nKeyMod |= ALTMOD;// We have to use Mods to get the ALT SYSKEY in SendTo mode

						m_nKeyMod |= ALTPERMMOD;
						SimKeyDown(VK_MENU);
					}
					break;

				case ALTUP:
					if ( m_nKeyMod & ALTPERMMOD)
					{
						m_nKeyMod |= ALTMOD;// We have to use Mods to get the ALT SYSKEY in SendTo mode

						m_nKeyMod ^= ALTPERMMOD;
						SimKeyUp(VK_MENU);
					}
					break;

				case SHIFTDOWN:
					if ( !(m_nKeyMod & SHIFTPERMMOD) )
					{
						m_nKeyMod |= SHIFTPERMMOD;
						SimKeyDown(VK_SHIFT);
					}
					break;

				case SHIFTUP:
					if ( m_nKeyMod & SHIFTPERMMOD)
					{
						m_nKeyMod ^= SHIFTPERMMOD;
						SimKeyUp(VK_SHIFT);
					}
					break;

				case CTRLDOWN:
					if ( !(m_nKeyMod & CTRLPERMMOD) )
					{
						m_nKeyMod |= CTRLPERMMOD;
						SimKeyDown(VK_CONTROL);
					}
					break;

				case CTRLUP:
					if ( m_nKeyMod & CTRLPERMMOD)
					{
						m_nKeyMod ^= CTRLPERMMOD;
						SimKeyUp(VK_CONTROL);
					}
					break;

				case LWINDOWN:
					if ( !(m_nKeyMod & LWINPERMMOD) )
					{
						m_nKeyMod |= LWINPERMMOD;
						SimKeyDown(VK_LWIN);
					}
					break;

				case LWINUP:
					if ( m_nKeyMod & LWINPERMMOD)
					{
						m_nKeyMod ^= LWINPERMMOD;
						SimKeyUp(VK_LWIN);
					}
					break;

				case RWINDOWN:
					if ( !(m_nKeyMod & RWINPERMMOD) )
					{
						m_nKeyMod |= RWINPERMMOD;
						SimKeyDown(VK_RWIN);
					}
					break;

				case RWINUP:
					if ( m_nKeyMod & RWINPERMMOD)
					{
						m_nKeyMod ^= RWINPERMMOD;
						SimKeyUp(VK_RWIN);
					}
					break;


				case ASC:
					// convert nRep to text and send the chars with ALT held down
					// For this to work we need to use a keybd_event
					// keystroke for the ALT key

					// If in SendTo mode this will fail unless we have the controls parent window
					// active :( - Removed 3.0.103 - Probably not a useful thing to force
					//if (m_hWnd && GetForegroundWindow() != GetParent(m_hWnd) && GetParent(m_hWnd) != NULL)
					//{
						//MessageBox(NULL, "", "", MB_OK);
						//g_oSetForeWinEx.Activate(GetParent(m_hWnd));
						//::Sleep(250);
					//	break;
					//}

					if ( !(m_nKeyMod & ALTPERMMOD) )
					{
						keybd_event(VK_MENU, m_scanAlt, 0, 0);
						Util_Sleep(1);
					}

					// ASCII 0 is 48, NUMPAD0 is 96, add on 48 to the ASCII
					n = 0;
					while (szRep[n] != '\0')
					{
						SimKeystroke(szRep[n]+48);	// Auto key delays
						n++;
					}

					if ( !(m_nKeyMod & ALTPERMMOD) )
					{
						keybd_event(VK_MENU, m_scanAlt, KEYEVENTF_KEYUP, 0);
						Util_Sleep(5);
					}

					break;

				} // End Switch

			} // End If

	} // End If

	// Clean up temp memory
	delete []szCmd;
	delete []szRep;

} // SendSpecial()
void CScripts::SendSpecialCh(char ch)
{
// Table to convert char >=128 to {Asc nnn} or to a diadic + letter
// the comment above the value show as € due to Courier Font but they are real Ansi chars
// 0 means no translation = try using the ALT+0nnn syntax
// value >127 (x7f) will be the translated value sent by ALT+nnn (not ALT+0nnn)
// value <128 define the diadic 0-3 bits index in g_cDiadic[] : if ' '  will not be sent
//								4-7 bits index in g_cDiadicLetter[]
	static char cAnsiToAscii [128] =
	{
// 80   €            ‚      ƒ      „      …      †      ‡      ˆ      ‰      Š      ‹      Œ            Ž      
     '\x80','\x81','\x82','\x83','\x84','\x85','\x86','\x87','\x88','\x89','\x8a','\x8b','\x8c','\x8d','\x8e','\x8f',

// 90         ‘      ’      “      ”     •:f9    –      —      ˜      ™      š      ›      œ            ž      Ÿ
     '\x90','\x91','\x92','\x93','\x94','\x95','\x96','\x97','\x98','\x99','\x9a','\x9b','\x9c','\x9d','\x9e','\x9f',

// A0          ¡      ¢      £      ¤      ¥      ¦      §      ¨      ©      ª      «      ¬      ­      ®      ¯
     '\xa0','\xa1','\xa2','\xa3','\xa4','\xa5','\xa6','\x15','\xa8','\xa9','\xaa','\xab','\xac','\xad','\xae','\xaf',

// B0   °      ±      ²      ³      ´      µ      ¶      ·      ¸      ¹      º      »      ¼      ½      ¾      ¿
     '\xb0','\xb1','\xb2','\xb3','\xb4','\xb5','\x14','\xb7','\xb8','\xb9','\xba','\xbb','\xbc','\xbd','\xbe','\xbf',

// C0   À      Á      Â      Ã      Ä      Å      Æ      Ç      È      É      Ê      Ë      Ì      Í      Î      Ï
     '\x62','\x22','\x32','\x42','\xc4','\xc5','\xc6','\xc7','\x64','\xc9','\x34','\x54','\x66','\x26','\x36','\x56',

// D0   Ð      Ñ      Ò      Ó      Ô      Õ      Ö      ×      Ø      Ù      Ú      Û      Ü      Ý      Þ      ß
     '\xd0','\xd1','\x68','\x28','\x38','\x48','\xd6','\xd7','\xd8','\x6a','\x2a','\x3a','\xdc','\x2c','\xde','\xdf',

// E0   à      á      â      ã      ä      å      æ      ç      è      é      ê      ë      ì      í      î      ï
     '\xe0','\xe1','\xe2','\x41','\xe4','\xe5','\xe6','\xe7','\xe8','\xe9','\xea','\xeb','\xec','\xed','\xee','\xef',

// F0   ð      ñ      ò      ó      ô      õ      ö      ÷      ø      ù      ú      û      ü      ý      þ      ÿ
     '\xf0','\xf1','\xf2','\xf3','\xf4','\x47','\xf6','\xf7','\xf8','\xf9','\xfa','\xfb','\xfc','\x2b','\xfe','\xff'
	};

//                                      0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
	static char g_cDiadicLetter[16] = {' ','a','A','e','E','i','I','o','O','u','U','y','Y','n','N',' '};
	char szAsc[10];

	int i = (ch - 128) & 0xff;
	i = cAnsiToAscii[i] & 0xff;

	// Do the key simulation using {ASC nnn} - not {ASC 0nnn}
	// Only the char code between whose corresponding value
	// in cAnsiToAscii[] >=128 can be sent directly
	if ( i>=128 || i<32 )
	{
		sprintf_s(szAsc, "ASC 0%d", i);
		SendSpecial(szAsc);
		m_nKeyMod &= RESETMOD;		// reset modifiers
		return;
	}


	// Try the key simulation using diadic keystrokes
	char ch1,ch2;

	// pick up the diadic char according to cTradAnsiLetter
	// 0-3 part is the index in szDiadic defining the first character to be sent
	//        this implementation will allow to change the szDiadic value
	//			and if set to blank not to send the diadic char
	//			This will allow to treat without extra char when language keyboard
	//			does not support this diadic char Ex; ~ in german

	ch1 = g_cDiadic[i>>4];

	// If our keyboard doesn't support diadics then we have no choice but to send the
	// ALT+0nnn code instead!
	if (ch1 == ' ')
	{
		// Doesn't support required diadic - i.e. english keyboards
		sprintf_s(szAsc, "ASC 0%d", (unsigned char)ch);
		SendSpecial(szAsc);
		m_nKeyMod &= RESETMOD;		// reset modifiers
	}
	else
	{
		// Does support the diadic key
		SendCh(ch1, 1);						// send diadic character
		m_nKeyMod &= RESETMOD;				// reset modifiers

		ch2 = g_cDiadicLetter[i & 0x0f];
		SendCh(ch2,1 );						// send non accent character
		m_nKeyMod &= RESETMOD;				// reset modifiers
	}

} // SendSpecialCh()
bool CScripts::GetSingleVKandMods(const char *szString, UINT &vk, bool &bShift, bool &bControl, bool &bAlt, bool &bWin)
{
	int		nPos = 0;
	char	ch;
	char	*szTemp;
	bool	bRes = true;						// Success by default
	int		n = 0;

	// Reset mods
	bShift = bControl = bAlt = bWin = false;

	// Allocate some temporary memory for szTemp
	szTemp =  new char[strlen(szString)+1];


	while ( szString[nPos] == '+' || szString[nPos] == '^' || szString[nPos] == '!' || szString[nPos] == '#' )
	{
		// Is there a modifier requested?
		if (szString[nPos] == '+')
			bShift = true;
		else if (szString[nPos] == '^')
			bControl = true;
		else if (szString[nPos] == '!')
			bAlt = true;
		else if (szString[nPos] == '#')
			bWin = true;

		++nPos;									// Next char
	}


	ch = szString[nPos++];						// Get next char


	// Is the next char a { or a simple key?
	if (ch == '{')
	{
		// Special key
		if ( ReadToChar('}', szString, szTemp, nPos) )
			bRes = false;						// Failed - no close bracket
		else
		{
			// Lookup special codes-  Look up the index of the key
			while ( (n < NUMKEYS) && (_stricmp(g_szKeyTable[n], szTemp)) )
				n++;

			// Is it a known or valid key
			if (n == NUMKEYS)
			{
				bRes = false;							// Unknown
			}
			else
			{
				if (g_cKeyLookupType[n] != SK_LOOKUP)
					bRes = false;						// Invalid
				else
					vk = g_nKeyCodes[n];
			}
		}
	}
	else
	{
		// Simple char
		vk = VkKeyScan(ch);

		if ( (vk & 0x0200)  ) 					// CTRL required?
			bControl = true;

		if ( (vk & 0x0400) )					// ALT required?
			bAlt = true;

		if ( (vk & 0x0100) )					// SHIFT required?
			bShift = true;
	}

	// Make sure only the VK code (lower byte) is passed back (sans shift states)
	vk = vk & 0xff;

	// Free temp string memory
	delete [] szTemp;

	return bRes;

} // GetSingleVKandMods()
void CScripts::KeyPress(const char *szSendKeys)
{
	char	*szTemp;
	char	ch;
	int		nPos = 0;
	int		nPosTemp;
	bool	bCapsWasOn = false;

	// Allocate some temporary memory for szTemp
	szTemp =  new char[strlen(szSendKeys)+1];

	// First, store the state of capslock, then turn off
	bCapsWasOn = SetToggleState(VK_CAPITAL, false);

	// Send the keys, but watch out for the main script pausing/closing
	while ( (ch = szSendKeys[nPos]) != '\0' )
	{
		nPos++;									// Next key

		// is it a special?
		switch (ch)
		{
			case '!':
				m_nKeyMod = m_nKeyMod | ALTMOD;
				break;
			case '^':
				m_nKeyMod = m_nKeyMod | CTRLMOD;
				break;
			case '+':
				m_nKeyMod = m_nKeyMod | SHIFTMOD;
				break;
			case '#':
				m_nKeyMod = m_nKeyMod | LWINMOD;
				break;

			case '{':
				nPosTemp = nPos;
				if ( ReadToChar('}', szSendKeys, szTemp, nPos) )
				{
					// NO CLOSE BRACKET!!?!
					nPos = nPosTemp;
					SendCh('{', 1);
					break;
				}
				else
				{
					SendSpecial(szTemp);
					m_nKeyMod &= RESETMOD;		// reset modifiers
					break;
				}

			default:
				SendCh(ch, 1);
				m_nKeyMod &= RESETMOD;			// reset modifiers
				break;

		} // End Switch

	} // End While


	//  Restore caps lock state
		SetToggleState(VK_CAPITAL, bCapsWasOn);

	// Free temp string memory
	delete [] szTemp;


} // KeyPress()
int CScripts::HotKeySet(const char* Key, luabridge::LuaRef Func, lua_State* L)
{
	// Initialize Hotkey Thread
	if (!Initialized){
		Initialize();
		Initialized = true;
	}


	bool	bShift, bControl, bAlt, bWin;
	int		nFreeHandle;
	UINT	mods = 0;
	UINT	vk;
	LPARAM	lParam;


	// Get the virtual key code and modifiers
	if (GetSingleVKandMods(Key, vk, bShift, bControl, bAlt, bWin) == false)
		 return 0; 		// Error

	if (bShift)
		mods |= MOD_SHIFT;
	if (bControl)
		mods |= MOD_CONTROL;
	if (bAlt)
		mods |= MOD_ALT;
	if (bWin)
		mods |= MOD_WIN;


	// Create an WM_HOTKEY compatible lParam for the modifiers and the VK
	lParam = (vk << 16) | mods;

	/*
	// Is this a duplicate or an unset (Function is blank)
	for (nFreeHandle = 0; nFreeHandle < MAXHOTKEYS; ++nFreeHandle)
	{

		if (m_HotKeyDetails[nFreeHandle] != NULL)
		{
			if (m_HotKeyDetails[nFreeHandle]->lParam == lParam)
			{
				// Are we reusing or unregistering?
				MessageBox(0,"Are we reusing or unregistering?","",0);
				if (Func == NULL)
				{
					UnregisterHotKey(wHandle[nFreeHandle], (int)m_HotKeyDetails[nFreeHandle]->wParam);	// Unregister
					delete m_HotKeyDetails[nFreeHandle];									// Delete memory
					m_HotKeyDetails[nFreeHandle] = NULL;									// Mark as empty
				}
				else
				{
					m_HotKeyDetails[nFreeHandle]->lFunction = &Func;	// Reuse
				}
				return 1;
			}
		}
	}
	*/

	// If we are here and Function == NULL (want to unregister) then we failed to find our
	// key to unregister in the code above == error
	if (Func == NULL)
		return 1;


	// Find a free handle
	for (nFreeHandle = 0; nFreeHandle < MAXHOTKEYS; ++nFreeHandle)
	{
		if (m_HotKeyDetails[nFreeHandle] == NULL)
		{
			rFunc[nFreeHandle] = new luabridge::LuaRef(L);
			*rFunc[nFreeHandle] = Func;
			m_HotKeyDetails[nFreeHandle] = new HotKeyDetails();	// Create new entry
			m_HotKeyDetails[nFreeHandle]->wParam = 0x0000 + nFreeHandle;
			m_HotKeyDetails[nFreeHandle]->lParam = lParam;
			m_HotKeyDetails[nFreeHandle]->lFunction = rFunc[nFreeHandle];

			Temp.ID = (int)m_HotKeyDetails[nFreeHandle]->wParam;
			Temp.Mods = mods;
			Temp.vk = vk;
			Temp.FreeHandle = nFreeHandle;
			
			bNeedToRegister = true;

			while (!bRegisterFinished)
				Sleep(50);

			return 1;		// Return (sucessfull or not)
		}
	}

	return 0;

} // HotKeySet()
bool CScripts::HandleHotKey(void)
{
	// See if there is a hotkey request in the queue - only process one per loop!
	if (m_nHotKeyQueuePos == g_HotKeyNext)
		return false;

	// What ID is the hotkey pressed?  Also increment the position and reset if needed
	WPARAM wParam = g_HotKeyQueue[m_nHotKeyQueuePos++];
	if (m_nHotKeyQueuePos >= MAXHOTKEYS)
		m_nHotKeyQueuePos = 0;					// reset

	// Find the corresponding hotkey definition and function
	int		n;

	for (n = 0; n < MAXHOTKEYS; ++n)
	{
		if (m_HotKeyDetails[n] != NULL && m_HotKeyDetails[n]->wParam == wParam)
			break;
	}
	if (n == MAXHOTKEYS)
		return false;							// Not found the ID! Ignore

	luabridge::LuaRef FuncRef = *m_HotKeyDetails[n]->lFunction;

	FuncRef();									// Call user defined function

	return true;								// Returning true will stop further

} // HandleHotKey()
void WINAPI CreateWndForHotkey(LPVOID)
{	
	try
	{
	MSG messages;
	WNDCLASSEX wcx; 

	char Name[] = "Lua Engine HotKey";

    wcx.cbSize = sizeof(wcx);          // size of structure 
    wcx.style = CS_HREDRAW | 
        CS_VREDRAW;                    // redraw if size changes 
    wcx.lpfnWndProc = WndProc;		   // points to window procedure 
    wcx.cbClsExtra = 0;                // no extra class memory 
    wcx.cbWndExtra = 0;                // no extra window memory 
    wcx.hInstance = DllModule;         // handle to instance 
    wcx.hIcon = LoadIcon(NULL, 
        IDI_APPLICATION);              // predefined app. icon 
    wcx.hCursor = LoadCursor(NULL, 
        IDC_ARROW);                    // predefined arrow
    wcx.lpszMenuName =  NULL;	   // name of menu resource 
	wcx.lpszClassName = Name;	   // name of window class 

 
    // Register the window class. 
 
	if (!RegisterClassExA(&wcx))
	{
		bRegisterFinished = true;
		return;
	}

	HWND Parent = FindWindow("Warcraft III", NULL);

	wHandle = CreateWindow( 
	Name,				 // name of window class 
	Name,				 // title-bar string 
	WS_CHILD,			 // child window 
	CW_USEDEFAULT,       // default horizontal position 
	CW_USEDEFAULT,       // default vertical position 
	CW_USEDEFAULT,       // default width 
	CW_USEDEFAULT,       // default height 
	Parent,				 // owner window 
	(HMENU) NULL,        // use class menu 
	DllModule,			 // handle to application instance 
	(LPVOID) NULL);      // no window-creation data 


	if (!wHandle)
	{
		bRegisterFinished = true;
		return;
	} 		


	for ( ;; )
	{
		if (bNeedToRegister)
		{
			RegisterHotKey(wHandle, Temp.ID, Temp.Mods, Temp.vk);
			bNeedToRegister = false;
			bRegisterFinished = true;
		}

		if (PeekMessage(&messages, wHandle, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&messages);
			DispatchMessage(&messages);
		}

	Sleep(5);
	}

	} // Try
	catch(...){}
		return;
	
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch(msg)
    {
        case WM_HOTKEY:
			g_HotKeyQueue[g_HotKeyNext++] = wParam;     // Store the hotkey ID pressed
			if (g_HotKeyNext >= MAXHOTKEYS)
				g_HotKeyNext = 0;
			Obj->HandleHotKey();
			Obj->Util_Sleep(500);
    }

    return DefWindowProc(hwnd,msg,wParam,lParam); 
}
