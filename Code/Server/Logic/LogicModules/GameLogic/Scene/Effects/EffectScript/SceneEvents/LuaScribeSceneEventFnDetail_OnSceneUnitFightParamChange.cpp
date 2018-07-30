#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaSubscribeSceneEventFnDetail.h"

namespace GameLogic
{
	static void OnSceneUnitFightParamChange(LuaSubcribeEventRecord *record, sol::table *self,
		std::shared_ptr<SceneUnit> su, bool is_fix, NetProto::EFightParam efp, int new_value, int old_value)
	{
		LuaSubcribeEventRecord::Item *item = record->head->next;
		while (item != record->head)
		{
			item->fn(*self, su, is_fix, efp, new_value, old_value);
			item = item->next;
		}
	}
	static bool SubscribeEvent_OnSceneUnitFightParamChange(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id)
	{
		record->subscribe_id = ev_proxy->Subscribe<std::shared_ptr<SceneUnit>, bool, NetProto::EFightParam, int, int>(ev_id,
			std::bind(OnSceneUnitFightParamChange, record, self, std::placeholders::_1, std::placeholders::_2,
				std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
		return record->subscribe_id > 0;
	}

	// Í¨¹ý LuaScribeSceneEventFnDetail ¼Ì³Ð
	int LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange::GetEventId()
	{
		return ESU_FightParamChange;
	}

	std::string LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange::GetLuaFunName()
	{
		return "OnSceneUnitFightParamChange";
	}

	FnSubscribeSceneEventHelp LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange::GetSubscribeEventFn() 
	{
		return SubscribeEvent_OnSceneUnitFightParamChange;
	}
}