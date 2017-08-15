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

EModuleRetCode ModuleMgr::Init(void *param)
{
	EModuleRetCode retCode = EModuleRetCode_Succ;
	for (auto module : m_modules)
	{
		if (nullptr == module)
			continue;

		EModuleRetCode ret = module->Init(param);
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Failed;
			break;
		}
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Pending;
		}
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Awake(void *param)
{
	EModuleRetCode retCode = EModuleRetCode_Succ;
	for (auto module : m_modules)
	{
		if (nullptr == module)
			continue;

		EModuleRetCode ret = module->Awake(param);
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Failed;
			break;
		}
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Pending;
		}
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Update(void *param)
{
	EModuleRetCode retCode = EModuleRetCode_Pending;
	for (auto module : m_modules)
	{
		if (nullptr == module)
			continue;

		EModuleRetCode ret = module->Update(param);
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Failed;
			break;
		}
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Realse(void *param)
{
	EModuleRetCode retCode = EModuleRetCode_Pending;
	for (auto module : m_modules)
	{
		if (nullptr == module)
			continue;

		EModuleRetCode ret = module->Release(param);
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Failed;
			break;
		}
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Destroy(void *param)
{
	EModuleRetCode retCode = EModuleRetCode_Pending;
	for (auto module : m_modules)
	{
		if (nullptr == module)
			continue;

		EModuleRetCode ret = module->Destroy(param);
		if (EModuleRetCode_Failed == ret)
		{
			retCode = EModuleRetCode_Failed;
			break;
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
	EMoudleName module_name = T::MODULE_NAME;
	assert(module_name > EMoudleName_Invalid \
		&& module_name < EMoudleName_Max);
	assert(nullptr != m_modules[module_name]);
	return m_modules[module_name];
}
