// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma message("Compiling precompiled header.\n")

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <string>


// TODO: reference additional headers your program requires here

#include "LuaJIT\src\lua.hpp"
#include "LuaBridge\LuaBridge.h"
#include "Variables.h"
