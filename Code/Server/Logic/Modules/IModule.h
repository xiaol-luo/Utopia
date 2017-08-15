#pragma once

enum EMoudleName
{
	EMoudleName_Invalid,
	EMoudleName_TIMER,
	EMoudleName_Config,
	EMoudleName_Network,
	EMoudleName_Max,
};

enum EModuleState
{

};

class IModule
{
public:
	IModule(EMoudleName module_name) { m_module_name = module_name; }
	virtual ~IModule() {}
	virtual EModuleState Init(void *param) = 0;
	virtual EModuleState Awake(void *param) = 0;
	virtual EModuleState Update(void *param) = 0;
	virtual EModuleState Release(void *param) = 0;
	virtual EModuleState Destroy(void *param) = 0;
	EMoudleName ModuleName() { return m_module_name; }

private:
	EMoudleName m_module_name = EMoudleName_Invalid;
};
