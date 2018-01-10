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
		return true;
	}
}

