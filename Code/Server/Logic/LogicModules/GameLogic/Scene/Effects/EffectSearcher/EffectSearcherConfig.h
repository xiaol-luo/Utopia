#pragma once

#include "GameLogic/Scene/Effects/EffectConfigBase.h"

namespace Config
{
	struct CsvEffectSearcherConfig;
}

namespace GameLogic
{
	class SceneEffects;

	class EffectSearcherConfig : public EffectConfigBase
	{
	public:
		virtual std::shared_ptr<EffectBase> CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const;

	public:
		bool InitCfg(const Config::CsvEffectSearcherConfig *csv_cfg, void **param);
		std::vector<int> m_effect_ids;

	protected:
	};
}
