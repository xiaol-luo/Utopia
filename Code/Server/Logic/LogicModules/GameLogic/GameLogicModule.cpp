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
#include "GameLogic/Network/GamePlayerMsgDefine.h"

GameLogicModule::GameLogicModule(ModuleMgr *module_mgr) : IGameLogicModule(module_mgr)
{
	m_csv_cfg_sets = new Config::CsvConfigSets();
	m_player_mgr = new GameLogic::PlayerMgr(this);
}

GameLogicModule::~GameLogicModule()
{
	delete m_csv_cfg_sets;
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

EModuleRetCode GameLogicModule::Awake()
{
	WaitModuleState(EMoudleName_Network, EModuleState_Awaked, false);

	bool ret = m_player_mgr->Awake("0.0.0.0", 10240);
	return ret ? EModuleRetCode_Succ : EModuleRetCode_Failed;
}

EModuleRetCode GameLogicModule::Update()
{
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

	m_log_module = nullptr;
	m_timer_module = nullptr;
	m_network_module = nullptr;
	return EModuleRetCode_Succ;
}