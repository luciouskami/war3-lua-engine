#pragma once

struct sCreateHotKey
{
	int ID;
	UINT Mods;
	UINT vk;
	int FreeHandle;
};


extern HMODULE DllModule;
extern HWND wHandle;
extern WPARAM			g_HotKeyQueue[64];	// Queue for hotkeys pressed
extern int				g_HotKeyNext;				// Next free hotkey position in queue

extern bool bNeedToRegister;
extern bool bRegisterFinished;