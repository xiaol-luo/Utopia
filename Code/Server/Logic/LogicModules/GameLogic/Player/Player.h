#pragma  once 

#include "Common/Define/NetworkDefine.h"
#include "Common/Macro/AllMacro.h"
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
	class SceneUnit;
	class NewScene;
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
		void Send(int protocol_id, char *msg, uint32_t msg_len);
		void Send(int protocol_id, google::protobuf::Message *msg);
		void Close();

	protected:
		PlayerMgr *m_player_mgr;
		std::shared_ptr<GameLogic::PlayerCnnHandler> m_cnn_handler = nullptr;
		void OnNetClose(int err_num);
		void OnNetOpen(int err_num);
		void OnNetRecv(char *data, uint32_t len);

	public:
		std::shared_ptr<SceneUnit> GetSu() { return m_su; }
		void SetSu(std::shared_ptr<SceneUnit> su) { m_su = su; }
		NewScene * GetScene() { return m_scene; }
		void SetScene(NewScene *scene) { m_scene = scene; }

	protected:
		std::weak_ptr<Hero> m_hero;
		std::shared_ptr<SceneUnit> m_su = nullptr;
		NewScene * m_scene = nullptr;
	};
}