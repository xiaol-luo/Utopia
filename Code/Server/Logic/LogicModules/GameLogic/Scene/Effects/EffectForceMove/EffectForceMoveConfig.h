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
		int GetTimeMs() const { return m_timeMs; }
		float GetSpeed() const { return m_speed; }
		bool IgnoreTerrian() const { return m_ignoreTerrian; }
		float GetMoveDeg() const { return m_moveDeg; }
		EEffectFilterAnchor GetAnchor() const { return m_anchor; }

	public:
		bool InitCfg(const Config::CsvEffectForceMoveConfig *csv_cfg);

	protected:
		EEffectFilterAnchor m_anchor;
		int m_timeMs = 0;
		float m_speed = 0;
		bool m_ignoreTerrian = false;
		float m_moveDeg = 0;
	};
}
