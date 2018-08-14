#include "EffectBase.h"
#include "EffectConfigBase.h"
#include <assert.h>
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/Skills/Skill.h"
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Effects/EffectFilterConfig.h"
#include "GameLogic/Scene/Config/SceneAllConfig.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"

namespace GameLogic
{
	EffectBase::EffectBase(const EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key)
	{
		assert(cfg && scene_effects);
		m_base_cfg = cfg;
		assert(m_base_cfg);
		m_effect_key = effect_key;
		m_scene_effects = scene_effects;
		m_scene = scene_effects->GetScene();
		m_scene_event_proxy = new EventDispacherProxy(scene_effects->GetScene()->GetEvDispacher());
	}

	EffectBase::~EffectBase()
	{
		m_user_effect_param.Reset();
		m_scene_event_proxy->CancelAll();
		delete m_scene_event_proxy; m_scene_event_proxy = nullptr;
	}

	std::shared_ptr<SceneUnit> EffectBase::GetCaster()
	{
		return m_user_effect_param.skill->GetCaster();
	}

	std::shared_ptr<SceneUnit> EffectBase::GetEffectTarget()
	{
		return m_scene->GetUnit(m_user_effect_param.target_suid);
	}
	std::shared_ptr<SceneUnit> EffectBase::GetSkillTarget()
	{
		return m_user_effect_param.use_skill_param->target_su.lock();
	}

	NewScene * EffectBase::GetScene()
	{
		return m_scene;
	}

	std::shared_ptr<SceneUnit> EffectBase::GetSceneUnit(uint64_t suid)
	{
		return m_scene->GetUnit(suid);
	}

	void EffectBase::Begin(UseEffectParam use_effect_param)
	{
		assert(EEffectStage_Wait == m_stage);
		assert(use_effect_param.skill);
		m_user_effect_param = use_effect_param;
		m_stage = EEffectStage_Begin;
		m_begin_ms = m_scene->GetLogicMs();

		if (this->Reversible())
		{
			m_scene_effects->AddEffect(this->shared_from_this());
		}

		this->OnBegin();
		if (IsDone())
			return;

		for (int effect_id : m_base_cfg->GetBeginEffectIds())
		{
			std::shared_ptr<EffectBase> begin_effect = m_scene_effects->CreateEffect(effect_id);
			assert(begin_effect);
			if (nullptr != begin_effect)
			{
				begin_effect->Begin(m_user_effect_param);
			}
		}
		this->OnLateBegin();
		if (IsDone())
			return;

		if (this->NeedGuide())
		{
			assert(m_user_effect_param.skill);
			std::shared_ptr<Skill> skill = std::dynamic_pointer_cast<Skill>(m_user_effect_param.skill);
			if (nullptr != skill)
				skill->AddGuideEffect(this->shared_from_this());
		}
	}

