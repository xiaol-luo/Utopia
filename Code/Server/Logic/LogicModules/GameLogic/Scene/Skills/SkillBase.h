#pragma once

#include <memory>
#include "SkillConfigBase.h"
#include "GameLogic/Scene/Defines/EffectDefine.h"
#include "GameLogic/Scene/Defines/SceneDefine.h"

namespace GameLogic
{
	class SceneUnit;
	class SceneUnitSkills;
	struct SceneAllConfig;

	class SkillBase : public std::enable_shared_from_this<SkillBase>
	{
	public:
		SkillBase(const SkillConfigBase *cfg);
		~SkillBase();

		int GetSkillId() { return m_cfg_base->id; }
		void SetSkillKey(uint64_t skill_key) { m_skill_key = skill_key; }
		uint64_t GetSkillKey() { return m_skill_key; }
		void SetSceneUnitSkills(std::shared_ptr<SceneUnitSkills> su_skills) { m_su_skills = su_skills; }
		std::shared_ptr<SceneUnitSkills> GetSceneUnitSkills() { return m_su_skills; }
		std::shared_ptr<SceneUnit> GetCaster();
		int64_t GetLogicMs(int64_t delta_ms = 0);

		virtual bool SetLevel(int lvl) { return false; }
		virtual void ReloadCfg(SceneAllConfig *sceneAllCfg) {}
		virtual void SyncClient() {}
		virtual SyncClientMsg GetPbMsg() { return std::move(SyncClientMsg(-1, nullptr)); }

	protected:
		uint64_t m_skill_key = 0;
		const SkillConfigBase *m_cfg_base = nullptr;
		std::shared_ptr<SceneUnitSkills> m_su_skills;
		UseSkillParam m_use_skill_param;
	};
}
