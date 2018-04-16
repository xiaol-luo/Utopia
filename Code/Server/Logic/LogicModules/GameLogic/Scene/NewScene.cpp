#include "NewScene.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include <assert.h>
#include "SceneModule/SceneModule.h"
#include "SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Log/LogModule.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/GameLogicModule.h"
#include "CommonModules/Timer/ITimerModule.h"
#include "GameLogic/Player/Player.h"
#include "GameLogic/GameLogicModule.h"
#include "GameLogic/Player/PlayerMgr.h"
#include "GameLogic/Scene/SceneModule/SceneView/SceneView.h"
#include "GameLogic/Scene/SceneModule/SceneView/ViewSnapshot.h"
#include "GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"
#include "Network/Protobuf/Battle.pb.h"
#include "Network/Protobuf/ProtoId.pb.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSight.h"
#include "GameLogic/Scene/Config/SceneAllConfig.h"

namespace GameLogic
{
	NewScene::NewScene(GameLogicModule *logic_module)
	{
		m_protobuf_arena = MemoryUtil::NewArena();
		m_game_logic = logic_module;
		m_ev_dispacher = new EventDispacher();
		memset(m_modules, 0, sizeof(m_modules));
		m_cfg = new SceneAllConfig();
	}

	NewScene::~NewScene()
	{
		delete m_protobuf_arena; m_protobuf_arena = nullptr;
		delete m_ev_dispacher; m_ev_dispacher = nullptr;
		for (auto &&module : m_modules)
		{
			delete module;
		}
		memset(m_modules, 0, sizeof(m_modules));

		delete m_cfg; m_cfg = nullptr;
	}

	void NewScene::AddModule(SceneModule * module)
	{
		assert(!m_awaked);
		assert(nullptr == m_modules[module->GetModuleName()]);
		m_modules[module->GetModuleName()] = module;
	}

	bool NewScene::Awake()
	{
		if (m_awaked)
			return false;
		bool ret = true;
		ret &= this->OnAwake();

		m_awaked = true;
		m_started = false;

		do 
		{
			if (!ret)
				break;

			for (auto &&module : m_modules)
			{
				if (nullptr != module)
					ret &= module->Init(this);
				if (!ret)
					break;
			}
			if (!ret)
				break;

			for (auto &&module : m_modules)
			{
				if (nullptr != module)
					ret &= module->Awake();
				if (!ret)
					break;
			}
			if (!ret)
				break;

			ret &= this->OnLateAwake();

		} while (false);

		this->TestSubscribeEvents();

		return ret;
	}

	void NewScene::Destroy()
	{
		this->OnDestroy();

		if (m_awaked)
		{
			m_awaked = false;
			for (auto &&module : m_modules)
			{
				if (nullptr != module)
					module->Realse();
			}
			for (auto &&module : m_modules)
			{
				if (nullptr != module)
					module->Destroy();
			}
		}
		for (auto &&module : m_modules)
		{
			delete module;
		}
		memset(m_modules, 0, sizeof(m_modules));

		for (auto & m_player_view_camp : m_player_view_camps)
		{
			for (auto kv_pair : m_player_view_camp)
			{
				kv_pair.second->SetSu(nullptr);
				kv_pair.second->SetScene(nullptr);
			}
		}

		this->OnLateDestroy();
	}

	float NewScene::GetLogicSec()
	{
		float sec = m_logic_ms * 1.0 / ITimerModule::MS_PER_SEC;
		return sec;
	}

	uint64_t NewScene::AddUnit(std::shared_ptr<SceneUnit> su)
	{
		if (nullptr == su)
			return SCENE_UNIT_INVALID_ID;
		++m_last_scene_unit_id;
		(SCENE_UNIT_INVALID_ID == m_last_scene_unit_id) ? ++m_last_scene_unit_id : 0;
		if (m_scene_units.count(su->GetId()) > 0 ||
			m_scene_units.count(m_last_scene_unit_id) > 0)
			return SCENE_UNIT_INVALID_ID;

		m_scene_units[m_last_scene_unit_id] = su;
		m_new_scene_unit_ids.insert(m_last_scene_unit_id);
		m_removed_scene_unit_ids.erase(m_last_scene_unit_id);
		su->EnterScene(this, m_last_scene_unit_id);
		return m_last_scene_unit_id;
	}

