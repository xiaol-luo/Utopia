#include "ViewMgr.h"
#include <fstream>
#include "ViewDefine.h"
#include "ViewGrid.h"
#include "Common/Utils/MemoryUtil.h"
#include "ViewUnit.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"
#include "ViewSnapshot.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"

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
					Vector2 center(m_grid_edge_length * row + m_grid_edge_length / 2, m_grid_edge_length * col + m_grid_edge_length / 2);
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
					for (ViewUnitSet::iterator it = grid->m_view_units.begin(); it != grid->m_view_units.end(); ++ it)
					{
						ViewUnit *view_unit = *it;
						snapshot->scene_objs.insert_or_assign(view_unit->GetObjId(), view_unit->GetSceneObjWptr());
					}
				}
			}

			for (int i = 0; i < EViewCamp_All; ++i)
			{
				ViewSnapshotDifference diff = m_curr_snapshots[i]->CalDifference(m_pre_snapshots[i]);
				// TODO: something
			}
		}
	}

	void ViewMgr::OnAddSceneObject(std::shared_ptr<SceneObject> scene_obj)
	{
		if (m_units.count(scene_obj->GetId()))
			return;

		ViewUnit *view_unit = new ViewUnit();
		bool ret = view_unit->Init(this, scene_obj);
		if (!ret)
		{
			delete view_unit;
			return;
		}
		m_units[scene_obj->GetId()] = view_unit;
		scene_obj->SetViewUnit(view_unit);
	}

	void ViewMgr::OnRemoveSceneObject(std::shared_ptr<SceneObject> scene_obj)
	{
		ViewUnitMap::iterator it = m_units.find(scene_obj->GetId());
		if (m_units.end() == it)
		{
			scene_obj->SetViewUnit(nullptr);
			return;
		}

		delete it->second;
		scene_obj->SetViewUnit(nullptr);
		m_units.erase(it);
	}
	void ViewMgr::OnSceneObjectPosChange(std::shared_ptr<SceneObject> scene_obj)
	{
		ViewUnit *view_unit = scene_obj->GetViewUnit();
		if (nullptr != view_unit)
		{
			view_unit->SetViewChange(true);
			view_unit->SetVisualChange(true);
		}
	}
}
