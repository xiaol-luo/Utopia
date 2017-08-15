#pragma once

#include "Modules/IModule.h"

class IConfigModule : IModule
{
public:
	IConfigModule() : IModule(EMoudleName_Config) {}
	virtual ~IConfigModule() {}
	virtual EModuleState Init(void *param) = 0;
	virtual EModuleState Awake(void *param) = 0;
	virtual EModuleState Update(void *param) = 0;
	virtual EModuleState Release(void *param) = 0;
	virtual EModuleState Destroy(void *param) = 0;
};
