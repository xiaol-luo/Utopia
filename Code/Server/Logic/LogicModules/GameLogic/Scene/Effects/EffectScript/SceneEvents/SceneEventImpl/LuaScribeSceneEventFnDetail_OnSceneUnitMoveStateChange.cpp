#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneEventFnDetail.h"
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneUnitEventFnDetail.h"

namespace GameLogic
{
	static const ESUEventId EVENT_ID = ESU_MoveStateChange;
	static const char *LUA_FN_NAME = "OnMoveStateChange";

	static void OnSceneUnitMoveStateChange(LuaSubcribeEventRecord *record, sol::table *self,
		std::shared_ptr<SceneUnit> su, NetProto::EMoveAgentState now_state, NetProto::EMoveAgentState old_state)
	{
		LuaScribeEventFnDetail_FireFnHelp(record, self, su, now_state, old_state);
	}

	static bool SubscribeSceneEvent_SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		record->subscribe_id = ev_proxy->Subscribe<std::shared_ptr<SceneUnit>, NetProto::EMoveAgentState, NetProto::EMoveAgentState>(ev_id,
			std::bind(OnSceneUnitMoveStateChange, record, self, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		return record->subscribe_id > 0;
	}
	static bool SubscribeSceneUnitEvent__SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		LuaScribeSceneUnitEventFnParam *fn_param = (LuaScribeSceneUnitEventFnParam *)(param);
		record->subscribe_id = ev_proxy->Subscribe<NetProto::EMoveAgentState, NetProto::EMoveAgentState>(ev_id,
			std::bind(OnSceneUnitMoveStateChange, record, self, fn_param->su, std::placeholders::_1, std::placeholders::_2));
		return record->subscribe_id > 0;
	}

	int LuaScribeSceneEventFnDetail_OnSceneUnitMoveStateChange::GetEventId()
	{
		return EVENT_ID;
	}

	std::string LuaScribeSceneEventFnDetail_OnSceneUnitMoveStateChange::GetLuaFunName()
	{
		return LUA_FN_NAME;
	}

	FnDoSubscribeEvent LuaScribeSceneEventFnDetail_OnSceneUnitMoveStateChange::GetSubscribeEventFn()
	{
		return SubscribeSceneEvent_SubscribeHelpFn;
	}

	int LuaScribeSceneUnitEventFnDetail_OnSceneUnitMoveStateChange::GetEventId()
	{
		return EVENT_ID;
	}
	FnDoSubscribeEvent LuaScribeSceneUnitEventFnDetail_OnSceneUnitMoveStateChange::GetSubscribeEventFn()
	{
		return SubscribeSceneUnitEvent__SubscribeHelpFn;
	}
}