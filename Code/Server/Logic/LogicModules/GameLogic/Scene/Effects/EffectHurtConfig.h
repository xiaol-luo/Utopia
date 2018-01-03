#pragma once

#include "EffectConfigBase.h"

namespace Config
{
	struct CsvEffectHurtConfig;
}

namespace GameLogic
{
	class SceneEffects;

	class EffectHurtConfig : public EffectConfigBase
	{
	public:
		virtual std::shared_ptr<EffectBase> CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const;

	public:
		bool InitCfg(const Config::CsvEffectHurtConfig *csv_cfg);
		int GetHurt() const { return m_hurt; }

	protected:
		int m_hurt = 0;
	};
}
