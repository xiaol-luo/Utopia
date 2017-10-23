#pragma  once 

#include "Common/Define/NetworkDefine.h"
#include "Common/Macro/MemoryPoolMacro.h"
#include <unordered_map>
#include <memory>
#include "protobuf/include/google/protobuf/message.h"

class GameLogicModule;
class INetConnectHander;
namespace GameLogic 
{ 
	class PlayerCnnHandler; 
	class PlayerMgr;
	class Hero;
}

namespace GameLogic
{
	class Player
	{
		friend class GameLogic::PlayerCnnHandler;
		using NetOpenCbFun = void (GameLogic::PlayerMgr::*)(int err_num);
		NewDelOperaDeclaration;
	public:
		Player(PlayerMgr *player_mgr, NetId netid);
		~Player();

		std::shared_ptr<INetConnectHander> GetCnnHandler();
		NetId GetNetId();
		void SendMsg(google::protobuf::Message *msg);

	protected:
		PlayerMgr *m_player_mgr;
		std::shared_ptr<GameLogic::PlayerCnnHandler> m_cnn_handler = nullptr;
		void OnNetClose(int err_num);
		void OnNetOpen(int err_num);
		void OnNetRecv(char *data, uint32_t len);

	public:
		std::weak_ptr<Hero> GetHero() { return m_hero; }
		void SetHero(std::shared_ptr<Hero> hero);
		bool CanRecvSceneMsg() { return m_can_recv_scene_msg; }
		void SetCanRecvSceneMsg(bool value) { m_can_recv_scene_msg = value; }

	protected:
		std::weak_ptr<Hero> m_hero;
		bool m_can_recv_scene_msg = false;
	};
}