	void EffectBase::End(EEffectEndCase end_case)
	{
		if (EEffectStage_Wait == m_stage || EEffectStage_End == m_stage)
			return;

		this->OnEnd(end_case);
		for (EndEffectId item : m_base_cfg->GetEndEffectIds())
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
				end_effect->Begin(m_user_effect_param);
			}
		}
		this->OnLateEnd(end_case);
		m_stage = EEffectStage_End;

		m_scene_effects->RemoveEffect(m_effect_key);
		m_user_effect_param.Reset();
	}

	void EffectBase::Loop(int64_t now_ms, int64_t delta_ms)
	{
		if (EEffectStage_Begin != m_stage && EEffectStage_Loop != m_stage)
			return;
		if (EEffectStage_Begin == m_stage)
			m_stage = EEffectStage_Loop;

		if (this->IsDone())
		{
			this->End(EEffectEndCase_Done);
			return;
		}
		this->OnLoop(now_ms, delta_ms);
		if (this->IsDone())
		{
			this->End(EEffectEndCase_Done);
			return;
		}
		this->FireLoopEffects(now_ms - m_begin_ms);
		this->OnLateLoop(now_ms, delta_ms);
		if (this->IsDone())
		{
			this->End(EEffectEndCase_Done);
		}
	}

	bool EffectBase::IsGuiding()
	{
		if (NeedGuide() && (EEffectStage_Begin == m_stage || EEffectStage_Loop == m_stage) &&
			m_next_loop_effect_idx < m_base_cfg->GetLoopEffectIds().effect_ids.size())
			return true;
		return false;
	}

	bool EffectBase::CanCancelGuide()
	{
		return !this->IsGuiding();
	}

	bool EffectBase::CancelGuide(bool is_force)
	{
		if (!is_force && !this->CanCancelGuide())
			return false;
		this->End(EEffectEndCase_Break);
		return true;
	}

	bool EffectBase::NeedGuide()
	{
		if (!this->Reversible())
			return false;
		return m_base_cfg->NeedGuide();
	}

	bool EffectBase::Reversible()
	{
		return m_base_cfg->Reversible();
	}
	bool EffectBase::IsDone()
	{
		return this->IsLoopEffectsDone();
	}

	void EffectBase::FireLoopEffects(int64_t elapse_ms)
	{
		if (this->IsLoopEffectsDone())
			return;

		const TimeLineEffectIdsConfig &cfg = m_base_cfg->GetLoopEffectIds();
		for (size_t idx = m_next_loop_effect_idx; idx < cfg.effect_ids.size(); ++idx)
		{
			const TimeLineEffectId &effect_id = cfg.effect_ids[idx];
			if (elapse_ms >= effect_id.wait_ms)
			{
				++m_next_loop_effect_idx;
				std::shared_ptr<EffectBase> new_effect = m_scene_effects->CreateEffect(effect_id.id);
				new_effect->Begin(m_user_effect_param);
			}
		}
	}

	bool EffectBase::IsLoopEffectsDone()
	{
		const TimeLineEffectIdsConfig &cfg = m_base_cfg->GetLoopEffectIds();
		return m_next_loop_effect_idx >= cfg.effect_ids.size();
	}

	std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> EffectBase::FilterSceneUnits()
	{
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> ret;
		EffectFilterShape shape;
		ESceneUnitFilterWayParams params;
		if (this->GenFilterWayParamByCfg(shape, params))
		{
			SceneUnitFilter *su_filter = m_scene->GetModule<SceneUnitFilter>();
			ret = su_filter->FilterSceneUnit(shape, params);
		}
		else
		{
			int filter_id = m_base_cfg->GetFilterId();
			if (SELECT_TARGET_FILTER_CONFIG_ID == filter_id)
			{
				std::shared_ptr<SceneUnit> target_su = this->GetEffectTarget();
				if (nullptr != target_su)
					ret[target_su->GetId()] = target_su;
			}
			if (SELECT_SELF_FILTER_CONFIG_ID == filter_id)
			{
				std::shared_ptr<SceneUnit> self_su = this->GetCaster();
				if (nullptr != self_su)
					ret[self_su->GetId()] = self_su;
			}
		}
		return std::move(ret);
	}

	bool EffectBase::GenFilterWayParamByCfg(EffectFilterShape &shape, ESceneUnitFilterWayParams & filter_way_param)
	{
		int filter_id = m_base_cfg->GetFilterId();
		if (filter_id <= 0)
			return false;

		SceneUnitFilter *su_filter = m_scene->GetModule<SceneUnitFilter>();
		const EffectFilterConfig *filter_cfg = m_scene->GetCfg()->effect_filter_cfg_mgr->GetCfg(filter_id);
		assert(filter_cfg);
		std::shared_ptr<SceneUnit> caster = this->GetCaster();

		// gen shape
		shape.shape = filter_cfg->shape;
		shape.shape_param = filter_cfg->shape_param;

		switch (filter_cfg->anchor)
		{
		case EEffectFilterAnchor_Caster:
		{
			shape.pos = caster->GetTransform()->GetPos().XZ();
		}
		break;
		case EEffectFilterAnchor_CastPos:
		{
			shape.pos = m_user_effect_param.use_skill_param->cast_pos;
		}
		break;
		case EEffectFilterAnchor_TargetPos:
		{
			shape.pos = m_user_effect_param.use_skill_param->pos;
		}
		break;
		case EEffectFilterAnchor_TargetUnit:
		{
			std::shared_ptr<SceneUnit> target_su = this->GetSkillTarget();
			if (nullptr == target_su)
			{
				shape.pos = m_user_effect_param.use_skill_param->pos;
			}
			else
			{
				shape.pos = target_su->GetTransform()->GetPos().XZ();
			}
		}
		case EEffectFilterAnchor_EffectTargetUnit:
		{
			std::shared_ptr<SceneUnit> target_su = this->GetEffectTarget();
			if (nullptr == target_su)
			{
				shape.pos = m_user_effect_param.pos;
			}
			else
			{
				shape.pos = target_su->GetTransform()->GetPos().XZ();
			}
		}
		break;
		case EEffectFilterAnchor_EffectTargetPos:
		{
			shape.pos = m_user_effect_param.pos;
		}
		break;
		default:
			break;
		}
		shape.dir = m_user_effect_param.dir;

		// gen filter param
		if (0 != filter_cfg->relations)
		{
			filter_way_param.is_active[ESceneUnitFilterWay_Relation] = true;
			filter_way_param.relations.caster = caster;
			filter_way_param.relations.relations = filter_cfg->relations;
		}
		if (filter_cfg->limit_num > 0)
		{
			filter_way_param.is_active[ESceneUnitFilterWay_LimitNum] = true;
			filter_way_param.limit_num.num = filter_cfg->limit_num;
			filter_way_param.limit_num.priority = filter_cfg->limit_num_priority;
		}
		if (0 != filter_cfg->unit_types)
		{
			filter_way_param.is_active[ESceneUnitFilterWay_UnitType] = true;
			filter_way_param.unit_type.allow_types = filter_cfg->unit_types;
		}

		return true;
	}
}
