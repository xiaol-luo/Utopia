#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"
#include "GameLogic/Scene/Defines/ViewDefine.h"
#include <float.h>

namespace GameLogic
{
	class SceneUnitTransform;
	class SceneView;

	class SceneUnitSight : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_Sight;
	public:
		SceneUnitSight();
		virtual ~SceneUnitSight() override;

		void SetSceneView(SceneView *scene_view);
		void SetRadius(float val);
		void SetViewCamp(EViewCamp val);
		EViewCamp GetViewCamp() { return m_view_camp; }
		void UpdateState();

	protected:
		virtual void OnEnterScene() override;
		virtual void OnDestroy() override;
		void ClearSight();
		SceneView *m_scene_view = nullptr;
		float m_sight_radius = 12.0f;
		EViewCamp m_view_camp = EViewCamp_Observer;
		ViewGridVec m_cover_girds;
	};
}