#pragma once

#include "ILogModule.h"

class LogModule : public ILogModule
{
public:
	LogModule(std::shared_ptr<ModuleMgr> module_mgr);
	virtual ~LogModule();
	virtual EModuleRetCode Init(void *param);
	virtual EModuleRetCode Awake(void *param);
	virtual EModuleRetCode Update(void *param);
	virtual EModuleRetCode Release(void *param);
	virtual EModuleRetCode Destroy(void *param);
};