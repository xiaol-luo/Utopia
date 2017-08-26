#include "GameLogicModule.h"
#include "CsvConfigSets.h"
#include "ModuleDef/ModuleMgr.h"
#include "CommonModules/Log/LogModule.h"
#include "CommonModules/Timer/ITimerModule.h"
#include "CommonModules/Network/INetworkModule.h"
#include "Player/PlayerMgr.h"
#include "ModuleDef/IModule.h"
#include "Network/Utils/LenCtxStreamParser.h"
#include "Network/Protobuf/msg.pb.h"
#include "Network/Protobuf/test.pb.h"
#include "Network/Utils/NetworkAgent.h"

GameLogicModule::GameLogicModule(ModuleMgr *module_mgr) : IGameLogicModule(module_mgr)
{
	m_csv_cfg_sets = new Config::CsvConfigSets();
	m_player_mgr = new GameLogic::PlayerMgr(this);
}

GameLogicModule::~GameLogicModule()
{
	delete m_csv_cfg_sets;
	m_test_timer = nullptr;
	m_test_listen_handler = nullptr;
	while (!m_test_cnn_handlers.empty())
		m_test_cnn_handlers.pop();

	if (nullptr != m_player_mgr)
	{
		delete m_player_mgr;
		m_player_mgr = nullptr;
	}
}

EModuleRetCode GameLogicModule::Init(void *param)
{
	WaitModuleState(EMoudleName_TIMER, EModuleState_Inited, false);
	WaitModuleState(EMoudleName_Log, EModuleState_Inited, false);
	WaitModuleState(EMoudleName_Network, EModuleState_Inited, false);

	m_log_module = m_module_mgr->GetModule<LogModule>();
	m_network_module = m_module_mgr->GetModule<INetworkModule>();
	m_timer_module = m_module_mgr->GetModule<ITimerModule>();

	this->InitClientMsgHandlerDescript();
	m_network_agent = new NetworkAgent(m_network_module);

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
	NetConnectHanderTest() : INetConnectHander(), parser(102400)
	{
	}
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
		uint32_t test_int = 0;
		char *test_data = nullptr;
		parser.AppendBuffer(data, len);
		while (parser.ParseNext())
		{
			test_int = parser.ContentLen();
			test_data = parser.Content();
		}
	}

	NetListenHanderTest *m_listen_handler = nullptr;
	LenCtxStreamParser parser;
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
	//net_module->Listen("0.0.0.0", 10240, nullptr, m_test_listen_handler);

	m_player_mgr->Awake("0.0.0.0", 10240);
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
			net_module->Close(m_test_cnn_handlers.front()->GetNetId());
			m_test_cnn_handlers.pop();
				
			char buff[Net::PROTOCOL_MAX_SIZE];
			Ping ping;
			ping.set_msgid(1);
			Pong pong;
			pong.set_msgid(2);

			for (int i = 0; i < 100; ++i)
			{
				std::shared_ptr<NetConnectHanderTest> handler = m_test_cnn_handlers.front();
				m_test_cnn_handlers.pop();
				m_test_cnn_handlers.push(handler);

				{
					char *p = buff;
					*(int32_t *)buff = ping.ByteSizeLong() + sizeof(int);
					p += sizeof(uint32_t);
					*(int *)p = ping.msgid();
					p += sizeof(int);
					ping.SerializeToArray(p, ping.ByteSizeLong());
					uint32_t send_len = ping.ByteSizeLong() + p - buff;
					net_module->Send(handler->GetNetId(), buff, send_len);
				}

				{
					char *p = buff;
					*(int32_t *)buff = pong.ByteSizeLong() + sizeof(int);
					p += sizeof(uint32_t);
					*(int *)p = pong.msgid();
					p += sizeof(int);
					pong.SerializeToArray(p, pong.ByteSizeLong());
					uint32_t send_len = pong.ByteSizeLong() + p - buff;
					*(int32_t *)buff = send_len - sizeof(uint32_t);
					net_module->Send(handler->GetNetId(), buff, send_len);
				}
			}
		}
	}

	m_player_mgr->Update(m_timer_module->NowMs());

	return EModuleRetCode_Succ;
}

EModuleRetCode GameLogicModule::Release()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode GameLogicModule::Destroy()
{
	this->UnInitClientMsgHandlerDescript();
	if (nullptr != m_network_agent)
	{
		delete m_network_agent;
		m_network_agent = nullptr;
	}
	return EModuleRetCode_Succ;
}
