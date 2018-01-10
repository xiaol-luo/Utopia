#include "EffectGroup.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "EffectGroupConfig.h"
#include "GameLogic/Scene/Defines/EffectUtils.h"

namespace GameLogic
{
	EffectGroup::EffectGroup(const EffectConfigBase * cfg, SceneEffects * scene_effects, uint64_t effect_key) 
		: EffectBase(cfg, scene_effects, effect_key)
	{
		m_cfg = dynamic_cast<const EffectGroupConfig *>(cfg);
		assert(m_cfg);
	}

	EffectGroup::~EffectGroup()
	{

	}
}