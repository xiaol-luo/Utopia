#include "LuaSubscribeEventDetail.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Utils/LuaUtils.h"

namespace GameLogic
{
	LuaSubscribeSceneEventDetail::LuaSubscribeSceneEventDetail(EffectScript * effect, EventDispacher * ev_proxy)
	{
		m_effect = effect;
		m_ev_proxy = new EventDispacherProxy(ev_proxy);
	}

	LuaSubscribeSceneEventDetail::~LuaSubscribeSceneEventDetail()
	{
		this->ClearAll();
		m_effect = nullptr;
		delete m_ev_proxy; m_ev_proxy = nullptr;
	}

	void LuaSubscribeSceneEventDetail::Remove(uint64_t record_item_id)
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

	void LuaSubscribeSceneEventDetail::ClearAll()
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
}