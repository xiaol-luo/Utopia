#include "Game.h"
#include "Modules/Log/LogModule.h"
#include "Modules/Config/ConfigModule.h"
#include <thread>
#include <chrono>
#include <ctime>

const int TRY_MAX_TIMES = 100000;

Game::Game()
{
	m_module_mgr = std::make_shared<ModuleMgr>();
}

Game::~Game()
{

}

bool Game::Init(void *param)
{
	if (EGameState_Free != m_game_state)
		return false;

	m_module_mgr->SetModule(std::make_shared<LogModule>(m_module_mgr));
	m_module_mgr->SetModule(std::make_shared<ConfigModule>(m_module_mgr));
	
	m_game_state = EGameState_Init;
	int loop_times = 0;
	EModuleRetCode retCode = EModuleRetCode_Succ;
	do
	{
		if (loop_times++ > 0)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(m_ms_per_frame));
		}
		retCode = m_module_mgr->Init(param);
	} while (EModuleRetCode_Pending == retCode && loop_times < TRY_MAX_TIMES);

	bool ret = EModuleRetCode_Succ == retCode;
	if (!ret) this->Quit();
	return ret;
}

bool Game::Awake(void *param)
{
	if (EGameState_Init != m_game_state)
		return false;

	m_game_state = EGameState_Awake;
	int loop_times = 0;
	EModuleRetCode retCode = EModuleRetCode_Succ;
	do
	{
		if (loop_times++ > 0)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(m_ms_per_frame));
		}
		retCode = m_module_mgr->Awake(param);
	} while (EModuleRetCode_Pending == retCode && loop_times < TRY_MAX_TIMES);

	bool ret = EModuleRetCode_Succ == retCode;
	if (!ret) this->Quit();
	return ret;
}

void Game::Update(void *param)
{
	if (EGameState_Awake != m_game_state)
		return;

	m_game_state = EGameState_Update;
	int loop_times = 0;
	EModuleRetCode retCode = EModuleRetCode_Succ;
	do
	{
		if (loop_times++ > 0)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(m_ms_per_frame));
		}
		retCode = m_module_mgr->Awake(param);
	} while (EModuleRetCode_Pending != retCode || EGameState_Update != m_game_state );
}

void Game::Realse(void *param)
{
	m_game_state = EGameState_Release;
	int loop_times = 0;
	EModuleRetCode retCode = EModuleRetCode_Succ;
	do
	{
		if (loop_times++ > 0)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(m_ms_per_frame));
		}
		retCode = m_module_mgr->Realse(param);
	} while (EModuleRetCode_Pending == retCode && loop_times < TRY_MAX_TIMES);
}

void Game::Destroy(void *param)
{
	m_game_state = EGameState_Destroy;
	int loop_times = 0;
	EModuleRetCode retCode = EModuleRetCode_Succ;
	do
	{
		if (loop_times++ > 0)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(m_ms_per_frame));
		}
		retCode = m_module_mgr->Destroy(param);
	} while (EModuleRetCode_Pending == retCode && loop_times < TRY_MAX_TIMES);
}

void Game::Loop()
{
	bool ret = true;
	ret = ret && this->Init(nullptr);
	ret = ret && this->Awake(nullptr);
	this->Update(nullptr);
	this->Realse(nullptr);
	this->Destroy(nullptr);
}

void Game::Quit()
{
	if (m_game_state <= EGameState_Update)
	{
		m_game_state = EGameState_Release;
	}
}


