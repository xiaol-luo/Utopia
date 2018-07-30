#include "EffectHurt.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "EffectHurtConfig.h"
#include "GameLogic/Scene/Defines/EffectUtils.h"

namespace GameLogic
{
	EffectHurt::EffectHurt(const EffectConfigBase * cfg, SceneEffects * scene_effects, uint64_t effect_key) 
		: EffectBase(cfg, scene_effects, effect_key)
	{
		m_cfg = dynamic_cast<const EffectHurtConfig *>(cfg);
		assert(m_cfg);
	}

	EffectHurt::~EffectHurt()
	{
	}

	void EffectHurt::OnBegin()
	{
		std::shared_ptr<SceneUnit> target_su = m_scene->GetUnit(m_user_effect_param.target_suid);
		if (nullptr != target_su)
		{
			if (nullptr != target_su && EffectUtil::UnitCanBeHurt(target_su))
			{
				std::shared_ptr<SceneUnitFightParam> su_fp = target_su->GetModule<SceneUnitFightParam>();
				if (nullptr != su_fp)
				{
					su_fp->AddHp(-m_cfg->GetHurt(), this);
				}
			}
		}
		m_is_done = true;
	}
}