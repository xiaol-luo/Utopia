#pragma once

#include "ViewDefine.h"

namespace GameLogic
{
	class ViewMgr;

	class ViewGrid
	{
	public:
		ViewGrid(ViewMgr *mgr, Vector2 center, float size, EViewGridType grid_type);
		~ViewGrid();

	private:
		ViewMgr *m_view_mgr = nullptr;
		Vector2 m_center;
		float m_size = 0;
		EViewGridType m_grid_type = EViewGrid_Ground;
		int m_observing_num[EViewCamp_All];
		ViewUnitSet m_view_units;
	};
}
