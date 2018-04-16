#include "EffectDefine.h"
#include "assert.h"
#include <algorithm>

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
	
	bool GenerateEndEffectIdVec(std::vector<EndEffectId> & out_ret, const std::vector<std::vector<int>>& input_vals)
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

	bool TimeLineEffectIdsConfig::Generate(TimeLineEffectIdsConfig & out_ret, const std::vector<std::vector<int>>& input_vals)
	{
		int min_wait_ms = INT_MAX;
		int max_wait_ms = INT_MIN;

		for (auto &&item : input_vals)
		{
			TimeLineEffectId eid;
			assert(TimeLineEffectId::Generate(eid, item));
			out_ret.effect_ids.push_back(eid);

			min_wait_ms = std::min(min_wait_ms, eid.wait_ms);
			max_wait_ms = std::max(max_wait_ms, eid.wait_ms);
		}

		out_ret.min_wait_ms = min_wait_ms;
		out_ret.max_wait_ms = max_wait_ms;
		return true;
	}
}
