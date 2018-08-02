#pragma once

#include <memory>
#include "ObjectBase.h"

class ModuleMgr;

enum EMoudleName
{
	EMoudleName_Invalid,
	EMoudleName_TIMER,
	EMoudleName_Log,
	EMoudleName_Network,
	EModuleName_Event,
	EMoudleName_GameLogic,
	EMoudleName_Max,
};

enum EModuleState
{
	EModuleState_Free,
	EModuleState_Initing,
	EModuleState_Inited,
	EModuleState_Awaking,
	EModuleState_Awaked,
	EModuleState_Updating,
	EModuleState_Quiting,
	EModuleState_Quited,
	EModuleState_Destroying,
	EModuleState_Destroyed,
	EModuleState_Error,
	EModuleState_Max,
};

enum EModuleRetCode
{
	EModuleRetCode_Succ,
	EModuleRetCode_Pending,
	EModuleRetCode_Failed,
	EModuleRetCode_Max,
};

class IModule : public ObjectBase
{
	friend class ModuleMgr;
public:
	IModule(ModuleMgr *module_mgr, EMoudleName module_name) 
	{ 
		m_module_mgr = module_mgr;  
		m_module_name = module_name; 
	}
	virtual ~IModule() {}

	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake() = 0;
	virtual EModuleRetCode Update() = 0;
	virtual EModuleRetCode Release() = 0;
	virtual EModuleRetCode Destroy() = 0;
	EMoudleName ModuleName() { return m_module_name; }
	EModuleState GetState() { return m_state; }

protected:
	EMoudleName m_module_name = EMoudleName_Invalid;
	ModuleMgr *m_module_mgr = nullptr;
	EModuleState m_state = EModuleState_Free;
	void SetState(EModuleState state) { m_state = state; }
};

#define WaitModuleState(module_name, wait_state, tolerate_nullptr) do				\
{																					\
	auto module = m_module_mgr->GetModule(module_name);							\
	if (nullptr == module && !tolerate_nullptr)										\
		return EModuleRetCode_Failed;												\
	if (nullptr != module && EModuleState_Error == module->GetState())				\
		return EModuleRetCode_Failed;												\
	if (nullptr != module && wait_state != module->GetState())						\
		return EModuleRetCode_Pending;												\
} while(false)
