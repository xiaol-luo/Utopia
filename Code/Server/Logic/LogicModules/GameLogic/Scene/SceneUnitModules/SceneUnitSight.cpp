#include "SceneUnitSight.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneModule/SceneView/SceneView.h"
#include "GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"
#include "Common/Geometry/GeometryUtils.h"

namespace GameLogic
{
	SceneUnitSight::SceneUnitSight() : SceneUnitModule(MODULE_TYPE)
	{
	}

	SceneUnitSight::~SceneUnitSight()
	{
		this->SetSceneView(nullptr);
	}

	void SceneUnitSight::SetSceneView(SceneView * scene_view)
	{
		if (nullptr == scene_view)
			this->ClearSight();
		m_scene_view = scene_view;
	}

	void SceneUnitSight::SetRadius(float val)
	{
		if (val < FLT_EPSILON)
			this->ClearSight();
		m_sight_radius = val;
	}

	void SceneUnitSight::SetViewCamp(EViewCamp val)
	{
		if (val != m_view_camp)
			this->ClearSight();
		m_view_camp = val;
	}

	bool CanSeeGrid(ViewGrid *locate_grid, ViewGrid *check_grid)
	{
		if (EViewGrid_Grass == check_grid->grid_type)
		{
			return EViewGrid_Grass == locate_grid->grid_type && locate_grid->grid_type_group == check_grid->grid_type_group;
		}

		return true;
	}
	bool CanBlockGrid(ViewGrid *locate_grid, ViewGrid *check_grid)
	{
		bool canBlock = false;
		switch (check_grid->grid_type)
		{
		case EViewGrid_Wall:
			canBlock = true;
			break;
		case EViewGrid_Grass:
			canBlock = EViewGrid_Grass != locate_grid->grid_type || locate_grid->grid_type_group != check_grid->grid_type_group;
		}
		return canBlock;
	}

	void SceneUnitSight::UpdateState()
	{
		this->ClearSight();

		if (nullptr == m_scene_view || m_sight_radius < FLT_EPSILON)
			return;
		if (m_view_camp < 0 || m_view_camp >= EViewCamp_Observer)
			return;

		Vector3 pos = this->GetOwner()->GetTransform()->GetPos();
		ViewGrid *locate_grid = m_scene_view->GetGrid(pos.x, pos.z);

		ViewGridSet cover_grids;
		if (nullptr != locate_grid)
		{
			Vector2 locate_pos = locate_grid->center;
			ViewGridVec tmp_grids = m_scene_view->GetCircleCoverGrids(locate_pos.x, locate_pos.y, m_sight_radius);
			cover_grids.insert(tmp_grids.begin(), tmp_grids.end());
			cover_grids.insert(locate_grid);
			ViewGridSet blind_grids; ViewGridVec block_grids;
			for (ViewGrid *grid : cover_grids)
			{
				if (grid == locate_grid) // 自己所在的位置必定可见且不可阻隔视线
					continue;
				if (!CanSeeGrid(locate_grid, grid))
					blind_grids.insert(grid);
				if (CanBlockGrid(locate_grid, grid))
					block_grids.push_back(grid);
			}
			if (!blind_grids.empty())
			{
				for (ViewGrid *grid : blind_grids)
					cover_grids.erase(grid);
				blind_grids.clear();
			}
			for (ViewGrid *block_grid : block_grids)
			{
				float half_grid_size = block_grid->grid_size / 2;
				Vector2 r1 = Vector2(block_grid->center.x - half_grid_size, block_grid->center.y - half_grid_size);
				Vector2 r2 = Vector2(block_grid->center.x + half_grid_size, block_grid->center.y + half_grid_size);
				for (ViewGrid *cover_grid : cover_grids)
				{
					if (cover_grid->grid_type == block_grid->grid_type &&
						cover_grid->grid_type_group == block_grid->grid_type_group)
						continue;
					bool isIntersect = GeometryUtils::IsIntersectRectLineSegment(r1, r2, locate_grid->center, cover_grid->center);
					if (isIntersect)
						blind_grids.insert(cover_grid);
				}
			}
			if (!blind_grids.empty())
			{
				for (ViewGrid *grid : blind_grids)
					cover_grids.erase(grid);
				blind_grids.clear();
			}
		}

		m_cover_girds.assign(cover_grids.begin(), cover_grids.end());
		for (auto grid : m_cover_girds)
		{
			++grid->observing_num[m_view_camp];
		}
	}

	void SceneUnitSight::OnEnterScene()
	{
	}

	void SceneUnitSight::OnDestroy()
	{
		this->SetSceneView(nullptr);
	}

	void SceneUnitSight::ClearSight()
	{
		if (m_cover_girds.empty())
			return;

		for (auto grid : m_cover_girds)
		{
			--grid->observing_num[m_view_camp];
		}
		m_cover_girds.clear();
	}
}