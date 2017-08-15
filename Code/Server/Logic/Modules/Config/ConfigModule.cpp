#include "ConfigModule.h"

ConfigModule::ConfigModule(std::shared_ptr<ModuleMgr> module_mgr) : IConfigModule(module_mgr)
{

}

ConfigModule::~ConfigModule()
{

}

EModuleRetCode ConfigModule::Init(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode ConfigModule::Awake(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode ConfigModule::Update(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode ConfigModule::Release(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode ConfigModule::Destroy(void *param)
{
	return EModuleRetCode_Succ;
}
