#include "LuaSubscribeEventDetail.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Utils/LuaUtils.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "EffectScript.h"
#include "SceneEvents/LuaSubscribeSceneEventFnDetail.h"

namespace GameLogic
{
	uint64_t LuaSubscribeSceneEventDetail::Subscribe(int evId, sol::protected_function lua_fn)
	{
		LuaScribeSceneEventFnDetail *hit_fn = nullptr;
		for (LuaScribeSceneEventFnDetail *item_fn : LuaScribeSceneEventFnDetail::s_allFnDetails)
		{
			if (item_fn->GetEventId() == evId)
			{
				hit_fn = item_fn;
			}
		}
		if (nullptr == hit_fn)
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
			auto subscribe_event_fn = hit_fn->GetSubscribeEventFn();
			bool ret = subscribe_event_fn(record, m_effect->GetLuaObject(), m_ev_proxy, evId);
			assert(ret);
		}
		return record_item_id;
	}
}