#include "PlayerMsgHandler.h"
#include "Utils/PlatformCompat.h"
#include "Network/Protobuf/msg.pb.h"
#include "Network/Protobuf/test.pb.h"
#include "Network/Protobuf/ProtoId.pb.h"
#include "Network/Protobuf/Common.pb.h"
#include "GameLogic/GameLogicModule.h"
#include "GameLogic/Player/Player.h"
#include "Network/Utils/NetworkAgent.h"
#include "GameLogic/Scene/SceneObject/Hero.h"
#include "GameLogic/Scene/Scene.h"
#include "Network/Protobuf/Battle.pb.h"
#include "Common/Utils/AutoReleaseUtil.h"
#include "GameLogic/Scene/SceneObject/Hero.h"

#define RegPlayerMsgHandler(id, msg_type, func) \
	msg_handle_descripts.push_back(new GameLogic::ClientMsgHandlerDescript<msg_type>(this, (int)id, &PlayerMsgHandler::func))

#define RegPlayerHandler(id, func) \
	msg_handle_descripts.push_back(new GameLogic::ClientEmptyMsgHandlerDescript(this, (int)id, &PlayerMsgHandler::func))


namespace GameLogic
{
	PlayerMsgHandler::PlayerMsgHandler(GameLogicModule *logic_module)
	{
		m_logic_module = logic_module;
		m_protobuf_arena = MemoryUtil::NewArena();
	}

	PlayerMsgHandler::~PlayerMsgHandler()
	{
		delete m_protobuf_arena; 
		m_protobuf_arena = nullptr;
	}

	void PlayerMsgHandler::Init()
	{
		uint32_t malloc_size = sizeof(GameLogic::IClientMsgHandlerDescript *) * PID_Max;
		m_client_msg_handler_descripts = (GameLogic::IClientMsgHandlerDescript **)malloc(malloc_size);
		memset(m_client_msg_handler_descripts, 0, malloc_size);

		std::vector<GameLogic::IClientMsgHandlerDescript *> msg_handle_descripts;
		RegPlayerMsgHandler(PID_Ping, Ping, OnHandlePlayerPingMsg);
		RegPlayerMsgHandler(PID_Pong, Pong, OnHandlePlayerPongMsg);
		RegPlayerHandler(PID_QueryFreeHero, OnQueryFreeHero);

		for (auto desc : msg_handle_descripts)
		{
			assert(nullptr == m_client_msg_handler_descripts[desc->Id()]);
			m_client_msg_handler_descripts[desc->Id()] = desc;
		}
	}

	void PlayerMsgHandler::Uninit()
	{
		if (nullptr != m_client_msg_handler_descripts)
		{
			for (int i = PID_Min + 1; i < PID_Max; ++i)
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
			if (protocol_id <= PID_Min || protocol_id >= PID_Max)
			{
				is_ok = false;
				break;
			}
			GameLogic::IClientMsgHandlerDescript *handler_descript = m_client_msg_handler_descripts[protocol_id];
			if (nullptr == handler_descript)
			{
				is_ok = false;
				break;
			}
			char *protobuf_data = data + PROTOCOL_LEN_DESCRIPT_SIZE;
			if (nullptr != handler_descript->Msg())
				handler_descript->Msg()->ParseFromArray(protobuf_data, data_len);
			handler_descript->Handle(protocol_id, handler_descript->Msg(), player);
			if (m_protobuf_arena->SpaceAllocated() > 1024 * 10)
				m_protobuf_arena->Reset();

		} while (false);
		if (!is_ok)
		{
			m_logic_module->GetNetAgent()->Close(player->GetNetId());
		}
	}

	void PlayerMsgHandler::OnHandlePlayerPingMsg(int protocol_id, Ping *msg, GameLogic::Player *player)
	{
		Pong *pong = google::protobuf::Arena::CreateMessage<Pong>(m_protobuf_arena);
		m_logic_module->GetNetAgent()->Send(player->GetNetId(), PID_Pong, pong);


		AutoReleaseUtil aru;
		Ping *xxx = new Ping();
		aru.Add(xxx);
	}

	void PlayerMsgHandler::OnHandlePlayerPongMsg(int protocol_id, Pong *msg, GameLogic::Player *player)
	{
		
	}

	void PlayerMsgHandler::OnQueryFreeHero(int protocol_id, GameLogic::Player *player)
	{
		std::shared_ptr<Hero> red_hero = m_logic_module->m_scene->GetRedHero();
		std::shared_ptr<Hero> blue_hero = m_logic_module->m_scene->GetBlueHero();

		RspFreeHero *rsp_msg = google::protobuf::Arena::CreateMessage<RspFreeHero>(m_protobuf_arena);
		if (nullptr == red_hero->GetPlayer())
			rsp_msg->add_free_hero_ids(red_hero->GetId());
		if (nullptr == blue_hero->GetPlayer())
			rsp_msg->add_free_hero_ids(blue_hero->GetId());

		m_logic_module->m_network_agent->Send(player->GetNetId(), PID_RspFreeHero, rsp_msg);
	}
}
