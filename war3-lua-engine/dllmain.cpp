// dllmain.cpp : Defines the entry point for the DLL application.

#include "stdafx.h"
#include "war3_lua_engine.h"
#include <boost/filesystem.hpp>
#include "Scripts.h"
#include <Process.h>
#include "resource.h"

namespace fs = ::boost::filesystem;

VOID LoadScript( LPVOID Args )
{

	char* ScriptName = (char*) Args;

	lua_State* L = luaL_newstate ();

	luaL_openlibs (L);

	int errorFunctionRef = War3LuaEngine::addTraceback (L);

	War3LuaEngine::addToState (L);

	int status = luaL_loadfile(L, ScriptName);
	if (status != 0) {
		lua_close(L);
		delete [] ScriptName;
		return;
    }

//	luabridge::LuaRef init_function = luabridge::getGlobal(L, "Init");
//	if (!lua_isnil(L,init_function))
//		init_function();

	lua_close(L);
	delete [] ScriptName;
	return;
}

void GetScripts(const fs::path& root, const std::string& ext, std::vector<fs::path>& ret)
{  
  if (!fs::exists(root)) return;

  if (fs::is_directory(root))
  {

    fs::recursive_directory_iterator it(root);
    fs::recursive_directory_iterator endit;

    while(it != endit)
    {
      if (fs::is_regular_file(*it) && it->path().extension() == ext)
      {
        ret.push_back(it->path().filename());
      }
      ++it;
    }
  }
	  
}

VOID MainThread( LPVOID )
{
	while (GetModuleHandle("Game.dll") == NULL) Sleep(1000);
	Sleep(5000);

	int iScripts = 0;

	std::vector<fs::path> Result;
	fs::path Path("Scripts");
	GetScripts(Path,".lua",Result);
	iScripts = Result.size();

	if (iScripts <= 0) return;

	for (int i = 0; i < iScripts; i++)
	{
		char ScriptPath[MAX_PATH] = "Scripts\\";
		strcat_s(ScriptPath,Result[i].string().c_str());
		char * myvariable = new char[MAX_PATH];
		*myvariable=0;
		strncat_s(myvariable, sizeof(ScriptPath), ScriptPath,MAX_PATH); // this is equivalent to what the nonstandard strlcpy would do
		_beginthread(LoadScript,0, (LPVOID)myvariable);
	}

	return;
}

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DllModule = hModule;
		DisableThreadLibraryCalls(hModule);
		_beginthread(MainThread,0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