	void NewScene::RemoveUnit(uint64_t id)
	{
		auto it = m_scene_units.find(id);
		if (m_scene_units.end() == it)
			return;

		std::shared_ptr<SceneUnit> su = it->second;
		su->LeaveScene();
		m_removed_scene_unit_ids.insert(m_last_scene_unit_id);
		m_new_scene_unit_ids.erase(m_last_scene_unit_id);
		m_scene_units.erase(it);
	}

	std::shared_ptr<SceneUnit> NewScene::GetUnit(uint64_t id)
	{
		std::shared_ptr<SceneUnit> ret = nullptr;
		auto it = m_scene_units.find(id);
		if (m_scene_units.end() != it)
			ret = it->second;
		return ret;
	}

	void NewScene::UpdateCachedSceneUnits()
	{
		if (!m_removed_scene_unit_ids.empty())
		{
			for (uint64_t objid : m_removed_scene_unit_ids)
			{
				m_cached_scene_units.erase(objid);
			}
			m_removed_scene_unit_ids.clear();
		}
		if (!m_new_scene_unit_ids.empty())
		{
			for (uint64_t objid : m_new_scene_unit_ids)
			{
				auto su = this->GetUnit(objid);
				if (nullptr != su)
					m_cached_scene_units.insert(std::make_pair(su->GetId(), su));
			}
			m_removed_scene_unit_ids.clear();
		}
	}
	
	void NewScene::Update()
	{
		if (!m_awaked)
			return;

		uint64_t now_ms = GlobalServerLogic->GetTimerModule()->NowMs();
		if (0 == m_last_real_ms)
		{
			m_last_real_ms = now_ms;
			return;
		}

		uint64_t delta_ms = now_ms - m_last_real_ms;
		m_last_real_ms = now_ms;
		if (m_is_pause)
			return;

		m_logic_detal_ms = delta_ms;
		m_logic_detal_ms = 100;
		m_logic_ms += m_logic_detal_ms;

		this->UpdateCachedSceneUnits();
		this->OnUpdate();

		if (!m_started)
		{
			m_started = true;
			for (auto &&module : m_modules)
			{
				if (nullptr != module)
					module->Start();
			}
		}
		else
		{
			for (auto &&module : m_modules)
			{
				if (nullptr != module)
					module->Update();
			}
		}
		this->MakeSnapshot(true);

		for (auto kv_pair : m_cached_scene_units)
		{
			auto su = kv_pair.second.lock();
			if (nullptr == su)
				continue;
			su->Update();
		}

		this->UpdateCachedSceneUnits();
		this->OnLateUpdate();
		m_protobuf_arena->Reset();
	}

	void NewScene::TestEvent(int ev_id, std::shared_ptr<SceneUnit> su)
	{
		GlobalLog->Debug(LogModule::LOGGER_ID_STDOUT, "NewScene::TestEvent ev_id:{0} su_id:{1}", ev_id, su->GetId());
	}

	void NewScene::TestSubscribeEvents()
	{
		m_ev_dispacher->Subscribe<std::shared_ptr<SceneUnit>>(ESU_EnterScene, std::bind(&NewScene::TestEvent, this, ESU_EnterScene, std::placeholders::_1));
		m_ev_dispacher->Subscribe<std::shared_ptr<SceneUnit>>(ESU_LeaveScene, std::bind(&NewScene::TestEvent, this, ESU_LeaveScene, std::placeholders::_1));
	}

	bool NewScene::PlayerSelectHero(Player * player, uint64_t su_id)
	{
		if (nullptr == player)
			return false;

		auto hero = this->GetUnit(su_id);
		if (nullptr != hero && hero->GetPlayerId() <= 0)
		{
			hero->SetPlayerId(player->GetNetId());
			player->SetSu(hero);
			player->SetScene(this);
			return true;
		}
		return false;
	}

	void NewScene::OnPlayerDisconnect(Player * player)
	{
		if (nullptr == player)
			return;

		for (auto & m_player_view_camp : m_player_view_camps)
		{
			m_player_view_camp.erase(player->GetNetId());
		}
	}

	void NewScene::OnPlayerQuit(Player * player)
	{
		if (nullptr == player)
			return;

		player->SetScene(nullptr);
		player->SetSu(nullptr);
		for (auto & m_player_view_camp : m_player_view_camps)
		{
			m_player_view_camp.erase(player->GetNetId());
		}
	}

