#pragma once

#include <memory>
#include "GameLogic/Scene/Defines/SceneDefine.h"

class EventDispacher;
class EventDispacherProxy;

namespace GameLogic
{
	class NewScene;
	class SceneUnitTransform;
	class SceneUnitModule;
	class SceneUnitEventProxy;

	class SceneUnit : public std::enable_shared_from_this<SceneUnit>
	{
	public:
		SceneUnit();
		~SceneUnit();

		void AddModule(std::shared_ptr<SceneUnitModule> module);
		void EnterScene(NewScene *scene, uint64_t id);
		void LeaveScene();
		void Update();

		NewScene * GetScene() { return m_scene; }
		EventDispacher * GetEvDispacher() { return m_event_dispacher; }
		SceneUnitEventProxy * GetEvProxy() { return m_event_proxy; }
		EventDispacherProxy * GetSceneEvProxy() { return m_scene_event_proxy; }
		uint64_t GetId() { return m_id; }

		template <typename T>
		std::shared_ptr<T> GetModule()
		{
			std::shared_ptr<T> ptr = nullptr;
			int idx = T::MODULE_TYPE;
			if (idx  >= 0 && idx < ESceneUnitModule_Count)
			{
				ptr = std::dynamic_pointer_cast<T>(m_modules[idx]);
			}
			return ptr;
		}

		std::shared_ptr<SceneUnitTransform> GetTransform() { return m_transform; }

	private:
		NewScene *m_scene = nullptr;
		uint64_t m_id = 0;

		bool m_inited = false;
		bool m_started = false;
		std::shared_ptr<SceneUnitModule> m_modules[ESceneUnitModule_Count];
		std::shared_ptr<SceneUnitTransform> m_transform = nullptr;

		EventDispacher *m_event_dispacher = nullptr;
		EventDispacherProxy *m_scene_event_proxy = nullptr;
		SceneUnitEventProxy *m_event_proxy = nullptr;
	};
}