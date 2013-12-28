#ifndef OFFSETS_H
#define OFFSETS_H

DWORD GetGameBase();
extern DWORD GameBase;

#define ADDPTR(NAME,VALUE) static DWORD  _##NAME = GetGameBase() + VALUE;

// CGame //
ADDPTR(GetLocation,0x4743A0)
ADDPTR(W3XPlayerData,0xAB65F4)
ADDPTR(W3XGlobalClass,0xAB4F80)
ADDPTR(GetHPlayerByNumber,0x3A1650)
ADDPTR(UnitSelect,0x381710)
ADDPTR(GetUnitArrayPtr,0x39B6E0)
ADDPTR(W3XTlsIndex,0xAB7BF4)
ADDPTR(IsUnitHero,0x33AA60)
ADDPTR(MoveAttackCmd,0x339DD0)
ADDPTR(MoveTargetCmd,0x339D50)
ADDPTR(UnitClass,0x931934)
ADDPTR(GetFloatStat,0x27AE90)
ADDPTR(PauseGameConst,0x9342F8)
ADDPTR(PauseGame,0x2F80A0)
ADDPTR(ResumeGameConst,0x934304)
ADDPTR(ResumeGame,0x2F7FE0)
ADDPTR(W3XConversion,0xAB7368)
ADDPTR(ConvertCoord1,0x6EEEF0)
ADDPTR(ConvertCoord2,0x6EEC20)
ADDPTR(W3XMinimap,0xAB6214)
ADDPTR(BigAssFloat,0x875AB8)
ADDPTR(MmapOffset,0x93A098)
ADDPTR(JSIDToPointer,0x459640)
ADDPTR(GetCurrentJassEnv,0x44B2E0)

// CJass //
ADDPTR(GetLocalPlayer,0x3BBB60);
ADDPTR(DisplayTimedTextToPlayer,0x3CB9B0);
ADDPTR(ChangeLevel,0x3BBC30);
ADDPTR(PingMinimap,0x3B4650);
ADDPTR(PingMinimapEx,0x3B8660);
ADDPTR(IsUnitVisible,0x3C7AF0);
ADDPTR(SelectUnit,0x3C7910);
ADDPTR(ClearSelection,0x3BBAA0);
ADDPTR(GetTriggerUnit,0x3BB240);
ADDPTR(GetOwningPlayer,0x3C8190);
ADDPTR(GetPlayerColor,0x3C1240);
ADDPTR(CreateTextTag,0x3BC580);
ADDPTR(SetTextTagText,0x3BC5D0);
ADDPTR(SetTextTagPosUnit,0x3CB890);
ADDPTR(SetTextTagColor,0x3BC6A0);
ADDPTR(SetTextTagVelocity,0x3BC700);
ADDPTR(SetTextTagFadepoint,0x3BC850);
ADDPTR(SetTextTagLifespan,0x3BC820);
ADDPTR(SetTextTagPermanent,0x3BC7C0);
ADDPTR(SetTextTagVisibility,0x3BC760);
ADDPTR(DialogCreate,0x3D2BC0);
ADDPTR(DialogDisplay,0x3CA030);
ADDPTR(DialogSetMessage,0x3C9F60);
ADDPTR(DialogAddQuitButton,0x3C9FE0);
ADDPTR(DialogAddButton,0x3C9F90);
ADDPTR(ClearTextMessages,0x3B4E60);
ADDPTR(JPauseGame,0x3BC4D0);
ADDPTR(GetHeroLevel,0x3C6ED0);
ADDPTR(GetUnitX,0x3C5510);
ADDPTR(GetUnitY,0x3C5550);
ADDPTR(GetPlayerId,0x3C9640);
ADDPTR(IsUnitAlly,0x3C7A70);
ADDPTR(IsUnitEnemy,0x3C7AD0);
ADDPTR(IsPlayerAlly,0x3C9530);
ADDPTR(IsPlayerEnemy,0x3C9580);
ADDPTR(IsPlayerObserver,0x3C9600);
ADDPTR(Player,0x3BBB30);
ADDPTR(GetPlayerRace,0x3C9620);
ADDPTR(DoNotSaveReplay,0x3B3550);
ADDPTR(GetPlayerState,0x3C9B00);
ADDPTR(GetPlayerScore,0x3C9B70);
ADDPTR(IsVisibleToPlayer,0x3C98F0);
ADDPTR(IsFoggedToPlayer,0x3C9980);
ADDPTR(IsMaskedToPlayer,0x3C9A10);
ADDPTR(ConvertRace,0x3B2600);
ADDPTR(ConvertPlayerState,0x3B2650);
ADDPTR(ConvertPlayerScore,0x3B2660);
ADDPTR(GetPlayerSlotState,0x3C12D0);
ADDPTR(ConvertPlayerSlotState,0x3B27D0);
ADDPTR(ConvertUnitState,0x3B2680);
ADDPTR(GetUnitState,0x3C5400);
ADDPTR(GetUnitTypeId,0x3C5910);
ADDPTR(GetPlayerName,0x3C0F60);
ADDPTR(GetUnitName,0x3C5950);
ADDPTR(GetItemName,0x3C4E90);
ADDPTR(GetItemCharges,0x3C5050);
#endif
