#include "EffectFilterConfig.h"
#include "Config/AutoCsvCode/effect/CsvEffectFilterConfig.h"
#include "Config/AutoCsvCode/CsvConfigSets.h"
#include <assert.h>

namespace GameLogic
{
	EffectFilterConfig::EffectFilterConfig()
	{

	}

	EffectFilterConfig::~EffectFilterConfig()
	{

	}

	bool EffectFilterConfig::InitCfg(Config::CsvEffectFilterConfig * csv_cfg)
	{
		m_id = csv_cfg->id;
		return true;
	}

	EffectFilterConfigMgr::EffectFilterConfigMgr()
	{

	}

	EffectFilterConfigMgr::~EffectFilterConfigMgr()
	{
		for (auto kv_pair : m_filter_cfgs)
		{
			delete kv_pair.second;
		}
		m_filter_cfgs.clear();
	}

	bool EffectFilterConfigMgr::LoadCfg(Config::CsvConfigSets * csv_cfgs, void * param)
	{
		for (Config::CsvEffectFilterConfig *item : csv_cfgs->csv_CsvEffectFilterConfigSet->cfg_vec)
		{
			EffectFilterConfig *cfg = new EffectFilterConfig();
			assert(cfg->InitCfg(item));
			auto ret = m_filter_cfgs.insert(std::make_pair(cfg->GetId(), cfg));
			assert(ret.second);
		}

		return true;
	}

	const EffectFilterConfig * EffectFilterConfigMgr::GetCfg(int id)
	{
		auto it = m_filter_cfgs.find(id);
		if (m_filter_cfgs.end() != it)
			return it->second;
		return nullptr;
	}
}