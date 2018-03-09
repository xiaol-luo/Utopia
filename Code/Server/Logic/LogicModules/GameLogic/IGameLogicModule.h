#pragma once

#include "ModuleDef/IModule.h"

class IGameLogicModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EMoudleName_GameLogic;
	IGameLogicModule(ModuleMgr *module_mgr) : IModule(module_mgr, MODULE_NAME) {}
	virtual ~IGameLogicModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake() = 0;
	virtual EModuleRetCode Update() = 0;
	virtual EModuleRetCode Release() = 0;
	virtual EModuleRetCode Destroy() = 0;
};
