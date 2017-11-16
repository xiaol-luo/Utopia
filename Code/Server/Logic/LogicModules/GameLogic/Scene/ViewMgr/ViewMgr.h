#pragma once

#include "ViewDefine.h"
#include <string>

namespace GameLogic
{
	struct ViewGrid;
	class Scene;
	struct ViewSnapshot;

	class ViewMgr
	{
	public: 
		ViewMgr(Scene *scene);
		~ViewMgr();
		bool LoadCfg(std::string file_path);
		void Update();

		ViewGridVec GetCircleCoverGrids(float center_x, float center_y, float radius);
		ViewGridVec GetAABBConverGrids(float min_x, float min_y, float max_x, float max_y);
		int CalGridIdx(int row, int col);
		bool CalRowCol(int grid_idx, int &row, int &col);
		int InRowIdx(float y);
		int InColIdx(float x);
		int InGridIdx(float x, float y);
		ViewGrid * GetGrid(float x, float y);
		ViewGrid * GetGrid(int grid_id);
		ViewGrid * GetUpGrid(int grid_idx);
		ViewGrid * GetRightGrid(int grid_idx);
		ViewGrid * GetButtomGrid(int grid_idx);
		ViewGrid * GetLeftGrid(int grid_idx);

		const ViewSnapshot * GetSnapshot(EViewCamp camp);
		
	protected:
		Scene *m_scene = nullptr;
		float m_grid_edge_length = 0;
		int m_row_num = 0;
		int m_col_num = 0;
		int m_grid_count = 0;
		float m_max_x = 0;
		float m_max_y = 0;
		ViewGrid **m_grids = nullptr;
		ViewUnitMap m_view_units;
		ViewSnapshot **m_curr_snapshots = nullptr;
		ViewSnapshot **m_pre_snapshots = nullptr;

	public:
		void OnAddSceneObject(std::shared_ptr<SceneObject> scene_obj);
		void OnRemoveSceneObject(std::shared_ptr<SceneObject> scene_obj);
		void OnSceneObjectPosChange(std::shared_ptr<SceneObject> scene_obj);
	};
}

