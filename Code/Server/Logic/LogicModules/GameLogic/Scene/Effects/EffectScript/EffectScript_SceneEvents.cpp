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
	static void OnSceneUnitFightParamChange(std::shared_ptr<SceneUnit> su, bool is_fix, NetProto::EFightParam efp, int new_value, int old_value, 
		EffectScript::LuaSubcribeItem *head, sol::table *self)
	{
		EffectScript::LuaSubcribeItem *item = head->next;
		while (nullptr != item)
		{
			item->fn(*self, su, is_fix, efp, new_value, old_value);
			item = item->next;
		}
	}

	uint64_t EffectScript::LuaSubscribeSceneEvent(int evId, sol::protected_function lua_fn)
	{
		if (!lua_fn.valid())
			return 0;
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
					head_item->event_handler_id =  
						m_scene_event_proxy->Subscribe<std::shared_ptr<SceneUnit>, bool, NetProto::EFightParam, int, int>(
							evId, std::bind(OnSceneUnitFightParamChange, std::placeholders::_1, std::placeholders::_2,
							std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, head_item, &m_lua_effect_script));
				}
				LuaSubcribeItem *head_item = it->second;
				LuaSubcribeItem *new_item = new LuaSubcribeItem();
				new_item->id = subscribe_id;
				new_item->fn = lua_fn;
				new_item->next = head_item->next;
				head_item->next = new_item;
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
}
