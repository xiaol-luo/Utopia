#include "LuaSubscribeEventDetail.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Utils/LuaUtils.h"
#include "EffectScript.h"
#include "SceneEvents/LuaScribeEventFnDetail.h"

namespace GameLogic
{
	LuaSubscribeEventDetail::LuaSubscribeEventDetail(sol::table * lua_table, EventDispacher * ev_proxy)
	{
		m_lua_table = lua_table;
		m_ev_proxy = new EventDispacherProxy(ev_proxy);
	}

	LuaSubscribeEventDetail::~LuaSubscribeEventDetail()
	{
		this->ClearAll();
		m_lua_table = nullptr;
		delete m_ev_proxy; m_ev_proxy = nullptr;
	}

	void LuaSubscribeEventDetail::Remove(uint64_t record_item_id)
	{
		LuaSubcribeEventRecord *hit_record = nullptr;
		LuaSubcribeEventRecord::Item *delete_item = nullptr;
		for (auto kv_pair : m_records)
		{
			LuaSubcribeEventRecord *record = kv_pair.second;
			LuaSubcribeEventRecord::Item *item = record->head->next;
			while (item != record->head)
			{
				if (item->id == record_item_id)
				{
					hit_record = record;
					delete_item = item;
					break;
				}
			}
			if (nullptr != delete_item)
				break;
			item = item->next;
		}

		if (nullptr != delete_item)
		{
			delete_item->pre->next = delete_item->next;
			delete_item->next->pre = delete_item->pre;
			delete delete_item; delete_item = nullptr;
		}
		if (nullptr != hit_record && hit_record->head->next == hit_record->head)
		{
			m_ev_proxy->Cancel(hit_record->subscribe_id);
			m_records.erase(hit_record->event_id);
			delete hit_record; hit_record = nullptr;
		}
	}

	void LuaSubscribeEventDetail::ClearAll()
	{
		for (auto kv_pair : m_records)
		{
			LuaSubcribeEventRecord *record = kv_pair.second;
			LuaSubcribeEventRecord::Item *item = record->head->next;
			while (item != record->head)
			{
				LuaSubcribeEventRecord::Item *next_item = item->next;
				delete item;
				item = next_item;
			}
			delete record;
		}
		m_ev_proxy->CancelAll();
		m_records.clear();
	}


	uint64_t LuaSubscribeEventDetail::Subscribe(int evId, sol::protected_function lua_fn, 
		void **param, std::vector<LuaScribeEventFnDetail *> &fn_details)
	{
		LuaScribeEventFnDetail *hit_fn = nullptr;
		for (LuaScribeEventFnDetail *item_fn : fn_details)
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
			bool ret = subscribe_event_fn(record, m_lua_table, m_ev_proxy, evId, param);
			assert(ret);
		}
		return record_item_id;
	}
}