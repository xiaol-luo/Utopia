#include "EffectScript.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "EffectScriptConfig.h"
#include "GameLogic/Scene/Defines/EffectUtils.h"
#include "Utils/LuaUtils.h"
#include "SolLuaBindUtils.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"

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
		newFn.error_handler = LuaUtils::ProtectFnErrorHandler();
		m_lua_effect_script = newFn(typeDefine, this, nullptr);
		assert(m_lua_effect_script.valid());
	}

	EffectScript::~EffectScript()
	{
		LuaClearAllSubscribe();
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
	}

	void EffectScript::LuaRemoveSubscribe(uint64_t subcribe_id)
	{
		LuaSubcribeItem *head_item = nullptr;
		LuaSubcribeItem *remove_item = nullptr;
		int evId = -1;
		for (auto kv_pair : m_lua_subcribe_items)
		{
			evId = kv_pair.first;
			head_item = kv_pair.second;
			LuaSubcribeItem *pre_item = head_item;
			LuaSubcribeItem *item = head_item->next;
			while (nullptr != item)
			{
				if (subcribe_id == item->id)
				{
					remove_item = item;
					pre_item->next = item->next;
					item->next = nullptr;
					delete item;
					break;
				}
				item = item->next;
			}
			if (nullptr != remove_item)
				break;
		}
		if (nullptr != remove_item)
		{
			delete remove_item; remove_item = nullptr;
		}
		if (nullptr != head_item && nullptr == head_item->next)
		{
			m_lua_subcribe_items.erase(evId);
			m_scene_event_proxy->Cancel(head_item->event_handler_id);
			delete head_item; head_item = nullptr;
		}
	}

	void EffectScript::LuaClearAllSubscribe()
	{
		std::vector<LuaSubcribeItem *> delete_items;
		for (auto kv_pair : m_lua_subcribe_items)
		{
			LuaSubcribeItem *item = kv_pair.second;
			while (nullptr != item)
			{
				delete_items.push_back(item);
				item = item->next;
			}
		}
		m_lua_subcribe_items.clear();
		m_scene_event_proxy->CancelAll();
		for (auto item : delete_items)
		{
			delete item;
		}
		delete_items.clear();
	}
}