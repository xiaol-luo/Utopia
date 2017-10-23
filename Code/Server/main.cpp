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
	lua.open_libraries(sol::lib::base, sol::lib::debug);
	{
		int x = 0;
		lua.set_function("beep", [&x] { ++x; });
		lua.script("beep()");
		printf("c++ beep result %d\n", x);
	}
	
	ret = lua.script_file("LuaScript/test_sol.lua");
}

int main(int argc, char **argv)
{
	L = luaL_newstate();
	TestSol(L);
	lua_close(L); L = nullptr;

	if (argc <= 2)
	{
		printf("cmd foramt : executable log_cfg_file cfg_dir\n");
		exit(1);
	}

	MemoryUtil::Init();

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
	std::vector<std::string, StlAllocator<std::string>> params;
	params.push_back(argv[1]);
	params.push_back(argv[2]);


	server_logic = new GameServerLogic();
	server_logic->SetInitParams(&params);
	server_logic->Loop();
	delete server_logic;
	MemoryUtil::Destroy();
}