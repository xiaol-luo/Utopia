#include "ViewGrid.h"


namespace GameLogic
{

	ViewGrid::ViewGrid(ViewMgr *mgr, int _id, int _row, int _col, Vector2 _center, float _size, EViewGridType _grid_type)
	{
		grid_id = _id;
		row = _row;
		col = _col;
		view_mgr = mgr;
		center = _center;
		grid_size = _size;
		grid_type = _grid_type;
		memset(observing_num, 0, sizeof(observing_num));
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
		return observing_num[camp];
	}
}
