#include "GameLogic/GameLogicModule.h"
#include "GameLogic/Player/PlayerMgr.h"
#include "CommonModules/Network/INetworkHandler.h"
#include "Player.h"
#include "CommonModules/Log/LogModule.h"
#include "CommonModules/Network/INetworkModule.h"
#include "Common/Macro/AllMacro.h"
#include "ServerLogics/ServerLogic.h"
#include "Network/Utils/NetworkAgent.h"

namespace GameLogic
{
	const NetId PlayerMgr::BROADCAST_NETID = 0;

	class PlayerListenHandler : public INetListenHander
	{
	public:
		PlayerListenHandler(GameLogic::PlayerMgr *player_mgr) : m_player_mgr(player_mgr) {}
		virtual ~PlayerListenHandler() { m_player_mgr = nullptr; }
		virtual void OnClose(int err_num);
		virtual void OnOpen(int err_num);
		virtual std::shared_ptr<INetConnectHander> GenConnectorHandler(NetId netid);

	protected:
		PlayerMgr *m_player_mgr;
	};

	void PlayerListenHandler::OnClose(int err_num)
	{
		m_player_mgr->OnListenClose(err_num);
	}

	void PlayerListenHandler::OnOpen(int err_num)
	{
		m_player_mgr->OnListenOpen(err_num);
	}

	std::shared_ptr<INetConnectHander> PlayerListenHandler::GenConnectorHandler(NetId netid)
	{
		Player *player = new Player(m_player_mgr, netid);
		return player->GetCnnHandler();
	}

	GameLogic::PlayerMgr::PlayerMgr(GameLogicModule *logic_module) : m_logic_module(logic_module)
	{
		m_net_listen_handler = std::make_shared<PlayerListenHandler>(this);
	}

	PlayerMgr::~PlayerMgr()
	{
		m_net_listen_handler = nullptr;
	}

	bool PlayerMgr::Awake(std::string ip, uint16_t port)
	{
		NetId netid = G_Net->Listen(ip, port, nullptr, m_net_listen_handler);
		return netid > 0;
	}

	void PlayerMgr::Update(long long now_ms)
	{
		if (!m_to_remove_players.empty())
		{
			for (auto player : m_to_remove_players)
				delete player;
			m_to_remove_players.clear();
		}
	}

	void PlayerMgr::OnCnnClose(int err_num, Player *player)
	{
		if (nullptr != player)
		{
			this->RemovePlayer(player->GetNetId());
			m_to_remove_players.insert(player);
		}
	}

	void PlayerMgr::OnCnnRecv(char *data, uint32_t len, Player *player)
	{
		m_logic_module->HandlePlayerMsg(data, len, player);
	}

	void PlayerMgr::OnCnnOpen(int err_num, Player *player)
	{
		if (0 == err_num)
		{
			m_players[player->GetNetId()] = player;
		}
		else
		{
			delete player; player = nullptr;
		}
	}

	void PlayerMgr::OnListenClose(int err_num)
	{

	}

	void PlayerMgr::OnListenOpen(int err_num)
	{

	}

	void PlayerMgr::RemovePlayer(NetId netid)
	{
		auto it = m_players.find(netid);
		if (m_players.end() != it)
		{
			G_Net->Close(netid);
			m_to_remove_players.insert(it->second);
			m_players.erase(it);
			it = m_players.end();
		}
	}

	void PlayerMgr::Send(NetId netid, int protocol_id, char * msg, uint32_t msg_len)
	{
		if (netid > 0)
		{
			G_NetAgent->Send(netid, protocol_id, msg, msg_len);
		}
		else
		{
			for (auto kv_pair : m_players)
			{
				// if (kv_pair.second->CanRecvSceneMsg())
					G_NetAgent->Send(kv_pair.first, protocol_id, msg, msg_len);
			}
		}
	}

	void PlayerMgr::Send(NetId netid, int protocol_id, google::protobuf::Message * msg)
	{
		if (netid > 0)
		{
			G_NetAgent->Send(netid, protocol_id, msg);
		}
		else
		{
			for (auto kv_pair : m_players)
			{
				G_NetAgent->Send(kv_pair.first, protocol_id, msg);
			}
		}
	}

	void PlayerMgr::Close(NetId netid)
	{
		G_NetAgent->Close(netid);
	}
}
