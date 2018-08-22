#include "EffectGroupConfig.h"
#include "EffectGroup.h"
#include "Config/AutoCsvCode/effect/CsvEffectGroupConfig.h"
#include <assert.h>
#include <sol.hpp>

namespace GameLogic
{
	std::shared_ptr<EffectBase> EffectGroupConfig::CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectGroup>(this, scene_effects, effect_key);
	}

	bool EffectGroupConfig::InitCfg(const Config::CsvEffectGroupConfig * csv_cfg, void **param)
	{
		sol::table json_cfg = *(sol::table *)param;
		if (json_cfg.valid())
		{
			m_id = json_cfg["id"];
			m_name = json_cfg["name"];

			{
				sol::table json_begin_effect_ids = json_cfg["begin_effect_ids"];
				for (auto kv_pair : json_begin_effect_ids)
				{
					int effect_id = kv_pair.second.as<int>();
					m_begin_effect_ids.push_back(effect_id);
				}
			}
			{
				sol::table json_begin_effect_ids = json_cfg["end_effect_ids"];
				std::vector<std::vector<int>> vecs;
				for (auto kv_pair : json_begin_effect_ids)
				{
					std::vector<int> vec_param;
					sol::table tb = kv_pair.second.as<sol::table>();
					vec_param.push_back(tb["end_case"]);
					vec_param.push_back(tb["effect_id"]);
					vecs.push_back(vec_param);
				}
				assert(GenerateEndEffectIdVec(m_end_effect_ids, vecs));
			}
			{
				sol::table json_begin_effect_ids = json_cfg["timeline_effect_ids"];
				std::vector<std::vector<int>> vecs;
				for (auto kv_pair : json_begin_effect_ids)
				{
					std::vector<int> vec_param;
					sol::table tb = kv_pair.second.as<sol::table>();
					vec_param.push_back(tb["begin_ms"]);
					vec_param.push_back(tb["effect_id"]);
					vecs.push_back(vec_param);
				}
				assert(TimeLineEffectIdsConfig::Generate(m_loop_effect_cfg, vecs));
			}
			m_need_guide = json_cfg["need_guide"];
			m_can_cancel_guide = json_cfg["can_cancel_guide"];

			return true;
		}
		else if (nullptr != csv_cfg)
		{
			m_id = csv_cfg->id;
			m_begin_effect_ids = csv_cfg->begin_effect_ids;
			assert(TimeLineEffectIdsConfig::Generate(m_loop_effect_cfg, csv_cfg->timeline_effect_ids));
			assert(GenerateEndEffectIdVec(m_end_effect_ids, csv_cfg->end_effect_ids));
			m_need_guide = csv_cfg->need_guide;
			m_can_cancel_guide = csv_cfg->can_cancel_guide;
			return true;
		}
		return false;
	}
}

