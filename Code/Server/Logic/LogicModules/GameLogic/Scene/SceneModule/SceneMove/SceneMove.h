#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"
#include <unordered_map>
#include <memory>

namespace GameLogic
{
	class NavMesh;
	class SceneUnitMove;
	class SceneUnit;

	class SceneMove : public SceneModule
	{
	public:
		static const ESceneModule MODULE_TYPE = ESceneModule_Move;
	public:
		SceneMove();
		virtual ~SceneMove() override;

	protected:
		virtual bool OnAwake() override;
		virtual void OnUpdate() override;

	protected:
		NavMesh *m_nav_mesh = nullptr;
		std::unordered_map<uint64_t, std::weak_ptr<SceneUnitMove>> m_su_moves;
		void OnSceneUnitEnterScene(std::shared_ptr<SceneUnit> su);
	};
}
