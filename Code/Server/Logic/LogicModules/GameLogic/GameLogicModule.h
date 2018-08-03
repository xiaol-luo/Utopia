#pragma once

#include "google/protobuf/message.h"
#include "IGameLogicModule.h"
#include <functional>
#include <vector>
#include "Common/Macro/AllMacro.h"

namespace GameLogic 
{
	class PlayerMgr;
}
namespace Config
{
	struct CsvConfigSets;
}

class NetListenHanderTest;
class NetConnectHanderTest;
class ITimerModule;
class INetworkModule;
class LogModule;
class GameLogicModule;
class NetworkAgent;
class EventDispacherProxy;

namespace GameLogic
{
	class NewScene;
	class Player;
	class PlayerMsgHandler;
}

class GameLogicModule : public IGameLogicModule
{
	friend GameLogic::PlayerMsgHandler;

	NewDelOperaDeclaration;
public:
	GameLogicModule(ModuleMgr *module_mgr);
	virtual ~GameLogicModule();
	virtual EModuleRetCode Init(void *param);
	virtual EModuleRetCode Awake();
	virtual EModuleRetCode Update();
	virtual EModuleRetCode Release();
	virtual EModuleRetCode Destroy();

	void HandlePlayerMsg(char *data, uint32_t data_len, GameLogic::Player *player);
	const std::string & GetCfgRootPath() { return m_cfg_root_path; }
	Config::CsvConfigSets * GetCsvCfgSet() { return m_csv_cfg_sets; }
	GameLogic::PlayerMgr * GetPlayerMgr() { return m_player_mgr; }
	void ReloadConfig();

private:
	Config::CsvConfigSets *m_csv_cfg_sets = nullptr;
	GameLogic::PlayerMgr *m_player_mgr = nullptr;
	GameLogic::PlayerMsgHandler *m_player_msg_handler = nullptr;
	GameLogic::NewScene *m_new_scene = nullptr;
	std::string m_cfg_root_path;
	std::vector<Config::CsvConfigSets *> m_expired_csv_cfg_sets;
	EventDispacherProxy *m_ev_proxy = nullptr;

	GameLogic::NewScene * CreateScene(std::string scene_type);

	void GmRecreateScene(std::string scene_type);
};

