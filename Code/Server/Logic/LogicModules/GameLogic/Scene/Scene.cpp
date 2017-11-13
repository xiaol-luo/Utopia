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
#include "Common/Geometry/Vector2.h"
#include "Common/Geometry/GeometryUtils.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Timer/ITimerModule.h"
#include "GameLogic/Player/PlayerMgr.h"
#include "GameLogic/Scene/ViewMgr/ViewMgr.h"
#include "GameLogic/Scene/EventDispacher/EventDispacher.h"

namespace GameLogic
{
	Scene::Scene(GameLogicModule *logic_module) : m_logic_module(logic_module)
	{
		m_protobuf_arena = MemoryUtil::NewArena();
		m_nav_mesh = new GameLogic::NavMesh(this);
		m_move_mgr = new GameLogic::MoveMgr(this);
		m_view_mgr = new GameLogic::ViewMgr(this);
		m_event_dispacher = new SceneEventDispacher(this);
	}
	
	Scene::~Scene()
	{
		delete m_protobuf_arena; m_protobuf_arena = nullptr;
		delete m_nav_mesh; m_nav_mesh = nullptr;
		delete m_move_mgr; m_move_mgr = nullptr;
		delete m_view_mgr; m_view_mgr = nullptr;
		delete m_event_dispacher; m_event_dispacher = nullptr;

	}

	bool Scene::Awake(void *param)
	{ 
		assert(m_logic_module->GetCsvCfgSet()->csv_CsvSceneConfigSet->cfg_vec.size() > 0);
		m_sceneCfg = m_logic_module->GetCsvCfgSet()->csv_CsvSceneConfigSet->cfg_vec[0];

		bool ret;
		ret = m_nav_mesh->LoadTerrain(m_logic_module->GetCfgRootPath() + "/" + m_sceneCfg->terrain_file_path);
		assert(ret);

		ret = m_view_mgr->LoadCfg(m_logic_module->GetCfgRootPath() + "/" + m_sceneCfg->terrain_file_path + ".view");
		assert(ret);

		ret = m_move_mgr->Awake();
		assert(ret);

		m_red_hero = std::make_shared<Hero>();
		this->AddObject(m_red_hero);
		m_red_hero->Flash(Vector3(50, 0, 50));

		m_blue_hero = std::make_shared<Hero>();
		this->AddObject(m_blue_hero);
		m_blue_hero->Flash(Vector3(50, 0, 50));

		Vector2 x1 = GeometryUtils::CalVector2(Vector2(0, 1), 90);
		Vector2 x2 = GeometryUtils::CalVector2(Vector2(0, 1), -90);
		Vector2 x3 = GeometryUtils::CalVector2(Vector2(0, 1), 180);


		float v1 = GeometryUtils::DeltaAngle(Vector2(0, 1), Vector2(1, 0));
		float v2 = GeometryUtils::DeltaAngle(Vector2(0, 1), Vector2(-1, 0));
		float v3 = GeometryUtils::DeltaAngle(Vector2(0, 1), Vector2(0, -1));
		
		if (false)
		{
			std::weak_ptr<Hero> hero = m_red_hero;
			GlobalServerLogic->GetTimerModule()->AddFirm([hero]() {
				std::shared_ptr<Hero> ptr = hero.lock();
				if (nullptr == ptr)
					return;

				// int rand_val = std::rand() % NetProto::EMoveAgentState_Max + 1;
				int rand_val = NetProto::EMoveAgentState_ForcePos;
				switch (rand_val)
				{
				case NetProto::EMoveAgentState_MoveToPos:
					// ptr->TryMoveToPos(Vector3(std::rand() % 100, 0, std::rand()%100));
					break;
				case NetProto::EMoveAgentState_MoveToDir:
					// ptr->TryMoveToDir(std::rand() % 36000 * 0.001 + 1);
					break;
				case NetProto::EMoveAgentState_ForceLine:
					ptr->ForceMoveLine(Vector2(std::rand() * (0 == std::rand() % 2 ? 1 : -1), std::rand() * (0 == std::rand() % 2 ? 1 : -1)), 3, 1.5, false);
					break;
				case NetProto::EMoveAgentState_ForcePos:
					ptr->ForcePos(Vector3(std::rand() % 20, 0, std::rand() % 20), 10);
					break;
				case NetProto::EMoveAgentState_Immobilized:
					ptr->Immobilized(std::rand() % 1000 + 1000);
					break;
				case NetProto::EMoveAgentState_Idle:
					ptr->CancelForceMove();
					ptr->CancelImmobilized();
					ptr->CancelMove();
					break;

				case NetProto::EMoveAgentState_Max:
					// ptr->Flash(Vector3(std::rand() % 105, std::rand() % 30, std::rand() % 105));
					break;
				}

			}, 3 * 1000, -1);
			
		}

		return true;
	}

	void Scene::Update(long long now_ms)
	{
		this->CheckSceneObjectsCache();
		for (auto it = m_scene_objs_cache.begin(); m_scene_objs_cache.end() != it; ++ it)
		{
			std::shared_ptr<SceneObject> scene_obj = it->second.lock();
			if (nullptr != scene_obj)
			{
				scene_obj->Update(now_ms);
				if (scene_obj->NeedSyncMutableState())
				{
					this->SendClient(PlayerMgr::BROADCAST_NETID, scene_obj->ColllectSyncClientMsg(SCMF_ForMutable));
					scene_obj->SetSyncMutableState(false);
				}
			}
		}
		this->CheckSceneObjectsCache();
		m_protobuf_arena->Reset();

		m_nav_mesh->UpdateTerrian();
		m_move_mgr->Update();
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
		m_scene_objs[m_last_scene_objid] = scene_obj;
		m_scene_objs_cache[m_last_scene_objid] = scene_obj;
		m_event_dispacher->OnAddSceneObject(scene_obj);
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
		m_event_dispacher->OnRemoveSceneObject(scene_obj);
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

	void Scene::SendClient(NetId netid, int protocol_id, google::protobuf::Message * msg)
	{
		m_logic_module->GetPlayerMgr()->Send(netid, protocol_id, msg);
	}

	void Scene::SendClient(NetId netid, const std::vector<SyncClientMsg>& msgs)
	{
		for (const SyncClientMsg & item : msgs)
		{
			m_logic_module->GetPlayerMgr()->Send(netid, item.protocol_id, item.msg);
		}
	}

	void Scene::PullAllSceneInfo(Player * player)
	{
		for (auto it = m_scene_objs_cache.begin(); m_scene_objs_cache.end() != it; ++it)
		{
			std::shared_ptr<SceneObject> scene_obj = it->second.lock();
			if (nullptr != scene_obj)
			{
				for (const SyncClientMsg & item : scene_obj->ColllectSyncClientMsg(SCMF_All))
				{
					player->Send(item.protocol_id, item.msg);
				}
			}
		}
	}
}