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
#include "GameLogic/Scene/ViewMgr/ViewSnapshot.h"
#include "GameLogic/Scene/ViewMgr/ViewGrid.h"

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

		{
			auto a = std::make_shared<Hero>();
			a->SetViewCamp(EViewCamp_Red);
			this->AddObject(a);
			a->Flash(Vector3(70, 0, 70));
		}
		{
			auto a = std::make_shared<Hero>();
			a->SetViewCamp(EViewCamp_Red);
			this->AddObject(a);
			a->Flash(Vector3(30, 0, 30));
		}
		{
			auto a = std::make_shared<Hero>();
			a->SetViewCamp(EViewCamp_Red);
			this->AddObject(a);
			a->Flash(Vector3(70, 0, 20));
		}


		m_red_hero = std::make_shared<Hero>();
		m_red_hero->SetViewCamp(EViewCamp_Red);
		this->AddObject(m_red_hero);
		m_red_hero->Flash(Vector3(50, 0, 50));

		m_blue_hero = std::make_shared<Hero>();
		m_blue_hero->SetViewCamp(EViewCamp_Blue);
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
		if (0 == m_last_real_ms)
		{
			m_last_real_ms = now_ms;
			return;
		}

		long long delta_ms = now_ms - m_last_real_ms;
		m_last_real_ms = now_ms;
		if (m_is_pause)
			return;

		m_logic_detal_ms = delta_ms;
		m_last_real_ms += delta_ms;
		this->CheckSceneObjectsCache();
		m_nav_mesh->UpdateTerrian();
		m_move_mgr->Update();
		for (auto it = m_scene_objs_cache.begin(); m_scene_objs_cache.end() != it; ++it)
		{
			std::shared_ptr<SceneObject> scene_obj = it->second.lock();
			if (nullptr == scene_obj)
				continue;
			scene_obj->Update(now_ms);
		}
		m_view_mgr->Update();
		this->HandleViewChange();
		for (auto kv_pari : m_scene_objs)
		{
			std::shared_ptr<SceneObject> sptr_so = kv_pari.second;
			sptr_so->SetSyncMutableState(false);
		}
		this->CheckSceneObjectsCache();
		m_protobuf_arena->Reset();
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

		scene_obj->SetScene(this);
		scene_obj->SetId(m_last_scene_objid);
		m_scene_objs[m_last_scene_objid] = scene_obj;
		m_scene_objs_cache[m_last_scene_objid] = scene_obj;
		m_event_dispacher->OnSceneAddObject(scene_obj);
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
		m_event_dispacher->OnSceneRemoveObject(scene_obj);
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

	void Scene::SendViewCamp(EViewCamp view_camp, int protocol_id, google::protobuf::Message * msg)
	{
		for (auto kv_pair : m_scene_objs)
		{
			std::shared_ptr<SceneObject> sptr_so = kv_pair.second;
			if (ESOT_Hero != sptr_so->GetObjectType() || sptr_so->GetViewCamp() != view_camp)
				continue;
			std::shared_ptr<Hero> sptr_hero = std::dynamic_pointer_cast<Hero>(sptr_so);
			Player *player = sptr_hero->GetPlayer();
			if (nullptr == player)
				continue;
			player->Send(protocol_id, msg);
		}
	}

	void Scene::SendViewCamp(EViewCamp view_camp, const std::vector<SyncClientMsg>& msgs)
	{
		for (auto kv_pair : m_scene_objs)
		{
			std::shared_ptr<SceneObject> sptr_so = kv_pair.second;
			if (ESOT_Hero != sptr_so->GetObjectType() || sptr_so->GetViewCamp() != view_camp)
				continue;
			std::shared_ptr<Hero> sptr_hero = std::dynamic_pointer_cast<Hero>(sptr_so);
			Player *player = sptr_hero->GetPlayer();
			if (nullptr == player)
				continue;
			for (const SyncClientMsg & item : msgs)
			{
				player->Send(item.protocol_id, item.msg);
			}
		}
	}

	void Scene::PullAllSceneInfo(Player * player)
	{
		this->SyncAllSceneObjectState(player, SCMF_All);
		{
			// view mgr
			NetProto::ViewAllGrids *msg = this->CreateProtobuf<NetProto::ViewAllGrids>();
			m_view_mgr->FillPbViewAllGrids(msg);
			player->Send(NetProto::PID_ViewAllGrids, msg);

			std::shared_ptr<Hero> hero = player->GetHero().lock();
			if (nullptr != hero)
			{
				NetProto::ViewSnapshot *snapshot = this->CreateProtobuf<NetProto::ViewSnapshot>();;
				m_view_mgr->FillPbViewSnapshot(hero->GetViewCamp(), snapshot);
				player->Send(NetProto::PID_ViewSnapshot, snapshot);
			}
		}
	}

	void Scene::SyncAllSceneObjectState(Player * player, int filter_flag)
	{
		std::weak_ptr<Hero> wptr_hero = player->GetHero();
		std::shared_ptr<Hero> sptr_hero = wptr_hero.lock();
		if (nullptr == sptr_hero)
			return;
		const ViewSnapshot *snapshot = m_view_mgr->GetSnapshot(sptr_hero->GetViewCamp());
		if (nullptr == snapshot)
			return;

		for (auto it : snapshot->scene_objs)
		{
			uint64_t objid = it.first;
			auto sptr_item = it.second.lock();
			if (nullptr == sptr_item)
				continue;
			for (const SyncClientMsg & item : sptr_item->ColllectSyncClientMsg(filter_flag))
			{
				player->Send(item.protocol_id, item.msg);
			}
		}
	}

	void Scene::HandleViewChange()
	{
		for (int view_camp = EViewCamp_None + 1; view_camp < EViewCamp_All; ++view_camp)
		{
			const ViewSnapshot *pre_snapshot = m_view_mgr->GetPreSnapshot((EViewCamp)view_camp);
			const ViewSnapshot *snapshot = m_view_mgr->GetSnapshot((EViewCamp)view_camp);
			if (nullptr == snapshot || nullptr == pre_snapshot)
				continue;

			ViewSnapshotDifference diff = snapshot->CalDifference(pre_snapshot);
			if (!diff.more_view_grids.empty() || !diff.more_view_grids.empty())
			{
				// view grids 
				NetProto::ViewSnapshotDiff *msg = this->CreateProtobuf<NetProto::ViewSnapshotDiff>();
				for (ViewGrid *grid : diff.more_view_grids)
					msg->add_more_grids(grid->grid_id);
				for (ViewGrid *grid : diff.miss_view_grids)
					msg->add_miss_grids(grid->grid_id);
				this->SendViewCamp((EViewCamp)view_camp, NetProto::PID_ViewSnapshotDiff, msg);
			}
			{
				// scene object 
				if (diff.miss_scene_objs.size() > 0)
				{
					NetProto::SceneObjectDisappear *msg = this->CreateProtobuf<NetProto::SceneObjectDisappear>();
					for (auto kv_pari : diff.miss_scene_objs)
					{
						msg->add_objids(kv_pari.first);
					}
					this->SendViewCamp((EViewCamp)view_camp, NetProto::PID_SceneObjectDisappear, msg);
				}
				for (auto kv_pari : diff.more_scene_objs)
				{
					auto sptr_so = kv_pari.second.lock();
					if (nullptr == sptr_so)
						continue;
					this->SendViewCamp((EViewCamp)view_camp, sptr_so->ColllectSyncClientMsg(SCMF_All));
				}
				for (auto kv_pari : snapshot->scene_objs)
				{
					uint64_t objid = kv_pari.first;
					if (diff.more_scene_objs.count(objid) > 0)
						continue;
					auto sptr_so = kv_pari.second.lock();
					if (nullptr == sptr_so)
						continue;
					if (!sptr_so->NeedSyncMutableState())
						continue;
					this->SendViewCamp((EViewCamp)view_camp, sptr_so->ColllectSyncClientMsg(SCMF_ForMutable));
				}
			}
		}
	}
}