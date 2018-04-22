#include "EffectSearcherConfig.h"
#include "EffectSearcher.h"
#include "Config/AutoCsvCode/effect/CsvEffectSearcherConfig.h"
#include <assert.h>

namespace GameLogic
{
	std::shared_ptr<EffectBase> EffectSearcherConfig::CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectSearcher>(this, scene_effects, effect_key);
	}

	bool EffectSearcherConfig::InitCfg(const Config::CsvEffectSearcherConfig * csv_cfg)
	{
		m_id = csv_cfg->id;
		m_reversible = false;
		m_filter_id = csv_cfg->filter_id;
		m_effect_ids = csv_cfg->effect_ids;
		return true;
	}
}

