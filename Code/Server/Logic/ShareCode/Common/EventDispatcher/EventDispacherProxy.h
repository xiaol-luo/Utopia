#pragma once

#include "EventDispacher.h"
#include <unordered_set>

class EventDispacherProxy
{
public:
	EventDispacherProxy(EventDispacher *ev_dispacher) : m_ev_dispacher(ev_dispacher) {}
	~EventDispacherProxy()
	{
		this->CancelAll();
	}

	template <typename... Args>
	void Fire(int id, Args... args)
	{
		m_ev_dispacher->Fire(id, args...);
	}

	template <typename...Args>
	int64_t Subscribe(int id, std::function<void(Args...)> f)
	{
		int64_t ret = m_ev_dispacher->Subscribe(id, f);
		if (EventDispacher::INVALID_ID != ret)
			m_subscribe_ids.insert(ret);
		return ret;
	}

	int64_t Subscribe(int id, std::function<void()> f)
	{
		int64_t ret = m_ev_dispacher->Subscribe(id, f);
		if (EventDispacher::INVALID_ID != ret)
			m_subscribe_ids.insert(ret);
		return ret;
	}

	void Cancel(int64_t subscribe_id)
	{
		if (m_subscribe_ids.count(subscribe_id) > 0)
		{
			m_ev_dispacher->Cancel(subscribe_id);
			m_subscribe_ids.erase(subscribe_id);
		}
	}

	void CancelAll()
	{
		for (uint64_t id : m_subscribe_ids)
		{
			m_ev_dispacher->Cancel(id);
		}
		m_subscribe_ids.clear();
	}

private:
	EventDispacher *m_ev_dispacher = nullptr;
	std::unordered_set<uint64_t> m_subscribe_ids;
};
