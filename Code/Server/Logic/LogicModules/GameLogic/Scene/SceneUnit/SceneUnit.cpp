#include "SceneUnit.h"
#include <assert.h>
#include "SceneUnitModule.h"
#include "SceneUnitModules/SceneUnitTransform.h"

namespace GameLogic
{
	SceneUnit::SceneUnit(uint64_t id)
	{
		m_id = id;
		m_transform = std::make_shared<SceneUnitTransform>();
		this->AddModule(m_transform);
	}

	SceneUnit::~SceneUnit()
	{
		for (auto &&module : m_modules)
		{
			module = nullptr;
		}
	}

	void SceneUnit::AddModule(std::shared_ptr<SceneUnitModule> module)
	{
		assert(!m_inited);
		assert(nullptr == m_modules[module->GetModuleName()]);
		m_modules[module->GetModuleName()] = module;
		module->SetOwner(this);
	}

	void SceneUnit::EnterScene(Scene * scene)
	{
		if (m_inited)
			return;
		m_inited = true;
		m_started = false;

		for (auto &&module : m_modules)
		{
			if (nullptr != module)
				module->Init();
		}
		for (auto &&module : m_modules)
		{
			if (nullptr != module)
				module->Awake();
		}
	}

	void SceneUnit::LeaveScene()
	{
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

		m_scene = nullptr;
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
}

