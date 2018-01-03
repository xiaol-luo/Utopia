#pragma once

#include <unordered_map>
#include "GameLogic/Scene/Defines/EffectDefine.h"

namespace Config
{
	struct CsvEffectFilterConfig;
	struct CsvConfigSets;
}

namespace GameLogic
{
	class EffectFilterConfig
	{
	public:
		EffectFilterConfig();
		~EffectFilterConfig();

		bool InitCfg(Config::CsvEffectFilterConfig *csv_cfg);
		int GetId() { return m_id; }

	private:
		int m_id = 0;
		int m_limit_num = 0;
		EEffectFilterLimitNumPriority m_limit_num_priority = EEffectFilterLimitNumPriority_None;
		uint64_t m_unit_types;
		int m_relations;

		EEffectFilterAnchor m_anchor = EEffectAnchor_Pos;
		EEffectFilterShape m_shape = EffectFilterShape_None;
		EffectFilterShapeParam m_shape_param;
	};

	struct EffectFilterParams
	{
		const EffectFilterConfig *cfg;
		std::unordered_set<uint64_t> exclude_suids;
	};

	class EffectFilterConfigMgr
	{
	public:
		EffectFilterConfigMgr();
		~EffectFilterConfigMgr();

		bool LoadCfg(Config::CsvConfigSets *csv_cfgs, void *param);
		const EffectFilterConfig * GetCfg(int id);

	private:
		std::unordered_map<int, EffectFilterConfig *> m_filter_cfgs;
	};
}
