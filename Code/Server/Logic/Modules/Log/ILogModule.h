#pragma once

#include "Modules/IModule.h"
#include "spdlog/spdlog.h"

enum ELogLevel
{
	ELogLevel_Invalid = 0,
	ELogLevel_Debug,
	ELogLevel_Info,
	ELogLevel_Warn,
	ELogLevel_Err,
	ELogLevel_Max
};

class ILogModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EMoudleName_Log;
	ILogModule(std::shared_ptr<ModuleMgr> module_mgr) : IModule(module_mgr, MODULE_NAME) {}
	virtual ~ILogModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake() = 0;
	virtual EModuleRetCode Update() = 0;
	virtual EModuleRetCode Release() = 0;
	virtual EModuleRetCode Destroy() = 0;

};
