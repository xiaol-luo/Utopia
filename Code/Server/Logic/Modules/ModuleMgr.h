#pragma once

#include <memory>
#include "Modules/IModule.h"

class ModuleMgr : ObjectBase
{
public:
	ModuleMgr();
	~ModuleMgr();

	EModuleRetCode Init(void *param);
	EModuleRetCode Awake(void *param);
	EModuleRetCode Update(void *param);
	EModuleRetCode Realse(void *param);
	EModuleRetCode Destroy(void *param);

	bool SetModule(std::shared_ptr<IModule> module);
	template <typename T>
	T GetModule();
	EModuleState GetState() { return m_modules_state; }

private:
	EModuleState m_modules_state;
	std::shared_ptr<IModule> m_modules[EMoudleName_Max];
};
