#pragma once

#include <memory>
#include "Common/Geometry/Vector2.h"
#include "Common/Geometry/Vector3.h"
#include "Common/Utils/Ticker.h"
#include "Network/Protobuf/BattleEnum.pb.h"
#include "GameLogic/Scene/Defines/SceneDefine.h"

namespace GameLogic
{
	class SceneUnit;
	struct SkillLevelConfig;
	struct SkillConfig;
	class SceneUnitSkills;


	class Skill : public std::enable_shared_from_this<Skill>
	{
	public:
		Skill(const SkillConfig *cfg);
		~Skill();

		int GetSkillId();
		void SetSceneUnitSkills(std::shared_ptr<SceneUnitSkills> su_skills) { m_su_skills = su_skills; }
		std::shared_ptr<SceneUnitSkills> GetSceneUnitSkills() { return m_su_skills; }
		bool SetLevel(int lvl);
		int GetLevel();
		int GetMaxLevel();
		inline void SetSkillKey(uint64_t skill_key) { m_skill_key = skill_key; }
		inline uint64_t GetSkillKey() { return m_skill_key; }
		const SkillLevelConfig * GetLvlCfg() { return m_lvl_cfg; }
		const SkillConfig * GetCfg() { return m_cfg; }
		int GetStage() { return m_state; }
		int GetStageBeginMs() { return m_stage_begin_ms; }

		void SetParams(int64_t target_suid, Vector3 pos, Vector2 dir);
		bool Begin();
		void HeartBeat();
		bool IsRunning();
		bool TryCancel();
		void SyncClient();
		SyncClientMsg GetPbMsg();

	protected:
		bool CheckCanCast();
		void SetFaceDir();
		void ReleaseEffects();
		void End();
		std::shared_ptr<SceneUnitSkills> m_su_skills;
		const SkillConfig *m_cfg = nullptr;
		const SkillLevelConfig *m_lvl_cfg = nullptr;
		uint64_t m_skill_key = 0;

		void ResetParams();
		uint64_t m_target_suid = 0;
		std::weak_ptr<SceneUnit> m_target_su;
		Vector3 m_pos;
		Vector2 m_dir;
		bool m_can_move = true;
		int64_t m_last_release_ms = LONG_MIN;
		int m_state = NetProto::ESS_End;
		int64_t m_stage_begin_ms = LONG_MAX;
		int64_t GetLogicMs(int64_t delta_ms = 0);
	};
}
