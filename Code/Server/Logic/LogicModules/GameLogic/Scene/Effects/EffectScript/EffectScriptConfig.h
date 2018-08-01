#pragma once

#include "GameLogic/Scene/Effects/EffectConfigBase.h"

namespace Config
{
	struct CsvEffectScriptConfig;
}

namespace GameLogic
{
	class SceneEffects;

	class EffectScriptConfig : public EffectConfigBase
	{
	public:
		virtual std::shared_ptr<EffectBase> CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const;

	public:
		bool InitCfg(const Config::CsvEffectScriptConfig *csv_cfg);
		const std::string & GetClassName() const { return m_class_name; }

	protected:
		std::string m_class_name;
		std::string m_use_lua_cfg_name;
	};
}
