#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneEventFnDetail.h"
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneUnitEventFnDetail.h"

namespace GameLogic
{
	static const ESceneEvent EVENT_ID = ESU_PosChange;
	static const char *LUA_FN_NAME = "OnPosChange";

	static void OnSceneUnitFightPosChange(LuaSubcribeEventRecord *record, sol::table *self,
		std::shared_ptr<SceneUnit> su, Vector3 now_pos, Vector3 old_pos)
	{
		LuaScribeEventFnDetail_FireFnHelp(record, self, su, now_pos, old_pos);
	}

	static bool SubscribeSceneEvent_SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		record->subscribe_id = ev_proxy->Subscribe<std::shared_ptr<SceneUnit>, Vector3, Vector3>(ev_id,
			std::bind(OnSceneUnitFightPosChange, record, self, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		return record->subscribe_id > 0;
	}
	static bool SubscribeSceneUnitEvent__SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		LuaScribeSceneUnitEventFnParam *fn_param = (LuaScribeSceneUnitEventFnParam *)(param);
		record->subscribe_id = ev_proxy->Subscribe<Vector3, Vector3>(ev_id,
			std::bind(OnSceneUnitFightPosChange, record, self, fn_param->su, std::placeholders::_1, std::placeholders::_2));
		return record->subscribe_id > 0;
	}

	int LuaScribeSceneEventFnDetail_OnSceneUnitPosChange::GetEventId()
	{
		return EVENT_ID;
	}

	std::string LuaScribeSceneEventFnDetail_OnSceneUnitPosChange::GetLuaFunName()
	{
		return LUA_FN_NAME;
	}

	FnDoSubscribeEvent LuaScribeSceneEventFnDetail_OnSceneUnitPosChange::GetSubscribeEventFn()
	{
		return SubscribeSceneEvent_SubscribeHelpFn;
	}

	int LuaScribeSceneUnitEventFnDetail_OnSceneUnitPosChange::GetEventId()
	{
		return EVENT_ID;
	}
	FnDoSubscribeEvent LuaScribeSceneUnitEventFnDetail_OnSceneUnitPosChange::GetSubscribeEventFn()
	{
		return SubscribeSceneUnitEvent__SubscribeHelpFn;
	}
}