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
	template <typename T> std::shared_ptr<T> ModuleMgr::GetModule() { return std::static_pointer_cast<T>(this->GetModule(T::MODULE_NAME)); }
	std::shared_ptr<IModule> GetModule(EMoudleName module_name);

private:
	bool m_is_free = true;
	std::shared_ptr<IModule> m_modules[EMoudleName_Max];
};
