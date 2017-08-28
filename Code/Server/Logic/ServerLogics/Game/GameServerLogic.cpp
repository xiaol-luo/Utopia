#include "GameServerLogic.h"
#include <memory>
#include <vector>
#include <string>
#include "CommonModules/Log/LogModule.h"
#include "CommonModules/Timer/TimerModule.h"
#include "CommonModules/Network/Impl/NetworkModule.h"
#include "LogicModules/GameLogic/GameLogicModule.h"
#include "Common/Utils/GlobalMemoryMgr.h"

GameServerLogic::GameServerLogic() : ServerLogic()
{

}

GameServerLogic::~GameServerLogic()
{

}

void GameServerLogic::SetInitParams(void *params)
{
	std::vector<std::string> strs = *(std::vector<std::string> *)params;
	std::string *log_param = new std::string(strs[0]);
	std::string *cfg_param = new std::string(strs[1]);

	m_init_params[EMoudleName_Log] = log_param;
	m_init_params[EMoudleName_GameLogic] = cfg_param;
}

void GameServerLogic::ClearInitParams()
{
	if (nullptr != m_init_params[EMoudleName_Log])
	{
		delete (std::string *)m_init_params[EMoudleName_Log];
		m_init_params[EMoudleName_Log] = nullptr;
	}
	if (nullptr != m_init_params[EMoudleName_GameLogic])
	{
		delete (std::string *)m_init_params[EMoudleName_GameLogic];
		m_init_params[EMoudleName_GameLogic] = nullptr;
	}
}

void GameServerLogic::SetupModules()
{
	m_module_mgr->SetModule(new LogModule(m_module_mgr));
	m_module_mgr->SetModule(new GameLogicModule(m_module_mgr));
	m_module_mgr->SetModule(new TimerModule(m_module_mgr));
	m_module_mgr->SetModule(new NetworkModule(m_module_mgr));
}
