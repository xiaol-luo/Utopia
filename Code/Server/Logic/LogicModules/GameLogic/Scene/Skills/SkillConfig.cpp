#include "SkillConfig.h"
#include "SkillConfig.h"
#include "Config/AutoCsvCode/skill/CsvSkillConfig.h"
#include "Config/AutoCsvCode/skill/CsvSkillLevelConfig.h"
#include "Config/AutoCsvCode/CsvConfigSets.h"
#include <sol.hpp>

namespace GameLogic
{
	SkillConfigSet::~SkillConfigSet()
	{
		this->Reset();
	}

	void SkillConfigSet::Reset()
	{
		for (auto kv_pair : skills)
		{
			delete kv_pair.second;
		}
		skills.clear();
	}

	bool SkillConfigSet::LoadCfg(Config::CsvConfigSets * csv_cfgs, void ** param)
	{
		this->Reset();

		if (nullptr == param)
		{
			Config::CsvSkillConfigSet *skill_set = csv_cfgs->csv_CsvSkillConfigSet;
			Config::CsvSkillLevelConfigSet *level_set = csv_cfgs->csv_CsvSkillLevelConfigSet;

			for (auto kv_pair : level_set->id_to_group)
			{
				SkillConfig *skill_cfg = new SkillConfig();
				int skill_id = kv_pair.first;
				Config::CsvSkillConfig *csv_skill = nullptr;
				{
					auto it = skill_set->id_to_key.find(skill_id);
					if (skill_set->id_to_key.end() != it)
						csv_skill = it->second;
				}
				assert(nullptr != csv_skill);
				skill_cfg->id = skill_id;
				skill_cfg->name = csv_skill->name;
				skill_cfg->is_normal_attack = csv_skill->is_normal_attack;
				skill_cfg->use_way = (NetProto::ESkillUseWay)csv_skill->use_way;
				for (int item : csv_skill->target_relations)
				{
					skill_cfg->target_relations |= 1 << item;
				}
				for (int item : csv_skill->target_types)
				{
					skill_cfg->target_types |= 1 << item;
				}

				for (Config::CsvSkillLevelConfig *csv_lvl : kv_pair.second)
				{
					assert(csv_lvl->level <= MAX_SKILL_LEVEL);
					assert(csv_lvl->level == skill_cfg->max_level + 1);
					skill_cfg->max_level = csv_lvl->level;
					SkillLevelConfig *lvl_cfg = new SkillLevelConfig();
					skill_cfg->level_cfgs[skill_cfg->max_level] = lvl_cfg;
					lvl_cfg->skill_cfg = skill_cfg;
					lvl_cfg->skill_id = skill_cfg->id;
					lvl_cfg->level = csv_lvl->level;
					lvl_cfg->consume_mp = csv_lvl->comsume_mp;
					lvl_cfg->cd = csv_lvl->cd;
					lvl_cfg->cast_distance = csv_lvl->cast_distance;
					lvl_cfg->preparing_span = csv_lvl->preparing_span;
					lvl_cfg->releasing_span = csv_lvl->releasing_span;
					lvl_cfg->lasting_span = csv_lvl->lasting_span;
					lvl_cfg->can_move = csv_lvl->can_move;
					lvl_cfg->release_effect_ids = csv_lvl->effect_ids;
				}

				skills.insert(std::make_pair(skill_cfg->id, skill_cfg));
			}
			return true;
		}
		else
		{
			sol::table skill_json_cfg = *(sol::table *)param;
		}
	}

	const SkillConfig * SkillConfigSet::GetSkill(int skill_id) const
	{
		auto it = skills.find(skill_id);
		if (skills.end() == it)
			return nullptr;
		return it->second;
	}
	const SkillLevelConfig * SkillConfigSet::GetSkill(int skill_id, int level) const
	{
		const SkillConfig *skill_cfg = this->GetSkill(skill_id);
		if (nullptr == skill_cfg)
			return nullptr;
		return skill_cfg->GetLvlCfg(level);
	}
	SkillConfig::~SkillConfig()
	{
		for (auto lvl_cfg : level_cfgs)
		{
			delete lvl_cfg;
		}
	}

	const SkillLevelConfig * SkillConfig::GetLvlCfg(int lvl) const
	{
		if (lvl < 0 || lvl > max_level)
			return nullptr;
		return level_cfgs[lvl];
	}

	SkillLevelConfig::~SkillLevelConfig()
	{
	}
}