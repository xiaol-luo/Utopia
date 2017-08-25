#include "Gamelogic/GameLogicModule.h"
#include "Network/Protobuf/msg.pb.h"
#include "Network/Protobuf/test.pb.h"
#include "GamePlayerMsgDefine.h"

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
		m_client_msg_handler_descripts = nullptr;
	}
}

void GameLogicModule::TestClientMsgHandler()
{
	for (int i = 0; i < GameLogic::PlayerMsgProtocol_Max; ++ i)
	{
		GameLogic::IClientMsgHandlerDescript *handle_descript = m_client_msg_handler_descripts[i];
		if (nullptr != handle_descript)
		{
			handle_descript->Handle(handle_descript->Id(), handle_descript->Msg(), nullptr);
		}
	}
}

void GameLogicModule::HandlePlayerMsg(Player *player, int protocol_id, char *data, uint32_t data_len)
{
	if (protocol_id <= GameLogic::PlayerMsgProtocol_Invalid || protocol_id >= GameLogic::PlayerMsgProtocol_Max)
		return;

	GameLogic::IClientMsgHandlerDescript *handler_descript = m_client_msg_handler_descripts[protocol_id];
	if (nullptr == handler_descript)
		return;
}

void GameLogicModule::OnHandlePlayerPingMsg(int protocol_id, Ping *msg, Player *player)
{
	int a = 0;
	++a;
}

void GameLogicModule::OnHandlePlayerPongMsg(int protocol_id, Pong *msg, Player *player)
{
	int a = 0;
	++a;
}

