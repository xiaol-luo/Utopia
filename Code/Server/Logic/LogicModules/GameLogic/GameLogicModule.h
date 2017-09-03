#pragma once

#include "google/protobuf/message.h"
#include "IGameLogicModule.h"
#include <functional>
#include "Common/Macro/MemoryPoolMacro.h"

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
class Ping;
class Pong;
class NetworkAgent;

namespace GameLogic
{
	class Player;

	class IClientMsgHandlerDescript
	{
	public:
		IClientMsgHandlerDescript() {}
		virtual ~IClientMsgHandlerDescript() {}
		inline int Id() { return protocol_id; }
		inline virtual google::protobuf::Message *Msg() = 0;
		inline virtual void Handle(int protocol_id, google::protobuf::Message *msg, Player *player) = 0;

	protected:
		int protocol_id = 0;
	};

	template <typename MsgType>
	class ClientMsgHandlerDescript : public IClientMsgHandlerDescript
	{
	public:
		using ProcessFuncType = void (GameLogicModule::*)(int, MsgType *, Player *);
		ClientMsgHandlerDescript(GameLogicModule *_game_module, int _protocol_id, ProcessFuncType _process)
		{
			game_module = _game_module;
			protocol_id = _protocol_id;
			process = _process;
			msg = new MsgType();
		}
		~ClientMsgHandlerDescript()
		{
			delete msg; 
			process = nullptr;
		}
		inline virtual google::protobuf::Message *Msg() { return msg; }
		inline virtual void Handle(int protocol_id, google::protobuf::Message *input_msg, Player *player)
		{
			(game_module->*process)(protocol_id, dynamic_cast<MsgType *>(input_msg), player);
		}

	protected:
		MsgType *msg = nullptr;
		ProcessFuncType process = nullptr;
		GameLogicModule *game_module = nullptr;
	};
}


class GameLogicModule : public IGameLogicModule
{
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
	LogModule * GetLog() { return m_log_module; }
	ITimerModule * GetTimer() { return m_timer_module; }
	INetworkModule * GetNetwork() { return m_network_module; }
	NetworkAgent *GetNetAgent() { return m_network_agent; }

private:
	Config::CsvConfigSets *m_csv_cfg_sets = nullptr;
	GameLogic::PlayerMgr *m_player_mgr = nullptr;
	LogModule *m_log_module = nullptr;
	ITimerModule *m_timer_module = nullptr;
	INetworkModule *m_network_module = nullptr;
	NetworkAgent *m_network_agent = nullptr;

private:
	GameLogic::IClientMsgHandlerDescript **m_client_msg_handler_descripts = nullptr;
	void InitClientMsgHandlerDescript();
	void UnInitClientMsgHandlerDescript();
	void OnHandlePlayerPingMsg(int protocol_id, Ping *msg, GameLogic::Player *player);
	void OnHandlePlayerPongMsg(int protocol_id, Pong *msg, GameLogic::Player *player);
};

