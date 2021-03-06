#pragma once

#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include <memory>

namespace GameLogic
{
	class SceneUnit;
	class SceneUnitEventProxy
	{
	public:
		SceneUnitEventProxy(EventDispacher *unit_dispacher, EventDispacherProxy *scene_proxy, std::shared_ptr<SceneUnit> unit)
		{
			m_unit = unit;
			m_unit_proxy = new EventDispacherProxy(unit_dispacher);
			m_scene_proxy = scene_proxy;
		}

		~SceneUnitEventProxy()
		{
			delete m_unit_proxy; m_unit_proxy = nullptr;
			m_scene_proxy = nullptr;
		}

		template <typename... Args>
		void Fire(int id, Args... args)
		{
			m_unit_proxy->Fire(id, args...);
			m_scene_proxy->Fire(id, m_unit.lock(), args...);
		}

		template <typename...Args>
		int64_t Subscribe(int id, std::function<void(Args...)> f)
		{
			return m_unit_proxy->Subscribe(id, f);
		}

		int64_t Subscribe(int id, std::function<void(void)> f)
		{
			return m_unit_proxy->Subscribe(id, f);
		}

		template <typename return_type, typename... Args>
		int64_t Subscribe(int id, std::function<return_type(Args...)>& f)
		{
			return m_unit_proxy->Subscribe(id, f);
		}

		template <typename return_type, typename... Args>
		int64_t Subscribe(int id, return_type(*f)(Args...))
		{
			return m_unit_proxy->Subscribe(id, f);
		}

		template <typename... Args, typename binder>
		int64_t Subscribe(int id, binder b)
		{
			return m_unit_proxy->Subscribe<Args...>(id, b);
		}

		void Cancel(int64_t subscribe_id)
		{
			m_unit_proxy->Cancel(subscribe_id);
		}

		void CancelAll()
		{
			m_unit_proxy->CancelAll();
		}


	private:
		std::weak_ptr<SceneUnit> m_unit;
		EventDispacherProxy *m_unit_proxy = nullptr;
		EventDispacherProxy *m_scene_proxy = nullptr;
	};
}
