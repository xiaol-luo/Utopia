#pragma once

#include <sol.hpp>
#include <stdint.h>
#include <google/protobuf/message.h>
#include "Network/Protobuf/Empty.pb.h"
#include "Common/Utils/MemoryUtil.h"
#include "Network/Protobuf/Gm.pb.h"
#include "Network/Protobuf/msg.pb.h"
#include "Network/Protobuf/test.pb.h"
#include "Network/Protobuf/PID.pb.h"
#include "Network/Protobuf/Common.pb.h"
#include "Network/Protobuf/Battle.pb.h"

class GameLogicModule;
class EventDispacherProxy;


#define RegPlayerMsgHandler(id, msg_type, func) \
	msg_handle_descripts.push_back(new GameLogic::ClientMsgHandlerDescript<msg_type>(this, (int)id, &PlayerMsgHandler::func))

#define RegPlayerHandler(id, func) \
	msg_handle_descripts.push_back(new GameLogic::ClientEmptyMsgHandlerDescript(this, (int)id, &PlayerMsgHandler::func))


namespace NetProto
{
	class Ping;
	class Pong;
	class Empty;
	class SelectHeroReq;
}

namespace GameLogic
{
	class PlayerMsgHandler;
	class Player;

	class IClientMsgHandlerDescript
	{
	public:
		IClientMsgHandlerDescript() {}
		virtual ~IClientMsgHandlerDescript() {}
		inline int Id() { return protocol_id; }
		inline google::protobuf::Message *Msg() { return msg; }
		virtual void Handle(int protocol_id, google::protobuf::Message *msg, Player *player) = 0;

	protected:
		int protocol_id = 0;
		google::protobuf::Message *msg = nullptr;
	};

	template <typename MsgType>
	class ClientMsgHandlerDescript : public IClientMsgHandlerDescript
	{
	public:
		using ProcessFuncType = void (PlayerMsgHandler::*)(int, MsgType *, Player *);
		ClientMsgHandlerDescript(PlayerMsgHandler *_msg_handler, int _protocol_id, ProcessFuncType _process)
		{
			msg_handler = _msg_handler;
			protocol_id = _protocol_id;
			process = _process;
			msg = new MsgType();
		}
		~ClientMsgHandlerDescript()
		{
			delete msg;
			process = nullptr;
		}
		inline virtual void Handle(int protocol_id, google::protobuf::Message *input_msg, Player *player)
		{
			(msg_handler->*process)(protocol_id, dynamic_cast<MsgType *>(input_msg), player);
		}

	protected:
		ProcessFuncType process = nullptr;
		PlayerMsgHandler *msg_handler = nullptr;
	};

	class ClientEmptyMsgHandlerDescript : public IClientMsgHandlerDescript
	{
	public:
		using ProcessFuncDefine = void (PlayerMsgHandler::*)(int, Player *);
		ClientEmptyMsgHandlerDescript(PlayerMsgHandler *_msg_handler, int _protocol_id, ProcessFuncDefine _process)
		{
			msg_handler = _msg_handler;
			protocol_id = _protocol_id;
			process = _process;
		}

		inline virtual void Handle(int protocol_id, google::protobuf::Message *input_msg, Player *player)
		{
			(msg_handler->*process)(protocol_id, player);
		}

		ProcessFuncDefine process;
		PlayerMsgHandler *msg_handler = nullptr;
	};


	class PlayerMsgHandler
	{
	public:
		PlayerMsgHandler(GameLogicModule *logic_module);
		~PlayerMsgHandler();

		void Init();
		void Uninit();
		void HandlePlayerMsg(char *data, uint32_t data_len, GameLogic::Player *player);

	protected:
		IClientMsgHandlerDescript **m_client_msg_handler_descripts = nullptr;
		GameLogicModule *m_logic_module = nullptr;
		google::protobuf::Arena *m_protobuf_arena = nullptr;
		std::string m_tmp_lua_msg_buf;
		sol::protected_function m_lua_msg_handler_fn;

	protected:
		void OnHandlePlayerPingMsg(int protocol_id, NetProto::Ping *msg, GameLogic::Player *player);
		void OnHandlePlayerPongMsg(int protocol_id, NetProto::Pong *msg, GameLogic::Player *player);
		void OnQueryFreeHero(int protocol_id, GameLogic::Player *player);
		void OnSelectHeroReq(int protocol_id, NetProto::SelectHeroReq *msg, GameLogic::Player *player);
		void OnLoadSceneComplete(int id, GameLogic::Player *player);
		void OnLeaveScene(int id, GameLogic::Player *player);
		void OnMoveToPos(int protocol_id, NetProto::MoveToPos *msg, GameLogic::Player *player);
		void OnStopMove(int id, GameLogic::Player *player);
		void OnHandleBattleOperation(int protocol_id, NetProto::BattleOperation *msg, GameLogic::Player *player);
		void OnReloadLuaScripts(int id, NetProto::ReloadLuaScripts *msg, GameLogic::Player *player);

		EventDispacherProxy *m_ev_proxy = nullptr;
	};
}

