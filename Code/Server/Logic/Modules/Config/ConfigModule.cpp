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
	delete m_csv_cfg_sets;
	m_test_timer = nullptr;
	m_test_listen_handler = nullptr;
	while (!m_test_cnn_handlers.empty())
		m_test_cnn_handlers.pop();
}

EModuleRetCode ConfigModule::Init(void *param)
{
	std::string *file_path = (std::string *)param;
	bool ret = m_csv_cfg_sets->Load(*file_path);
	m_state = ret ? EModuleState_Inited : EModuleState_Error;
	return ret ? EModuleRetCode_Succ : EModuleRetCode_Failed;
}

class NetConnectHanderTest;
class NetListenHanderTest : public INetListenHander
{
public:
	virtual void OnClose(int errnu) {}
	virtual void OnOpen(int errnu) {}
	NetListenHanderTest() : INetListenHander() {}
	virtual ~NetListenHanderTest() 
	{
		handlers.clear();
	}
	virtual std::shared_ptr<INetConnectHander> GenConnectorHandler(NetId netid);
	std::map<NetId, std::shared_ptr<INetConnectHander>> handlers;
};

class NetConnectHanderTest : public INetConnectHander
{
public:
	NetConnectHanderTest() : INetConnectHander() {}
	virtual ~NetConnectHanderTest() 
	{
		m_listen_handler = nullptr;
	}
	virtual void OnClose(int errnu) 
	{
		if (nullptr != m_listen_handler)
			m_listen_handler->handlers.erase(this->GetNetId());
	}
	virtual void OnOpen(int errnu) 
	{
		if (0 != errnu && nullptr != m_listen_handler)
		{
			m_listen_handler->handlers.erase(this->GetNetId());
		}
	}
	virtual void OnRecvData(char *data, uint32_t len) 
	{
		if (len > 2)
		{
			data[len - 2] = '\n';
			data[len - 1] = 0;
			printf("%lld ---- %u \n %s", m_netid, len, data); 
		}
	}
	NetListenHanderTest *m_listen_handler = nullptr;
};

std::shared_ptr<INetConnectHander> NetListenHanderTest::GenConnectorHandler(NetId netid)
{
	std::shared_ptr<NetConnectHanderTest> handler = std::make_shared<NetConnectHanderTest>();
	handler->SetNetId(netid);
	handler->m_listen_handler = this;
	handlers[netid] = handler;
	return handler;
}

EModuleRetCode ConfigModule::Awake()
{
	WaitModuleState(EMoudleName_Network, EModuleState_Awaked, false);

	m_test_timer = std::make_shared<ObjectBase>();
	m_test_listen_handler = std::make_shared<NetListenHanderTest>();
	std::shared_ptr<INetworkModule> net_module = m_module_mgr->GetModule<INetworkModule>();
	net_module->Listen("0.0.0.0", 10240, nullptr, m_test_listen_handler);
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
		std::shared_ptr<LogModule> log_module = m_module_mgr->GetModule<LogModule>();

		if (m_test_cnn_handlers.size() < 200)
		{
			std::shared_ptr<NetConnectHanderTest> handler = nullptr;
			// handler = std::make_shared<NetConnectHanderTest>();
			// m_test_cnn_handlers.push(handler);
			// net_module->Connect("127.0.0.1", 10240, nullptr, handler);
			for (int i = 0; i < 20; ++i)
			{
				handler = std::make_shared<NetConnectHanderTest>();
				m_test_cnn_handlers.push(handler);
				net_module->ConnectAsync("127.0.0.1", 10240, nullptr, handler);
			}
		}
		else
		{
			for (int i = 0; i < 200; ++i)
			{
				std::shared_ptr<NetConnectHanderTest> handler = m_test_cnn_handlers.front();
				m_test_cnn_handlers.pop();
				m_test_cnn_handlers.push(handler);
				char *tmp = "hello world  \n ";
				net_module->Send(handler->GetNetId(), tmp, strlen(tmp));
				log_module->Debug(3, tmp);
			}
		}
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
