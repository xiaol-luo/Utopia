#pragma once

#include <memory>
#include "GameLogic/Scene/Defines/SceneDefine.h"

class EventDispacherProxy;

namespace GameLogic
{
	class SceneUnit;
	class SceneUnitEventProxy;

	class SceneUnitModule : public std::enable_shared_from_this<SceneUnitModule>
	{
		friend SceneUnit;
	public:
		SceneUnitModule(ESceneUnitModule module_name) { m_module_name = module_name; };
		virtual ~SceneUnitModule();

		inline SceneUnit * GetOwner() { return m_owner; }
		inline ESceneUnitModule GetModuleName() { return m_module_name; }
		template <typename T>
		std::shared_ptr<T> GetSharedPtr()
		{
			return std::dynamic_pointer_cast<T>(shared_from_this());
		}
		template <typename T>
		std::shared_ptr<T> GetSharedPtr() const
		{
			return std::dynamic_pointer_cast<T>(shared_from_this());
		}

		virtual uint64_t GetId();
		virtual void SetId(uint64_t val) {}
		inline SceneUnitEventProxy * GetEvProxy() { return m_event_proxy; }
		inline EventDispacherProxy * GetSceneEvProxy() { return m_scene_event_proxy; }

	protected:
		SceneUnit *m_owner = nullptr;
		ESceneUnitModule m_module_name = ESceneUnitModule_Count;
		EventDispacherProxy *m_scene_event_proxy = nullptr;
		SceneUnitEventProxy *m_event_proxy = nullptr;

	private:
		void Init(SceneUnit *owner);
		void Awake() { this->OnAwake(); }
		void Start() { this->OnUpdate(); }
		void Update() { this->OnUpdate(); }
		void Realse() { this->OnRelease(); }
		void Destroy();

	protected:
		virtual void OnInit() {}
		virtual void OnAwake() {}
		virtual void OnUpdate() {}
		virtual void OnRelease() {}
		virtual void OnDestroy() {}
	};
}