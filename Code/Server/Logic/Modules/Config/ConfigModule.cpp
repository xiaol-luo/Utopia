#include "ConfigModule.h"
#include "CsvConfigSets.h"
#include "Modules/ModuleMgr.h"
#include "modules/Log/LogModule.h"

ConfigModule::ConfigModule(std::shared_ptr<ModuleMgr> module_mgr) : IConfigModule(module_mgr)
{
	m_csv_cfg_sets = new Config::CsvConfigSets();
}

ConfigModule::~ConfigModule()
{

}

EModuleRetCode ConfigModule::Init(void *param)
{
	if (EModuleState_Error == m_state)
		return EModuleRetCode_Failed;
	if (EModuleState_Inited == m_state)
		return EModuleRetCode_Succ;

	WaitModuleState(EMoudleName_Log, EModuleState_Inited, false);

	std::string *file_path = (std::string *)param;
	bool ret = m_csv_cfg_sets->Load(*file_path);
	m_state = ret ? EModuleState_Inited : EModuleState_Error;

	std::shared_ptr<LogModule> log_module = m_module_mgr->GetModule<LogModule>();
	for (int k = 0; k < 01000; ++k)
	for (int i = 0; i < 10; ++i)
	{
		log_module->Debug(i, "i= {0}, {1} : 123xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", i, "Debug");
		log_module->Info(i, "i= {0}, {1} : 123xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", i, "Info");
		log_module->Warn(i, "i= {0}, {1} : 123xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", i, "Warn");
		log_module->Error(i, "i= {0}, {1} : 123xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", i, "Error");
		log_module->Log((ELogLevel)3, i, "i= {0}, {1} : 123xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", i, "Error");
		log_module->Record((ELogLevel)3, i, "i= {0}, {Record} : 123xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	}

	return ret ? EModuleRetCode_Succ : EModuleRetCode_Failed;
}

EModuleRetCode ConfigModule::Awake()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode ConfigModule::Update()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode ConfigModule::Release()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode ConfigModule::Destroy()
{
	return EModuleRetCode_Succ;
}
