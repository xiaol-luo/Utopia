#pragma once

#include "Modules/IModule.h"

class INetworkModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EMoudleName_Network;
	INetworkModule(std::shared_ptr<ModuleMgr> module_mgr) : IModule(module_mgr , MODULE_NAME) {}
	virtual ~INetworkModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake(void *param) = 0;
	virtual EModuleRetCode Update(void *param) = 0;
	virtual EModuleRetCode Release(void *param) = 0;
	virtual EModuleRetCode Destroy(void *param) = 0;
};
