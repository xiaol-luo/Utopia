#include "ConfigModule.h"
#include "CsvConfigSets.h"
#include "Modules/ModuleMgr.h"
#include "Modules/Log/LogModule.h"
#include "Modules/Timer/ITimerModule.h"
#include "Modules/Network/INetworkModule.h"

ConfigModule::ConfigModule(std::shared_ptr<ModuleMgr> module_mgr) : IConfigModule(module_mgr)
{
	m_csv_cfg_sets = new Config::CsvConfigSets();
}

ConfigModule::~ConfigModule()
{

}

EModuleRetCode ConfigModule::Init(void *param)
{
	WaitModuleState(EMoudleName_Log, EModuleState_Inited, false);

	std::string *file_path = (std::string *)param;
	bool ret = m_csv_cfg_sets->Load(*file_path);
	m_state = ret ? EModuleState_Inited : EModuleState_Error;

	std::shared_ptr<LogModule> log_module = m_module_mgr->GetModule<LogModule>();
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
/*
class NetConnectHanderTest : public INetConnectHander
{
public:
	virtual void OnError(NetId netid, int errnu) {}
	virtual void OnSucc(NetId netid) {}
	virtual void OnClose(NetId netid) {}
	virtual void OnRecvData(NetId netid, char *data, uint32_t len) {}
};

class NetListenHanderTest : public INetListenHander
{
public:
	virtual void OnError(NetId netid, int errnu) {}
	virtual void OnSucc(NetId netid) {}
	virtual void OnClose(NetId netid) {}
	virtual void OnNewConnect(NetId netid) 
	{

	}

	virtual std::shared_ptr<INetConnectHander>  GenConnectorHandler(NetId netid)
	{
		return std::make_shared<NetConnectHanderTest>();
	}
};
*/

EModuleRetCode ConfigModule::Awake()
{
	WaitModuleState(EMoudleName_Network, EModuleState_Awaked, false);

	m_test_timer = std::make_shared<ObjectBase>();
	// m_test_listen_handler = std::make_shared<NetListenHanderTest>();
	// m_test_cnn_handler = std::make_shared<NetConnectHanderTest>();
	std::shared_ptr<INetworkModule> net_module = m_module_mgr->GetModule<INetworkModule>();
	// net_module->Listen("0.0.0.0", 10240, nullptr, m_test_listen_handler);
	return EModuleRetCode_Succ;
}

EModuleRetCode ConfigModule::Update()
{
	std::shared_ptr<ITimerModule> timer_module = m_module_mgr->GetModule<ITimerModule>();
	// timer_module->AddNext(TestTimer, 0);
	for (int i = 0; i < 1; ++ i)
	{
		// timer_module->AddFirm([this]() { for (int i = 0; i < 1000; ++i); }, 100 * 1, -1);
		// timer_module->AddFirm([this]() { m_module_mgr->GetModule<LogModule>()->Info(7, "TestTimer"); }, 1000 * 1, -1);
		// timer_module->AddNext([this]() { m_module_mgr->GetModule<LogModule>()->Info(7, "TestTimer"); }, 0);
	}

	{
		std::shared_ptr<INetworkModule> net_module = m_module_mgr->GetModule<INetworkModule>();
		// net_module->Connect("127.0.0.1", 10240, nullptr, m_test_cnn_handler);
	}
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
