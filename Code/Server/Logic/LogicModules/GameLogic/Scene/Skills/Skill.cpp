#include "Skill.h"
#include "GameLogic/Scene/Config/SkillConfig.h"

namespace GameLogic
{
	Skill::Skill(SkillLevelConfig *cfg)
	{

	}

	Skill::~Skill()
	{

	}
	void Skill::SetLevel(int lvl)
	{
		m_lvl_cfg = m_cfg->GetLvlCfg(lvl);
	}

	void Skill::Begin()
	{
	}
	void Skill::HeartBeat()
	{
	}
	void Skill::End()
	{
	}
}

