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
	m_is_free = false;

	EModuleRetCode retCode = EModuleRetCode_Succ;
	for (int i = EMoudleName_Invalid + 1; i < EMoudleName_Max; ++ i)
	{
		auto module = m_modules[i];
		void *param = init_params[i];
		if (nullptr != module && EModuleState_Free == module->GetState())
			module->SetState(EModuleState_Initing);
		if (nullptr == module || EModuleState_Initing != module->GetState())
			continue;

		EModuleRetCode ret = module->Init(param);
		if (EModuleRetCode_Failed == ret)
		{
			module->SetState(EModuleState_Error);
			retCode = EModuleRetCode_Failed;
			break;
		}
		if (EModuleRetCode_Pending == ret)
			retCode = EModuleRetCode_Pending;
		if (EModuleRetCode_Succ == ret)
			module->SetState(EModuleState_Inited);
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Awake()
{
	EModuleRetCode retCode = EModuleRetCode_Succ;
	for (auto module : m_modules)
	{
		if (nullptr != module && EModuleState_Inited == module->GetState())
			module->SetState(EModuleState_Awaking);
		if (nullptr == module || EModuleState_Awaking != module->GetState())
			continue;

		EModuleRetCode ret = module->Awake();
		if (EModuleRetCode_Failed == ret)
		{
			module->SetState(EModuleState_Error);
			retCode = EModuleRetCode_Failed;
			break;
		}
		if (EModuleRetCode_Pending == ret)
			retCode = EModuleRetCode_Pending;
		if (EModuleRetCode_Succ == ret)
			module->SetState(EModuleState_Awaked);
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Update()
{

	EModuleRetCode retCode = EModuleRetCode_Pending;
	for (auto module : m_modules)
	{
		if (nullptr != module && EModuleState_Awaked == module->GetState())
			module->SetState(EModuleState_Updating);
		if (nullptr == module || EModuleState_Updating != module->GetState())
			continue;

		EModuleRetCode ret = module->Update();
		if (EModuleRetCode_Failed == ret)
		{
			module->SetState(EModuleState_Error);
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
		if (nullptr != module && EModuleState_Updating == module->GetState())
			module->SetState(EModuleState_Quiting);
		if (nullptr == module || EModuleState_Quiting != module->GetState())
			continue;

		EModuleRetCode ret = module->Release();
		if (EModuleRetCode_Failed == ret)
		{
			module->SetState(EModuleState_Error);
			retCode = EModuleRetCode_Failed;
			break;
		}
		if (EModuleRetCode_Pending == ret)
			retCode = EModuleRetCode_Pending;
		if (EModuleRetCode_Succ == ret)
			module->SetState(EModuleState_Quited);
	}
	return retCode;
}

EModuleRetCode ModuleMgr::Destroy()
{
	EModuleRetCode retCode = EModuleRetCode_Succ;
	for (auto module : m_modules)
	{
		if (nullptr != module && EModuleState_Quited == module->GetState())
			module->SetState(EModuleState_Destroying);
		if (nullptr == module || EModuleState_Destroying != module->GetState())
			continue;

		EModuleRetCode ret = module->Destroy();
		if (EModuleRetCode_Failed == ret)
		{
			module->SetState(EModuleState_Error);
			retCode = EModuleRetCode_Failed;
			break;
		}
		if (EModuleRetCode_Pending == ret)
			retCode = EModuleRetCode_Pending;
		if (EModuleRetCode_Succ == ret)
			module->SetState(EModuleState_Destroyed);
	}
	if (EModuleRetCode_Succ == retCode)
	{
		for (int i = EMoudleName_Invalid + 1; i < EMoudleName_Max; ++i)
			m_modules[i] = nullptr;		
	}
	return retCode;
}

bool ModuleMgr::SetModule(std::shared_ptr<IModule> module)
{
	if (m_is_free)
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

std::shared_ptr<IModule> ModuleMgr::GetModule(EMoudleName module_name)
{
	if (module_name > EMoudleName_Invalid && module_name < EMoudleName_Max)
	{
		return m_modules[module_name];
	}
	return nullptr;
}
