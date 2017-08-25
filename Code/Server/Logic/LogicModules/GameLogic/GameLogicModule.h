#pragma once

// #include "google/protobuf/message.h"
#include "IGameLogicModule.h"
#include <vector>
#include <queue>
#include <functional>
#include "Network/Protobuf/msg.pb.h"

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
class Player;

class GameLogicModule;


namespace GameLogic
{
	class IClientMsgHandleDescript
	{
	public:
		IClientMsgHandleDescript() {}
		~IClientMsgHandleDescript() {}

		virtual void Handle(int protocol_id, google::protobuf::Message *msg, Player *player) = 0;
	};

	template <typename MsgType>
	class ClientMsgHandleDescript : public IClientMsgHandleDescript
	{
	public:
		using ProcessFuncType = void (GameLogicModule::*)(int, MsgType *, Player *);
		//using ProcessFuncType = std::function<void(int, MsgType *, Player *)>;
		ClientMsgHandleDescript(GameLogicModule *_game_module, int _protocol_id, ProcessFuncType _process)
		{
			game_module = _game_module;
			protocol_id = _protocol_id;
			process = _process;
			msg = new MsgType();
		}

		~ClientMsgHandleDescript()
		{
			delete msg;
			process = nullptr;
		}

		virtual void Handle(int protocol_id, google::protobuf::Message *input_msg, Player *player)
		{
			(game_module->*process)(protocol_id, dynamic_cast<MsgType *>(input_msg), player);
		}

		int protocol_id = 0;
		MsgType *msg = nullptr;
		ProcessFuncType process = nullptr;
		GameLogicModule *game_module = nullptr;
	};
}


class GameLogicModule : public IGameLogicModule
{
public:
	GameLogicModule(ModuleMgr *module_mgr);
	virtual ~GameLogicModule();
	virtual EModuleRetCode Init(void *param);
	virtual EModuleRetCode Awake();
	virtual EModuleRetCode Update();
	virtual EModuleRetCode Release();
	virtual EModuleRetCode Destroy();

private:
	Config::CsvConfigSets *m_csv_cfg_sets = nullptr;
	std::shared_ptr<ObjectBase> m_test_timer = nullptr;
	std::shared_ptr<NetListenHanderTest> m_test_listen_handler = nullptr;
	std::queue<std::shared_ptr<NetConnectHanderTest>> m_test_cnn_handlers;

	GameLogic::PlayerMgr *m_player_mgr = nullptr;
	LogModule *m_log_module = nullptr;
	ITimerModule *m_timer_module = nullptr;
	INetworkModule *m_network_module = nullptr;

	void HandlePlayerMsg(int protocol_id, google::protobuf::Message *msg, Player *player);

	GameLogic::IClientMsgHandleDescript *testClientMsgHandleDesc;

private:
	void OnTestHandlePlayerMsg(int protocol_id, Ping *msg, Player *player) {}
};

