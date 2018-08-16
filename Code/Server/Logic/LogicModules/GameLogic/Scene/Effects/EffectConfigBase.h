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
		bool NeedGuide() const { return m_need_guide; }
		bool Reversible() const { return m_reversible; }
		bool CanCancelGuide() const { return m_can_cancel_guide; }
		int GetId() const { return m_id; }
		int GetFilterId() const { return m_filter_id; }

	public:
		virtual bool FinalCheck() { return true; }

	protected:
		int m_id = 0;
		std::string m_name;
		EffectIdVec m_begin_effect_ids;
		EndEffectIdVec m_end_effect_ids;
		TimeLineEffectIdsConfig m_loop_effect_cfg;
		bool m_need_guide = false;
		bool m_reversible = true;	// �Ƿ���棬hurt heal�������Բ�����, ����������
		bool m_can_cancel_guide = true;
		int m_filter_id = 0;
	};
}