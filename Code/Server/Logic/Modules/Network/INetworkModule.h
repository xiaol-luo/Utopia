#pragma once

#include "Modules/IModule.h"

class INetworkModule : IModule
{
public:
	INetworkModule() : IModule(EMoudleName_Network) {}
	virtual ~INetworkModule() {}
	virtual EModuleState Init(void *param) = 0;
	virtual EModuleState Awake(void *param) = 0;
	virtual EModuleState Update(void *param) = 0;
	virtual EModuleState Release(void *param) = 0;
	virtual EModuleState Destroy(void *param) = 0;
};
