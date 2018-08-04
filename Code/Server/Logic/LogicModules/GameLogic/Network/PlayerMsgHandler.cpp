#include "PlayerMsgHandler.h"
#include "Utils/PlatformCompat.h"
#include "GameLogic/GameLogicModule.h"
#include "GameLogic/Player/Player.h"
#include "Network/Utils/NetworkAgent.h"
#include "Common/Utils/AutoReleaseUtil.h"
#include "Common/Macro/AllMacro.h"
#include "CommonModules/Log/LogModule.h"
#include <memory>
#include "LuaHelps/LuaLoadFiles.h"
#include "ServerLogics/ServerLogic.h"

static const char *NET_HANDLER_NAMESPACE = "net_handler";
static const char *NET_PLAYER_HANDLER_FN = "OnPlayerMsg";

#define RegPlayerMsgHandler(id, msg_type, func) \
	msg_handle_descripts.push_back(new GameLogic::ClientMsgHandlerDescript<msg_type>(this, (int)id, &PlayerMsgHandler::func))

#define RegPlayerHandler(id, func) \
	msg_handle_descripts.push_back(new GameLogic::ClientEmptyMsgHandlerDescript(this, (int)id, &PlayerMsgHandler::func))

namespace GameLogic
{
	void PlayerMsgHandler::Init()
	{
		m_ev_proxy = G_Event->CreateProxy();
		uint32_t malloc_size = sizeof(GameLogic::IClientMsgHandlerDescript *) * NetProto::PID_Max;
		m_client_msg_handler_descripts = (GameLogic::IClientMsgHandlerDescript **)malloc(malloc_size);
		memset(m_client_msg_handler_descripts, 0, malloc_size);

		std::vector<GameLogic::IClientMsgHandlerDescript *> msg_handle_descripts;
		RegPlayerMsgHandler(NetProto::PID_Ping, NetProto::Ping, OnHandlePlayerPingMsg);
		RegPlayerMsgHandler(NetProto::PID_Pong, NetProto::Pong, OnHandlePlayerPongMsg);

		// Scene
		RegPlayerHandler(NetProto::PID_QueryFreeHero, OnQueryFreeHero);
		RegPlayerMsgHandler(NetProto::PID_SelectHeroReq, NetProto::SelectHeroReq, OnSelectHeroReq);
		RegPlayerHandler(NetProto::PID_LoadSceneComplete, OnLoadSceneComplete);
		RegPlayerHandler(NetProto::PID_LeaveScene, OnLeaveScene);
		RegPlayerMsgHandler(NetProto::PID_MoveToPos, NetProto::MoveToPos, OnMoveToPos);
		RegPlayerHandler(NetProto::PID_StopMove, OnStopMove);
		RegPlayerMsgHandler(NetProto::PID_BattleOperaReq, NetProto::BattleOperation, OnHandleBattleOperation);

		// GM
		RegPlayerHandler(NetProto::PID_ReloadConfigReq, OnReloadConfig);
		RegPlayerMsgHandler(NetProto::PID_ReloadLuaScripts, NetProto::ReloadLuaScripts, OnReloadLuaScripts);
		RegPlayerMsgHandler(NetProto::PID_RecreateSceneReq, NetProto::RecreateSceneReq, OnGmRecreateScene);

		for (auto desc : msg_handle_descripts)
		{
			assert(nullptr == m_client_msg_handler_descripts[desc->Id()]);
			m_client_msg_handler_descripts[desc->Id()] = desc;
		}

		sol::state_view lsv(LuaUtils::GetState());
		m_lua_msg_handler_fn = lsv[NET_HANDLER_NAMESPACE][NET_PLAYER_HANDLER_FN];
		assert(m_lua_msg_handler_fn.valid());
		m_lua_msg_handler_fn.error_handler = LuaUtils::ProtectFnErrorHandler();
	}

