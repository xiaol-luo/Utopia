#include <stdio.h>
#include "Utils/ConfigUtil.h"
#include "ServerLogics/Game/GameServerLogic.h"
#include "event2/event.h"
// #include <vld.h>
#include <signal.h>
#include "MemoryPool/MemoryPoolMgr.h"
#include "Common/Utils/MemoryUtil.h"
#include "ShareCode/Network/Utils/LenCtxStreamParserEx.h"
#include <stdint.h>
#include "MemoryPool/StlAllocator.h"
#include "Utils/LuaUtils.h"

#include <sol.hpp>

extern ServerLogic *server_logic;

void QuitGame(int signal)
{
	if (nullptr != server_logic)
		server_logic->Quit();
}

lua_State *L;

void TestSol(lua_State *l)
{
	sol::state_view lua(l);
	sol::protected_function_result ret;
	{
		int x = 0;
		lua.set_function("beep", [&x] { ++x; });
		lua.script("beep()");
		printf("c++ beep result %d\n", x);
	}
	
	ret = lua.script_file("LuaScript/test_sol.lua");
}

void test(int a, float b)
{
	
}

namespace SolLuaBind
{
	extern void SolLuaBind(lua_State *L);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("cmd foramt : executable setting_file \n");
		exit(1);
	}

	MemoryUtil::Init();
	LuaUtils::Init();
	sol::state_view lsv(LuaUtils::luaState);
	SolLuaBind::SolLuaBind(LuaUtils::luaState);

	std::vector<std::string, StlAllocator<std::string>> params;
	std::string loadLuaCfgFile;
	{
		std::string settingPath = argv[1];
		sol::protected_function_result pfr = lsv.script_file(settingPath, LuaUtils::ErrorFn);
		if (!pfr.valid())
		{
			sol::error e = pfr;
			printf("error: %s", e.what());
			exit(2);
		}

		const char *LOG_CONFIG_FILE = "LogConfigFile";
		const char *CONFIG_DIR = "ConfigDir";
		const char *LOAD_LUA_CONFIG_FILE = "LoadLuaConfigFile";

		loadLuaCfgFile = lsv[LOAD_LUA_CONFIG_FILE];
		std::string logConfigFile = lsv[LOG_CONFIG_FILE];
		std::string configDir = lsv[CONFIG_DIR];
		assert(!logConfigFile.empty() && !configDir.empty());
		params.push_back(logConfigFile);
		params.push_back(configDir);
	}

#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
	signal(SIGINT, QuitGame);
	signal(SIGBREAK, QuitGame);
#else
	signal(SIGINT, QuitGame);
	signal(SIGPIPE, SIG_IGN);
#endif

	std::srand(time(NULL));


	server_logic = new GameServerLogic();
	server_logic->SetInitParams(&params);
	server_logic->Loop();
	delete server_logic;
	LuaUtils::Uninit();
	MemoryUtil::Destroy();
}