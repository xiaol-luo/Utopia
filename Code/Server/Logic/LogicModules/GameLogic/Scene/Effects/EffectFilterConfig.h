#pragma once

#include <unordered_map>
#include "GameLogic/Scene/Defines/EffectDefine.h"
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"

namespace Config
{
	struct CsvEffectFilterConfig;
	struct CsvConfigSets;
}

namespace GameLogic
{
	struct EffectFilterConfig
	{
		bool InitCfg(Config::CsvEffectFilterConfig *csv_cfg);
		
		int id = 0;
		std::string name;
		int limit_num = 0;
		EEffectFilterLimitNumPriority limit_num_priority = EEffectFilterLimitNumPriority_None;
		uint64_t unit_types = 0;
		int relations = 0;
		EEffectFilterAnchor anchor = EEffectFilterAnchor_Caster;
		EEffectFilterShape shape = EEffectFilterShape_None;
		EffectFilterShapeParam shape_param;

		SceneUnitFilterWayParams GenFilterWayParams() const;
	};

	class EffectFilterConfigMgr
	{
	public:
		EffectFilterConfigMgr();
		~EffectFilterConfigMgr();

		bool LoadCfg(Config::CsvConfigSets *csv_cfgs, void **param);
		const EffectFilterConfig * GetCfg(int id);

	private:
		std::unordered_map<int, EffectFilterConfig *> m_filter_cfgs;
	};
}