	PlayerMsgHandler::PlayerMsgHandler(GameLogicModule *logic_module)
	{
		m_logic_module = logic_module;
		m_protobuf_arena = MemoryUtil::NewArena();
	}

	PlayerMsgHandler::~PlayerMsgHandler()
	{
		if (nullptr != m_ev_proxy)
		{
			delete m_ev_proxy;
			m_ev_proxy = nullptr;
		}
		delete m_protobuf_arena;
		m_protobuf_arena = nullptr;
	}

	void PlayerMsgHandler::Uninit()
	{
		if (nullptr != m_client_msg_handler_descripts)
		{
			for (int i = NetProto::PID_Min + 1; i < NetProto::PID_Max; ++i)
				delete m_client_msg_handler_descripts[i];
			free(m_client_msg_handler_descripts);
			m_client_msg_handler_descripts = nullptr;
		}
	}

	void PlayerMsgHandler::HandlePlayerMsg(char *data, uint32_t data_len, GameLogic::Player *player)
	{
		static const uint32_t PROTOCOL_LEN_DESCRIPT_SIZE = sizeof(int);
		assert(nullptr != player);

		bool is_ok = true;
		do
		{
			if (nullptr == data || data_len < PROTOCOL_LEN_DESCRIPT_SIZE)
			{
				is_ok = false;
				break;
			}
			int protocol_id = ntohl(*(int *)data);
			if (protocol_id <= NetProto::PID_Min || protocol_id >= NetProto::PID_Max)
			{
				is_ok = false;
				break;
			}
			char *protobuf_data = data + PROTOCOL_LEN_DESCRIPT_SIZE;
			uint32_t protobuf_len = data_len - PROTOCOL_LEN_DESCRIPT_SIZE;

			bool is_msg_handled = false;
			// c++ msg handler
			GameLogic::IClientMsgHandlerDescript *handler_descript = m_client_msg_handler_descripts[protocol_id];
			if (nullptr != handler_descript)
			{
				if (nullptr != handler_descript->Msg())
				{
					handler_descript->Msg()->Clear();
					if (!handler_descript->Msg()->ParsePartialFromArray(protobuf_data, protobuf_len))
					{
						is_ok = false;
						G_Log->Error(LogModule::LOGGER_ID_STDERR + 1, "c++ msg parse from net buffer fail for protocol id {}", protocol_id);
						break;
					}
				}

				is_msg_handled = true;
				handler_descript->Handle(protocol_id, handler_descript->Msg(), player);
			}

			// lua msg handler
			{
				m_tmp_lua_msg_buf.assign(protobuf_data, protobuf_len);
				sol::protected_function_result ret = m_lua_msg_handler_fn(protocol_id, m_tmp_lua_msg_buf, player);
				if (ret.valid())
				{
					bool lua_ret = ret.get<bool>();
					if (lua_ret)
					{
						is_msg_handled = true;
					}
				}
			}

			if (m_protobuf_arena->SpaceAllocated() > 1024 * 10)
				m_protobuf_arena->Reset();

			if (!is_msg_handled)
			{
				is_ok = false;
				G_Log->Error(LogModule::LOGGER_ID_STDERR + 1, "not handler function for protocol id {}", protocol_id);
				break;
			}

		} while (false);
		if (!is_ok)
		{
			G_NetAgent->Close(player->GetNetId());
		}
	}

	void PlayerMsgHandler::OnHandlePlayerPingMsg(int protocol_id, NetProto::Ping *msg, GameLogic::Player *player)
	{
		NetProto::Pong *pong = google::protobuf::Arena::CreateMessage<NetProto::Pong>(m_protobuf_arena);
		G_NetAgent->Send(player->GetNetId(), NetProto::PID_Pong, pong);
	}

	void PlayerMsgHandler::OnHandlePlayerPongMsg(int protocol_id, NetProto::Pong *msg, GameLogic::Player *player)
	{

	}
}
