#include "Windows.h"
#include "Variables.h"


HMODULE DllModule;
HWND wHandle;
// HotKey stuff
WPARAM			g_HotKeyQueue[64];	// Queue for hotkeys pressed
int				g_HotKeyNext;				// Next free hotkey position in queue

bool bNeedToRegister;
bool bRegisterFinished;