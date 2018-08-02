#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneEventFnDetail.h"
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneUnitEventFnDetail.h"

namespace GameLogic
{
	static void OnSceneUnitFightHpMpChange(LuaSubcribeEventRecord *record, sol::table *self,
		std::shared_ptr<SceneUnit> su, int now_val, int old_val, int delta_val, EffectBase *effect)
	{
		LuaScribeEventFnDetail_FireFnHelp(record, self, su, now_val, old_val, delta_val, effect);
	}
	static bool SubscribeSceneEvent_SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		record->subscribe_id = ev_proxy->Subscribe<std::shared_ptr<SceneUnit>, int, int, int, EffectBase *>(ev_id,
			std::bind(OnSceneUnitFightHpMpChange, record, self, std::placeholders::_1, std::placeholders::_2,
				std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
		return record->subscribe_id > 0;
	}
	static bool SubscribeSceneUnitEvent_SubscribeHelpFn(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id, void **param)
	{
		LuaScribeSceneUnitEventFnParam *fn_param = (LuaScribeSceneUnitEventFnParam *)(param);
		record->subscribe_id = ev_proxy->Subscribe<int, int, int, EffectBase *>(ev_id,
			std::bind(OnSceneUnitFightHpMpChange, record, self, fn_param->su, std::placeholders::_1, std::placeholders::_2,
				std::placeholders::_3, std::placeholders::_4));
		return record->subscribe_id > 0;
	}

	int LuaScribeSceneEventFnDetail_OnSceneUnitHpMpChange::GetEventId()
	{
		return event_id;
	}
	std::string LuaScribeSceneEventFnDetail_OnSceneUnitHpMpChange::GetLuaFunName()
	{
		return lua_fn_name;
	}

	FnDoSubscribeEvent LuaScribeSceneEventFnDetail_OnSceneUnitHpMpChange::GetSubscribeEventFn()
	{
		return SubscribeSceneEvent_SubscribeHelpFn;
	}

	int LuaScribeSceneUnitEventFnDetail_OnSceneUnitHpMpChange::GetEventId()
	{
		return event_id;
	}
	FnDoSubscribeEvent LuaScribeSceneUnitEventFnDetail_OnSceneUnitHpMpChange::GetSubscribeEventFn()
	{
		return SubscribeSceneUnitEvent_SubscribeHelpFn;
	}
}