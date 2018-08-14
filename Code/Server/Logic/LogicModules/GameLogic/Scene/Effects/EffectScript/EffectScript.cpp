#include "EffectScript.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "EffectScriptConfig.h"
#include "GameLogic/Scene/Defines/EffectUtils.h"
#include "Utils/LuaUtils.h"
#include "SolLuaBindUtils.h"
#include "GameLogic/Scene/Defines/ESceneEvent.h"
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
		m_lua_effect_script = newFn(typeDefine, this, m_cfg);
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

	uint64_t EffectScript::SubscribeSuEvent(std::shared_ptr<SceneUnit> su, int ev_id, sol::protected_function lua_fn)
	{
		if (nullptr == su || !lua_fn.valid())
			return 0;

		LuaScribeEventFnDetail *hit_fn_detail = nullptr;
		for (LuaScribeEventFnDetail *fn_detail : LuaScribeSceneUnitEventFnDetail::s_allFnDetails)
		{
			if (ev_id == fn_detail->GetEventId())
			{
				hit_fn_detail = fn_detail;
				break;
			}
		}
		if (nullptr == hit_fn_detail)
			return 0;

		LuaSubscribeEventDetail *ev_detail = nullptr;
		{
			auto ev_detail_it = m_lua_subscribe_su_event_details.find(su->GetId());
			if (m_lua_subscribe_su_event_details.end() == ev_detail_it)
			{
				LuaSubscribeEventDetail *ev_detail = new LuaSubscribeEventDetail(
					&m_lua_effect_script, su->GetEvDispacher());
				auto ret_it = m_lua_subscribe_su_event_details.insert(std::make_pair(su->GetId(), ev_detail));
				assert(ret_it.second);
				ev_detail_it = ret_it.first;
			}
			ev_detail = ev_detail_it->second;
		}

		LuaScribeSceneUnitEventFnParam ev_param;
		ev_param.su = su;
		uint64_t ret = ev_detail->Subscribe(ev_id, lua_fn, (void**)&ev_param, LuaScribeSceneUnitEventFnDetail::s_allFnDetails);
		return ret;
	}

	void EffectScript::RemoveSuEvent(uint64_t su_id, uint64_t record_item_id)
	{
		auto ev_detail_it = m_lua_subscribe_su_event_details.find(su_id);
		if (m_lua_subscribe_su_event_details.end() == ev_detail_it)
			return;

		LuaSubscribeEventDetail *ev_detail = ev_detail_it->second;
		ev_detail->Remove(record_item_id);
	}

	void EffectScript::CancelAllSuEvent(uint64_t su_id)
	{
		auto ev_detail_it = m_lua_subscribe_su_event_details.find(su_id);
		if (m_lua_subscribe_su_event_details.end() == ev_detail_it)
			return;

		LuaSubscribeEventDetail *ev_detail = ev_detail_it->second;
		m_lua_subscribe_su_event_details.erase(ev_detail_it);
		delete ev_detail; ev_detail = nullptr;
	}

	void EffectScript::OnBegin()
	{
		sol::table scene_events = m_lua_effect_script["scene_events"];
		if (scene_events.valid())
		{
			for (LuaScribeEventFnDetail *elem : LuaScribeSceneEventFnDetail::s_allFnDetails)
			{
				LuaScribeSceneEventFnDetail *fn_detail = dynamic_cast<LuaScribeSceneEventFnDetail*>(elem);
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
		luaFn(m_lua_effect_script, now_ms, delta_ms);
	}

	void EffectScript::OnLateEnd(EEffectEndCase end_case)
	{
		sol::protected_function luaFn = m_lua_effect_script["on_late_end"];
		luaFn(m_lua_effect_script);

		m_lua_subscribe_scene_event_dtail->ClearAll();
	}
}