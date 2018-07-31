#pragma  once 

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "Common/Define/NetworkDefine.h"
#include "Common/Macro/MemoryPoolMacro.h"
#include "MemoryPool/StlAllocator.h"

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
		NewDelOperaDeclaration;
	public:
		const static uint64_t BROADCAST_NETID/* = 0*/;
	public: 
		PlayerMgr(GameLogicModule *logic_module);
		~PlayerMgr();

		bool Awake(std::string ip, uint16_t port);
		void Update(long long now_ms);
		void OnCnnClose(int err_num, Player *player);
		void OnCnnRecv(char *data, uint32_t len, Player *player);
		void OnCnnOpen(int err_num, Player *player);
		void RemovePlayer(NetId netid);
		void Send(NetId netid, int protocol_id, char *msg, uint32_t msg_len);
		void Send(NetId netid, int protocol_id, google::protobuf::Message *msg);
		void Close(NetId netid);

	protected:
		GameLogicModule *m_logic_module = nullptr;
		std::shared_ptr<INetListenHander> m_net_listen_handler = nullptr;
		std::unordered_map<NetId, Player *, std::hash<NetId>, std::equal_to<NetId>, StlAllocator<std::pair<const NetId, Player *>>> m_players;
		void OnListenClose(int err_num);
		void OnListenOpen(int err_num);

		std::unordered_set<Player *, std::hash<Player *>, std::equal_to<Player *>, StlAllocator<Player *>> m_to_remove_players;
	};
}