	void NewScene::SetPlayerViewCamp(Player *player, EViewCamp view_camp)
	{
		if (nullptr == player || view_camp < 0 || view_camp > EViewCamp_Observer)
			return;

		for (auto & m_player_view_camp : m_player_view_camps)
		{
			m_player_view_camp.erase(player->GetNetId());
		}
		m_player_view_camps[view_camp].insert(std::make_pair(player->GetNetId(), player));

		std::unordered_set<EViewCamp> camps;
		if (EViewCamp_Observer == view_camp)
		{
			camps.insert(EViewCamp_Red);
			camps.insert(EViewCamp_Blue);
			camps.insert(EViewCamp_Monster);
		}
		else
		{
			camps.insert(view_camp);
		}

		SceneView *scene_view = this->GetModule<SceneView>();
		{
			// view mgr
			NetProto::ViewAllGrids *msg = this->CreateProtobuf<NetProto::ViewAllGrids>();
			scene_view->FillPbViewAllGrids(msg);
			player->Send(NetProto::PID_ViewAllGrids, msg);

			auto su = player->GetSu();
			if (nullptr != su && nullptr != su->GetModule<SceneUnitSight>())
			{
				su->GetModule<SceneUnitSight>()->GetViewCamp();
				NetProto::ViewSnapshot *snapshot = this->CreateProtobuf<NetProto::ViewSnapshot>();;
				scene_view->FillPbViewSnapshot(su->GetModule<SceneUnitSight>()->GetViewCamp(), snapshot);
				player->Send(NetProto::PID_ViewSnapshot, snapshot);
			}
		}

		auto snapshots = this->GetModule<SceneView>()->GetSnapshot();
		for (EViewCamp camp : camps)
		{
			for (auto kv_pair : snapshots[camp]->scene_units)
			{
				auto su = kv_pair.second.lock();
				if (nullptr != su)
				{
					for (auto & msg : su->CollectPBInit())
					player->Send(msg.protocol_id, msg.msg);
				}
			}
		}
	}

	void NewScene::SendPlayer(NetId netid, int protocol_id, google::protobuf::Message * msg)
	{
		m_game_logic->GetPlayerMgr()->Send(netid, protocol_id, msg);
	}

	void NewScene::SendPlayer(NetId netid, const std::vector<SyncClientMsg>& msgs)
	{
		for (auto &msg : msgs)
			this->SendPlayer(netid, msg.protocol_id, msg.msg);
	}

	void NewScene::SendObservers(int64_t su_id, int protocol_id, google::protobuf::Message * msg)
	{
		SceneView *scene_view = this->GetModule<SceneView>();
		auto snapshots = scene_view->GetSnapshot();
		for (int camp = 0; camp < EViewCamp_Observer; ++camp)
		{
			if (snapshots[camp]->CanSeeSu(su_id))
				this->SendViewCamp((EViewCamp)camp, protocol_id, msg, false);
		}
		this->SendViewCamp(EViewCamp_Observer, protocol_id, msg, false);
	}

	void NewScene::SendObservers(int64_t su_id, const std::vector<SyncClientMsg>& msgs)
	{
		for (auto &msg : msgs)
			this->SendObservers(su_id, msg.protocol_id, msg.msg);
	}

	void NewScene::SendViewCamp(EViewCamp view_camp, int protocol_id, google::protobuf::Message * msg, bool to_ob)
	{
		if (view_camp < 0 || view_camp > EViewCamp_All)
			return;

		std::unordered_set<EViewCamp> camps;
		if (EViewCamp_All == view_camp)
		{
			camps.insert(EViewCamp_Red);
			camps.insert(EViewCamp_Blue);
			camps.insert(EViewCamp_Monster);
			static_assert(3 == EViewCamp_Observer, "add view camp should modify here");
		}
		else
		{
			camps.insert(view_camp);
		}
		if (to_ob)
			camps.insert(view_camp);

		for (EViewCamp camp : camps)
		{
			for (auto kv_pair : m_player_view_camps[camp])
			{
				kv_pair.second->Send(protocol_id, msg);
			}
		}
	}

