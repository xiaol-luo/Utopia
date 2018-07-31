
#pragma once

#include "GameLogic/Scene/Effects/EffectBase.h"
#include <sol.hpp>

class EventDispacher;

namespace GameLogic
{
	class EffectScript;
	class LuaScribeEventFnDetail;

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
		struct Item
		{
			uint64_t id = 0;
			sol::protected_function fn;
			Item *pre = nullptr;
			Item *next = nullptr;
		};
		Item *head = nullptr;
	};

	class LuaSubscribeEventDetail
	{
	public:
		LuaSubscribeEventDetail(sol::table *lua_table, EventDispacher *ev_dispacter);
		~LuaSubscribeEventDetail();

		uint64_t Subscribe(int evId, sol::protected_function lua_fn, void **param,
			std::vector<LuaScribeEventFnDetail *> &fn_details);
		void Remove(uint64_t record_item_id);
		void ClearAll();

	private:
		uint64_t m_last_record_item_id = 0;
		EventDispacherProxy *m_ev_proxy = nullptr;
		sol::table *m_lua_table = nullptr;
		std::unordered_map<int, LuaSubcribeEventRecord*> m_records;
	};
}