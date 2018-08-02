#include "ServerLogic.h"
#include <thread>
#include <chrono>
#include <ctime>
#include "CommonModules/Timer/ITimerModule.h"
#include "CommonModules/Log/LogModule.h"
#include "CommonModules/Network/INetworkModule.h"
#include "Network/Utils/NetworkAgent.h"
#include "Common/Macro/AllMacro.h"

ServerLogic *server_logic = nullptr;
const int TRY_MAX_TIMES = 100000;

ServerLogic::ServerLogic()
{
	m_module_mgr = new ModuleMgr(this);
	memset(m_init_params, 0, sizeof(m_init_params));
}

ServerLogic::~ServerLogic()
{
	delete m_module_mgr;
	m_module_mgr = nullptr;
}

bool ServerLogic::Init()
{
	if (EServerLogicState_Free != m_state)
		return false;

	this->SetupModules();

	m_state = EServerLogicState_Init;
	int loop_times = 0;
	EModuleRetCode retCode = EModuleRetCode_Succ;
	do
	{
		if (loop_times > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(m_loop_span_ms));
		retCode = m_module_mgr->Init(m_init_params);
	} while (EModuleRetCode_Pending == retCode && loop_times++ < TRY_MAX_TIMES);

	bool ret = EModuleRetCode_Succ == retCode;
	if (!ret)
	{
		this->Quit();
	}
	else
	{
		m_network_agent = new NetworkAgent(this->GetNet());
		m_ev_proxy = this->GetEvent()->CreateProxy();
	}
	return ret;
}

bool ServerLogic::Awake()
{
	if (EServerLogicState_Init != m_state)
		return false;

	m_state = EServerLogicState_Awake;
	int loop_times = 0;
	EModuleRetCode retCode = EModuleRetCode_Succ;
	do
	{
		if (loop_times > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(m_loop_span_ms));
		retCode = m_module_mgr->Awake();
	} while (EModuleRetCode_Pending == retCode && loop_times++ < TRY_MAX_TIMES);

	bool ret = EModuleRetCode_Succ == retCode;
	if (!ret) this->Quit();
	return ret;
}

void ServerLogic::Update()
{
	if (EServerLogicState_Awake != m_state)
		return;

	m_state = EServerLogicState_Update;
	int loop_times = 0;
	EModuleRetCode retCode = EModuleRetCode_Succ;
	do
	{
		retCode = m_module_mgr->Update();
		if (EModuleRetCode_Failed == retCode)
			this->Quit();

		ITimerModule *timer_module = m_module_mgr->GetModule<ITimerModule>();
		long long consume_ms = timer_module->RealNowMs() - timer_module->NowMs();
		// GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT, "ServerLogic consume time {0} ms", consume_ms);
		long long sleep_time = m_loop_span_ms - consume_ms;
		if (sleep_time > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	} while (EServerLogicState_Update == m_state );
}

void ServerLogic::Realse()
{
	m_state = EServerLogicState_Release;
	int loop_times = 0;
	EModuleRetCode retCode = EModuleRetCode_Succ;
	do
	{
		if (loop_times > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(m_loop_span_ms));
		retCode = m_module_mgr->Realse();
	} while (EModuleRetCode_Pending == retCode && loop_times++ < TRY_MAX_TIMES);
}

void ServerLogic::Destroy()
{
	m_state = EServerLogicState_Destroy;
	int loop_times = 0;
	EModuleRetCode retCode = EModuleRetCode_Succ;
	do
	{
		if (loop_times > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(m_loop_span_ms));
		retCode = m_module_mgr->Destroy();
	} while (EModuleRetCode_Pending == retCode && loop_times++ < TRY_MAX_TIMES);

	if (nullptr != m_network_agent)
	{
		delete m_network_agent;
		m_network_agent = nullptr;
	}
	if (nullptr != m_ev_proxy)
	{
		delete m_ev_proxy;
		m_ev_proxy = nullptr;
	}
	this->ClearInitParams();
}

void ServerLogic::Loop()
{
	bool ret = true;
	ret = ret && this->Init();
	ret = ret && this->Awake();
	this->Update();
	this->Realse();
	this->Destroy();
	m_state = EServerLogicState_Max;
}

void ServerLogic::Quit()
{
	if (m_state <= EServerLogicState_Update)
	{
		m_state = EServerLogicState_Release;
	}
}

INetworkModule * ServerLogic::GetNet()
{
	return m_module_mgr->GetModule<INetworkModule>();
}

ITimerModule * ServerLogic::GetTimer()
{
	return m_module_mgr->GetModule<ITimerModule>();
}

LogModule * ServerLogic::GetLog()
{
	return m_module_mgr->GetModule<LogModule>();
}

EventModule * ServerLogic::GetEvent()
{
	return m_module_mgr->GetModule<EventModule>();
}
