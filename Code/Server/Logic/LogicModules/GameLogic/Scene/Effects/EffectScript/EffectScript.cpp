#include "EffectScript.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "EffectScriptConfig.h"
#include "GameLogic/Scene/Defines/EffectUtils.h"
#include "Utils/LuaUtils.h"
#include "SolLuaBindUtils.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeEventFnDetail.h"
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneEventFnDetail.h"
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneUnitEventFnDetail.h"

namespace GameLogic
{
	EffectScript::EffectScript(const EffectConfigBase * cfg, SceneEffects * scene_effects, uint64_t effect_key) 
		: EffectBase(cfg, scene_effects, effect_key)
	{
		m_cfg = dynamic_cast<const EffectScriptConfig *>(cfg);
		assert(m_cfg);

		sol::state_view lsv(LuaUtils::luaState);
		sol::table typeDefine = SolLuaBindUtils::GetLuaNameSpaceTable(lsv, m_cfg->GetClassName());
		assert(typeDefine.valid());
		sol::protected_function newFn = typeDefine["new"];
		assert(newFn.valid());
		newFn.error_handler = LuaUtils::ProtectFnErrorHandler();
		m_lua_effect_script = newFn(typeDefine, this, nullptr);
		assert(m_lua_effect_script.valid());

		m_lua_subscribe_scene_event_dtail = new LuaSubscribeEventDetail(&m_lua_effect_script, m_scene_event_proxy->GetEventDispacher());
	}

	EffectScript::~EffectScript()
	{
		delete m_lua_subscribe_scene_event_dtail; m_lua_subscribe_scene_event_dtail = nullptr;

		for (auto kv_pair : m_lua_subscribe_su_event_details)
		{
			delete kv_pair.second;
		}
		m_lua_subscribe_su_event_details.clear();
	}

	bool EffectScript::SubscribeSuEvent(std::shared_ptr<SceneUnit> su, int ev_id, sol::object param)
	{
		return false;
	}

	bool EffectScript::CancelSuEvent(uint64_t su_id, int ev_id)
	{
		return false;
	}

	bool EffectScript::CancelAllSuEvent(uint64_t su_id)
	{
		return false;
	}

	void EffectScript::OnBegin()
	{
		sol::table scene_events = m_lua_effect_script["scene_events"];
		if (scene_events.valid())
		{
			for (LuaScribeEventFnDetail *fn_detail : LuaScribeSceneEventFnDetail::s_allFnDetails)
			{
				std::string lua_fn_name = fn_detail->GetLuaFunName();
				int event_id = fn_detail->GetEventId();
				sol::protected_function fn = scene_events.get<sol::protected_function>(lua_fn_name);
				if (fn.valid())
				{
					m_lua_subscribe_scene_event_dtail->Subscribe(event_id, fn, nullptr, LuaScribeSceneEventFnDetail::s_allFnDetails);
				}
			}
		}
	}

	void EffectScript::OnLateBegin()
	{
		sol::protected_function luaFn = m_lua_effect_script["on_late_begin"];
		luaFn.error_handler = LuaUtils::ProtectFnErrorHandler();
		luaFn(m_lua_effect_script);
	}

	bool EffectScript::IsDone()
	{
		bool is_done = m_lua_effect_script.get_or("is_done", true);
		return is_done;
	}

	void EffectScript::OnLateLoop(int64_t now_ms, int64_t delta_ms)
	{
		sol::protected_function luaFn = m_lua_effect_script["on_late_loop"];
		luaFn.error_handler = LuaUtils::ProtectFnErrorHandler();
		luaFn(m_lua_effect_script, now_ms, delta_ms);
	}

	void EffectScript::OnLateEnd(EEffectEndCase end_case)
	{
		sol::protected_function luaFn = m_lua_effect_script["on_late_end"];
		luaFn.error_handler = LuaUtils::ProtectFnErrorHandler();
		luaFn(m_lua_effect_script);

		m_lua_subscribe_scene_event_dtail->ClearAll();
	}
}