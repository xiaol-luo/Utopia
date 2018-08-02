#pragma once

#include "ModuleDef/ModuleMgr.h"
#include "CommonModules/Event/EventModule.h"
#include "CommonModules/Log/LogModule.h"
#include "CommonModules/Timer/ITimerModule.h"
#include "CommonModules/Network/INetworkModule.h"
#include "ShareCode/Network/Utils/NetworkAgent.h"

enum EServerLogicState
{
	EServerLogicState_Free,
	EServerLogicState_Init,
	EServerLogicState_Awake,
	EServerLogicState_Update,
	EServerLogicState_Release,
	EServerLogicState_Destroy,
	EServerLogicState_Max,
};

class ServerLogic
{
public:
	ServerLogic();
	virtual ~ServerLogic();

	virtual void SetInitParams(void *params) = 0;
	void Loop();
	void Quit();
	EServerLogicState GetState() { return m_state; }
	ModuleMgr * GetModuleMgr() { return m_module_mgr; }

	
	INetworkModule * GetNet();
	ITimerModule * GetTimer();
	LogModule * GetLog();
	EventModule * GetEvent();
	NetworkAgent * GetNetAgent() { return m_network_agent; }

protected:
	virtual void SetupModules() = 0;
	virtual void ClearInitParams() = 0;
	bool Init();
	bool Awake();
	void Update();
	void Realse();
	void Destroy();

	EServerLogicState m_state = EServerLogicState_Free;
	ModuleMgr *m_module_mgr = nullptr;
	int m_loop_span_ms = 100;
	void * m_init_params[EMoudleName_Max];

	NetworkAgent *m_network_agent = nullptr;
	EventDispacherProxy *m_ev_proxy = nullptr;
};

