#pragma once

#include <vector>
#include <functional>
#include "Network/Protobuf/BattleEnum.pb.h"
#include "Common/Utils/NumUtils.h"

namespace GameLogic
{
	class FightParameterMgr;

	class FightParameter
	{
	public:
		using ValueChangeCallback = std::function<void(NetProto::EFightParam efp, int new_value, int old_value)>;
	public: 
		FightParameter();
		~FightParameter();

		void SetFightParam(NetProto::EFightParam val) { m_fight_param = val; }
		void SetPercentAsDenominator(bool val) { m_is_percent_as_denominator = val; } 

		void SetBaseValueCalStrategy(NumUtil::ECalculateStrategy cs, bool recal = true) { m_base_value.SetCalculateStrategy(cs, recal); }
		void SetBaseValueMin(int val, bool recal = true) { m_base_value.SetMinValue(val, recal); recal ? this->Recal() : 0; }
		void SetBaseValueMax(int val, bool recal = true) { m_base_value.SetMaxValue(val, recal); recal ? this->Recal() : 0;}
		void AddBaseValue(int val, int unique_id = 0, bool recal = true) { m_base_value.Add(val, unique_id, recal); recal ? this->Recal() : 0; }
		void RemoveBaseValue(int val, int unique_id = 0, bool recal = true) { m_base_value.Remove(val, unique_id, recal); recal ? this->Recal() : 0; }

		void SetExtraPercentCalStrategy(NumUtil::ECalculateStrategy cs, bool recal = true) { m_extra_percent.SetCalculateStrategy(cs, recal); }
		void SetExtraPercentMin(int val, bool recal = true) { m_extra_percent.SetMinValue(val, recal); recal ? this->Recal() : 0; }
		void SetExtraPercentMax(int val, bool recal = true) { m_extra_percent.SetMaxValue(val, recal); recal ? this->Recal() : 0; }
		void AddExtraPercent(int val, int unique_id = 0, bool recal = true) { m_extra_percent.Add(val, unique_id, recal); recal ? this->Recal() : 0; }
		void RemoveExtraPercent(int val, int unique_id = 0, bool recal = true) { m_extra_percent.Remove(val, unique_id, recal);  recal ? this->Recal() : 0; }

		void SetExtraValueCalStrategy(NumUtil::ECalculateStrategy cs, bool recal = true) { m_extra_value.SetCalculateStrategy(cs, recal); }
		void SetExtraValueMin(int val, bool recal = true) { m_extra_value.SetMinValue(val, recal); recal ? this->Recal() : 0; }
		void SetExtraValueMax(int val, bool recal = true) { m_extra_value.SetMaxValue(val, recal); recal ? this->Recal() : 0; }
		void AddExtraValue(int val, int unique_id = 0, bool recal = true) { m_extra_value.Add(val, unique_id, recal); recal ? this->Recal() : 0; }
		void RemoveExtraValue(int val, int unique_id = 0, bool recal = true) { m_extra_value.Remove(val, unique_id, recal); recal ? this->Recal() : 0; }

		void SetMinValue(int val);
		void SetMaxValue(int val);
		void Recal();
		NetProto::EFightParam GetFightParam() { return m_fight_param; }
		int GetValue(bool recal = false);
		void SetValueChangeCallback(ValueChangeCallback cb) { m_value_change_cb = cb; }

	private:
		NetProto::EFightParam m_fight_param;
		bool m_is_percent_as_denominator = false;
		
		NumUtil::FightParameterValue<int, int> m_base_value;
		NumUtil::FightParameterValue<int, int> m_extra_value;
		NumUtil::FightParameterValue<int, int> m_extra_percent;
	
		int m_value = 0;
		int m_min_value = INT32_MIN;
		int m_max_value = INT32_MAX;

		ValueChangeCallback m_value_change_cb = nullptr;
	};
}