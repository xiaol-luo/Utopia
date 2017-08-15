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
	return EModuleRetCode_Succ;
}

EModuleRetCode ModuleMgr::Awake(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode ModuleMgr::Update(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode ModuleMgr::Realse(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode ModuleMgr::Destroy(void *param)
{
	return EModuleRetCode_Succ;
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