	void NewScene::SendViewCamp(EViewCamp view_camp, const std::vector<SyncClientMsg>& msgs, bool to_ob)
	{
		for (auto &msg : msgs)
			this->SendViewCamp(view_camp, msg.protocol_id, msg.msg, to_ob);
	}
	void NewScene::MakeSnapshot(bool syncClient)
	{
		SceneView *scene_view = this->GetModule<SceneView>();
		scene_view->MakeSnapshot();
		auto curr_snapshot = scene_view->GetSnapshot();
		auto pre_snapshot = scene_view->GetPreSnapshot();
		
		for (int camp = 0; camp < EViewCamp_Observer; ++camp)
		{
			ViewSnapshotDifference diff = curr_snapshot[camp]->CalDifference(pre_snapshot[camp]);
			ViewCampDiff &camp_diff = m_view_camp_diff[camp];
			for (ViewGrid *grid : diff.miss_view_grids)
			{
				camp_diff.more_gird_ids.erase(grid->grid_id);
				camp_diff.miss_grid_ids.insert(grid->grid_id);
			}
			for (ViewGrid *grid : diff.more_view_grids)
			{
				camp_diff.more_gird_ids.insert(grid->grid_id);
				camp_diff.miss_grid_ids.erase(grid->grid_id);
			}
			for (auto kv_pair : diff.miss_su)
			{
				camp_diff.miss_su_ids.insert(kv_pair.first);
				camp_diff.more_sus.erase(kv_pair.first);
			}
			for (auto kv_pair : diff.more_su)
			{
				camp_diff.miss_su_ids.erase(kv_pair.first);
				camp_diff.more_sus[kv_pair.first] = kv_pair.second;
			}
		}
		if (syncClient)
		{
			for (int camp = 0; camp < EViewCamp_Observer; ++camp)
			{
				ViewCampDiff &diff = m_view_camp_diff[camp];
				if (!diff.more_gird_ids.empty() || !diff.miss_grid_ids.empty())
				{
					// view grids 
					NetProto::ViewSnapshotDiff *msg = this->CreateProtobuf<NetProto::ViewSnapshotDiff>();
					for (int grid_id : diff.more_gird_ids)
						msg->add_more_grids(grid_id);
					for (int grid_id : diff.miss_grid_ids)
						msg->add_miss_grids(grid_id);
					this->SendViewCamp((EViewCamp)camp, NetProto::PID_ViewSnapshotDiff, msg, true);
				}

				{
					// scene object 
					if (diff.miss_su_ids.size() > 0)
					{
						NetProto::SceneObjectDisappear *msg = this->CreateProtobuf<NetProto::SceneObjectDisappear>();
						for (int64_t su_id : diff.miss_su_ids)
						{
							msg->add_objids(su_id);
						}
						this->SendViewCamp((EViewCamp)camp, NetProto::PID_SceneObjectDisappear, msg, true);
					}
					for (auto kv_pari : diff.more_sus)
					{
						auto sptr_su = kv_pari.second.lock();
						if (nullptr == sptr_su)
							continue;
						this->SendViewCamp((EViewCamp)camp ,sptr_su->CollectPBInit(), true);
					}
					for (auto kv_pari : curr_snapshot[camp]->scene_units)
					{
						uint64_t objid = kv_pari.first;
						if (diff.more_sus.count(objid) > 0)
							continue;
						auto sptr_su = kv_pari.second.lock();
						if (nullptr == sptr_su)
							continue;
						this->SendViewCamp((EViewCamp)camp, sptr_su->CollectPbMutable(), true);
					}

					diff.Clear();
				}
			}

			for (auto kv_pair : m_scene_units)
			{
				kv_pair.second->ClearPbDirty();
			}
		}
	}

	NetProto::ESceneUnitRelation NewScene::SceneUnitRelation(std::shared_ptr<SceneUnit> one, std::shared_ptr<SceneUnit> another)
	{
		if (nullptr == one || nullptr == another)
			return NetProto::ESceneUnitRelation_None;

		if (one->GetId() == another->GetId())
		{
			return NetProto::ESceneUnitRelation_Self;
		}

		NetProto::ESceneUnitCamp one_camp = one->GetCamp();
		NetProto::ESceneUnitCamp another_camp = another->GetCamp();
		if (NetProto::ESceneUnitCamp_Neutral == one_camp || NetProto::ESceneUnitCamp_Neutral == another_camp)
		{
			return NetProto::ESceneUnitRelation_None;
		}

		return one_camp == another_camp ? NetProto::ESceneUnitRelation_Friend : NetProto::ESceneUnitRelation_Enemy;
	}

	NetProto::ESceneUnitRelation NewScene::SceneUnitRelation(SceneUnit * one, SceneUnit * another)
	{
		if (nullptr == one || nullptr == another)
			return NetProto::ESceneUnitRelation_None;
		return this->SceneUnitRelation(one->shared_from_this(), another->shared_from_this());
	}
}