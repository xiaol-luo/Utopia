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

		Vector3 pos = this->GetOwner()->GetTransform()->GetPos();
		ViewGrid *locate_grid = m_scene_view->GetGrid(pos.x, pos.z);
		if (nullptr != locate_grid)
		{
			if (ESceneObjectShape_Circle == m_shape)
				m_cover_girds = m_scene_view->GetCircleCoverGrids(locate_grid->center.x, locate_grid->center.y, this->GetRadius());
			for (auto grid : m_cover_girds)
			{
				grid->su_bodies.insert_or_assign(this->GetId(), this->GetOwner()->shared_from_this());
			}
		}
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