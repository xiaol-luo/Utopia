#include "EffectDefine.h"
#include "assert.h"

namespace GameLogic
{
	bool EndEffectId::Generate(EndEffectId & out_ret, const std::vector<int>& input_vals)
	{
		assert(input_vals.size() >= 2);
		assert(input_vals[0] >= 0 && input_vals[0] <= EEffectEndCase_Break);
		out_ret.end_case = (EEffectEndCase)input_vals[0];
		out_ret.id = input_vals[1];
		return true;
	}
	
	bool GenerateEndEffectIdVec(EndEffectIdVec & out_ret, const std::vector<std::vector<int>>& input_vals)
	{
		for (auto &&item : input_vals)
		{
			EndEffectId eid;
			assert(EndEffectId::Generate(eid, item));
			out_ret.push_back(eid);
		}
		return true;
	}
	
	bool TimeLineEffectId::Generate(TimeLineEffectId & out_ret, const std::vector<int>& input_vals)
	{
		assert(input_vals.size() >= 2);
		assert(input_vals[0] >= 0);
		out_ret.wait_ms = (EEffectEndCase)input_vals[0];
		out_ret.id = input_vals[1];
		return true;
	}

	bool TimeLineEffectIdsConfig::Generate(TimeLineEffectIdVec & out_ret, const std::vector<std::vector<int>>& input_vals)
	{
		for (auto &&item : input_vals)
		{
			TimeLineEffectId eid;
			assert(TimeLineEffectId::Generate(eid, item));
			out_ret.push_back(eid);
		}
		return true;
	}
}
