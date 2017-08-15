#pragma once

#include <memory>
#include "ObjectBase.h"

class ModuleMgr;

enum EMoudleName
{
	EMoudleName_Invalid,
	EMoudleName_TIMER,
	EMoudleName_Config,
	EMoudleName_Network,
	EMoudleName_Log,
	EMoudleName_Max,
};

enum EModuleState
{
	EModuleState_Free,
	EModuleState_Initing,
	EModuleState_Inited,
	EModuleState_Awaking,
	EModuleState_Awaked,
	EModuleState_Updating,
	EModuleState_Updated,
	EModuleState_Quiting,
	EModuleState_Quited,
	EModuleState_Destroying,
	EModuleState_Destroyed,
	EModuleState_Max,
};

enum EModuleRetCode
{
	EModuleRetCode_Succ,
	EModuleRetCode_Pending,
	EModuleRetCode_Failed,
	EModuleRetCode_Max,
};

class IModule : ObjectBase
{
public:
	IModule(std::shared_ptr<ModuleMgr> module_mgr, EMoudleName module_name) 
	{ 
		m_module_mgr = module_mgr;  
		m_module_name = module_name; 
	}
	virtual ~IModule() {}

	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake(void *param) = 0;
	virtual EModuleRetCode Update(void *param) = 0;
	virtual EModuleRetCode Release(void *param) = 0;
	virtual EModuleRetCode Destroy(void *param) = 0;
	EMoudleName ModuleName() { return m_module_name; }

protected:
	EMoudleName m_module_name = EMoudleName_Invalid;
	std::shared_ptr<ModuleMgr> m_module_mgr = nullptr;
};
