#pragma  once 

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "Common/Define/NetworkDefine.h"

class GameLogicModule;
class INetListenHander;
namespace GameLogic 
{ 
	class Player; 
	class PlayerListenHandler;
}

namespace GameLogic
{
	class PlayerMgr
	{
		friend GameLogic::PlayerListenHandler;
	public: 
		PlayerMgr(GameLogicModule *logic_module);
		~PlayerMgr();

		bool Awake(std::string ip, uint16_t port);
		void Update(long long now_ms);
		void OnCnnClose(int err_num, Player *player);
		void OnCnnRecv(char *data, uint32_t len, Player *player);
		void OnCnnOpen(int err_num, Player *player);

		void RemovePlayer(NetId netid);

	protected:
		GameLogicModule *m_logic_module = nullptr;
		std::shared_ptr<INetListenHander> m_net_listen_handler = nullptr;
		std::unordered_map<NetId, GameLogic::Player *> m_players;
		void OnListenClose(int err_num);
		void OnListenOpen(int err_num);

		std::unordered_set<Player *> m_to_remove_players;
	};
}