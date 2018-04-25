#pragma once

#include <memory>
#include "Common/Utils/Ticker.h"
#include "Network/Protobuf/BattleEnum.pb.h"
#include "GameLogic/Scene/Defines/SceneDefine.h"
#include "GameLogic/Scene/Defines/EffectDefine.h"
#include "SkillBase.h"

namespace GameLogic
{
	class SceneUnit;
	struct SkillLevelConfig;
	class SkillConfig;
	class SceneUnitSkills;
	class EffectBase;
	struct SceneAllConfig;

	class Skill : public SkillBase
	{
	public:
		Skill(const SkillConfig *cfg);
		~Skill();

		virtual bool SetLevel(int lvl) override;
		int GetLevel();
		int GetMaxLevel();
		const SkillConfig * GetCfg() { return m_cfg; }
		virtual void ReloadCfg(SceneAllConfig *sceneAllCfg) override;
		int GetStage() { return m_state; }
		int GetStageBeginMs() { return m_stage_begin_ms; }

		void SetParams(int64_t target_suid, Vector3 pos, Vector2 dir);
		bool Begin();
		bool InCd();
		void HeartBeat();
		bool IsRunning();
		bool TryCancel();
		bool CanCancel();
		virtual void SyncClient() override;
		virtual SyncClientMsg GetPbMsg() override;

		void AddGuideEffect(std::shared_ptr<EffectBase> effect);
		void RemoveGuideEffect(uint64_t effect_key);
		void ClearGuideEffects();

	protected:
		bool CheckCanCast();
		void SetFaceDir();
		void ReleaseEffects();
		void End();
		std::shared_ptr<SceneUnitSkills> m_su_skills;
		const SkillConfig *m_cfg = nullptr;
		const SkillLevelConfig *m_lvl_cfg = nullptr;
		uint64_t m_skill_key = 0;

		UseSkillParam m_use_skill_param;

		std::unordered_map<uint64_t, std::shared_ptr<EffectBase>> m_guide_effects;
		bool m_can_move = true;
		int64_t m_last_release_ms = LONG_MIN;
		int m_state = NetProto::ESS_End;
		int64_t m_stage_begin_ms = LONG_MAX;
		int64_t GetLogicMs(int64_t delta_ms = 0);
	};
}
