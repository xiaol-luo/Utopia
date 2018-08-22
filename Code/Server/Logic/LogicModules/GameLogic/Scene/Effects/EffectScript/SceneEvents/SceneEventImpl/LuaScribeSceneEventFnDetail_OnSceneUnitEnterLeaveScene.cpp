
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneEventFnDetail.h"
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneUnitEventFnDetail.h"

namespace GameLogic
{
	static void OnSceneUnitEnterLeaveScene(LuaSubcribeEventRecord *record, sol::table *self,
		std::shared_ptr<SceneUnit> su)
	{
		LuaScribeEventFnDetail_FireFnHelp(record, self, su);
	}

	static bool SubscribeSceneEvent_SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		record->subscribe_id = ev_proxy->Subscribe<std::shared_ptr<SceneUnit>>(ev_id,
			std::bind(OnSceneUnitEnterLeaveScene, record, self, std::placeholders::_1));
		return record->subscribe_id > 0;
	}
	static bool SubscribeSceneUnitEvent_SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		LuaScribeSceneUnitEventFnParam *fn_param = (LuaScribeSceneUnitEventFnParam *)(param);
		record->subscribe_id = ev_proxy->Subscribe(ev_id,
			std::bind(OnSceneUnitEnterLeaveScene, record, self, fn_param->su));
		return record->subscribe_id > 0;
	}

	int LuaScribeSceneEventFnDetail_OnSceneUnitEnterLeaveScene::GetEventId()
	{
		return event_id;
	}

	std::string LuaScribeSceneEventFnDetail_OnSceneUnitEnterLeaveScene::GetLuaFunName()
	{
		return lua_fn_name;
	}

	FnDoSubscribeEvent LuaScribeSceneEventFnDetail_OnSceneUnitEnterLeaveScene::GetSubscribeEventFn()
	{
		return SubscribeSceneEvent_SubscribeHelpFn;
	}

	int LuaScribeSceneUnitEventFnDetail_OnSceneUnitEnterLeaveScene::GetEventId()
	{
		return event_id;
	}
	FnDoSubscribeEvent LuaScribeSceneUnitEventFnDetail_OnSceneUnitEnterLeaveScene::GetSubscribeEventFn()
	{
		return SubscribeSceneUnitEvent_SubscribeHelpFn;
	}
}