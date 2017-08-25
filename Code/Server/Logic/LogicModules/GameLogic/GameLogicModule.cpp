#include "GameLogicModule.h"
#include "CsvConfigSets.h"
#include "ModuleDef/ModuleMgr.h"
#include "CommonModules/Log/LogModule.h"
#include "CommonModules/Timer/ITimerModule.h"
#include "CommonModules/Network/INetworkModule.h"
#include "Network/Utils/NetProtocolParser.h"
#include "Player/PlayerMgr.h"
#include "ModuleDef/IModule.h"

GameLogicModule::GameLogicModule(ModuleMgr *module_mgr) : IGameLogicModule(module_mgr)
{
	m_csv_cfg_sets = new Config::CsvConfigSets();
	m_player_mgr = new GameLogic::PlayerMgr(this);

	this->InitClientMsgHandlerDescript();
}

GameLogicModule::~GameLogicModule()
{
	delete m_csv_cfg_sets;
	m_test_timer = nullptr;
	m_test_listen_handler = nullptr;
	while (!m_test_cnn_handlers.empty())
		m_test_cnn_handlers.pop();
}

EModuleRetCode GameLogicModule::Init(void *param)
{
	WaitModuleState(EMoudleName_TIMER, EModuleState_Inited, false);
	WaitModuleState(EMoudleName_Log, EModuleState_Inited, false);
	WaitModuleState(EMoudleName_Network, EModuleState_Inited, false);

	m_log_module = m_module_mgr->GetModule<LogModule>();
	m_network_module = m_module_mgr->GetModule<INetworkModule>();
	m_timer_module = m_module_mgr->GetModule<ITimerModule>();

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

static char NetConnectHanderTestBuffer[302400];

class NetConnectHanderTest : public INetConnectHander
{
public:
	NetConnectHanderTest() : INetConnectHander(), parser(nullptr)
	{
		parser = new NetProtocolParser(NetConnectHanderTestBuffer, sizeof(NetConnectHanderTestBuffer));
	}
	virtual ~NetConnectHanderTest() 
	{
		m_listen_handler = nullptr;
		delete(parser);
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
		uint32_t test_int = 0;
		char *test_data = nullptr;
		parser->AppendBuffer(data, len);
		while (parser->ParseNext())
		{
			test_int = parser->ContentLen();
			test_data = parser->Content();
		}
	}

	NetListenHanderTest *m_listen_handler = nullptr;
	NetProtocolParser *parser = nullptr;
};

std::shared_ptr<INetConnectHander> NetListenHanderTest::GenConnectorHandler(NetId netid)
{
	std::shared_ptr<NetConnectHanderTest> handler = std::make_shared<NetConnectHanderTest>();
	handler->SetNetId(netid);
	handler->m_listen_handler = this;
	handlers[netid] = handler;
	return handler;
}

EModuleRetCode GameLogicModule::Awake()
{
	WaitModuleState(EMoudleName_Network, EModuleState_Awaked, false);

	m_test_timer = std::make_shared<ObjectBase>();
	m_test_listen_handler = std::make_shared<NetListenHanderTest>();
	auto net_module = m_module_mgr->GetModule<INetworkModule>();
	net_module->Listen("0.0.0.0", 10240, nullptr, m_test_listen_handler);
	return EModuleRetCode_Succ;
}

EModuleRetCode GameLogicModule::Update()
{
	auto timer_module = m_module_mgr->GetModule<ITimerModule>();
	// timer_module->AddNext(TestTimer, 0);
	for (int i = 0; i < 1; ++ i)
	{
		// timer_module->AddFirm([this]() { for (int i = 0; i < 1000; ++i); }, 100 * 1, -1);
		// timer_module->AddFirm([this]() { m_module_mgr->GetModule<LogModule>()->Info(7, "TestTimer"); }, 1000 * 1, -1);
		// timer_module->AddNext([this]() { m_module_mgr->GetModule<LogModule>()->Info(7, "TestTimer"); }, 0);
	}

	{
		auto net_module = m_module_mgr->GetModule<INetworkModule>();
		auto log_module = m_module_mgr->GetModule<LogModule>();

		if (m_test_cnn_handlers.size() < 100)
		{
			std::shared_ptr<NetConnectHanderTest> handler = nullptr;
			// handler = std::make_shared<NetConnectHanderTest>();
			// m_test_cnn_handlers.push(handler);
			// net_module->Connect("127.0.0.1", 10240, nullptr, handler);
			for (int i = 0; i < 10; ++i)
			{
				handler = std::make_shared<NetConnectHanderTest>();
				m_test_cnn_handlers.push(handler);
				net_module->ConnectAsync("127.0.0.1", 10240, nullptr, handler);
			}
		}
		else
		{
			char buff[Net::PROTOCOL_MAX_SIZE];

			sprintf(buff + sizeof(uint32_t), " say %s", "hello world !");

			for (int i = 0; i < 100; ++i)
			{
				std::shared_ptr<NetConnectHanderTest> handler = m_test_cnn_handlers.front();
				m_test_cnn_handlers.pop();
				m_test_cnn_handlers.push(handler);
				uint32_t len = 1 + std::rand() % (sizeof(buff) - sizeof(uint32_t));
				// len = 3;
				*(uint32_t *)buff = len;
				net_module->Send(handler->GetNetId(), buff, len + sizeof(uint32_t));

				continue;

				uint32_t total_len = len + sizeof(uint32_t);
				uint32_t sended_len = 0;
				while (total_len - sended_len > 0)
				{
					uint32_t randVal = 1 + std::rand() % (total_len - sended_len + 1);
					// randVal = 3;
					if (sended_len + randVal > total_len)
						randVal = total_len - sended_len;
					handler->parser->AppendBuffer(buff + sended_len, randVal);
					while (handler->parser->ParseNext());
					sended_len += randVal;
				}
			}
		}
	}

	this->TestClientMsgHandler();

	return EModuleRetCode_Succ;
}

EModuleRetCode GameLogicModule::Release()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode GameLogicModule::Destroy()
{
	this->UnInitClientMsgHandlerDescript();
	return EModuleRetCode_Succ;
}
