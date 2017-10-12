#include "Scene.h"
#include "SceneObject/SceneObject.h"
#include "SceneObject/Hero.h"
#include "Common/Utils/MemoryUtil.h"
#include "Network/Protobuf/Battle.pb.h"
#include "Network/Protobuf/ProtoId.pb.h"
#include "GameLogic/Player/Player.h"
#include "GameLogic/GameLogicModule.h"
#include "Network/Utils/NetworkAgent.h"
#include "Navigation/NavMesh.h"
#include "MoveMgr/MoveMgr.h"
#include "GameLogic/GameLogicModule.h"
#include "CsvConfigSets.h"
#include "Scene/CsvSceneConfig.h"

namespace GameLogic
{
	Scene::Scene(GameLogicModule *logic_module) : m_logic_module(logic_module)
	{
		m_protobuf_arena = MemoryUtil::NewArena();
		m_navMesh = new GameLogic::NavMesh(this);
		m_moveMgr = new GameLogic::MoveMgr(this);
	}
	
	Scene::~Scene()
	{
		delete m_protobuf_arena;
		m_protobuf_arena = nullptr;
	}

	bool Scene::Awake(void *param)
	{ 
		assert(m_logic_module->GetCsvCfgSet()->csv_CsvSceneConfigSet->cfg_vec.size() > 0);
		m_sceneCfg = m_logic_module->GetCsvCfgSet()->csv_CsvSceneConfigSet->cfg_vec[0];

		bool ret;
		ret = m_navMesh->LoadTerrain(m_logic_module->GetCfgRootPath() + "/" + m_sceneCfg->terrain_file_path);
		assert(ret);

		ret = m_moveMgr->Awake();
		assert(ret);

		m_red_hero = std::make_shared<Hero>();
		this->AddObject(m_red_hero);
		// m_blue_hero = std::make_shared<Hero>();
		// this->AddObject(m_blue_hero);

		return true;
	}

	void Scene::Update(long long now_ms)
	{
		this->CheckSceneObjectsCache();
		for (auto it = m_scene_objs_cache.begin(); m_scene_objs_cache.end() != it; ++ it)
		{
			std::shared_ptr<SceneObject> scene_obj = it->second.lock();
			if (nullptr != scene_obj)
				scene_obj->Update(now_ms);
		}
		this->CheckSceneObjectsCache();
		m_protobuf_arena->Reset();

		m_navMesh->UpdateTerrian();
		m_moveMgr->Update();
	}

	int64_t Scene::AddObject(std::shared_ptr<SceneObject> scene_obj)
	{
		if (nullptr == scene_obj)
			return 0;
		++m_last_scene_objid;
		if (m_last_scene_objid == INVALID_SCENE_OBJID)
			m_last_scene_objid = 1;
		if (m_scene_objs.find(m_last_scene_objid) != m_scene_objs.end())
			return 0;

		scene_obj->LeaveScene();
		scene_obj->SetScene(this);
		scene_obj->SetId(m_last_scene_objid);
		{
			std::shared_ptr<MoveObject> move_ptr = std::dynamic_pointer_cast<MoveObject>(scene_obj);
			if (nullptr != move_ptr)
				m_moveMgr->OnMoveObjectEnterScene(move_ptr);
		}
		scene_obj->OnEnterScene(this);
		m_scene_objs[m_last_scene_objid] = scene_obj;
		m_scene_objs_cache[m_last_scene_objid] = scene_obj;

		return m_last_scene_objid;
	}

	void Scene::RemoveObject(int64_t objid)
	{
		if (m_red_hero->GetId() == objid || m_blue_hero->GetId() == objid)
			return;

		auto it = m_scene_objs.find(objid);
		if (m_scene_objs.end() == it)
			return;

		std::shared_ptr<SceneObject> scene_obj = it->second;
		{
			std::shared_ptr<MoveObject> move_ptr = std::dynamic_pointer_cast<MoveObject>(scene_obj);
			if (nullptr != move_ptr)
				m_moveMgr->OnMoveObjectEnterScene(move_ptr);
		}
		scene_obj->OnLeaveScene(this);
		scene_obj->SetScene(nullptr);
		scene_obj->SetId(INVALID_SCENE_OBJID);
		scene_obj = nullptr;
		m_removed_scene_objids.insert(objid);
		m_scene_objs.erase(it);
	}

	void Scene::CheckSceneObjectsCache()
	{
		if (!m_removed_scene_objids.empty())
		{
			for (uint64_t objid : m_removed_scene_objids)
			{
				m_scene_objs_cache.erase(objid);
			}
			m_removed_scene_objids.clear();
		}
	}

	void Scene::PullAllSceneInfo(Player * player)
	{
		NetProto::AllSceneObject *msg = google::protobuf::Arena::CreateMessage<NetProto::AllSceneObject>(m_protobuf_arena);
		// NetProto::SceneObject *so = msg->add_objs();
		m_logic_module->GetNetAgent()->Send(player->GetNetId(), NetProto::PID_PullAllSceneInfoRsp, msg);
	}
}