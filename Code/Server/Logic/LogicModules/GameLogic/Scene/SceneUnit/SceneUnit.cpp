#include "SceneUnit.h"
#include <assert.h>
#include "SceneUnitModule.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitEventProxy.h"

namespace GameLogic
{
	SceneUnit::SceneUnit()
	{
		m_event_dispacher = new ::EventDispacher();
		m_transform = std::make_shared<SceneUnitTransform>();
	}

	SceneUnit::~SceneUnit()
	{
		for (auto &&module : m_modules)
		{
			module = nullptr;
		}
		m_transform = nullptr;
		delete m_event_proxy;  m_event_proxy = nullptr;
		delete m_scene_event_proxy; m_scene_event_proxy = nullptr;
		delete m_event_dispacher; m_event_dispacher = nullptr;
	}

	void SceneUnit::EnterScene(NewScene *scene, uint64_t id)
	{
		if (m_inited)
			return;
		m_inited = true;
		m_started = false;

		this->GetTransform();
		{
			m_scene = scene;
			m_id = id;
			m_scene_event_proxy = new EventDispacherProxy(m_scene->GetEvDispacher());
			m_event_proxy = new SceneUnitEventProxy(m_event_dispacher, m_scene_event_proxy, this->shared_from_this());
		}

		for (auto &&module : m_modules)
		{
			if (nullptr != module)
				module->Init(this->shared_from_this());
		}
		for (auto &&module : m_modules)
		{
			if (nullptr != module)
				module->Awake();
		}

		this->GetEvProxy()->Fire(ESU_EnterScene);
	}

	void SceneUnit::LeaveScene()
	{
		this->GetEvProxy()->Fire(ESU_LeaveScene);

		if (m_inited)
		{
			m_inited = false;
			for (auto &&module : m_modules)
			{
				if (nullptr != module)
					module->Realse();
			}
			for (auto &&module : m_modules)
			{
				if (nullptr != module)
					module->Destroy();
			}
		}
		for (auto &&module : m_modules)
		{
			module = nullptr;
		}

		{
			delete m_event_proxy;  m_event_proxy = nullptr;
			delete m_scene_event_proxy; m_scene_event_proxy = nullptr;
			m_scene = nullptr;
		}
	}

	int Test(int a, int b)
	{
		return 0;
	}

	void SceneUnit::Update()
	{
		if (!m_started)
		{
			m_started = true;
			for (auto &&module : m_modules)
			{
				if (nullptr != module)
					module->Start();
			}
		}
		else
		{
			for (auto &&module : m_modules)
			{
				if (nullptr != module)
					module->Update();
			}
		}
	}
	std::shared_ptr<SceneUnitTransform> SceneUnit::GetTransform()
	{
		if (nullptr == m_transform->GetOwner())
			this->AddModule(m_transform);
		return m_transform;
	}
	std::vector<SyncClientMsg> SceneUnit::CollectPBInit()
	{
		std::vector<SyncClientMsg> msgs;
		for (auto module : m_modules)
		{
			if (nullptr != module)
			{
				for (auto & msg : module->CollectPBInit())
					msgs.push_back(msg);
			}
		}
		return std::move(msgs);
	}
	std::vector<SyncClientMsg> SceneUnit::CollectPbMutable()
	{
		std::vector<SyncClientMsg> msgs;
		for (auto module : m_modules)
		{
			if (nullptr != module && module->IsPbDirty())
			{
				for (auto & msg : module->CollectPbMutable())
					msgs.push_back(msg);
			}
		}
		return std::move(msgs);
	}
	void SceneUnit::SendSelf(int protocol_id, google::protobuf::Message * msg)
	{
		if (0 == m_player_id || nullptr == m_scene)
			return;
		m_scene->SendPlayer(m_player_id, protocol_id, msg);
	}

	void SceneUnit::SendSelf(const std::vector<SyncClientMsg>& msgs)
	{
		if (0 == m_player_id || nullptr == m_scene)
			return;
		m_scene->SendPlayer(m_player_id, msgs);
	}
	void SceneUnit::SendObservers(int protocol_id, google::protobuf::Message * msg)
	{
		if (nullptr == m_scene)
			return;
		m_scene->SendObservers(m_id, protocol_id, msg);
	}
	void SceneUnit::SendObservers(const std::vector<SyncClientMsg>& msgs)
	{
		if (nullptr == m_scene)
			return;
		m_scene->SendObservers(m_id, msgs);
	}
	void SceneUnit::ClearPbDirty()
	{
		for (auto module : m_modules)
		{
			if (nullptr != m_modules)
				module->ClearPbDirty();
		}
	}
}

