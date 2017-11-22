#include "FightParameter.h"

static const float F_PERCENT_DEVIDE = 10000.0f;
static const float F_1_Over_PERCENT_DIVIDE = 1 / F_PERCENT_DEVIDE;

namespace GameLogic
{
	FightParameter::FightParameter()
	{
	}

	FightParameter::~FightParameter()
	{
	}

	void FightParameter::SetMinValue(int val)
	{
		m_min_value = val;
		NumUtil::MakeInAscOrder(m_min_value, m_max_value);
		m_value = NumUtil::GetInRange(m_value, m_min_value, m_max_value);
	}

	void FightParameter::SetMaxValue(int val)
	{
		m_max_value = val;
		NumUtil::MakeInAscOrder(m_min_value, m_max_value);
		m_value = NumUtil::GetInRange(m_value, m_min_value, m_max_value);
	}

	void FightParameter::Recal()
	{
		int old_value = m_value;
		float add_percent = 1 + m_extra_percent.GetValue() * F_1_Over_PERCENT_DIVIDE;
		int base_value = m_base_value.GetValue();
		int extra_value = m_extra_value.GetValue();
		if (m_is_percent_as_denominator)
		{
			if (0 == add_percent)
				add_percent = FLT_EPSILON;
			m_value = base_value / add_percent + extra_value;
		}
		else
		{
			m_value = base_value * add_percent + extra_value;
		}
		m_value = NumUtil::GetInRange(m_value, m_min_value, m_max_value);
		if (nullptr != m_value_change_cb && m_value != old_value)
			m_value_change_cb(m_fight_param, m_value, old_value);
	}
	int FightParameter::GetValue(bool recal)
	{
		if (recal)
			this->Recal();
		return m_value;
	}
}