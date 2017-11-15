#include "ViewMgr.h"
#include <fstream>
#include "ViewDefine.h"
#include "ViewGrid.h"
#include "Common/Utils/MemoryUtil.h"
#include "ViewUnit.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"
#include "ViewSnapshot.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"
#include "Common/Utils/NumUtils.h"
#include "Common/Geometry/GeometryUtils.h"

namespace GameLogic
{
	ViewMgr::ViewMgr(Scene *scene)
	{
		m_scene = scene;
		m_pre_snapshots = (ViewSnapshot **)Malloc(sizeof(ViewSnapshot *) * EViewCamp_All);
		m_curr_snapshots = (ViewSnapshot **)Malloc(sizeof(ViewSnapshot *) * EViewCamp_All);
		for (int i = 0; i < EViewCamp_All; ++i)
		{
			m_pre_snapshots[i] = new ViewSnapshot();
			m_curr_snapshots[i] = new ViewSnapshot();
		}
	}

	ViewMgr::~ViewMgr()
	{
		if (nullptr != m_grids)
		{
			for (int i = 0; i < m_grid_count; ++i)
			{
				if (nullptr != m_grids[i])
				{
					delete m_grids[i];
				}
			}
			Free(m_grids);
		}
		m_grids = nullptr;
		m_grid_count = 0;

		for (int i = 0; i < EViewCamp_All; ++i)
		{
			delete m_pre_snapshots[i];
			delete m_curr_snapshots[i];
		}
		Free(m_pre_snapshots); m_pre_snapshots = nullptr;
		Free(m_curr_snapshots); m_curr_snapshots = nullptr;
	}

	bool ViewMgr::LoadCfg(std::string file_path)
	{
		std::ifstream  ifs(file_path);
		if (!ifs.good())
			return false;

		do
		{
			char line_buffer[128];
			ifs.getline(line_buffer, sizeof(line_buffer));
			if (ifs.fail())
				break;
			int ret = sscanf(line_buffer, "%f %d %d", &m_grid_edge_length, &m_row_num, &m_col_num);
			if (m_grid_edge_length <= 0 || m_row_num <= 0 || m_col_num <= 0)
				break;


			// m_grids = new ViewGrid[m_row_count * m_col_count];
			m_grid_count = m_row_num * m_col_num;
			m_grids = (ViewGrid **)Malloc(sizeof(ViewGrid *) * m_grid_count);
			memset(m_grids, 0, sizeof(ViewGrid *) * m_grid_count);
			m_max_x = m_col_num * m_grid_edge_length;
			m_max_y = m_row_num * m_grid_edge_length;
			

			bool isOk = true;
			for (int row = 0; row < m_row_num; ++ row)
			{
				if (!isOk)
					break;

				for (int col = 0; col < m_col_num; ++col)
				{
					if (!isOk)
						break;

					int val = 0;
					if (!ifs.eof())
					{
						ifs >> val;
						if (ifs.fail())
						{
							isOk = false;
							break;
						}
					}

					int grid_idx = m_col_num * row + col;
					Vector2 center(m_grid_edge_length * col + m_grid_edge_length / 2, m_grid_edge_length * row + m_grid_edge_length / 2);
					ViewGrid *grid = new ViewGrid(this, grid_idx, center, m_grid_edge_length, (EViewGridType)val);
					m_grids[m_row_num * row + col] = grid;
				}
			}
		} while (false);
		
		ifs.close();
		return true;
	}

	void ViewMgr::Update()
	{
		{
			for (auto it : m_view_units)
			{
				it.second->UpdateState();
			}
		}
		{
			ViewSnapshot **tmp_snapshot = m_pre_snapshots;
			m_pre_snapshots = m_curr_snapshots;
			m_curr_snapshots = tmp_snapshot;

			for (int camp = 0; camp < EViewCamp_All; ++camp)
			{
				ViewSnapshot *snapshot = m_curr_snapshots[camp];
				snapshot->Reset();
				for (int idx = 0; idx < m_grid_count; ++idx)
				{
					ViewGrid *grid = m_grids[idx];
					if (!grid->CanSee(camp))
						continue;
					snapshot->view_grids.push_back(grid);
					for (auto it : grid->m_body_units)
					{
						ViewUnit *view_unit = it.second;
						snapshot->scene_objs.insert_or_assign(view_unit->GetObjId(), view_unit->GetSceneObjWptr());
					}
				}
			}

			for (int i = 0; i < EViewCamp_All; ++i)
			{
				ViewSnapshotDifference diff = m_curr_snapshots[i]->CalDifference(m_pre_snapshots[i]);
				if (!diff.miss_scene_objs.empty() ||
					!diff.more_scene_objs.empty() ||
					!diff.miss_view_grids.empty() ||
					!diff.more_view_grids.empty())
				{
					diff.PrintLog();
				}
			}
		}
	}

