#include "ViewGrid.h"


namespace GameLogic
{

	ViewGrid::ViewGrid(ViewMgr *mgr, Vector2 center, float size, EViewGridType grid_type)
	{
		m_view_mgr = mgr;
		m_center = center;
		m_size = size;
		m_grid_type = grid_type;
		memset(m_observing_num, 0, sizeof(m_observing_num));
	}

	ViewGrid::~ViewGrid()
	{

	}
}
