#include "Player.h"
#include "PlayerMgr.h"
#include "CommonModules/Network/INetworkHandler.h"
#include "Network/Handlers/LenCtxNetStreamCnnHandler.h"
#include "Common/Utils/MemoryUtil.h"
#include "Common/Macro/AllMacro.h"
#include "CommonModules/Log/LogModule.h"
#include "Network/Utils/NetworkAgent.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "ServerLogics/ServerLogic.h"

namespace GameLogic
{
	class PlayerCnnHandler : public LenCtxNetStreamCnnHandler
	{
		NewDelOperaDeclaration;
	public:
		PlayerCnnHandler(NetId netid, GameLogic::Player *player);
		virtual ~PlayerCnnHandler();
		virtual void OnClose(int err_num);
		virtual void OnOpen(int err_num);

	protected:
		virtual void OnParseSuccess(char *data, uint32_t len);
		virtual void OnParseFail();
		GameLogic::Player *m_player = nullptr;
	};

	NewDelOperaImplement(PlayerCnnHandler);

	PlayerCnnHandler::PlayerCnnHandler(NetId netid, GameLogic::Player *player)
		: LenCtxNetStreamCnnHandler(Net::PROTOCOL_MAX_SIZE), m_player(player)
	{
		this->SetNetId(netid);
	}

	PlayerCnnHandler::~PlayerCnnHandler()
	{
		m_player = nullptr;
	}

	void PlayerCnnHandler::OnClose(int err_num)
	{
		m_player->OnNetClose(err_num);
	}

	void PlayerCnnHandler::OnOpen(int err_num)
	{
		m_player->OnNetOpen(err_num);
	}

	void PlayerCnnHandler::OnParseSuccess(char *data, uint32_t len)
	{
		m_player->OnNetRecv(m_parser.Content(), m_parser.ContentLen());
	}

	void PlayerCnnHandler::OnParseFail()
	{
		m_player->m_player_mgr->RemovePlayer(this->GetNetId());
	}

	Player::Player(PlayerMgr *player_mgr, NetId netid)
		: m_player_mgr(player_mgr)
	{
		m_cnn_handler = std::make_shared<PlayerCnnHandler>(netid, this);
	}

	Player::~Player()
	{
		m_hero.reset();
		m_player_mgr = nullptr;
		m_cnn_handler = nullptr;
		m_scene = nullptr;
		m_su = nullptr;
	}

	std::shared_ptr<INetConnectHander> Player::GetCnnHandler()
	{
		return m_cnn_handler;
	}

	NetId Player::GetNetId()
	{
		return m_cnn_handler ? m_cnn_handler->GetNetId() : 0;
	}

	void Player::SendMsg(google::protobuf::Message * msg)
	{

	}

	void Player::Send(int protocol_id, char * msg, uint32_t msg_len)
	{
		G_NetAgent->Send(this->GetNetId(), protocol_id, msg, msg_len);
	}

	void Player::Send(int protocol_id, google::protobuf::Message * msg)
	{
		G_NetAgent->Send(this->GetNetId(), protocol_id, msg);
	}

	void Player::Close()
	{
		G_NetAgent->Close(this->GetNetId());
	}

	void Player::OnNetClose(int err_num)
	{
		G_Log->Debug(LogModule::LOGGER_ID_STDOUT, "{0} is close, errno {1}", this->m_cnn_handler->GetNetId(), err_num);
		if (nullptr != m_scene)
		{
			m_scene->OnPlayerDisconnect(this);
			m_scene = nullptr;
		}
		if (nullptr != m_su)
		{
			m_su->SetPlayerId(0);
			m_su = nullptr;
		}

		m_player_mgr->OnCnnClose(err_num, this);
	}

	void Player::OnNetOpen(int err_num)
	{
		m_player_mgr->OnCnnOpen(err_num, this);
	}

	void Player::OnNetRecv(char *data, uint32_t len)
	{
		m_player_mgr->OnCnnRecv(data, len, this);
	}
}