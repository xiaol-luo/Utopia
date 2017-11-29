#include "SceneView.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/GameLogicModule.h"
#include "Config/AutoCsvCode/Scene/CsvSceneConfig.h"
#include <fstream>
#include "Common/Utils/MemoryUtil.h"
#include "Common/Utils/NumUtils.h"
#include "Common/Geometry/GeometryUtils.h"
#include <queue>
#include "Common/Geometry/Vector2.h"
#include "Common/Geometry/Vector3.h"
#include "GameLogic/Scene/ViewMgr/ViewGrid.h"
#include "GameLogic/Scene/ViewMgr/ViewSnapshot.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitSight.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitBody.h"

namespace GameLogic
{
	SceneView::SceneView() : SceneModule(MODULE_TYPE)
	{
		m_pre_snapshots = (ViewSnapshot **)Malloc(sizeof(ViewSnapshot *) * EViewCamp_Observer);
		m_curr_snapshots = (ViewSnapshot **)Malloc(sizeof(ViewSnapshot *) * EViewCamp_Observer);
		for (int i = 0; i < EViewCamp_Observer; ++i)
		{
			m_pre_snapshots[i] = new ViewSnapshot();
			m_curr_snapshots[i] = new ViewSnapshot();
		}
	}

	SceneView::~SceneView()
	{
		for (int i = 0; i < EViewCamp_Observer; ++i)
		{
			delete m_pre_snapshots[i];
			delete m_curr_snapshots[i];
		}
		Free(m_pre_snapshots); m_pre_snapshots = nullptr;
		Free(m_curr_snapshots); m_curr_snapshots = nullptr;
	}

	void SceneView::MakeSnapshot()
	{
		{
			std::vector<uint64_t> expired_ids;
			for (auto kv_pair : m_scene_units)
			{
				auto su = kv_pair.second.lock();
				if (nullptr == su)
				{
					expired_ids.push_back(kv_pair.first);
					continue;
				}
				auto su_sight = su->GetModule<SceneUnitSight>();
				if (nullptr != su_sight)
					su_sight->UpdateState();
				auto su_body = su->GetModule<SceneUnitBody>();
				if (nullptr != su_body)
					su_body->UpdateState();
			}
			if (!expired_ids.empty())
			{
				for (uint64_t id : expired_ids)
					m_scene_units.erase(id);
			}
		}
		{
			ViewSnapshot **tmp_snapshot = m_pre_snapshots;
			m_pre_snapshots = m_curr_snapshots;
			m_curr_snapshots = tmp_snapshot;

			for (int camp = 0; camp < EViewCamp_Observer; ++camp)
			{
				ViewSnapshot *snapshot = m_curr_snapshots[camp];
				snapshot->Reset();
				for (int idx = 0; idx < m_grid_count; ++idx)
				{
					ViewGrid *grid = m_grids[idx];
					if (!grid->CanSee(camp))
						continue;
					snapshot->view_grids.push_back(grid);
					for (auto it : grid->su_bodies)
					{
						std::shared_ptr<SceneUnit> su = it.second.lock();
						if (nullptr == su)
							continue;
						snapshot->scene_units.insert_or_assign(su->GetId(), su);
					}
				}
			}
		}
	}

	bool SceneView::OnAwake()
	{
		bool ret = false;
		Config::CsvSceneConfig *scene_cfg = m_scene->GetCfg();
		ret = this->LoadCfg(m_scene->GetGameLogic()->GetCfgRootPath() + "/" + scene_cfg->terrain_file_path + ".view");
		assert(ret);
		this->GetSceneEvProxy()->Subscribe<SceneUnit *>(ESU_EnterScene,
			std::bind(&SceneView::OnSceneUnitEnterScene, this, std::placeholders::_1));
		return ret;
	}

	void SceneView::OnUpdate()
	{

	}

	void SceneView::OnRelease()
	{
		for (int i = 0; i < EViewCamp_Observer; ++i)
		{
			m_pre_snapshots[i]->Reset();
			m_curr_snapshots[i]->Reset();
		}

		for (auto kv_pair : m_scene_units)
		{
			auto su = kv_pair.second.lock();
			if (nullptr == su)
				continue;
			auto su_sight = su->GetModule<SceneUnitSight>();
			if (nullptr != su_sight)
				su_sight->SetSceneView(nullptr);
			auto su_body = su->GetModule<SceneUnitBody>();
			if (nullptr != su_body)
				su_body->SetSceneView(nullptr);
		}

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
	}

	ViewGridVec SceneView::GetCircleCoverGrids(float center_x, float center_y, float radius)
	{
		ViewGridVec possible_grids = this->GetAABBConverGrids(center_x - radius, center_y - radius, center_x + radius, center_y + radius);
		ViewGridVec grids;
		for (auto grid : possible_grids)
		{
			if (GeometryUtils::IsCirlceRectIntersect(
				Vector2(center_x, center_y), radius,
				grid->center, m_grid_edge_length, m_grid_edge_length))
			{
				grids.push_back(grid);
			}
		}
		return grids;
	}

	ViewGridVec SceneView::GetAABBConverGrids(float x1, float y1, float x2, float y2)
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

	int SceneView::CalGridIdx(int row, int col)
	{
		if (row < 0 || row >= m_row_num || col < 0 || col >= m_col_num)
			return VIEW_GRID_INVALID_IDX;
		return row * m_col_num + col;
	}

