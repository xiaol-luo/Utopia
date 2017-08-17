#pragma once

#include "IConfigModule.h"

namespace Config
{
	struct CsvConfigSets;
}

class ConfigModule : public IConfigModule
{
public:
	ConfigModule(std::shared_ptr<ModuleMgr> module_mgr);
	virtual ~ConfigModule();
	virtual EModuleRetCode Init(void *param);
	virtual EModuleRetCode Awake();
	virtual EModuleRetCode Update();
	virtual EModuleRetCode Release();
	virtual EModuleRetCode Destroy();
	virtual void * GetCfg() { return m_csv_cfg_sets; }

private:
	Config::CsvConfigSets *m_csv_cfg_sets = nullptr;

	std::shared_ptr<ObjectBase> m_test_timer;
};