#include "SceneEffects.h"
#include "GameLogic/Scene/Effects/EffectConfigMgr.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Config/SceneAllConfig.h"
#include "GameLogic/Scene/Effects/EffectConfigBase.h"

namespace GameLogic
{
	SceneEffects::SceneEffects() : SceneModule(MODULE_TYPE)
	{

	}

	SceneEffects::~SceneEffects()
	{

	}
	std::shared_ptr<EffectBase> SceneEffects::CreateEffect(int effect_id)
	{
		EffectConfigMgr *cfg_mgr = this->GetScene()->GetCfg()->effect_cfg_mgr;
		const EffectConfigBase *cfg = cfg_mgr->GetCfg(effect_id);
		if (nullptr != cfg)
			return cfg->CreateEffect();
		return nullptr;
	}
	bool SceneEffects::AddEffect(std::shared_ptr<EffectBase> effect)
	{
		if (nullptr == effect || effect->GetKey() <= 0)
			return false;

		auto ret = m_effects.insert(std::make_pair(effect->GetKey(), effect));
		return ret.second;
	}
	void SceneEffects::RemoveEffect(uint64_t effect_key)
	{
		m_effects.erase(effect_key);
	}
}


