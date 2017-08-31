#include <stdio.h>
#include "Utils/ConfigUtil.h"
#include "ServerLogics/Game/GameServerLogic.h"
#include "event2/event.h"
// #include <vld.h>
#include <signal.h>
#include "MemoryPool/MemoryPoolMgr.h"
#include "Common/Utils/MemoryUtil.h"
#include "ShareCode/Network/Handlers/TryTemplate.hpp"
#include <stdint.h>

ServerLogic *server_logic = nullptr;

void QuitGame(int signal)
{
	if (nullptr != server_logic)
		server_logic->Quit();
}

int main(int argc, char **argv)
{
	{
		UseLenPraser<uint32_t> xxx;
		UseLenPraser<uint32_t, NetSteamLenPraser<uint32_t, sizeof(uint32_t)>> yyy;
		char buffer[256];
		*(uint32_t *)buffer = 123;

		for (int i = 3; i < 9; ++i)
		{
			uint32_t len = 0;
			len = xxx.ParseNext(buffer, i);
			len = yyy.ParseNext(buffer, i);
			++len;
		}
	}

	{
		UseLenPraser<uint64_t> xxx;
		UseLenPraser<uint64_t, NetSteamLenPraser<uint64_t, sizeof(uint64_t)>> yyy;
		char buffer[256];
		*(uint64_t *)buffer = 123;

		for (int i = 3; i < 9; ++i)
		{
			uint64_t len = 0;
			len = xxx.ParseNext(buffer, i);
			len = yyy.ParseNext(buffer, i);
			++len;
		}
	}



	if (argc <= 2)
	{
		printf("cmd foramt : executable log_cfg_file cfg_dir\n");
		exit(1);
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

	MemoryUtil::Init();
	std::srand(time(NULL));
	std::vector<std::string> params;
	params.push_back(argv[1]);
	params.push_back(argv[2]);

	GameServerLogic *xxx = new GameServerLogic[5]();
	delete[]xxx;
	server_logic = new GameServerLogic();
	server_logic->SetInitParams(&params);
	server_logic->Loop();
	delete server_logic;
	MemoryUtil::Destroy();
}