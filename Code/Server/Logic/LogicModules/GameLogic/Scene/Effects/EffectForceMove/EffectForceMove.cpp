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
			std::shared_ptr<SceneUnitMove> su_mv = target_su->GetModule<SceneUnitMove>();
			if (nullptr != su_mv)
			{
				Vector2 mv_dir = Vector2::zero;
				bool ret = CalForceMoveDir(this->shared_from_this(), m_cfg->GetAnchor(), m_cfg->GetMoveDeg(), &mv_dir);
				if (ret)
				{
					su_mv->ForceMoveLine(mv_dir, m_cfg->GetSpeed(), m_cfg->GetTimeSec(), m_cfg->IgnoreTerrian());
				}
			}
		}
		m_is_done = true;
	}
}