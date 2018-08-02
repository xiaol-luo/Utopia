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
		const std::string & GetStrParam() const { return m_str_param; }
		const std::string & GetJsonParam() const { return m_json_param; }
		int GetIntParam() const { return m_int_param; }

	protected:
		std::string m_class_name;
		std::string m_str_param;
		std::string m_json_param;
		int m_int_param;
	};
}
