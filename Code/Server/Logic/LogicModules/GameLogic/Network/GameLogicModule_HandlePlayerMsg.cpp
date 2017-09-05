#include "Gamelogic/GameLogicModule.h"
#include "Network/Protobuf/msg.pb.h"
#include "Network/Protobuf/test.pb.h"
#include "GamePlayerMsgDefine.h"
#include "Utils/PlatformCompat.h"
#include "Network/Utils/NetworkAgent.h"
#include "GameLogic/Player/Player.h"

#define RegPlayerMsgHandler(id, msg_type, func) \
	msg_handle_descripts.push_back(new GameLogic::ClientMsgHandlerDescript<msg_type>(this, id, &GameLogicModule::func))

void GameLogicModule::InitClientMsgHandlerDescript()
{
	uint32_t malloc_size = sizeof(GameLogic::IClientMsgHandlerDescript *) * GameLogic::PlayerMsgProtocol_Max;
	m_client_msg_handler_descripts = (GameLogic::IClientMsgHandlerDescript **)malloc(malloc_size);
	memset(m_client_msg_handler_descripts, 0, malloc_size);
	
	std::vector<GameLogic::IClientMsgHandlerDescript *> msg_handle_descripts;
	RegPlayerMsgHandler(GameLogic::PlayerMsgProtocol_Ping, Ping, OnHandlePlayerPingMsg);
	RegPlayerMsgHandler(GameLogic::PlayerMsgProtocol_Pong, Pong, OnHandlePlayerPongMsg);

	for (auto desc : msg_handle_descripts)
	{
		assert(nullptr == m_client_msg_handler_descripts[desc->Id()]);
		m_client_msg_handler_descripts[desc->Id()] = desc;
	}
}

void GameLogicModule::UnInitClientMsgHandlerDescript()
{
	if (nullptr != m_client_msg_handler_descripts)
	{
		for (int i = 0; i < GameLogic::PlayerMsgProtocol_Max; ++i)
			delete m_client_msg_handler_descripts[i];
		free(m_client_msg_handler_descripts);
		m_client_msg_handler_descripts = nullptr;
	}
}

void GameLogicModule::HandlePlayerMsg(char *data, uint32_t data_len, GameLogic::Player *player)
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
		if (protocol_id <= GameLogic::PlayerMsgProtocol_Invalid || protocol_id >= GameLogic::PlayerMsgProtocol_Max)
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
		handler_descript->Msg()->ParseFromArray(protobuf_data, data_len);
		handler_descript->Handle(protocol_id, handler_descript->Msg(), player);

	} while (false);
	if (!is_ok)
	{
		m_network_agent->Close(player->GetNetId());
	}
}

void GameLogicModule::OnHandlePlayerPingMsg(int protocol_id, Ping *msg, GameLogic::Player *player)
{
	msg->set_msgid(protocol_id);
	Pong pong;
	pong.set_userid(2);
	m_network_agent->Send(player->GetNetId(), 2, &pong);
}

void GameLogicModule::OnHandlePlayerPongMsg(int protocol_id, Pong *msg, GameLogic::Player *player)
{
	msg->set_msgid(protocol_id);
}

