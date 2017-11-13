#pragma once

#include "ViewDefine.h"
#include <string>

namespace GameLogic
{
	class ViewGrid;
	class Scene;

	class ViewMgr
	{
	public: 
		ViewMgr(Scene *scene);
		~ViewMgr();
		bool LoadCfg(std::string file_path);

	protected:
		Scene *m_scene = nullptr;
		float m_grid_edge_length = 0;
		int m_row_num = 0;
		int m_col_num = 0;
		int m_grid_count = 0;
		ViewGrid **m_grids = nullptr;
		ViewUnitMap m_units;

	public:
		void OnAddSceneObject(std::shared_ptr<SceneObject> scene_obj);
		void OnRemoveSceneObject(std::shared_ptr<SceneObject> scene_obj);
	};
}

