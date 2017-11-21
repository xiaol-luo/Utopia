#include "FightParameterMgr.h"
#include "FightParameter.h"
#include <string>

namespace GameLogic
{
	FightParameterMgr::FightParameterMgr(FightUnit * fight_unit)
	{
		m_fight_unit = fight_unit;
		memset(m_params, 0, sizeof(m_params));
	}

	FightParameterMgr::~FightParameterMgr()
	{
		for (int i = 0; i < sizeof(m_params) / sizeof(m_params[0]); ++i)
		{
			if (nullptr != m_params[i])
			{
				delete m_params[i];
				m_params[i] = nullptr;
			}
		}
	}


}