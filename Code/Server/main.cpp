#include <stdio.h>
#include "Utils/ConfigUtil.h"
#include "ServerLogics/Game/GameServerLogic.h"

int main(int argc, char **argv)
{
	if (argc <= 2)
	{
		printf("cmd foramt : executable log_cfg_file cfg_dir\n");
		exit(1);
	}

	std::vector<std::string> params;
	// params.push_back("F:/git-dir/Utopia/Data/Config/auto-csv/AutoCsvConfig/Log/CsvLogConfig.csv");
	// params.push_back("F:/git-dir/Utopia/Data/Config/auto-csv/AutoCsvConfig");
	params.push_back(argv[1]);
	params.push_back(argv[2]);
	ServerLogic *game = new GameServerLogic();
	game->SetInitParams(&params);
	game->Loop();
}