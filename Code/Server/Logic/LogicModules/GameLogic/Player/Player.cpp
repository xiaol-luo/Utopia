#include "player.h"
#include "PlayerMgr.h"
#include "CommonModules/Network/INetworkHandler.h"
#include "Network/Handlers/LenCtxNetStreamCnnHandler.h"
#include "Common/Utils/MemoryUtil.h"
#include "Common/Utils/LogUtil.h"

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
		m_player_mgr = nullptr;
		m_cnn_handler = nullptr;
	}

	std::shared_ptr<INetConnectHander> Player::GetCnnHandler()
	{
		return m_cnn_handler;
	}

	NetId Player::GetNetId()
	{
		return m_cnn_handler ? m_cnn_handler->GetNetId() : 0;
	}

	void Player::OnNetClose(int err_num)
	{
		LogUtil::Debug(1, "{0} is close, errno {1}", this->m_cnn_handler->GetNetId(), err_num);
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