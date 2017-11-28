#include "NewScene.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include <assert.h>
#include "SceneModule/SceneModule.h"
#include "SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Log/LogModule.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/GameLogicModule.h"
#include "CommonModules/Timer/ITimerModule.h"
#include "GameLogic/Player/Player.h"
#include "GameLogic/GameLogicModule.h"
#include "GameLogic/Player/PlayerMgr.h"

namespace GameLogic
{
	NewScene::NewScene(GameLogicModule *logic_module)
	{
		m_game_logic = logic_module;
		m_ev_dispacher = new EventDispacher();
		memset(m_modules, 0, sizeof(m_modules));
	}

	NewScene::~NewScene()
	{
		delete m_ev_dispacher; m_ev_dispacher = nullptr;
		for (auto &&module : m_modules)
		{
			delete module;
		}
		memset(m_modules, 0, sizeof(m_modules));
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

		long now_ms = GlobalServerLogic->GetTimerModule()->NowMs();
		if (0 == m_last_real_ms)
		{
			m_last_real_ms = now_ms;
			return;
		}

		long long delta_ms = now_ms - m_last_real_ms;
		m_last_real_ms = now_ms;
		if (m_is_pause)
			return;

		// m_logic_detal_ms = delta_ms;
		m_logic_detal_ms = 50;
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

		for (auto kv_pair : m_cached_scene_units)
		{
			auto su = kv_pair.second.lock();
			if (nullptr == su)
				continue;
			su->Update();
		}

		this->UpdateCachedSceneUnits();
		this->OnLateUpdate();

		this->GetEvDispacher()->Fire(ES_TestHeartBeat);
	}

	void NewScene::TestEvent(int ev_id, SceneUnit * su)
	{
		GlobalLog->Debug(LogModule::LOGGER_ID_STDOUT, "NewScene::TestEvent ev_id:{0} su_id:{1}", ev_id, su->GetId());
	}

	void NewScene::TestSubscribeEvents()
	{
		m_ev_dispacher->Subscribe<SceneUnit *>(ESU_EnterScene, std::bind(&NewScene::TestEvent, this, ESU_EnterScene, std::placeholders::_1));
		m_ev_dispacher->Subscribe<SceneUnit *>(ESU_LeaveScene, std::bind(&NewScene::TestEvent, this, ESU_LeaveScene, std::placeholders::_1));
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

	void NewScene::SetPlayerViewCamp(Player *player, EViewCamp view_camp)
	{
		if (nullptr == player || view_camp < 0 || view_camp > EViewCamp_Observer)
			return;

		for (auto & m_player_view_camp : m_player_view_camps)
		{
			m_player_view_camp.erase(player->GetNetId());
		}
		m_player_view_camps[view_camp].insert(std::make_pair(player->GetNetId(), player));

		// pull all data
	}
	void NewScene::SendClient(NetId netid, int protocol_id, google::protobuf::Message * msg)
	{
		m_game_logic->GetPlayerMgr()->Send(netid, protocol_id, msg);
	}

	void NewScene::SendClient(NetId netid, const std::vector<SyncClientMsg>& msgs)
	{
		for (auto &msg : msgs)
			this->SendClient(netid, msg.protocol_id, msg.msg);
	}
	void NewScene::SendViewCamp(EViewCamp view_camp, int protocol_id, google::protobuf::Message * msg)
	{
		if (view_camp < 0 || view_camp >= EViewCamp_Observer)
			return;

		for (auto kv_pair : m_player_view_camps[view_camp])
		{
			kv_pair.second->Send(protocol_id, msg);
		}
		for (auto kv_pair : m_player_view_camps[EViewCamp_Observer])
		{
			kv_pair.second->Send(protocol_id, msg);
		}
	}

	void NewScene::SendViewCamp(EViewCamp view_camp, const std::vector<SyncClientMsg>& msgs)
	{
		if (view_camp < 0 || view_camp >= EViewCamp_Observer)
			return;

		for (auto &msg : msgs)
		{
			for (auto kv_pair : m_player_view_camps[view_camp])
			{
				kv_pair.second->Send(msg.protocol_id, msg.msg);
			}
			for (auto kv_pair : m_player_view_camps[EViewCamp_Observer])
			{
				kv_pair.second->Send(msg.protocol_id, msg.msg);
			}
		}
	}
}