#pragma once
#include "stdafx.h"
#include "Game.h"

struct CJassStringData {
	DWORD vtable;
	DWORD refCount;
	DWORD dwUnk1;
	DWORD pUnk2;
	DWORD pUnk3;
	DWORD pUnk4;
	DWORD pUnk5;
	char *data;
};

struct CJassString {
	DWORD vtable;
	DWORD dw0;
	CJassStringData *data;
	DWORD dw1;
};

union DWFP
{
	DWORD dw;
	float fl;
};

typedef DWORD CODE;
typedef DWORD HUNIT;
typedef DWORD HWIDGET;
typedef DWORD HLIGHTNING;
typedef DWORD HPLAYER;
typedef DWORD HEFFECT;
typedef DWORD HLOCATION;
typedef DWORD HEFFECTTYPE;
typedef DWORD HRECT;
typedef DWORD HWEATHEREFFECT;
typedef DWORD HCAMERAFIELD;
typedef DWORD HBOOLEXPR;
typedef DWORD HSOUND;
typedef DWORD HCAMERASETUP;
typedef DWORD HITEMTYPE;
typedef DWORD HCONDITIONFUNC;
typedef DWORD HAIDIFFICULTY;
typedef DWORD HALLIANCETYPE;
typedef DWORD HATTACKTYPE;
typedef DWORD HBLENDMODE;
typedef DWORD HDAMAGETYPE;
typedef DWORD HDIALOGEVENT;
typedef DWORD HFGAMESTATE;
typedef DWORD HFOGSTATE;
typedef DWORD HGAMEDIFFICULTY;
typedef DWORD HGAMEEVENT;
typedef DWORD HGAMESPEED;
typedef DWORD HGAMETYPE;
typedef DWORD HIGAMESTATE;
typedef DWORD HLIMITOP;
typedef DWORD HMAPCONTROL;
typedef DWORD HMAPDENSITY;
typedef DWORD HMAPFLAG;
typedef DWORD HMAPSETTING;
typedef DWORD HMAPVISIBILITY;
typedef DWORD HPATHINGTYPE;
typedef DWORD HPLACEMENT;
typedef DWORD HPLAYERCOLOR;
typedef DWORD HPLAYEREVENT;
typedef DWORD HPLAYERGAMERESULT;
typedef DWORD HPLAYERSCORE;
typedef DWORD HPLAYERSLOTSTATE;
typedef DWORD HPLAYERSTATE;
typedef DWORD HPLAYERUNITEVENT;
typedef DWORD HRACE;
typedef DWORD HRACEPREFERENCE;
typedef DWORD HRARITYCONTROL;
typedef DWORD HSOUNDTYPE;
typedef DWORD HSTARTLOCPRIO;
typedef DWORD HTEXMAPFLAGS;
typedef DWORD HUNITEVENT;
typedef DWORD HUNITSTATE;
typedef DWORD HUNITTYPE;
typedef DWORD HVERSION;
typedef DWORD HVOLUMEGROUP;
typedef DWORD HWEAPONTYPE;
typedef DWORD HWIDGETEVENT;
typedef DWORD HDESTRUCTABLE;
typedef DWORD HDEFEATCONDITION;
typedef DWORD HFOGMODIFIER;
typedef DWORD HFORCE;
typedef DWORD HGROUP;
typedef DWORD HIMAGE;
typedef DWORD HITEM;
typedef DWORD HITEMPOOL;
typedef DWORD HLEADERBOARD;
typedef DWORD HMULTIBOARD;
typedef DWORD HQUEST;
typedef DWORD HREGION;
typedef DWORD HTEXTTAG;
typedef DWORD HTIMER;
typedef DWORD HTIMERDIALOG;
typedef DWORD HTRACKABLE;
typedef DWORD HTRIGGER;
typedef DWORD HUBERSPLAT;
typedef DWORD HUNITPOOL;
typedef DWORD HFILTERFUNC;
typedef DWORD HDIALOG;
typedef DWORD HBUTTON;
typedef DWORD HHASHTABLE;
typedef DWORD HGAMECACHE;
typedef DWORD HGAMESTATE;
typedef DWORD HHANDLE;
typedef DWORD HABILITY;
typedef DWORD HEVENTID;
typedef DWORD HQUESTITEM;
typedef DWORD HMULTIBOARDITEM;
typedef DWORD HTRIGGERACTION;
typedef DWORD HTRIGGERCONDITION;
typedef DWORD HEVENT;
typedef DWORD HAGENT;
typedef DWORD HTERRAINDEFORMATION;
typedef DWORD HJSSTRING;



