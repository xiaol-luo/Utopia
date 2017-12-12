#pragma once

#include "EffectConfigBase.h"
#include "EffectConfigMgr.h"
#include <memory>
#include "GameLogic/Scene/Defines/EffectDefine.h"

namespace GameLogic
{
	class Skill;
	class NewScene;
	class SceneEffects;
	class SceneUnit;

	class EffectBase : public std::enable_shared_from_this<EffectBase>
	{
	public:
		EffectBase(const EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key);
		virtual ~EffectBase();

		uint64_t GetKey() { return m_effect_key; }
		const EffectConfigBase * GetCfg() { return m_cfg; }
		std::shared_ptr<Skill> GetSkill() { return m_skill; }

		void Begin(std::shared_ptr<Skill> skill, uint64_t target_suid, Vector3 pos, Vector2 dir);
		void End(EEffectEndCase end_case);
		void Loop(int64_t now_ms, int64_t delta_ms);

		bool IsGuilding();
		virtual bool CanCancelGuild();
		virtual bool CanCelGuild(bool is_force);

	protected:
		virtual bool NeedGuild(); // 是否需要引导
		// 是否可复原，true则执行完begin直接返回，不加入SceneEfffect，不执行Loop和end。用与heal和hurt等
		virtual bool Reversible();
		virtual void OnBegin(std::shared_ptr<Skill> skill, uint64_t target_suid, Vector3 pos, Vector2 dir) {}
		virtual void OnEnd(EEffectEndCase end_case) {}
		virtual void OnLoop(int64_t now_ms, int64_t delta_ms) {}
		virtual void OnLateBegin(std::shared_ptr<Skill> skill, uint64_t target_suid, Vector3 pos, Vector2 dir) {}
		virtual void OnLateEnd(EEffectEndCase end_case) {}
		virtual void OnLateLoop(int64_t now_ms, int64_t delta_ms) {}

	protected:
		uint64_t m_effect_key = 0;
		int64_t m_begin_ms = -1;
		EEffectStage m_stage = EEffectStage_Wait;
		size_t m_next_loop_effect_idx = 0;
		SceneEffects *m_scene_effects = nullptr;
		const EffectConfigBase *m_cfg = nullptr;
		NewScene *m_scene = nullptr;
		std::shared_ptr<Skill> m_skill = nullptr;
		uint64_t m_target_suid = 0;
		Vector2 m_target_dir;
		Vector3 m_target_pos;
	};
}
