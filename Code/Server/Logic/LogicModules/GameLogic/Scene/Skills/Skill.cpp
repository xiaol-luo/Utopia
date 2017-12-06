#include "Skill.h"
#include "GameLogic/Scene/Config/SkillConfig.h"

namespace GameLogic
{
	Skill::Skill(const SkillConfig * cfg)
	{
		assert(cfg && cfg->max_level >= 0);
		m_cfg = cfg;
		m_lvl_cfg = cfg->level_cfgs[0];
	}

	Skill::~Skill()
	{

	}

	int Skill::GetSkillId()
	{
		return m_cfg->id;
	}

	bool Skill::SetLevel(int lvl)
	{
		if (lvl < 0 || lvl > m_cfg->max_level)
			return false;
		m_lvl_cfg = m_cfg->GetLvlCfg(lvl);
		return true;
	}

	int Skill::GetLevel()
	{
		return m_lvl_cfg->level;
	}

	int Skill::GetMaxLevel()
	{
		return m_cfg->max_level;
	}

	void Skill::SetParams(int64_t target_suid, Vector3 pos, Vector2 dir)
	{
	}

	bool Skill::Begin()
	{
		return false;
	}
	void Skill::HeartBeat()
	{
	}
	bool Skill::IsRunning()
	{
		return false;
	}
	bool Skill::TryCancel()
	{
		return false;
	}
	void Skill::End()
	{
	}
}

