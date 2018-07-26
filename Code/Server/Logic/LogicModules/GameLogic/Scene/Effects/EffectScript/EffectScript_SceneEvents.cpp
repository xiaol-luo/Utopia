#include "EffectScript.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "EffectScriptConfig.h"
#include "GameLogic/Scene/Defines/EffectUtils.h"
#include "Utils/LuaUtils.h"
#include "SolLuaBindUtils.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "assert.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"

namespace GameLogic
{
	static void OnSceneUnitFightParamChange(std::shared_ptr<SceneUnit> su, bool is_fix, NetProto::EFightParam efp, int new_value, int old_value, EffectScript::LuaSubcribeItem *head, sol::table self)
	{
		EffectScript::LuaSubcribeItem *item = head->next;
		while (nullptr != item)
		{
			sol::protected_function fn = item->fn;
			item = item->next;
			fn(self, su, is_fix, efp, new_value, old_value);
		}
	}

	uint64_t EffectScript::LuaSubscribeSceneEvent(int evId, sol::protected_function lua_fn)
	{
		bool isInserted = false;
		++m_last_subcribe_id;
		uint64_t subscribe_id = m_last_subcribe_id;
		auto it = m_lua_subcribe_items.find(evId);
		switch (evId)
		{
			case ESU_FightParamChange:
			{
				if (m_lua_subcribe_items.end() == it)
				{
					LuaSubcribeItem *head_item = new LuaSubcribeItem();
					auto ret = m_lua_subcribe_items.insert(std::make_pair(evId, head_item));
					assert(ret.second);
					it = ret.first;
					m_scene_event_dispacher->Subscribe<std::shared_ptr<SceneUnit>, bool, NetProto::EFightParam, int, int>(
						evId, std::bind(OnSceneUnitFightParamChange, std::placeholders::_1, std::placeholders::_2,
						std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, head_item, m_lua_effect_script));
				}
				LuaSubcribeItem *head_item = it->second;
				LuaSubcribeItem *new_item = new LuaSubcribeItem();
				new_item->next = head_item->next;
				head_item->next = new_item;
				new_item->id = subscribe_id;
				isInserted = true;
			}
			break;

			default:
				break;
		}
		if (isInserted)
		{
			lua_fn.error_handler = LuaUtils::ProtectFnErrorHandler();
		}
		return isInserted ? 0 : subscribe_id;
	}

	void EffectScript::LuaRemoveSubscribe(uint64_t subcribe_id)
	{
		bool isFound = false;
		LuaSubcribeItem *head_item = nullptr;
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
					bool isFound = true;
					pre_item->next = item->next;
					delete item;
					break;
				}
			}
			if (isFound)
				break;
		}
		if (isFound && -1 != evId && nullptr != head_item && nullptr == head_item->next)
		{
			m_scene_event_dispacher->Cancel(evId);
			m_lua_subcribe_items.erase(evId);
			delete head_item; head_item = nullptr;
		}
	}

	void EffectScript::LuaClearAllSubscribe()
	{
		std::vector<LuaSubcribeItem *> delete_items;
		for (auto kv_pair : m_lua_subcribe_items)
		{
			m_scene_event_dispacher->Cancel(kv_pair.first);
			LuaSubcribeItem *item = kv_pair.second;
			while (nullptr != item)
			{
				delete_items.push_back(item);
			}
		}
		m_lua_subcribe_items.clear();
		for (auto item : delete_items)
		{
			delete item;
		}
		delete_items.clear();
	}

}