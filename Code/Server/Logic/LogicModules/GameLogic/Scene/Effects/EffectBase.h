#pragma once

#include "EffectConfigBase.h"
#include "EffectConfigMgr.h"
#include <memory>
#include "GameLogic/Scene/Defines/EffectDefine.h"

namespace GameLogic
{
	class SkillBase;
	class NewScene;
	class SceneEffects;
	class SceneUnit;
	struct EffectFilterShape;
	struct ESceneUnitFilterWayParams;

	class EffectBase : public std::enable_shared_from_this<EffectBase>
	{
	public:
		EffectBase(const EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key);
		virtual ~EffectBase();

		uint64_t GetKey() { return m_effect_key; }
		const EffectConfigBase * GetCfg() { return m_base_cfg; }
		std::shared_ptr<SkillBase> GetSkill() { return m_user_effect_param.skill; }
		std::shared_ptr<SceneUnit> GetCaster();
		std::shared_ptr<SceneUnit> GetEffectTarget();
		UseEffectParam GetUseEffectParam() { return m_user_effect_param; }

		void Begin(UseEffectParam use_effect_param);
		void End(EEffectEndCase end_case);
		void Loop(int64_t now_ms, int64_t delta_ms);

		bool IsGuiding();
		virtual bool CanCancelGuide();
		virtual bool CanCelGuide(bool is_force);

	protected:
		virtual bool NeedGuide(); // 是否需要引导
		// 是否可复原，true则执行完begin直接返回，不加入SceneEfffect，不执行Loop和end。用与heal和hurt等
		virtual bool Reversible();
		virtual void OnBegin() {}
		virtual void OnEnd(EEffectEndCase end_case) {}
		virtual void OnLoop(int64_t now_ms, int64_t delta_ms) {}
		virtual void OnLateBegin() {}
		virtual void OnLateEnd(EEffectEndCase end_case) {}
		virtual void OnLateLoop(int64_t now_ms, int64_t delta_ms) {}
		virtual bool IsDone();
		void FireLoopEffects(int64_t elaspe_ms);
		bool IsLoopEffectsDone();

	protected:
		uint64_t m_effect_key = 0;
		int64_t m_begin_ms = -1;
		EEffectStage m_stage = EEffectStage_Wait;
		size_t m_next_loop_effect_idx = 0;
		SceneEffects *m_scene_effects = nullptr;
		const EffectConfigBase *m_base_cfg = nullptr;
		NewScene *m_scene = nullptr;
		UseEffectParam m_user_effect_param;

	protected:
		virtual std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> FilterSceneUnits();
		bool GenFilterWayParamByCfg(EffectFilterShape &shape, ESceneUnitFilterWayParams &filter_way_param);
	};
}
