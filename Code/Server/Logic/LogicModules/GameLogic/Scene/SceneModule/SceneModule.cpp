#include "SceneModule.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/NewScene.h"

namespace GameLogic
{
	SceneModule::~SceneModule()
	{
	}

	bool SceneModule::Init(NewScene *scene)
	{
		m_scene = scene;
		m_event_proxy = new EventDispacherProxy(m_scene->GetEvDispacher());
		return this->OnInit();
	}

	void SceneModule::Destroy()
	{
		this->OnDestroy();
		delete m_event_proxy; m_event_proxy = nullptr;
	}
}
