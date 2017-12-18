#pragma once

#include <unordered_map>
#include <string>
#include "Network/Protobuf/BattleEnum.pb.h"

namespace Config
{
	struct CsvConfigSets;
}

namespace GameLogic
{
	struct SkillConfig;
	struct SkillLevelConfig
	{
		~SkillLevelConfig();

		SkillConfig *skill_cfg = nullptr;
		int skill_id = -1;
		int level = -1;
		int consume_mp = 0;
		int cd = 0;
		int cast_distance = 0;
		int preparing_span = 0;
		int releasing_span = 0;
		int lasting_span = 0;
		bool can_move = false;
		std::vector<int> release_effect_ids;
	};

	struct SkillConfig
	{
		const static int MAX_SKILL_LEVEL = 5;
		~SkillConfig();
		int id = 0;
		std::string name;
		bool is_normal_attack = false;
		NetProto::ESkillUseWay use_way;
		int target_relations = 0;
		int target_types = 0;
		int max_level = -1;
		SkillLevelConfig *level_cfgs[MAX_SKILL_LEVEL + 1];

		const SkillLevelConfig * GetLvlCfg(int lvl) const;
	};

	struct SkillConfigSet
	{
		std::unordered_map<int, SkillConfig *> skills;

		~SkillConfigSet();

		void Reset();
		bool LoadCfg(Config::CsvConfigSets *csv_cfgs, void *param);

		const SkillConfig * GetSkill(int skill_id) const;
		const SkillLevelConfig * GetSkill(int skill_id, int level) const;
	};
}