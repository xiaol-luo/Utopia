#pragma once

#include <vector>
#include <memory>
#include "GameLogic/Scene/Defines/EffectDefine.h"

namespace GameLogic
{
	class EffectBase;
	class SceneEffects;

	class EffectConfigBase
	{
	public:
		virtual std::shared_ptr<EffectBase> CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const = 0;
		const EffectIdVec & GetBeginEffectIds() const { return m_begin_effect_ids; }
		const EndEffectIdVec & GetEndEffectIds() const { return m_end_effect_ids; }
		const TimeLineEffectIdsConfig & GetLoopEffectIds() const { return m_loop_effect_cfg; }
		bool NeedGuild() const { return m_need_guild; }
		bool Reversible() const { return m_reversible; }
		bool CanCancelGuild() const { return m_can_cancel_guild; }

	public:
		void SetId(int val) { id = val; }
		void SetNeedGuild(bool val) { m_need_guild = val; }
		void SetReversible(bool val) { m_reversible = val; }
		void SetCanCancelGuild(bool val) { m_can_cancel_guild = val; }
		void SetBeginEffectIds(const EffectIdVec &val) { m_begin_effect_ids = val; }
		void SetEndEffectIds(const EndEffectIdVec &val) { m_end_effect_ids = val; }
		void SetLoopEffectCfg(const TimeLineEffectIdsConfig &val) { m_loop_effect_cfg = val; }
	protected:
		int id = 0;
		EffectIdVec m_begin_effect_ids;
		EndEffectIdVec m_end_effect_ids;
		TimeLineEffectIdsConfig m_loop_effect_cfg;
		bool m_need_guild = false;
		bool m_reversible = true;
		bool m_can_cancel_guild = true;
	};
}