#pragma once

#include "GameLogic/Scene/Defines/SceneDefine.h"

class EventDispacherProxy;

namespace GameLogic
{
	class NewScene;
	class SceneModule
	{
		friend NewScene;
	public:
		SceneModule(ESceneModule module_name) { m_module_name = module_name; };
		virtual ~SceneModule();
		inline ESceneModule GetModuleName() { return m_module_name; }
		inline NewScene * GetScene() { return m_scene; }
		inline EventDispacherProxy * GetSceneEvProxy() { return m_event_proxy; }
	
	protected:
		NewScene *m_scene = nullptr;
		ESceneModule m_module_name = ESceneModule_Count;
		EventDispacherProxy *m_event_proxy = nullptr;

	private:
		bool Init(NewScene *owner);
		bool Awake() { return this->OnAwake(); }
		void Start() { this->OnUpdate(); }
		void Update() { this->OnUpdate(); }
		void Realse() { this->OnRelease(); }
		void Destroy();

	protected:
		virtual bool OnInit() { return true; }
		virtual bool OnAwake() { return true; }
		virtual void OnUpdate() {}
		virtual void OnRelease() {}
		virtual void OnDestroy() {}
	};
}
