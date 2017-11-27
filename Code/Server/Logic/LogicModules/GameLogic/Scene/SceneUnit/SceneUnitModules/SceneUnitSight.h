#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"
#include "GameLogic/Scene/ViewMgr/ViewDefine.h"

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
		void UpdateState();

	protected:
		virtual void OnAwake() override;
		virtual void OnDestroy() override;
		void ClearSight();
		SceneView *m_scene_view = nullptr;
		float m_sight_radius = 6.0f;
		EViewCamp m_view_camp = EViewCamp_None;
		ViewGridVec m_cover_girds;
	};
}