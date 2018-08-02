#pragma once

#include "ModuleDef/IModule.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"

class EventModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EModuleName_Event;
	EventModule(ModuleMgr *module_mgr);
	virtual ~EventModule();
	virtual EModuleRetCode Init(void *param);
	virtual EModuleRetCode Awake();
	virtual EModuleRetCode Update();
	virtual EModuleRetCode Release();
	virtual EModuleRetCode Destroy();
	
	EventDispacherProxy * CreateProxy();

	template <typename... Args>
	void Fire(int id, Args... args)
	{
		m_ev_dispacher->Fire(id, args...);
	}

protected:
	EventDispacher *m_ev_dispacher = nullptr;
};
