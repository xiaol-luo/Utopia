#include "ServerLogic.h"
#include <thread>
#include <chrono>
#include <ctime>
#include "CommonModules/Timer/ITimerModule.h"

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

	m_timer_module = m_module_mgr->GetModule<ITimerModule>();

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
	if (!ret) this->Quit();
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

		long long consume_ms = m_timer_module->RealNowMs() - m_timer_module->NowMs();
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

	m_timer_module = nullptr;
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


