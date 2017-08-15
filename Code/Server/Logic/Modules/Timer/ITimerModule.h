#pragma once

#include "Modules/IModule.h"

class ITimerModule : IModule
{
public:
	ITimerModule() : IModule(EMoudleName_TIMER) {}
	virtual ~ITimerModule() {}
	virtual EModuleState Init(void *param) = 0;
	virtual EModuleState Awake(void *param) = 0;
	virtual EModuleState Update(void *param) = 0;
	virtual EModuleState Release(void *param) = 0;
	virtual EModuleState Destroy(void *param) = 0;
};
