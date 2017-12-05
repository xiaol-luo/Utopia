#include "SceneUnitModule.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include <Common/EventDispatcher/EventDispacherProxy.h>
#include "GameLogic/Scene/SceneUnit/SceneUnitEventProxy.h"
#include "GameLogic/Scene/NewScene.h"

namespace GameLogic
{
	SceneUnitModule::~SceneUnitModule()
	{
		delete m_scene_event_proxy; m_scene_event_proxy = nullptr;
		delete m_event_proxy; m_event_proxy = nullptr;
		m_owner = nullptr;
	}
	uint64_t GameLogic::SceneUnitModule::GetId()
	{
		if (nullptr == m_owner)
			return 0;
		return m_owner->GetId();
	}
	void SceneUnitModule::Init(std::shared_ptr<SceneUnit> owner)
	{
		m_owner = owner;
		m_scene_event_proxy = new EventDispacherProxy(m_owner->GetScene()->GetEvDispacher());
		m_event_proxy = new SceneUnitEventProxy(m_owner->GetEvDispacher(), m_scene_event_proxy, m_owner);
		this->OnInit();
	}
	void SceneUnitModule::Destroy()
	{
		this->OnDestroy();
		delete m_scene_event_proxy; m_scene_event_proxy = nullptr;
		delete m_event_proxy; m_event_proxy = nullptr;
		m_owner = nullptr;
	}
}
