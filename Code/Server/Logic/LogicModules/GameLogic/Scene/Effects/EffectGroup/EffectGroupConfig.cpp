#include "EffectGroupConfig.h"
#include "EffectGroup.h"
#include "Config/AutoCsvCode/effect/CsvEffectGroupConfig.h"
#include <assert.h>

namespace GameLogic
{
	std::shared_ptr<EffectBase> EffectGroupConfig::CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectGroup>(this, scene_effects, effect_key);
	}

	bool EffectGroupConfig::InitCfg(const Config::CsvEffectGroupConfig * csv_cfg)
	{
		m_id = csv_cfg->id;
		m_begin_effect_ids = csv_cfg->begin_effect_ids;
		assert(TimeLineEffectIdsConfig::Generate(m_loop_effect_cfg, csv_cfg->timeline_effect_ids));
		assert(GenerateEndEffectIdVec(m_end_effect_ids, csv_cfg->end_effect_ids));
		m_need_guide = csv_cfg->need_guide;
		m_can_cancel_guide = csv_cfg->can_cancel_guide;
		return true;
	}
}

