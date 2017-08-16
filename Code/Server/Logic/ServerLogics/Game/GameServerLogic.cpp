#include "GameServerLogic.h"
#include "Modules/Log/LogModule.h"
#include "Modules/Config/ConfigModule.h"
#include <memory>
#include <vector>
#include <string>

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
	m_init_params[EMoudleName_Config] = cfg_param;
}

void GameServerLogic::ClearInitParams()
{
	if (nullptr != m_init_params[EMoudleName_Log])
	{
		delete m_init_params[EMoudleName_Log];
		m_init_params[EMoudleName_Log] = nullptr;
	}
	if (nullptr != m_init_params[EMoudleName_Config])
	{
		delete m_init_params[EMoudleName_Config];
		m_init_params[EMoudleName_Config] = nullptr;
	}
}

void GameServerLogic::SetupModules()
{
	m_module_mgr->SetModule(std::make_shared<LogModule>(m_module_mgr));
	m_module_mgr->SetModule(std::make_shared<ConfigModule>(m_module_mgr));
}
