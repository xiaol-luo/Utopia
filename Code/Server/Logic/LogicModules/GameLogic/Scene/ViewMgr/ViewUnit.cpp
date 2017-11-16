#include "ViewUnit.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"
#include "ViewGrid.h"
#include "ViewMgr.h"
#include "Common/Geometry/GeometryUtils.h"

namespace GameLogic
{
	ViewUnit::ViewUnit()
	{
	}

	ViewUnit::~ViewUnit()
	{
		this->Reset();
	}

	bool ViewUnit::Init(ViewMgr *view_mgr, std::shared_ptr<SceneObject> scene_obj)
	{
		this->Reset();
		m_view_mgr = view_mgr;
		m_scene_obj = scene_obj;
		m_objid = scene_obj->GetId();
		m_view_camp = scene_obj->GetViewCamp();
		m_has_body = true;
		m_has_view = true;
		return true;
	}

	void ViewUnit::Reset()
	{
		if (!m_has_view && !m_has_body)
			return;

		m_view_mgr = nullptr;
		auto scene_obj = m_scene_obj.lock();
		if (nullptr != scene_obj && scene_obj->GetViewUnit() == this)
				scene_obj->SetViewUnit(nullptr);
		m_scene_obj.reset();
		m_objid = 0;
		m_view_camp = EViewCamp_None;
		if (m_has_view)
		{
			for (auto view_grid : m_view_cover_girds)
			{
				--view_grid->observing_num[m_view_camp];
			}
		}
		m_view_cover_girds.clear();
		
		if (m_has_body)
		{
			for (auto view_grid : m_body_cover_girds)
			{
				view_grid->body_units.erase(m_objid);
			}
		}
		m_body_cover_girds.clear();

		m_has_body = false;
		m_has_view = false;
	}

	Vector2 ViewUnit::GetPos()
	{
		auto so = this->GetSceneObjSptr();
		if (nullptr != so)
			return so->GetPos().xz();
		return InvalidViewPos;
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

	struct VectorAndAngle
	{
		Vector2 v;
		float angle = 0;
	};

	void ViewUnit::UpdateState()
	{
		std::shared_ptr<SceneObject> so = m_scene_obj.lock();
		if (nullptr == so)
		{
			this->Reset();
			return;
		}

		Vector3 pos = so->GetPos();
		ViewGrid *locate_grid = m_view_mgr->GetGrid(pos.x, pos.z);
		bool needUpdate = (nullptr == locate_grid || nullptr == m_locate_grid || locate_grid != m_locate_grid);
		if (!needUpdate)
			return;

		m_locate_grid = locate_grid;
		Vector2 locate_pos = m_locate_grid->center;

		if (m_has_body)
		{
			ViewGridVec cover_grids = m_view_mgr->GetCircleCoverGrids(locate_pos.x, locate_pos.y, so->GetBodyRadius());
			for (auto grid : m_body_cover_girds)
			{
				grid->body_units.erase(m_objid);
			}
			m_body_cover_girds = cover_grids;
			for (auto grid : m_body_cover_girds)
			{
				grid->body_units.insert(std::make_pair(m_objid, this));
			}
		}

		if (m_has_view)
		{
			ViewGridSet cover_grids;
			{
				ViewGridVec tmp_grids = m_view_mgr->GetCircleCoverGrids(locate_pos.x, locate_pos.y, so->GetViewRadius());
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
						bool isIntersect = GeometryUtils::IsRectLineSegmentIntersect(r1, r2, locate_grid->center, cover_grid->center);
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
			for (auto grid : m_view_cover_girds)
			{
				--grid->observing_num[m_view_camp];
			}
			m_view_cover_girds.assign(cover_grids.begin(), cover_grids.end());
			for (auto grid : m_view_cover_girds)
			{
				++grid->observing_num[m_view_camp];
			}
		}
	}
}