#include "EffectDefine.h"
#include "assert.h"
#include <algorithm>
#include "GameLogic/Scene/Effects/EffectBase.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/Skills/Skill.h"
#include "Common/Geometry/GeometryUtils.h"

namespace GameLogic
{
	bool EndEffectId::Generate(EndEffectId & out_ret, const std::vector<int>& input_vals)
	{
		assert(input_vals.size() >= 2);
		assert(input_vals[0] >= 0 && input_vals[0] <= EEffectEndCase_Break);
		out_ret.end_case = (EEffectEndCase)input_vals[0];
		out_ret.id = input_vals[1];
		return true;
	}
	
	bool GenerateEndEffectIdVec(std::vector<EndEffectId> & out_ret, const std::vector<std::vector<int>>& input_vals)
	{
		for (auto &&item : input_vals)
		{
			EndEffectId eid;
			assert(EndEffectId::Generate(eid, item));
			out_ret.push_back(eid);
		}
		return true;
	}

	// EEffectFilterRelation
	static std::unordered_map<std::string, EEffectFilterAnchor> Effect_Filter_Anchor_Map({
		{ "target_pos", EEffectFilterAnchor_TargetPos },
		{ "target_unit", EEffectFilterAnchor_TargetUnit },
		{ "caster", EEffectFilterAnchor_Caster },
		{ "cast_pos", EEffectFilterAnchor_CastPos },
		{ "effect_target_unit", EEffectFilterAnchor_EffectTargetUnit },
		{ "effect_target_pos", EEffectFilterAnchor_EffectTargetPos },
	});
	EEffectFilterAnchor StrToEffectFilterAnchor(const std::string & str)
	{
		return ConfigUtil::ConvertUtil(Effect_Filter_Anchor_Map, str);
	}

	static std::unordered_map<std::string, EForceMoveAnchor> Force_Move_Anchor_Map({
		{ "target_pos", EForceMoveAnchor_TargetPos },
		{ "target_unit", EForceMoveAnchor_TargetUnit },
		{ "caster", EForceMoveAnchor_Caster },
		{ "cast_pos", EForceMoveAnchor_CastPos },
		{ "effect_target_unit", EForceMoveAnchor_EffectTargetUnit },
		{ "effect_target_pos", EForceMoveAnchor_EffectTargetPos },
		{ "effect_dir", EForceMoveAnchor_EffectDir },
		{ "skill_dir", EForceMoveAnchor_SkillDir },
		{ "cast_face_dir", EForceMoveAnchor_CastFaceDir },
	});
	EForceMoveAnchor StrToForceMoveAnchor(const std::string & str)
	{
		return ConfigUtil::ConvertUtil(Force_Move_Anchor_Map, str);
	}

	bool CalForceMoveDir(const std::shared_ptr<EffectBase> effect_base, EForceMoveAnchor anchor, float deg, Vector2 *out_dir)
	{
		if (nullptr == effect_base)
			return false;

		std::shared_ptr<SceneUnit> effect_target_su = effect_base->GetEffectTarget();
		if (nullptr == effect_target_su)
			return false;

		Vector2 effect_target_su_pos = effect_target_su->GetTransform()->GetPos().XZ();
		auto m_user_effect_param = effect_base->GetUseEffectParam();
		Vector2 link_vec2;
		switch (anchor)
		{
		case GameLogic::EForceMoveAnchor_Caster:
		{
			Vector2 caster_pos = effect_base->GetCaster()->GetTransform()->GetPos().XZ();
			link_vec2 = effect_target_su_pos - caster_pos;
		}
		break;
		case GameLogic::EForceMoveAnchor_CastPos:
		{
			Vector2 cast_pos = m_user_effect_param.use_skill_param->cast_pos;
			link_vec2 = effect_target_su_pos - cast_pos;
		}
		break;
		case GameLogic::EForceMoveAnchor_EffectTargetPos:
		{
			link_vec2 = effect_target_su_pos - m_user_effect_param.pos;
		}
		case GameLogic::EForceMoveAnchor_EffectTargetUnit:
		{
			link_vec2 = Vector2::zero;
		}
		break;
		case GameLogic::EForceMoveAnchor_TargetUnit:
		{
			Vector2 skill_target_su_pos = m_user_effect_param.use_skill_param->pos;
			std::shared_ptr<SceneUnit> skill_target_su = effect_base->GetSkillTarget();
			if (nullptr != skill_target_su)
			{
				skill_target_su_pos = m_user_effect_param.use_skill_param->pos;
			}
			link_vec2 = effect_target_su_pos - skill_target_su_pos;
		}
		break;
		case GameLogic::EForceMoveAnchor_TargetPos:
		{
			Vector2 skill_target_su_pos = m_user_effect_param.use_skill_param->pos;
			link_vec2 = effect_target_su_pos - skill_target_su_pos;
		}
		break;
		case GameLogic::EForceMoveAnchor_EffectDir:
		{
			link_vec2 = m_user_effect_param.dir;
		}
		break;
		case GameLogic::EForceMoveAnchor_SkillDir:
		{
			link_vec2 = m_user_effect_param.use_skill_param->dir;
		}
		break;
		case GameLogic::EForceMoveAnchor_CastFaceDir:
		{
			link_vec2 = m_user_effect_param.use_skill_param->cast_face_dir;
		}
		break;
		default:
			break;
		}
		if (link_vec2 == Vector2::zero)
			link_vec2 = effect_target_su->GetTransform()->GetFaceDir();
		*out_dir = Vector2::Normalize(GeometryUtils::RotateVector2(link_vec2, deg));
		return true;
	}
	
	bool TimeLineEffectId::Generate(TimeLineEffectId & out_ret, const std::vector<int>& input_vals)
	{
		assert(input_vals.size() >= 2);
		assert(input_vals[0] >= 0);
		out_ret.wait_ms = (EEffectEndCase)input_vals[0];
		out_ret.id = input_vals[1];
		return true;
	}

	bool TimeLineEffectIdsConfig::Generate(TimeLineEffectIdsConfig & out_ret, const std::vector<std::vector<int>>& input_vals)
	{
		int min_wait_ms = INT_MAX;
		int max_wait_ms = INT_MIN;

		for (auto &&item : input_vals)
		{
			TimeLineEffectId eid;
			assert(TimeLineEffectId::Generate(eid, item));
			out_ret.effect_ids.push_back(eid);

			min_wait_ms = std::min(min_wait_ms, eid.wait_ms);
			max_wait_ms = std::max(max_wait_ms, eid.wait_ms);
		}

		out_ret.min_wait_ms = min_wait_ms;
		out_ret.max_wait_ms = max_wait_ms;
		return true;
	}
}
