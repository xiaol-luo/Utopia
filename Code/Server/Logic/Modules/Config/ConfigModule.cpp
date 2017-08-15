#include "ConfigModule.h"
#include "CsvConfigSets.h"

ConfigModule::ConfigModule(std::shared_ptr<ModuleMgr> module_mgr) : IConfigModule(module_mgr)
{
	m_csv_cfg_sets = new Config::CsvConfigSets();
}

ConfigModule::~ConfigModule()
{

}

EModuleRetCode ConfigModule::Init(void *param)
{
	std::string file_path = "Data/AutoCsvConfig";
	bool ret = m_csv_cfg_sets->Load(file_path);
	return ret ? EModuleRetCode_Succ : EModuleRetCode_Failed;
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
