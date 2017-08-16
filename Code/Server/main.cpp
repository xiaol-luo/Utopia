#include <stdio.h>
#include "Utils/ConfigUtil.h"
#include "ServerLogics/Game/GameServerLogic.h"

int main(int argc, char **argv)
{
	printf("hello world");

	int a = 0;
	ConfigUtil::Str2BaseValue("123", a);

	std::vector<std::string> params;
	params.push_back("F:/git-dir/Utopia/Data/Config/auto-csv/AutoCsvConfig/Log/CsvLogConfig.csv");
	params.push_back("F:/git-dir/Utopia/Data/Config/auto-csv/AutoCsvConfig");
	ServerLogic *game = new GameServerLogic();
	game->SetInitParams(&params);
	game->Loop();
}