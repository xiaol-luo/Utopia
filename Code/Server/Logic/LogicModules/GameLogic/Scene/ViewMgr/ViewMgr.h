#pragma once

#include <string>

namespace GameLogic
{
	class ViewMgr
	{
	public: 
		ViewMgr();
		~ViewMgr();
		bool LoadCfg(std::string file_path);

	protected:
		float m_grid_size = 0;
		int m_row_count = 0;
		int m_col_count = 0;

	};
}

