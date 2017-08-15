#pragma once

#include "Modules/IModule.h"

class ILogModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EMoudleName_Log;
	ILogModule(std::shared_ptr<ModuleMgr> module_mgr) : IModule(module_mgr, MODULE_NAME) {}
	virtual ~ILogModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake(void *param) = 0;
	virtual EModuleRetCode Update(void *param) = 0;
	virtual EModuleRetCode Release(void *param) = 0;
	virtual EModuleRetCode Destroy(void *param) = 0;
};
