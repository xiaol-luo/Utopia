#pragma once

#include "GameLogic/Scene/Effects/EffectBase.h"
#include "LuaSubscribeEventDetail.h"
#include <sol.hpp>

namespace GameLogic
{
	class EffectScriptConfig;
	class EffectScript : public EffectBase
	{
	public:
		EffectScript(const EffectConfigBase *cfg, SceneEffects *scene_effects, uint64_t effect_key);
		virtual ~EffectScript();

		sol::table * GetLuaObject() { return &m_lua_effect_script; }

	protected:
		virtual void OnBegin() override;
		virtual void OnLateBegin() override;
		virtual bool IsDone() override;
		virtual void OnLateLoop(int64_t now_ms, int64_t delta_ms) override;
		virtual void OnLateEnd(EEffectEndCase end_case) override;
		
	protected:
		const EffectScriptConfig *m_cfg = nullptr;
		sol::table m_lua_effect_script;

		LuaSubscribeSceneEventDetail *m_lua_subscribe_scene_event_dtail = nullptr;
	};
}
