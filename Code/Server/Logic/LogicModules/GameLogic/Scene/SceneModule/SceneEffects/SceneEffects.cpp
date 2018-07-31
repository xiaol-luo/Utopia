#include "SceneEffects.h"
#include "GameLogic/Scene/Effects/EffectConfigMgr.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Config/SceneAllConfig.h"
#include "GameLogic/Scene/Effects/EffectConfigBase.h"

namespace GameLogic
{
	const ESceneModule SceneEffects::MODULE_TYPE = ESceneModule_Effects;

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
		{
			0 == ++m_last_effect_key ? m_last_effect_key = 1 : 0;
			return cfg->CreateEffect(this, m_last_effect_key);
		}
		return nullptr;
	}
	bool SceneEffects::AddEffect(std::shared_ptr<EffectBase> effect)
	{
		if (nullptr == effect || effect->GetKey() <= 0)
			return false;

		auto ret = m_effects.insert(std::make_pair(effect->GetKey(), effect));
		if (ret.second)
			m_removed_effects.erase(effect->GetKey());
		return ret.second;
	}
	void SceneEffects::RemoveEffect(uint64_t effect_key)
	{
		m_removed_effects.insert(effect_key);
	}

	void SceneEffects::OnUpdate()
	{
		this->CheckRemoveEffects();
		uint64_t now_ms = m_scene->GetLogicMs();
		uint64_t delta_ms = m_scene->GetLogicDetalMs();
		for (auto kv_pair : m_effects)
		{
			kv_pair.second->Loop(now_ms, delta_ms);
		}
		this->CheckRemoveEffects();
	}
	void SceneEffects::CheckRemoveEffects()
	{
		if (m_removed_effects.empty())
			return;

		for (uint64_t id : m_removed_effects)
			m_effects.erase(id);
		m_removed_effects.clear();
	}
}