typedef void 	(__cdecl *pDisplayTimedTextToPlayer)			(HPLAYER hPlayer, float* x, float* y, float* Duration, CJassString* Text);
extern pDisplayTimedTextToPlayer	DisplayTimedTextToPlayer;

typedef HPLAYER 	(__cdecl *pGetLocalPlayer)					();
extern pGetLocalPlayer	GetLocalPlayer;

typedef void 	(__cdecl *pChangeLevel)							(CJassString* newLevel, bool doScoreScreen);
extern pChangeLevel	ChangeLevel;

typedef void 	(__cdecl *pPingMinimap)							(float* x, float* y, float* duration);
extern pPingMinimap	PingMinimap;

typedef void 	(__cdecl *pPingMinimapEx)						(float* x, float* y, float* duration, int red, int green, int blue, bool extraEffects);
extern pPingMinimapEx	PingMinimapEx;

typedef bool 	(__cdecl *pIsUnitVisible)						(HUNIT hUnit, HPLAYER hPlayer);
extern pIsUnitVisible	IsUnitVisible;

typedef void 	(__cdecl *pSelectUnit)							(HUNIT hUnit, bool flag);
extern pSelectUnit	SelectUnit;

typedef HUNIT 	(__cdecl *pGetTriggerUnit)						();
extern pGetTriggerUnit	GetTriggerUnit;

typedef HPLAYER 	(__cdecl *pGetOwningPlayer)					(HUNIT hUnit);
extern pGetOwningPlayer	GetOwningPlayer;

typedef HPLAYERCOLOR 	(__cdecl *pGetPlayerColor)				(HPLAYER hPlayer);
extern pGetPlayerColor	GetPlayerColor;

typedef HDIALOG 	(__cdecl *pDialogCreate)					();
extern pDialogCreate	DialogCreate;

typedef void 	(__cdecl *pDialogDisplay)						(HPLAYER hPlayer , HDIALOG hDialog , bool flag);
extern pDialogDisplay	DialogDisplay;

typedef void 	(__cdecl *pDialogSetMessage)					(HDIALOG hDialog , CJassString *Message);
extern pDialogSetMessage	DialogSetMessage;

typedef HBUTTON 	(__cdecl *pDialogAddQuitButton)				(HDIALOG hDialog , bool ShowScoreScreen , CJassString *ButtonText , int Hotkey);
extern pDialogAddQuitButton	DialogAddQuitButton;

typedef HBUTTON 	(__cdecl *pDialogAddButton)					(HDIALOG hDialog , CJassString *ButtonText , int Hotkey);
extern pDialogAddButton	DialogAddButton;

typedef void 	(__cdecl *pClearTextMessages)					();
extern pClearTextMessages	ClearTextMessages;

typedef HTEXTTAG 	(__cdecl *pCreateTextTag)					();
extern pCreateTextTag	CreateTextTag;

typedef void	(__cdecl *pSetTextTagText)						(HTEXTTAG hTextTag, CJassString* Text, float *height);
extern pSetTextTagText	SetTextTagText;

typedef void	(__cdecl *pSetTextTagPosUnit)					(HTEXTTAG hTextTag, int hUnit, float *heightOffset);
extern pSetTextTagPosUnit	SetTextTagPosUnit;

typedef void	(__cdecl *pSetTextTagColor)						(HTEXTTAG hTextTag, int red, int green, int blue, int alpha);
extern pSetTextTagColor	SetTextTagColor;

typedef void	(__cdecl *pSetTextTagVelocity)					(HTEXTTAG hTextTag, float *xvel, float *yvel);
extern pSetTextTagVelocity	SetTextTagVelocity;

typedef void	(__cdecl *pSetTextTagFadepoint)					(HTEXTTAG hTextTag, float *fadepoint);
extern pSetTextTagFadepoint	SetTextTagFadepoint;

typedef void	(__cdecl *pSetTextTagLifespan)					(HTEXTTAG hTextTag, float *lifespan);
extern pSetTextTagLifespan	SetTextTagLifespan;

typedef void	(__cdecl *pSetTextTagPermanent)					(HTEXTTAG hTextTag, bool flag);
extern pSetTextTagPermanent	SetTextTagPermanent;

typedef void	(__cdecl *pSetTextTagVisibility)				(HTEXTTAG hTextTag, bool flag);
extern pSetTextTagVisibility	SetTextTagVisibility;

typedef void 	(__cdecl *pClearSelection)						();
extern pClearSelection	ClearSelection;

typedef void 	(__cdecl *pPauseGame)							(bool flag);
extern pPauseGame	PauseGame;

typedef int 	(__cdecl *pGetHeroLevel)						(HUNIT hUnit);
extern pGetHeroLevel	GetHeroLevel;

