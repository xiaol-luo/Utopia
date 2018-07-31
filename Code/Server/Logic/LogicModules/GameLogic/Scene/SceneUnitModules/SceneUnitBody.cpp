#include "SceneUnitBody.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneModule/SceneView/SceneView.h"
#include "GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"
#include "Common/Geometry/GeometryUtils.h"
#include "Common/Geometry/Vector3.h"
#include "Common/Geometry/Vector2.h"

namespace GameLogic
{
	const ESceneUnitModule SceneUnitBody::MODULE_TYPE = ESceneUnitModule_Body;

	SceneUnitBody::SceneUnitBody() : SceneUnitModule(MODULE_TYPE)
	{

	}

	SceneUnitBody::~SceneUnitBody()
	{
		this->SetSceneView(nullptr);
	}

	void SceneUnitBody::SetSceneView(SceneView * scene_view)
	{
		if (nullptr == scene_view)
			this->ResetCoverGrids();
		m_scene_view = scene_view;
	}

	void SceneUnitBody::SetRadius(float val)
	{
		if (ESceneObjectShape_Circle != m_shape)
			return;
		if (val < FLT_EPSILON)
			this->ResetCoverGrids();
		m_size_x = val;
	}

	float SceneUnitBody::GetRadius()
	{
		if (ESceneObjectShape_Circle != m_shape)
			return 0;
		return m_size_x < FLT_EPSILON ? 0 : m_size_x;
	}

	void SceneUnitBody::UpdateState()
	{
		this->ResetCoverGrids();

		if (nullptr == m_scene_view)
			return;
		if (ESceneObjectShape_Circle == m_shape && this->GetRadius() < FLT_EPSILON)
			return;

		int unitType = this->GetOwner()->GetUnitType();
		Vector3 pos = this->GetOwner()->GetTransform()->GetPos();
		ViewGrid *locate_grid = m_scene_view->GetGrid(pos.x, pos.z);
		if (nullptr != locate_grid)
		{
			if (ESceneObjectShape_Circle == m_shape)
				m_cover_girds = m_scene_view->GetCircleCoverGrids(locate_grid->center.x, locate_grid->center.y, this->GetRadius());
			for (auto grid : m_cover_girds)
			{
				grid->su_bodies[this->GetId()] = this->GetOwner()->shared_from_this();
			}
		}
	}

	AABB2 SceneUnitBody::CovertRect()
	{
		AABB2 ret;
		Vector2 pos = m_owner->GetTransform()->GetPos().XZ();
		if (ESceneObjectShape_Circle == m_shape)
		{
			Circle circle;
			circle.center = pos;
			circle.radius = m_size_x;
			ret = GeometryUtils::BuildAABB2(circle);
		}
		if (ESceneObjectShape_Rect == m_shape)
		{
			OBB2 obb;
			obb.center = pos;
			obb.x_half_size = m_size_x / 2;
			obb.y_half_size = m_size_y / 2;
			obb.y_axis_dir = m_owner->GetTransform()->GetFaceDir();
			ret = GeometryUtils::BuildAABB2(obb);
		}
		return ret;
	}

	OBB2 SceneUnitBody::GetShapeObb2()
	{
		OBB2 obb;
		obb.center = m_owner->GetTransform()->GetPos().XZ();
		obb.x_half_size = m_size_x;
		obb.y_half_size = m_size_y;
		obb.y_axis_dir = m_owner->GetTransform()->GetFaceDir();
		return std::move(obb);
	}

	Circle SceneUnitBody::GetShapeCircle()
	{
		Circle circle;
		circle.center = m_owner->GetTransform()->GetPos().XZ();
		circle.radius = m_size_x;
		return circle;
	}

	void SceneUnitBody::OnLeaveScene()
	{
		this->ResetCoverGrids();
	}

	void SceneUnitBody::ResetCoverGrids()
	{
		if (m_cover_girds.empty())
			return;

		for (auto grid : m_cover_girds)
		{
			grid->su_bodies.erase(this->GetId());
		}
		m_cover_girds.clear();
	}
}