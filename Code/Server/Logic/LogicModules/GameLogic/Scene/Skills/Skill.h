#pragma once

#include <memory>

namespace GameLogic
{
	struct SkillLevelConfig;
	struct SkillConfig;
	class SceneUnitSkills;


	class Skill : public std::enable_shared_from_this<Skill>
	{
	public:
		Skill(const SkillConfig *cfg);
		~Skill();

		void SetSceneUnitSkills(std::shared_ptr<SceneUnitSkills> su_skills) { m_su_skills = su_skills; }
		std::shared_ptr<SceneUnitSkills> GetSceneUnitSkills() { return m_su_skills; }
		bool SetLevel(int lvl);
		int GetLevel();
		int GetMaxLevel();
		inline void SetSkillKey(uint64_t skill_key) { m_skill_key = skill_key; }
		inline uint64_t GetSkillKey() { return m_skill_key; }
		const SkillLevelConfig * GetLvlCfg() { return m_lvl_cfg; }
		const SkillConfig * GetCfg() { return m_cfg; }
		void Begin();
		void HeartBeat();
		void End();

	protected:
		std::shared_ptr<SceneUnitSkills> m_su_skills;
		const SkillConfig *m_cfg = nullptr;
		const SkillLevelConfig *m_lvl_cfg = nullptr;
		uint64_t m_skill_key = 0;
	};
}