typedef Float /* DWFP */ 	(__cdecl *pGetUnitX)				(HUNIT hUnit);
extern pGetUnitX	GetUnitX;

typedef Float /* DWFP */	(__cdecl *pGetUnitY)				(HUNIT hUnit);
extern pGetUnitY	GetUnitY;

typedef int 	(__cdecl *pGetPlayerId)							(HPLAYER hPlayer);
extern pGetPlayerId	GetPlayerId;

typedef bool 	(__cdecl *pIsUnitAlly)							(HUNIT hUnit, HPLAYER hPlayer);
extern pIsUnitAlly	IsUnitAlly;

typedef bool 	(__cdecl *pIsUnitEnemy)							(HUNIT hUnit, HPLAYER hPlayer);
extern pIsUnitEnemy	IsUnitEnemy;

typedef bool 	(__cdecl *pIsPlayerAlly)						(HPLAYER hPlayer1, HPLAYER hPlayer2);
extern pIsPlayerAlly	IsPlayerAlly;

typedef bool 	(__cdecl *pIsPlayerEnemy)						(HPLAYER hPlayer1, HPLAYER hPlayer2);
extern pIsPlayerEnemy	IsPlayerEnemy;

typedef bool 	(__cdecl *pIsPlayerObserver)					(HPLAYER hPlayer);
extern pIsPlayerObserver	IsPlayerObserver;

typedef HPLAYER 	(__cdecl *pPlayer)							(int Index);
extern pPlayer	Player;

typedef HRACE 	(__cdecl *pGetPlayerRace)						(HPLAYER hPlayer);
extern pGetPlayerRace	GetPlayerRace;

typedef HRACE 	(__cdecl *pDoNotSaveReplay)						();
extern pDoNotSaveReplay	DoNotSaveReplay;

typedef int 	(__cdecl *pGetPlayerState)						(HPLAYER hPlayer, HPLAYERSTATE hPlayerState);
extern pGetPlayerState	GetPlayerState;

typedef int 	(__cdecl *pGetPlayerScore)						(HPLAYER hPlayer, HPLAYERSCORE hPlayerState);
extern pGetPlayerScore	GetPlayerScore;

typedef bool 	(__cdecl *pIsVisibleToPlayer)					(float *x, float *y, HPLAYER hPlayer);
extern pIsVisibleToPlayer	IsVisibleToPlayer;

typedef bool 	(__cdecl *pIsFoggedToPlayer)					(float *x, float *y, HPLAYER hPlayer);
extern pIsFoggedToPlayer	IsFoggedToPlayer;

typedef bool 	(__cdecl *pIsMaskedToPlayer)					(float *x, float *y, HPLAYER hPlayer);
extern pIsMaskedToPlayer	IsMaskedToPlayer;

typedef HRACE 	(__cdecl *pConvertRace)							(int i);
extern pConvertRace	ConvertRace;

typedef HPLAYERSTATE 	(__cdecl *pConvertPlayerState)			(int i);
extern pConvertPlayerState	ConvertPlayerState;

typedef HPLAYERSCORE 	(__cdecl *pConvertPlayerScore)			(int i);
extern pConvertPlayerScore	ConvertPlayerScore;

typedef HPLAYERSLOTSTATE 	(__cdecl *pGetPlayerSlotState)		(HPLAYER hPlayer);
extern pGetPlayerSlotState	GetPlayerSlotState;

typedef HPLAYERSLOTSTATE 	(__cdecl *pConvertPlayerSlotState)	(int i);
extern pConvertPlayerSlotState	ConvertPlayerSlotState;

typedef HUNITSTATE 	(__cdecl *pConvertUnitState)				(int i);
extern pConvertUnitState	ConvertUnitState;

typedef Float 	(__cdecl *pGetUnitState)						(HUNIT hUnit, HUNITSTATE hUnitState);
extern pGetUnitState	GetUnitState;

typedef int 	(__cdecl *pGetUnitTypeId)						(HUNIT hUnit);
extern pGetUnitTypeId	GetUnitTypeId;

typedef HJSSTRING 	(__cdecl *pGetPlayerName)					(HPLAYER hPlayer);
extern pGetPlayerName	GetPlayerName;

typedef HJSSTRING 	(__cdecl *pGetUnitName)						(HUNIT hUnit);
extern pGetUnitName	GetUnitName;

typedef HJSSTRING 	(__cdecl *pGetItemName)						(HITEM hItem);
extern pGetItemName	GetItemName;

typedef INT 	(__cdecl *pGetItemCharges)						(HITEM hItem);
extern pGetItemCharges	GetItemCharges;
