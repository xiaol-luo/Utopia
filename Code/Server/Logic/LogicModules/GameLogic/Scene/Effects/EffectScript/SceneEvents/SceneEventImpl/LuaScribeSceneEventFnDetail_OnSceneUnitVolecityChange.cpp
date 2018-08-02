#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneEventFnDetail.h"
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneUnitEventFnDetail.h"

namespace GameLogic
{
	static const ESUEventId EVENT_ID = ESU_VolecityChange;
	static const char *LUA_FN_NAME = "OnVolecityChange";

	static void OnSceneUnitVolecityChange(LuaSubcribeEventRecord *record, sol::table *self,
		std::shared_ptr<SceneUnit> su, Vector3 new_v, Vector3 old_v)
	{
		LuaScribeEventFnDetail_FireFnHelp(record, self, su, new_v, old_v);
	}

	static bool SubscribeSceneEvent_SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		record->subscribe_id = ev_proxy->Subscribe<std::shared_ptr<SceneUnit>, Vector3, Vector3>(ev_id,
			std::bind(OnSceneUnitVolecityChange, record, self, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		return record->subscribe_id > 0;
	}
	static bool SubscribeSceneUnitEvent__SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		LuaScribeSceneUnitEventFnParam *fn_param = (LuaScribeSceneUnitEventFnParam *)(param);
		record->subscribe_id = ev_proxy->Subscribe<Vector3, Vector3>(ev_id,
			std::bind(OnSceneUnitVolecityChange, record, self, fn_param->su, std::placeholders::_1, std::placeholders::_2));
		return record->subscribe_id > 0;
	}

	int LuaScribeSceneEventFnDetail_OnSceneUnitVolecityChange::GetEventId()
	{
		return EVENT_ID;
	}

	std::string LuaScribeSceneEventFnDetail_OnSceneUnitVolecityChange::GetLuaFunName()
	{
		return LUA_FN_NAME;
	}

	FnDoSubscribeEvent LuaScribeSceneEventFnDetail_OnSceneUnitVolecityChange::GetSubscribeEventFn()
	{
		return SubscribeSceneEvent_SubscribeHelpFn;
	}

	int LuaScribeSceneUnitEventFnDetail_OnSceneUnitVolecityChange::GetEventId()
	{
		return EVENT_ID;
	}
	FnDoSubscribeEvent LuaScribeSceneUnitEventFnDetail_OnSceneUnitVolecityChange::GetSubscribeEventFn()
	{
		return SubscribeSceneUnitEvent__SubscribeHelpFn;
	}
}