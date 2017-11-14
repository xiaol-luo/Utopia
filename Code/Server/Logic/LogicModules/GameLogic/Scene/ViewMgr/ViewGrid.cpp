#include "ViewGrid.h"


namespace GameLogic
{

	ViewGrid::ViewGrid(ViewMgr *mgr, int id, Vector2 center, float size, EViewGridType grid_type)
	{
		grid_id = id;
		m_view_mgr = mgr;
		m_center = center;
		m_size = size;
		m_grid_type = grid_type;
		memset(m_observing_num, 0, sizeof(m_observing_num));
	}

	ViewGrid::~ViewGrid()
	{

	}
	bool ViewGrid::CanSee(EViewCamp camp)
	{
		return this->CanSee((int)camp);
	}
	bool ViewGrid::CanSee(int camp)
	{
		if (camp < EViewCamp_None || camp > EViewCamp_All)
			return false;
		return m_observing_num[camp];
	}
}
