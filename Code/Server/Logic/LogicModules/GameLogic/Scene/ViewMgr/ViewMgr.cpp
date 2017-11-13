#include "ViewMgr.h"
#include <fstream>
#include "ViewDefine.h"
#include "ViewGrid.h"
#include "Common/Utils/MemoryUtil.h"

namespace GameLogic
{

	ViewMgr::ViewMgr(Scene *scene)
	{
		m_scene = scene;
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
					ViewGrid *grid = new ViewGrid(this, center, m_grid_edge_length, (EViewGridType)val);
					m_grids[m_row_num * row + col] = grid;
				}
			}
		} while (false);
		
		ifs.close();
		return true;
	}

	void ViewMgr::OnAddSceneObject(std::shared_ptr<SceneObject> scene_obj)
	{

	}

	void ViewMgr::OnRemoveSceneObject(std::shared_ptr<SceneObject> scene_obj)
	{

	}
}
