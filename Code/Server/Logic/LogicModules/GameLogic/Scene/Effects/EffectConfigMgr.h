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

		bool LoadCfg(Config::CsvConfigSets *csv_cfgs);
		const EffectConfigBase * GetCfg(int id);

	protected:
		std::unordered_map<int, EffectConfigBase *> m_effect_cfgs;
	};
}