	ViewGridVec ViewMgr::GetCircleCoverGrids(float center_x, float center_y, float radius)
	{
		ViewGridVec possible_grids = this->GetAABBConverGrids(center_x - radius, center_y - radius, center_x + radius, center_y + radius);
		ViewGridVec grids;
		for (auto grid : possible_grids)
		{
			if (GeometryUtils::IsCirlceRectIntersect(
				Vector2(center_x, center_y), radius, 
				grid->m_center, m_grid_edge_length, m_grid_edge_length))
			{
				grids.push_back(grid);
			}
		}
		return grids;
	}

	ViewGridVec ViewMgr::GetAABBConverGrids(float x1, float y1, float x2, float y2)
	{
		ViewGridVec grids;
		int row1 = InRowIdx(y1);
		int col1 = InColIdx(x1);
		int row2 = InRowIdx(y2);
		int col2 = InColIdx(x2);
		if ((row1 < 0 && row2 < 0) || (row1 >= m_row_num || row2 >= m_row_num) ||
			(col1 < 0 && col2 < 0) || (col1 >= m_col_num && col2 >= m_col_num))
			return grids;
		
		row1 = NumUtil::GetInRange(row1, 0, m_row_num);
		row2 = NumUtil::GetInRange(row2, 0, m_row_num);
		col1 = NumUtil::GetInRange(col1, 0, m_col_num);
		col2 = NumUtil::GetInRange(col2, 0, m_col_num);
		NumUtil::MakeInAscOrder(row1, row2);
		NumUtil::MakeInAscOrder(col1, col2);

		for (int row = row1; row <= row2; ++row)
		{
			for (int col = col1; col <= col2; ++col)
			{
				int grid_idx = CalGridIdx(row, col);
				if (grid_idx >= 0 && grid_idx < m_grid_count)
					grids.push_back(m_grids[grid_idx]);
			}
		}
		return grids;
	}

	int ViewMgr::CalGridIdx(int row, int col)
	{
		return row * m_col_num + col;
	}

	int ViewMgr::InRowIdx(float y)
	{
		if (y < 0)
			return INT32_MIN;
		if (y >= m_max_y)
			return INT32_MAX;
		return y / m_grid_edge_length;
	}

	int ViewMgr::InColIdx(float x)
	{
		if (x < 0)
			return INT32_MIN;
		if (x >= m_max_x)
			return INT32_MAX;
		return x / m_grid_edge_length;
	}

	int ViewMgr::InGridIdx(float x, float y)
	{
		int row = this->InRowIdx(y);
		int col = this->InColIdx(x);
		if (row < 0 || row >= m_row_num || col < 0 || col >= m_col_num)
			return VIEW_GRID_INVALID_IDX;
		return CalGridIdx(row, col);
	}

	ViewGrid * ViewMgr::GetGrid(float x, float y)
	{
		int grid_idx = this->InGridIdx(x, y);
		if (VIEW_GRID_INVALID_IDX == grid_idx)
			return nullptr;
		return m_grids[grid_idx];

	}

	void ViewMgr::OnAddSceneObject(std::shared_ptr<SceneObject> scene_obj)
	{
		if (m_view_units.count(scene_obj->GetId()))
			return;

		ViewUnit *view_unit = new ViewUnit();
		bool ret = view_unit->Init(this, scene_obj);
		if (!ret)
		{
			delete view_unit;
			return;
		}
		m_view_units[scene_obj->GetId()] = view_unit;
		scene_obj->SetViewUnit(view_unit);
	}

	void ViewMgr::OnRemoveSceneObject(std::shared_ptr<SceneObject> scene_obj)
	{
		ViewUnitMap::iterator it = m_view_units.find(scene_obj->GetId());
		if (m_view_units.end() == it)
		{
			scene_obj->SetViewUnit(nullptr);
			return;
		}

		delete it->second;
		scene_obj->SetViewUnit(nullptr);
		m_view_units.erase(it);
	}
	void ViewMgr::OnSceneObjectPosChange(std::shared_ptr<SceneObject> scene_obj)
	{
		ViewUnit *view_unit = scene_obj->GetViewUnit();
		if (nullptr != view_unit)
		{

		}
	}
}
