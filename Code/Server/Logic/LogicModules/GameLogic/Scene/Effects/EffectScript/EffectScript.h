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

	public:
		uint64_t SubscribeSuEvent(std::shared_ptr<SceneUnit> su, int ev_id, sol::protected_function lua_fn);
		void RemoveSuEvent(uint64_t su_id, uint64_t record_item_id);
		void CancelAllSuEvent(uint64_t su_id);

	protected:
		virtual void OnBegin() override;
		virtual void OnLateBegin() override;
		virtual bool IsDone() override;
		virtual void OnLateLoop(int64_t now_ms, int64_t delta_ms) override;
		virtual void OnLateEnd(EEffectEndCase end_case) override;
		
	public:
		std::shared_ptr<SceneUnit> GetSu(uint64_t);

	protected:
		const EffectScriptConfig *m_cfg = nullptr;
		sol::table m_lua_effect_script;

		LuaSubscribeEventDetail *m_lua_subscribe_scene_event_dtail = nullptr;
		std::unordered_map<uint64_t, LuaSubscribeEventDetail *> m_lua_subscribe_su_event_details;
	};
}
