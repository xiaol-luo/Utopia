#include "LuaSubscribeEventDetail.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Utils/LuaUtils.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "EffectScript.h"

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
	bool SubscribeEvent_OnSceneUnitFightParamChange(LuaSubcribeEventRecord *record, sol::table *self, EventDispacherProxy *ev_proxy, int ev_id)
	{
		record->subscribe_id = ev_proxy->Subscribe<std::shared_ptr<SceneUnit>, bool, NetProto::EFightParam, int, int>(ev_id, 
			std::bind(OnSceneUnitFightParamChange, record, self, std::placeholders::_1, std::placeholders::_2,
				std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
		return record->subscribe_id > 0;
	}
	
	typedef bool (*FnSubscribeSceneEventHelp)(LuaSubcribeEventRecord*, sol::table *self, EventDispacherProxy*, int);
	static std::unordered_map<int, FnSubscribeSceneEventHelp> s_subscribe_scene_event_help_fns({
		{ ESU_FightParamChange,  SubscribeEvent_OnSceneUnitFightParamChange }
	});

	uint64_t LuaSubscribeSceneEventDetail::Subscribe(int evId, sol::protected_function &lua_fn)
	{
		auto subscribe_fn_it = s_subscribe_scene_event_help_fns.find(evId);
		if (s_subscribe_scene_event_help_fns.end() == subscribe_fn_it)
			return 0;

		auto record_it = m_records.find(evId);
		if (m_records.end() == record_it)
		{
			LuaSubcribeEventRecord *new_record = new LuaSubcribeEventRecord();
			new_record->event_id = evId;
			auto ret = m_records.insert(std::make_pair(evId, new_record));
			assert(ret.second);
			record_it = ret.first;
		}

		++m_last_record_item_id;
		uint64_t record_item_id = m_last_record_item_id;
		LuaSubcribeEventRecord *record = record_it->second;
		LuaSubcribeEventRecord::Item *item = new LuaSubcribeEventRecord::Item();
		item->id = record_item_id;
		item->fn = lua_fn;
		lua_fn.error_handler = LuaUtils::ProtectFnErrorHandler();
		record->head->next->pre = item;
		item->next = record->head->next;
		record->head->next = item;
		item->pre = record->head;

		if (record->subscribe_id <= 0)
		{
			bool ret = subscribe_fn_it->second(record, m_effect->GetLuaObject(), m_ev_proxy, evId);
			assert(ret);
		}
		return record_item_id;
	}
}