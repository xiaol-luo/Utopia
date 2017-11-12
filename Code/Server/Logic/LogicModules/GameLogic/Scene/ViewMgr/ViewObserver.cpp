#include "ViewObserver.h"

namespace GameLogic
{
	ViewObserver::ViewObserver(ViewMgr *view_mgr, uint64_t id, float view_range, ViewCamp view_camp)
	{
		m_view_mgr = view_mgr;
		m_id = id;
		m_view_range = view_range;
		m_view_camp = view_camp;
	}

	ViewObserver::~ViewObserver()
	{

	}
}