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
		float GetTimeSec() const { return m_timeSec; }
		float GetSpeed() const { return m_speed; }
		bool IgnoreTerrian() const { return m_ignoreTerrian; }
		float GetMoveDeg() const { return m_moveDeg; }
		EForceMoveAnchor GetAnchor() const { return m_anchor; }

	public:
		bool InitCfg(const Config::CsvEffectForceMoveConfig *csv_cfg, void **param);

	protected:
		EForceMoveAnchor m_anchor;
		int m_timeSec = 0;
		float m_speed = 0;
		bool m_ignoreTerrian = false;
		float m_moveDeg = 0;

		enum MoveSetting
		{
			TimeSpeed,
			TimeDistance,
			DistanceSpeed
		};
	};
}
