#include "EffectSearcher.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "EffectSearcherConfig.h"
#include "GameLogic/Scene/Defines/EffectUtils.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Config/SceneAllConfig.h"
#include "GameLogic/Scene/Effects/EffectConfigMgr.h"
#include "Common/Macro/AllMacro.h"
#include "CommonModules/Log/LogModule.h"
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"
#include "ServerLogics/ServerLogic.h"

namespace GameLogic
{
	EffectSearcher::EffectSearcher(const EffectConfigBase * cfg, SceneEffects * scene_effects, uint64_t effect_key)
		: EffectBase(cfg, scene_effects, effect_key)
	{
		m_cfg = dynamic_cast<const EffectSearcherConfig *>(cfg);
		assert(m_cfg);
	}

	EffectSearcher::~EffectSearcher()
	{
	}

	void EffectSearcher::OnBegin()
	{
		UseEffectParam user_effect_param = m_user_effect_param;
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> effected_units;
		if (m_cfg->m_is_extract)
		{
			effected_units = this->ExtractSceneUnit();
		}
		else
		{
			effected_units = this->FindSceneUnits();
		}
		for (auto kv_pair : effected_units)
		{
			std::shared_ptr<SceneUnit> target_su = kv_pair.second;
			user_effect_param.target_suid = target_su->GetId();
			for (int cfgId : m_cfg->m_effect_ids)
			{
				std::shared_ptr<EffectBase> effect = m_scene_effects->CreateEffect(cfgId);
				if (nullptr == effect)
				{
					G_Log->Debug(LogModule::LOGGER_ID_STDOUT, "create effect is fail id = {0}", cfgId);
					continue;
				}
				effect->Begin(user_effect_param);
			}
		}
		m_is_done = true;
	}
}