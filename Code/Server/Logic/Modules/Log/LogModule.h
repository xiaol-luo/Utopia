#pragma once

#include "ILogModule.h"

class LogModule : public ILogModule
{
public:
	LogModule(std::shared_ptr<ModuleMgr> module_mgr);
	virtual ~LogModule();
	virtual EModuleRetCode Init(void *param);
	virtual EModuleRetCode Awake();
	virtual EModuleRetCode Update();
	virtual EModuleRetCode Release();
	virtual EModuleRetCode Destroy();

private:

};