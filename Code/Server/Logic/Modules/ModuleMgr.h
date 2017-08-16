#pragma once

#include <memory>
#include "Modules/IModule.h"

class ModuleMgr : ObjectBase
{
public:
	ModuleMgr();
	~ModuleMgr();

	EModuleRetCode Init(void * init_params[EMoudleName_Max]);
	EModuleRetCode Awake();
	EModuleRetCode Update();
	EModuleRetCode Realse();
	EModuleRetCode Destroy();

	bool SetModule(std::shared_ptr<IModule> module);
	template <typename T>
	T GetModule();
	std::shared_ptr<IModule> GetModule(EMoudleName module_name);
	EModuleState GetState() { return m_modules_state; }

private:
	EModuleState m_modules_state = EModuleState_Free;
	std::shared_ptr<IModule> m_modules[EMoudleName_Max];
};
