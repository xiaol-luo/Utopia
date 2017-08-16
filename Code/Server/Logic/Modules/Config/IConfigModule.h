#pragma once

#include "Modules/IModule.h"

class IConfigModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EMoudleName_Config;
	IConfigModule(std::shared_ptr<ModuleMgr> module_mgr) : IModule(module_mgr, MODULE_NAME) {}
	virtual ~IConfigModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake() = 0;
	virtual EModuleRetCode Update() = 0;
	virtual EModuleRetCode Release() = 0;
	virtual EModuleRetCode Destroy() = 0;
};
