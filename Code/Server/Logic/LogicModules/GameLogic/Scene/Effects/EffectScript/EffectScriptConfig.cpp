#include "EffectScriptConfig.h"
#include "EffectScript.h"
#include "Config/AutoCsvCode/effect/CsvEffectScriptConfig.h"
#include <assert.h>

namespace GameLogic
{
	std::shared_ptr<EffectBase> EffectScriptConfig::CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectScript>(this, scene_effects, effect_key);
	}

	bool EffectScriptConfig::InitCfg(const Config::CsvEffectScriptConfig * csv_cfg, void **param)
	{
		sol::table json_cfg = *(sol::table *)param;
		if (json_cfg.valid())
		{
			m_id = json_cfg["id"];
			m_name = json_cfg["name"];
			m_class_name = json_cfg["class_name"];
			m_str_param = json_cfg["string_param"];
			m_json_param = json_cfg["json_param"];
			m_int_param = json_cfg["int_param"];
		}
		else if (nullptr != csv_cfg)
		{
			m_id = csv_cfg->id;
			m_class_name = csv_cfg->class_name;
			m_str_param = csv_cfg->str_param;
			m_json_param = csv_cfg->json_param;
			m_int_param = csv_cfg->int_param;
			m_reversible = true;
		}

		return true;
	}
}

