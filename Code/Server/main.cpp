#include <stdio.h>
#include "Utils/ConfigUtil.h"
#include "ServerLogics/Game/GameServerLogic.h"
#include "event2/event.h"
#include <vld.h>
#include <signal.h>

ServerLogic *game = nullptr;

void QuitGame(int signal)
{
	if (nullptr != game)
		game->Quit();
}

int main(int argc, char **argv)
{
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

	std::vector<std::string> params;
	params.push_back(argv[1]);
	params.push_back(argv[2]);
	game = new GameServerLogic();
	game->SetInitParams(&params);
	game->Loop();
	delete game;
}