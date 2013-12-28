#pragma once
#include "stdafx.h"

#define ADDR(X,REG)\
	__asm MOV REG,DWORD PTR DS:[X] \
	__asm MOV REG,DWORD PTR DS:[REG]

static int GS_NOTHING = 0;
static int GS_LOBBY = 1;
static int GS_LOADING = 3;
static int GS_INGAME = 4;
static int GS_PAUSED = 6;

static int STAT_HP = 0;
static int STAT_MAXHP = 1;
static int STAT_MANA = 2;
static int STAT_MAXMANA = 3;

#define FLAG_ILLUSION 0x40000000;
#define FLAG_INVIS 0x1000000;
#define FLAG_DEAD 0x100;

static DWORD CMD_MOVE = 0xD0003;
static DWORD CMD_ATTACK = 0xD000F;
static DWORD CMD_HOLD = 0xD0019;	
static DWORD CMD_STOP = 0xD0004;

struct Unit
{
	DWORD dwDummy[3];
	DWORD dwID1;
	DWORD dwID2;
	BYTE _1[0x1C];
	DWORD dwClassId;
	BYTE _2[0x1C];
	DWORD HealthBar;
	DWORD UNK;
	DWORD dwOwnerSlot;
};

struct Location
{
	float X;
	float Y;
	float Z;
};

struct MmapLoc
{
	DWORD X;
	DWORD Y;
};

union Float
{
	float fl;
	DWORD dw;
};