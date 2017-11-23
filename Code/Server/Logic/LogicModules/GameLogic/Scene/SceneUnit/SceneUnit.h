#pragma once

#include <memory>
#include "GameLogic/Scene/Defines/SceneObjectDefine.h"

namespace GameLogic
{
	class Scene;
	class SceneUnitTransform;
	class SceneUnitModule;

	class SceneUnit : public std::enable_shared_from_this<SceneUnit>
	{
	public:
		SceneUnit(uint64_t id);
		~SceneUnit();

		void AddModule(std::shared_ptr<SceneUnitModule> module);
		void EnterScene(Scene *scene);
		void LeaveScene();
		void Update();

		Scene * GetScene() { return m_scene; }
		uint64_t GetId() { return m_id; }

		std::shared_ptr<SceneUnitTransform> GetTransform() { return m_transform; }

	private:
		Scene *m_scene = nullptr;
		uint64_t m_id = 0;

		bool m_inited = false;
		bool m_started = false;
		std::shared_ptr<SceneUnitModule> m_modules[ESceneUnitModule_Count];
		std::shared_ptr<SceneUnitTransform> m_transform;
	};
}