#include "ModuleMgr.h"
#include <assert.h>

ModuleMgr::ModuleMgr()
{

}

ModuleMgr::~ModuleMgr()
{
	for (int i = 0; i < EMoudleName_Max; ++ i)
	{
		m_modules[i] = nullptr;
	}
}

EModuleRetCode ModuleMgr::Init(void * init_params[EMoudleName_Max])
{
	EModuleRetCode retCode = EModuleRetCode_Succ;
	for (int i = EMoudleName_Invalid + 1; i < EMoudleName_Max; ++ i)
	{
		auto module = m_modules[i];
		void *param = init_params[i];
		if (nullptr == module)
			continue;

		EModuleRetCode ret = module->Init(param);
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Failed;
			break;
		}
		if (EModuleRetCode_Pending == ret)
		{
			retCode = EModuleRetCode_Pending;
		}
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Awake()
{
	EModuleRetCode retCode = EModuleRetCode_Succ;
	for (auto module : m_modules)
	{
		if (nullptr == module)
			continue;

		EModuleRetCode ret = module->Awake();
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Failed;
			break;
		}
		if (EModuleRetCode_Pending == ret)
		{
			retCode = EModuleRetCode_Pending;
		}
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Update()
{
	EModuleRetCode retCode = EModuleRetCode_Pending;
	for (auto module : m_modules)
	{
		if (nullptr == module)
			continue;

		EModuleRetCode ret = module->Update();
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Failed;
			break;
		}
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Realse()
{
	EModuleRetCode retCode = EModuleRetCode_Succ;
	for (auto module : m_modules)
	{
		if (nullptr == module)
			continue;

		EModuleRetCode ret = module->Release();
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Failed;
			break;
		}
		if (EModuleRetCode_Pending == ret)
		{
			retCode = EModuleRetCode_Pending;
		}
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Destroy()
{
	EModuleRetCode retCode = EModuleRetCode_Succ;
	for (auto module : m_modules)
	{
		if (nullptr == module)
			continue;

		EModuleRetCode ret = module->Destroy();
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Failed;
			break;
		}
		if (EModuleRetCode_Pending == ret)
		{
			retCode = EModuleRetCode_Pending;
		}
	}
	return retCode;
}

bool ModuleMgr::SetModule(std::shared_ptr<IModule> module)
{
	if (EModuleState_Free == m_modules_state)
	{
		EMoudleName module_name = module->ModuleName();
		assert(module_name > EMoudleName_Invalid && module_name < EMoudleName_Max);
		if (nullptr == m_modules[module_name])
		{
			m_modules[module_name] = module;
			return true;
		}
	}
	return false;
}

template <typename T>
T ModuleMgr::GetModule()
{
	return this->GetModule(T::MODULE_NAME);
}

std::shared_ptr<IModule> ModuleMgr::GetModule(EMoudleName module_name)
{
	if (module_name > EMoudleName_Invalid && module_name < EMoudleName_Max)
	{
		return m_modules[module_name];
	}
	return nullptr;
}