	bool SceneView::CalRowCol(int grid_idx, int & row, int & col)
	{
		if (0 == m_col_num || 0 == m_row_num || grid_idx < 0 || grid_idx >= m_grid_count)
			return false;

		row = grid_idx / m_col_num;
		col = grid_idx % m_col_num;
		return true;
	}

	int SceneView::InRowIdx(float y)
	{
		if (y < 0)
			return INT32_MIN;
		if (y >= m_max_y)
			return INT32_MAX;
		return y / m_grid_edge_length;
	}

	int SceneView::InColIdx(float x)
	{
		if (x < 0)
			return INT32_MIN;
		if (x >= m_max_x)
			return INT32_MAX;
		return x / m_grid_edge_length;
	}

	int SceneView::InGridIdx(float x, float y)
	{
		int row = this->InRowIdx(y);
		int col = this->InColIdx(x);
		return CalGridIdx(row, col);
	}

	ViewGrid * SceneView::GetGrid(float x, float y)
	{
		int grid_idx = this->InGridIdx(x, y);
		return this->GetGrid(grid_idx);
	}

	ViewGrid * SceneView::GetGrid(int grid_id)
	{
		if (grid_id < 0 || grid_id >= m_grid_count)
			return nullptr;
		return m_grids[grid_id];
	}

	ViewGrid * SceneView::GetUpGrid(int grid_idx)
	{
		int row, col;
		if (!this->CalRowCol(grid_idx, row, col))
			return nullptr;
		int idx = this->CalGridIdx(row - 1, col);
		return this->GetGrid(idx);
	}

	ViewGrid * SceneView::GetRightGrid(int grid_idx)
	{
		int row, col;
		if (!this->CalRowCol(grid_idx, row, col))
			return nullptr;
		int idx = this->CalGridIdx(row, col + 1);
		return this->GetGrid(idx);
	}

	ViewGrid * SceneView::GetButtomGrid(int grid_idx)
	{
		int row, col;
		if (!this->CalRowCol(grid_idx, row, col))
			return nullptr;
		int idx = this->CalGridIdx(row + 1, col);
		return this->GetGrid(idx);
	}

	ViewGrid * SceneView::GetLeftGrid(int grid_idx)
	{
		int row, col;
		if (!this->CalRowCol(grid_idx, row, col))
			return nullptr;
		int idx = this->CalGridIdx(row, col - 1);
		return this->GetGrid(idx);
	}

	bool SceneView::LoadCfg(std::string file_path)
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
			for (int row = 0; row < m_row_num; ++row)
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
					ViewGrid *grid = new ViewGrid(grid_idx, row, col, center, m_grid_edge_length, (EViewGridType)val);
					m_grids[m_row_num * row + col] = grid;
				}
			}
		} while (false);

		{
			std::queue<ViewGrid *> grid_queue;
			int group_value = 0;
			for (int grid_idx = 0; grid_idx < m_grid_count; ++grid_idx)
			{
				ViewGrid *grid = m_grids[grid_idx];
				if (EViewGrid_Grass == grid->grid_type && 0 == grid->grid_type_group)
				{
					++group_value;
					grid_queue.push(grid);
					while (!grid_queue.empty())
					{
						ViewGrid *handle_grid = grid_queue.front();
						grid_queue.pop();
						if (nullptr == handle_grid || EViewGrid_Grass != handle_grid->grid_type || 0 != handle_grid->grid_type_group)
							continue;
						handle_grid->grid_type_group = group_value;
						grid_queue.push(this->GetUpGrid(handle_grid->grid_id));
						grid_queue.push(this->GetRightGrid(handle_grid->grid_id));
						grid_queue.push(this->GetButtomGrid(handle_grid->grid_id));
						grid_queue.push(this->GetLeftGrid(handle_grid->grid_id));
					}
				}
			}
		}
		{
			std::queue<ViewGrid *> grid_queue;
			int group_value = 0;
			for (int grid_idx = 0; grid_idx < m_grid_count; ++grid_idx)
			{
				ViewGrid *grid = m_grids[grid_idx];
				if (EViewGrid_Wall == grid->grid_type && 0 == grid->grid_type_group)
				{
					++group_value;
					grid_queue.push(grid);
					while (!grid_queue.empty())
					{
						ViewGrid *handle_grid = grid_queue.front();
						grid_queue.pop();
						if (nullptr == handle_grid || EViewGrid_Wall != handle_grid->grid_type || 0 != handle_grid->grid_type_group)
							continue;
						handle_grid->grid_type_group = group_value;
						grid_queue.push(this->GetUpGrid(handle_grid->grid_id));
						grid_queue.push(this->GetRightGrid(handle_grid->grid_id));
						grid_queue.push(this->GetButtomGrid(handle_grid->grid_id));
						grid_queue.push(this->GetLeftGrid(handle_grid->grid_id));
					}
				}
			}
		}

		ifs.close();
		return true;
	}
	void SceneView::OnSceneUnitEnterScene(SceneUnit * su)
	{
		auto su_sight = su->GetModule<SceneUnitSight>();;
		auto su_body = su->GetModule<SceneUnitBody>();
		if (nullptr != su_sight || nullptr != su_body)
			m_scene_units.insert_or_assign(su->GetId(), su->shared_from_this());
	}
}


