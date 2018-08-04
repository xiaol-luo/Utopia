#include "GameLogicModule.h"
#include "GameLogic/Scene/NewScene.h"
#include "ShareCode/Network/Protobuf/Gm.pb.h"
#include "ShareCode/Network/Protobuf/PID.pb.h"
#include "GameLogic/Player/PlayerMgr.h"
#include "Logic/LuaHelps/LuaLoadFiles.h"

void GameLogicModule::GmRecreateScene(std::string scene_type)
{
	this->ReloadConfig();
	LuaUtils::LoadScripts_DoLoadScript(false, std::set<std::string>());

	GameLogic::NewScene *scene = this->CreateScene(scene_type);
	if (nullptr != scene)
	{
		if (nullptr != m_new_scene)
		{
			m_new_scene->Destroy();
			delete m_new_scene; 
			m_new_scene = nullptr;
		}
		for (auto item : m_expired_csv_cfg_sets)
		{
			delete item;
		}
		m_expired_csv_cfg_sets.clear();

		m_new_scene = scene;
	}
	NetProto::RecreateSceneRsp msg;
	msg.set_is_succ(nullptr != scene);
	m_player_mgr->Send(GameLogic::PlayerMgr::BROADCAST_NETID, NetProto::PID_RecreateSceneRsp, &msg);
}
