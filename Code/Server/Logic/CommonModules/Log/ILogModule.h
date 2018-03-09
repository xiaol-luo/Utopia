#pragma once

#include "ModuleDef/IModule.h"
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
	ILogModule(ModuleMgr *module_mgr) : IModule(module_mgr, MODULE_NAME) {}
	virtual ~ILogModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake() = 0;
	virtual EModuleRetCode Update() = 0;
	virtual EModuleRetCode Release() = 0;
	virtual EModuleRetCode Destroy() = 0;

	virtual void Record(ELogLevel log_level, int log_id, std::string msg) = 0;
	virtual void Record(ELogLevel log_level, int log_id, const char *msg) = 0;
};
