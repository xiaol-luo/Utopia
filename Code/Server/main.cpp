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

ServerLogic *server_logic = nullptr;

void QuitGame(int signal)
{
	if (nullptr != server_logic)
		server_logic->Quit();
}

int main(int argc, char **argv)
{
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