#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"
#include "GameLogic/Scene/Defines/ViewDefine.h"

namespace GameLogic
{
	class SceneView;

	class SceneUnitBody : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_Body;
	public:
		SceneUnitBody();
		virtual ~SceneUnitBody() override;

		void SetSceneView(SceneView *scene_view);
		void SetRadius(float val);
		float GetRadius();
		void UpdateState();

	protected:
		ESceneObjectShape m_shape = ESceneObjectShape_Circle;
		float m_size_x = 0.0f;
		float m_size_y = 0.0f;
		ViewGridVec m_cover_girds;
		SceneView *m_scene_view = nullptr;
		void ResetCoverGrids();
	};
}