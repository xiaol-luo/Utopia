#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"
#include "GameLogic/Scene/Defines/ViewDefine.h"
#include "Common/Geometry/GeometryDefine.h"

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

		AABB2 CovertRect();
		ESceneObjectShape GetEShape() { return m_shape; }
		OBB2 GetShapeObb2();
		Circle GetShapeCircle();

	protected:
		ESceneObjectShape m_shape = ESceneObjectShape_Circle;
		float m_size_x = 0.0f;
		float m_size_y = 0.0f;
		ViewGridVec m_cover_girds;
		SceneView *m_scene_view = nullptr;
		void ResetCoverGrids();
	};
}