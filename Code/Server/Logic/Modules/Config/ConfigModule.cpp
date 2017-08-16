#include "ConfigModule.h"
#include "CsvConfigSets.h"
#include "Modules/ModuleMgr.h"

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

	WaitModuleState(EMoudleName_Log, EModuleState_Inited);

	std::string *file_path = (std::string *)param;
	bool ret = m_csv_cfg_sets->Load(*file_path);
	m_state = ret ? EModuleState_Inited : EModuleState_Error;
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
