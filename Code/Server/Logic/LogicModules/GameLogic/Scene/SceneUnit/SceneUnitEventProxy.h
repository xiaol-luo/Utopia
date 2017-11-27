#pragma once

#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"

namespace GameLogic
{
	class SceneUnit;
	class SceneUnitEventProxy
	{
	public:
		SceneUnitEventProxy(EventDispacher *unit_dispacher, EventDispacherProxy *scene_proxy, SceneUnit *unit)
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
			m_scene_proxy->Fire(id, m_unit, args...);
		}

		template <typename...Args, typename F>
		int64_t Subscribe(int id, F f)
		{
			m_unit_proxy->Subscribe(id, f);
		}

		template <typename Ret, typename...Args>
		int64_t Subscribe(int id, std::function<Ret(Args...)> f)
		{
			m_unit_proxy->Subscribe(id, f);
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
		SceneUnit *m_unit = nullptr;
		EventDispacherProxy *m_unit_proxy = nullptr;
		EventDispacherProxy *m_scene_proxy = nullptr;
	};
}