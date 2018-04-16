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
	NewScene * SceneUnitModule::GetScene()
	{
		if (nullptr != m_owner)
			return m_owner->GetScene();
		return nullptr;
	}
	uint64_t GameLogic::SceneUnitModule::GetId()
	{
		if (nullptr == m_owner)
			return 0;
		return m_owner->GetId();
	}
	void SceneUnitModule::Init(SceneUnit *owner)
	{
		m_owner = owner;
		m_scene_event_proxy = new EventDispacherProxy(m_owner->GetScene()->GetEvDispacher());
		m_event_proxy = new SceneUnitEventProxy(m_owner->GetEvDispacher(), m_scene_event_proxy, m_owner->shared_from_this());
		this->OnInit();
	}
	void SceneUnitModule::Destroy()
	{
		this->OnDestroy();
		delete m_scene_event_proxy; m_scene_event_proxy = nullptr;
		delete m_event_proxy; m_event_proxy = nullptr;
		m_owner = nullptr;
	}
	void SceneUnitModule::SendSelf(int protocol_id, google::protobuf::Message * msg)
	{
		if (nullptr != m_owner)
			m_owner->SendSelf(protocol_id, msg);
	}
	void SceneUnitModule::SendSelfEx(std::vector<SyncClientMsg> msgs)
	{
		if (nullptr != m_owner)
			m_owner->SendSelfEx(msgs);
	}
	void SceneUnitModule::SendObservers(int protocol_id, google::protobuf::Message * msg)
	{
		if (nullptr != m_owner)
			m_owner->SendObservers(protocol_id, msg);
	}
	void SceneUnitModule::SendObserversEx(std::vector<SyncClientMsg> msgs)
	{
		if (nullptr != m_owner)
			m_owner->SendObserversEx(msgs);
	}
}
