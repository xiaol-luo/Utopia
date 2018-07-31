#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"

namespace GameLogic
{
	class NavMesh;

	class SceneNavMesh : public SceneModule
	{
	public:
		static const ESceneModule MODULE_TYPE/* = ESceneModule_NavMesh*/;
	public:
		SceneNavMesh();
		virtual ~SceneNavMesh() override;

		inline NavMesh * GetNavMesh() { return m_nav_mesh; }

	protected:
		virtual bool OnAwake() override;

	protected:
		NavMesh *m_nav_mesh = nullptr;
	};
}
