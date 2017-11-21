#pragma once

#include <vector>
#include "Network/Protobuf/BattleEnum.pb.h"

namespace GameLogic
{
	enum ECalulateNumberStrategy
	{
		ECPS_Overlay = 0,		// 叠加
		ECPS_MaxPriority,		// 最大优先
		ECPS_MinPriority,		// 最小优先

		ECPS_Count,
	};

	using CalulateNumberStrategy = int (*)(const std::vector<int> nums);

	class FightParameter
	{
	public: 
		FightParameter();
		~FightParameter();

		void SetFightParam(NetProto::EFightParam val) { m_fight_param = val; }
		void SetValueAsDenominator(bool val) { m_is_value_as_denominator = val; } 

	private:
		void Recal();
	private:
		NetProto::EFightParam m_fight_param;
		bool m_is_value_as_denominator = false;
		bool m_is_changed = false;
		
		int m_add_percent = 0;
		int m_min_add_percent = INT32_MIN;
		int m_max_add_percent = INT32_MAX;
		std::vector<int> m_add_percents;
		ECalulateNumberStrategy m_cal_percent_strategy;

		int m_base_value = 0;
		int m_min_base_value = INT32_MIN;
		int m_max_base_value = INT32_MAX;
		std::vector<int> m_base_values;
		ECalulateNumberStrategy m_cal_base_value_strategy;

		int m_value = 0;
		int m_min_value = INT32_MIN;
		int m_max_value = INT32_MAX;
	};
}