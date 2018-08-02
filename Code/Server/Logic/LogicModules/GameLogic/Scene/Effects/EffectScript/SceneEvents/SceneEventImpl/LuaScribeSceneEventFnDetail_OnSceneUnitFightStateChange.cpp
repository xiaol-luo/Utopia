#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneEventFnDetail.h"
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneUnitEventFnDetail.h"

namespace GameLogic
{
	static void OnSceneUnitFightStateChange(LuaSubcribeEventRecord *record, sol::table *self,
		std::shared_ptr<SceneUnit> su, bool attach_state)
	{
		LuaScribeEventFnDetail_FireFnHelp(record, self, su, attach_state);
	}
	static bool SubscribeSceneEvent_SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		record->subscribe_id = ev_proxy->Subscribe<std::shared_ptr<SceneUnit>, bool>(ev_id,
			std::bind(OnSceneUnitFightStateChange, record, self, std::placeholders::_1, std::placeholders::_2));
		return record->subscribe_id > 0;
	}
	static bool SubscribeSceneUnitEvent_SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		LuaScribeSceneUnitEventFnParam *fn_param = (LuaScribeSceneUnitEventFnParam *)(param);
		record->subscribe_id = ev_proxy->Subscribe<bool>(ev_id,
			std::bind(OnSceneUnitFightStateChange, record, self, fn_param->su, std::placeholders::_1));
		return record->subscribe_id > 0;
	}

	int LuaScribeSceneEventFnDetail_OnSceneUnitFightStateChange::GetEventId()
	{
		return event_id;
	}
	std::string LuaScribeSceneEventFnDetail_OnSceneUnitFightStateChange::GetLuaFunName()
	{
		return lua_fn_name;
	}
	FnDoSubscribeEvent LuaScribeSceneEventFnDetail_OnSceneUnitFightStateChange::GetSubscribeEventFn()
	{
		return SubscribeSceneEvent_SubscribeHelpFn;
	}

	int LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightStateChange::GetEventId()
	{
		return event_id;
	}
	FnDoSubscribeEvent LuaScribeSceneUnitEventFnDetail_OnSceneUnitFightStateChange::GetSubscribeEventFn()
	{
		return SubscribeSceneUnitEvent_SubscribeHelpFn;
	}
}