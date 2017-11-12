#pragma once

#include "ViewDefine.h"

namespace GameLogic
{
	class ViewObserver
	{
	public:
		ViewObserver(ViewMgr *view_mgr, uint64_t id, float view_range, ViewCamp view_camp);
		~ViewObserver();

	private:
		ViewMgr *m_view_mgr = nullptr;
		uint64_t m_id = 0;
		float m_view_range = 0;
		ViewCamp m_view_camp = ViewCamp_None;
	};
}