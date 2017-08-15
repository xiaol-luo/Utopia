#include "LogModule.h"

LogModule::LogModule(std::shared_ptr<ModuleMgr> module_mgr) : ILogModule(module_mgr)
{

}

LogModule::~LogModule() 
{

}

EModuleRetCode LogModule::Init(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode LogModule::Awake(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode LogModule::Update(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode LogModule::Release(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode LogModule::Destroy(void *param)
{
	return EModuleRetCode_Succ;
}
