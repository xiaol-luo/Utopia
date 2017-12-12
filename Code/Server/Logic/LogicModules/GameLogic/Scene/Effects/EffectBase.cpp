#include "EffectBase.h"
#include "EffectConfigBase.h"
#include <assert.h>
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace GameLogic
{
	EffectBase::EffectBase(EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key)
	{
		assert(cfg && scene_effects);
		m_cfg = cfg;
		m_effect_key = effect_key;
		m_scene_effects = scene_effects;
		m_scene = scene_effects->GetScene();
	}

	EffectBase::~EffectBase()
	{
	}

	void EffectBase::Begin(std::shared_ptr<Skill> skill, uint64_t target_suid, Vector3 pos, Vector2 dir)
	{
		assert(m_stage = EEffectStage_Wait);
		assert(skill);
		m_skill = skill;
		m_target_suid = target_suid;
		m_target_dir = dir;
		m_target_pos = pos;
		m_stage = EEffectStage_Begin;
		m_begin_ms = m_scene->GetLogicMs();

		if (this->Reversible())
		{
			m_scene_effects->AddEffect(this->shared_from_this());
		}

		this->OnBegin(m_skill, m_target_suid, m_target_pos, m_target_dir);
		for (int effect_id : m_cfg->GetBeginEffectIds())
		{
			std::shared_ptr<EffectBase> begin_effect = m_scene_effects->CreateEffect(effect_id);
			assert(begin_effect);
			if (nullptr != begin_effect)
			{
				begin_effect->Begin(m_skill, m_target_suid, m_target_pos, m_target_dir);
			}
		}
		this->OnLateBegin(skill, target_suid, pos, dir);

		if (this->NeedGuild())
		{
			// TODO : HOLD BY SKILL
		}
	}

	void EffectBase::End(EEffectEndCase end_case)
	{
		this->OnEnd(end_case);
		for (EndEffectId item : m_cfg->GetEndEffectIds())
		{
			bool will_create = false;
			if (EEffectEndCase_Both == item.end_case)
				will_create = true;
			else if (item.end_case == end_case)
				will_create = true;
			if (!will_create)
				continue;

			std::shared_ptr<EffectBase> end_effect = m_scene_effects->CreateEffect(item.id);
			assert(end_effect);
			if (nullptr != end_effect)
			{
				end_effect->Begin(m_skill, m_target_suid, m_target_pos, m_target_dir);
			}
		}
		this->OnLateEnd(end_case);
		m_stage = EEffectStage_End;

		m_scene_effects->RemoveEffect(m_effect_key);
	}

	void EffectBase::Loop(int64_t now_ms, int64_t delta_ms)
	{
		if (EEffectStage_Begin != m_stage && EEffectStage_Loop != m_stage)
			return;
		if (EEffectStage_Begin == m_stage)
			m_stage = EEffectStage_Loop;

		const TimeLineEffectIdsConfig &cfg = m_cfg->GetLoopEffectIds();
		if (m_next_loop_effect_idx >= cfg.effect_ids.size())
		{
			this->End(EEffectEndCase_Done);
			return;
		}
		int64_t elapse_ms = now_ms - m_begin_ms;
		if (elapse_ms < cfg.min_wait_ms)
			return;
		for (size_t idx = m_next_loop_effect_idx; idx < cfg.effect_ids.size(); ++idx)
		{
			const TimeLineEffectId &effect_id = cfg.effect_ids[idx];
			if (elapse_ms >= effect_id.wait_ms)
			{
				++m_next_loop_effect_idx;
				std::shared_ptr<EffectBase> new_effect = m_scene_effects->CreateEffect(effect_id.id);
				new_effect->Begin(m_skill, m_target_suid, m_target_pos, m_target_dir);
			}
		}
	}

	bool EffectBase::IsGuilding()
	{
		if (NeedGuild() && (EEffectStage_Begin == m_stage || EEffectStage_Loop == m_stage) &&
			m_next_loop_effect_idx < m_cfg->GetLoopEffectIds().effect_ids.size())
			return true;
		return false;
	}

	bool EffectBase::CanCancelGuild()
	{
		if (this->CanCancelGuild())
			return true;
		return !this->IsGuilding();
	}

	bool EffectBase::CanCelGuild(bool is_force)
	{
		if (!is_force && !this->CanCancelGuild())
			return false;
		this->End(EEffectEndCase_Break);
		return true;
	}

	bool EffectBase::NeedGuild()
	{
		if (!this->Reversible())
			return false;
		return m_cfg->NeedGuild();
	}

	bool EffectBase::Reversible()
	{
		return m_cfg->Reversible();
	}
}
