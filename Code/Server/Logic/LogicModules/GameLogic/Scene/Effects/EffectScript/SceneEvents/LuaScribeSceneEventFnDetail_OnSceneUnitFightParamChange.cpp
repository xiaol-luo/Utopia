#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneEventFnDetail.h"
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneUnitEventFnDetail.h"

namespace GameLogic
{
	static void OnSceneUnitFightParamChange(LuaSubcribeEventRecord *record, sol::table *self,
		std::shared_ptr<SceneUnit> su, bool is_fix, NetProto::EFightParam efp, 
		int new_value, int old_value, sol::object lua_param)
	{
		LuaSubcribeEventRecord::Item *item = record->head->next;
		while (item != record->head)
		{
			item->fn(*self, su, is_fix, efp, new_value, old_value, lua_param);
			item = item->next;
		}
	}

	static bool SubscribeSceneEvent_OnSceneUnitFightParamChange(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		record->subscribe_id = ev_proxy->Subscribe<std::shared_ptr<SceneUnit>, bool, NetProto::EFightParam, int, int>(ev_id,
			std::bind(OnSceneUnitFightParamChange, record, self, std::placeholders::_1, std::placeholders::_2,
				std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, nullptr));
		return record->subscribe_id > 0;
	}

	static const ESUEventId EVENT_ID = ESU_FightParamChange;
	static const char *LUA_FN_NAME = "OnSceneUnitFightParamChange";

	// LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange
	int LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange::GetEventId()
	{
		return EVENT_ID;
	}

	std::string LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange::GetLuaFunName()
	{
		return LUA_FN_NAME;
	}

	FnDoSubscribeEvent LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange::GetSubscribeEventFn() 
	{
		return SubscribeSceneEvent_OnSceneUnitFightParamChange;
	}

	// LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightParamChange
	int LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightParamChange::GetEventId()
	{
		return EVENT_ID;
	}

	std::string LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightParamChange::GetLuaFunName()
	{
		return LUA_FN_NAME;
	}

	static bool SubscribeSceneUnitEvent_OnSceneUnitFightParamChange(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		LuaScribeSceneUnitEventFnParam *fn_param = (LuaScribeSceneUnitEventFnParam *)(*param);
		record->subscribe_id = ev_proxy->Subscribe<bool, NetProto::EFightParam, int, int>(ev_id,
			std::bind(OnSceneUnitFightParamChange, record, self, fn_param->su, std::placeholders::_1,
				std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, fn_param->lua_param));
		return record->subscribe_id > 0;
	}
	FnDoSubscribeEvent LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightParamChange::GetSubscribeEventFn()
	{
		return SubscribeSceneUnitEvent_OnSceneUnitFightParamChange;
	}
}