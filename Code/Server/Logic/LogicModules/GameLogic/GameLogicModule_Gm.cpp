#include "GameLogicModule.h"
#include "GameLogic/Scene/NewScene.h"
#include "ShareCode/Network/Protobuf/Gm.pb.h"
#include "ShareCode/Network/Protobuf/PID.pb.h"
#include "GameLogic/Player/PlayerMgr.h"

void GameLogicModule::GmRecreateScene(std::string scene_type)
{
	GameLogic::NewScene *scene = this->CreateScene(scene_type);
	if (nullptr != scene)
	{
		delete m_new_scene;
		m_new_scene = scene;
	}
	NetProto::RecreateSceneRsp msg;
	msg.set_is_succ(nullptr != scene);
	m_player_mgr->Send(GameLogic::PlayerMgr::BROADCAST_NETID, NetProto::PID_RecreateSceneRsp, &msg);
}
