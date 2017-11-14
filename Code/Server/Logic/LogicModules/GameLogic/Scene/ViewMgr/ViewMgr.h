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

	protected:
		Scene *m_scene = nullptr;
		float m_grid_edge_length = 0;
		int m_row_num = 0;
		int m_col_num = 0;
		int m_grid_count = 0;
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

