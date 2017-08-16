#include "LogModule.h"
#include "Modules/ModuleMgr.h"
#include "log/CsvLogConfig.h"

LogModule::LogModule(std::shared_ptr<ModuleMgr> module_mgr) : ILogModule(module_mgr)
{

}

LogModule::~LogModule() 
{

}

EModuleRetCode LogModule::Init(void *param)
{
	if (EModuleState_Error == m_state)
		return EModuleRetCode_Failed;
	if (EModuleState_Inited == m_state)
		return EModuleRetCode_Succ;

	Config::CsvLogConfigSet log_cfg;
	std::string *file_path = (std::string *)param;
	bool ret = log_cfg.Load(*file_path);
	m_state = ret ? EModuleState_Inited : EModuleState_Error;
	return ret ? EModuleRetCode_Succ : EModuleRetCode_Failed;
}

EModuleRetCode LogModule::Awake()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode LogModule::Update()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode LogModule::Release()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode LogModule::Destroy()
{
	return EModuleRetCode_Succ;
}
