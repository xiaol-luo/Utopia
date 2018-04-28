#include "EffectForceMove.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "EffectForceMoveConfig.h"
#include "GameLogic/Scene/Defines/EffectUtils.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "Common/Geometry/GeometryUtils.h"
#include "GameLogic/Scene/Skills/Skill.h"

namespace GameLogic
{
	EffectForceMove::EffectForceMove(const EffectConfigBase * cfg, SceneEffects * scene_effects, uint64_t effect_key)
		: EffectBase(cfg, scene_effects, effect_key)
	{
		m_cfg = dynamic_cast<const EffectForceMoveConfig *>(cfg);
		assert(m_cfg);
	}

	EffectForceMove::~EffectForceMove()
	{

	}

	void EffectForceMove::OnBegin()
	{
		std::shared_ptr<SceneUnit> target_su = m_scene->GetUnit(m_user_effect_param.target_suid);
		if (nullptr != target_su)
		{
			if (nullptr != target_su)
			{
				std::shared_ptr<SceneUnitMove> su_mv = target_su->GetModule<SceneUnitMove>();
				if (nullptr != su_mv)
				{
					Vector3 target_su_pos = target_su->GetTransform()->GetPos();
					Vector3 link_vec3;
					switch (m_cfg->GetAnchor())
					{
					case GameLogic::EEffectAnchor_Pos:
					{
						link_vec3 = target_su_pos - m_user_effect_param.pos;
					}
					break;
					case GameLogic::EEffectAnchor_SkillOwner:
					{
						Vector3 caster_pos = m_user_effect_param.skill->GetCaster()->GetTransform()->GetPos();
						link_vec3 = target_su_pos - caster_pos;
					}
					break;
					case GameLogic::EEffectAnchor_Target:
					{
						link_vec3 = Vector3::zero;
					}
					break;
					}
					Vector2 link_vec2 = link_vec3.XZ();
					if (link_vec2 == Vector2::zero)
						link_vec2 = target_su->GetTransform()->GetFaceDir();
					Vector2 mv_dir = GeometryUtils::RotateVector2(link_vec2, m_cfg->GetMoveDeg());

					su_mv->ForceMoveLine(mv_dir, m_cfg->GetSpeed(), m_cfg->GetTimeSec(), m_cfg->IgnoreTerrian());
				}
			}
		}
		m_is_done = true;
	}
}