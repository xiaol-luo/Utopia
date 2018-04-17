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
#include "Utils/PlatformCompat.h"

extern ServerLogic *server_logic;
namespace SolLuaBind
{
	extern void SolLuaBind(lua_State *L);
}

void QuitGame(int signal)
{
	if (nullptr != server_logic)
		server_logic->Quit();
}

struct ParseArgsRet
{
	bool isOk = true;
	std::string reason;

	std::string workDir;
	std::string settingFile;
};

ParseArgsRet ParseArgs(int argc, char **argv)
{
	struct Fns
	{
		static void ReadWorkDir(const std::string &arg, ParseArgsRet &ret)
		{
			ret.workDir = arg;
		}
		static void CheckWorkDir(ParseArgsRet &ret)
		{
			if (ret.workDir.empty())
			{
				ret.isOk = false;
				ret.reason = "work dir is empty";
			}
		}
		static void ReadSettingFile(const std::string &arg, ParseArgsRet &ret)
		{
			ret.settingFile = arg;
		}
		static void CheckSettingFile(ParseArgsRet &ret)
		{
			if (ret.settingFile.empty())
			{
				ret.isOk = false;
				ret.reason = "setting file is empty";
			}
		}
	};
	using Fn = void (*)(const std::string &arg, ParseArgsRet &ret);
	using CheckFn = void(*)(ParseArgsRet &ret);
	struct OptFns
	{
		OptFns(Fn _fn, CheckFn _checkFn)
		{
			fn = _fn;
			checkFn = _checkFn;
		}
		Fn fn;
		CheckFn checkFn;
	};
	std::map<std::string, OptFns> optProcessFns = {
		{ "-wd", OptFns(Fns::ReadWorkDir, Fns::CheckWorkDir) },
		{ "-sf", OptFns(Fns::ReadSettingFile, Fns::CheckSettingFile) },
	};

	ParseArgsRet ret;
	OptFns *lastFns = nullptr;
	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		auto it = optProcessFns.find(arg);
		if (optProcessFns.end() != it)
		{
			lastFns = &it->second;
			continue;
		}
		if (nullptr == lastFns)
		{
			ret.isOk = false;
			ret.reason = "cmd format error!";
			break;
		}
		lastFns->fn(arg, ret);
		if (!ret.isOk)
			break;
	}
	if (ret.isOk)
	{
		for (auto &&it : optProcessFns)
		{
			it.second.checkFn(ret);
			if (!ret.isOk)
				break;
		}
	}
	return ret;
}

int main(int argc, char **argv)
{
	// parse argv
	ParseArgsRet parseArgsRet = ParseArgs(argc, argv);
	if (!parseArgsRet.isOk)
	{
		printf("ParseArgs fail, reason is %s", parseArgsRet.reason.c_str());
		exit(10);
	}

	// change work dir
	int ret = chdir(parseArgsRet.workDir.c_str());
	char pathBuf[1024] = { 0 };
	printf("current work dir is %s\n", getcwd(pathBuf, sizeof(pathBuf)));
	if (0 != ret)
	{
		printf("chdir fail ret %d, error %d %s\n", ret, errno, strerror(errno));
		exit(20);
	}

	MemoryUtil::Init();
	LuaUtils::Init();

	std::vector<std::string, StlAllocator<std::string>> params;
	{
		sol::state_view lsv(LuaUtils::luaState);
		std::string settingPath = parseArgsRet.settingFile;
		sol::protected_function_result pfr = lsv.script_file(settingPath, LuaUtils::ErrorFn);
		if (!pfr.valid())
		{
			sol::error e = pfr;
			printf("error: %s\n", e.what());
			exit(30);
		}

		{
			// params
			const char *ConfigTable = "ConfigTable";
			const char *LOG_CONFIG_FILE = "LogConfigFile";
			const char *CONFIG_DIR = "ConfigDir";

			sol::table cfgTable = lsv[ConfigTable];
			lsv[ConfigTable] = nullptr;
			std::string logConfigFile = cfgTable[LOG_CONFIG_FILE];
			std::string configDir = cfgTable[CONFIG_DIR];
			assert(!logConfigFile.empty() && !configDir.empty());
			params.push_back(logConfigFile);
			params.push_back(configDir);
		}

		{
			// load lua scripts
			SolLuaBind::SolLuaBind(LuaUtils::luaState);
			const char *LOAD_LUA_FILES = "LoadLuaFiles";
			sol::table luaFiles = lsv[LOAD_LUA_FILES];
			lsv[LOAD_LUA_FILES] = nullptr;
			for (auto kv_pair : luaFiles)
			{
				sol::object ss = kv_pair.second;
				std::string filePath = ss.as<std::string>();
				sol::protected_function_result ret = lsv.script_file(filePath, LuaUtils::ErrorFn);
				if (!ret.valid())
				{
					sol::error e = ret;
					printf("error: %s", e.what());
					exit(40);
				}
			}
		}
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