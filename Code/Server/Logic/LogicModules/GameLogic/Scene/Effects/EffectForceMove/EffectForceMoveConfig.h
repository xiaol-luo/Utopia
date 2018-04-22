#pragma once

#include "GameLogic/Scene/Effects/EffectConfigBase.h"

namespace Config
{
	struct CsvEffectForceMoveConfig;
}

namespace GameLogic
{
	class SceneEffects;

	class EffectForceMoveConfig : public EffectConfigBase
	{
	public:
		virtual std::shared_ptr<EffectBase> CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const;

	public:
		bool InitCfg(const Config::CsvEffectForceMoveConfig *csv_cfg);

	protected:
	};
}
