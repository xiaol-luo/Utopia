#pragma once

namespace GameLogic
{
	struct SkillLevelConfig;
	struct SkillConfig;


	class Skill
	{
	public:
		Skill(SkillLevelConfig *cfg);
		~Skill();

		void SetLevel(int lvl);
		const SkillLevelConfig * GetLvlCfg() { return m_lvl_cfg; }
		const SkillConfig * GetCfg() { return m_cfg; }
		void Begin();
		void HeartBeat();
		void End();

	protected:
		const SkillConfig *m_cfg = nullptr;
		const SkillLevelConfig *m_lvl_cfg = nullptr;
	};
}
