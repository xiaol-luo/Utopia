#pragma once

#include "EventDispacher.h"
#include <unordered_set>
#include <vector>

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

	template <typename return_type, typename... Args>
	int64_t Subscribe(int id, std::function<return_type(Args...)>& f)
	{
		int64_t ret = m_ev_dispacher->Subscribe(id, f);
		if (EventDispacher::INVALID_ID != ret)
			m_subscribe_ids.insert(ret);
		return ret;
	}

	template <typename return_type, typename... Args>
	int64_t Subscribe(int id, return_type(*f)(Args...))
	{
		int64_t ret = m_ev_dispacher->Subscribe(id, f);
		if (EventDispacher::INVALID_ID != ret)
			m_subscribe_ids.insert(ret);
		return ret;
	}

	template <typename... Args, typename binder>
	int64_t Subscribe(int id, binder b)
	{
		int64_t ret = m_ev_dispacher->Subscribe<Args...>(id, b);
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
		std::vector<uint64_t> subscribe_ids(m_subscribe_ids.begin(), m_subscribe_ids.end());
		for (uint64_t id : subscribe_ids)
		{
			this->Cancel(id);
		}
	}

	EventDispacher * GetEventDispacher() { return m_ev_dispacher; }

private:
	EventDispacher *m_ev_dispacher = nullptr;
	std::unordered_set<uint64_t> m_subscribe_ids;
};
