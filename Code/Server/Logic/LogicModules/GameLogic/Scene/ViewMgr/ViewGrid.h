#pragma once

#include "ViewDefine.h"

namespace GameLogic
{
	class ViewMgr;

	struct ViewGrid
	{
		ViewGrid(ViewMgr *mgr, int _id, Vector2 center, float size, EViewGridType grid_type);
		~ViewGrid();
		bool CanSee(EViewCamp camp);
		bool CanSee(int camp);

		int grid_id = -1;
		ViewMgr *m_view_mgr = nullptr;
		Vector2 m_center;
		float m_size = 0;
		EViewGridType m_grid_type = EViewGrid_Ground;
		int m_observing_num[EViewCamp_All];
		ViewUnitSet m_view_units;
	};
}
