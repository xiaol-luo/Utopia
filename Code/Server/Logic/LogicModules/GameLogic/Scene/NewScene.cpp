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
}