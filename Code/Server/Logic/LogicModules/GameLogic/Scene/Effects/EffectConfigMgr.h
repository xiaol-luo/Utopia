#pragma once

#include <unordered_map>

namespace Config
{
	struct CsvConfigSets;
}

namespace GameLogic
{
	class EffectConfigBase;

	class EffectConfigMgr
	{
	public: 
		EffectConfigMgr();
		~EffectConfigMgr();

		bool LoadCfg(Config::CsvConfigSets *csv_cfgs, void **param);
		const EffectConfigBase * GetCfg(int id);
		const std::unordered_map<int, EffectConfigBase *> & GetAllCfg() { return m_effect_cfgs; }

	protected:
		std::unordered_map<int, EffectConfigBase *> m_effect_cfgs;
	};
}
