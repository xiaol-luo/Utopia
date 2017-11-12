#pragma once

#include "ViewDefine.h"

namespace GameLogic
{
	class ViewMgr;

	class ViewGrid
	{
	public:
		ViewGrid(ViewMgr *mgr, Vector2 center, float size);
		~ViewGrid();

	private:
		ViewMgr *m_view_mgr = nullptr;
		Vector2 m_center;
		float m_size = 0;
		ViewObserverMap m_observers;
		ViewVisualUnitMap m_visual_units;
	};
}
