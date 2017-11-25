#pragma once

#include <stdint.h>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "GameLogic/Scene/Defines/SceneDefine.h"
class EventDispacher;

namespace Config
{
	struct CsvSceneConfig;
}

namespace GameLogic
{
	class SceneModule;
	class SceneUnit;

	class NewScene
	{
	public:
		NewScene();
		virtual ~NewScene();

		void AddModule(SceneModule *module);
		bool Awake();
		void Update();
		void Destroy();
	protected:
		virtual bool OnAwake() { return true; }
		virtual bool OnLateAwake() { return true; }
		virtual void OnUpdate() {}
		virtual void OnLateUpdatae() {}
		virtual void OnDestroy() {}
		virtual void OnLateDestroy() {}

	public:
		inline long GetLogicMs() { return m_logic_ms; }
		inline long GetLogicDetalMs() { return m_logic_detal_ms; }
		inline EventDispacher * GetEvDispacher() { return m_ev_dispacher; }
	protected:
		bool m_is_pause = false;
		uint64_t m_logic_ms = 0;
		uint64_t m_logic_detal_ms = 0;
		uint64_t m_last_real_ms = 0;
		EventDispacher *m_ev_dispacher;
		Config::CsvSceneConfig *m_sceneCfg = nullptr;

		bool m_awaked = false;
		bool m_started = false;
		SceneModule *m_modules[ESceneModule_Count];

	public:
		uint64_t AddUnit(std::shared_ptr<SceneUnit> su);
		void RemoveUnit(uint64_t id);
		std::shared_ptr<SceneUnit> GetUnit(uint64_t id);

	protected:
		uint64_t m_last_scene_unit_id;
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> m_scene_units;
		std::unordered_map<uint64_t, std::weak_ptr<SceneUnit>> m_cached_scene_units;
		std::unordered_set<uint64_t> m_removed_scene_unit_ids;
		std::unordered_set<uint64_t> m_new_scene_unit_ids;
		void UpdateCachedSceneUnits();

	protected:
		void TestEvent(int ev_id, SceneUnit *su);
		void TestSubscribeEvents();
	};
}
