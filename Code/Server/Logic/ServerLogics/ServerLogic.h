#pragma once

#include "Modules/ModuleMgr.h"

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
protected:
	virtual void SetupModules() = 0;
	virtual void ClearInitParams() = 0;
	bool Init();
	bool Awake();
	void Update();
	void Realse();
	void Destroy();

	EServerLogicState m_state = EServerLogicState_Free;
	std::shared_ptr<ModuleMgr> m_module_mgr = nullptr;
	int m_loop_span_ms = 100;
	void * m_init_params[EMoudleName_Max];
};
