
#pragma once

#include "GameLogic/Scene/Effects/EffectBase.h"
#include <sol.hpp>

class EventDispacher;

namespace GameLogic
{
	class EffectScript;
	struct LuaSubcribeEventRecord
	{
		LuaSubcribeEventRecord()
		{
			head = new Item();
			head->pre = head;
			head->next = head;
		}
		~LuaSubcribeEventRecord()
		{
			delete head; head = nullptr;
		}

		int event_id = 0;
		uint64_t subscribe_id = 0;
		std::unordered_set<uint64_t> subcribe_ids;
		struct Item
		{
			uint64_t id = 0;
			sol::protected_function fn;
			Item *pre = nullptr;
			Item *next = nullptr;
		};
		Item *head = nullptr;
	};

	class LuaSubscribeSceneEventDetail
	{
	public:
		LuaSubscribeSceneEventDetail(EffectScript *effect, EventDispacher *ev_dispacter);
		~LuaSubscribeSceneEventDetail();

		uint64_t Subscribe(int evId, sol::protected_function &lua_fn);
		void Remove(uint64_t record_item_id);
		void ClearAll();

	private:
		uint64_t m_last_record_item_id = 0;
		EventDispacherProxy *m_ev_proxy = nullptr;
		EffectScript *m_effect = nullptr;
		std::unordered_map<int, LuaSubcribeEventRecord*> m_records;
	};
}