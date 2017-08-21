#pragma once

#include "IConfigModule.h"
#include <vector>
#include <queue>

namespace Config
{
	struct CsvConfigSets;
}
class NetListenHanderTest;
class NetConnectHanderTest;

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

	std::shared_ptr<ObjectBase> m_test_timer = nullptr;
	std::shared_ptr<NetListenHanderTest> m_test_listen_handler = nullptr;
	std::queue<std::shared_ptr<NetConnectHanderTest>> m_test_cnn_handlers;
};