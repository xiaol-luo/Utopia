#include "EventModule.h"

EventModule::EventModule(ModuleMgr * module_mgr) 
	: IModule(module_mgr, EventModule::MODULE_NAME)
{
	m_ev_dispacher = new EventDispacher();
}

EventModule::~EventModule()
{
	delete m_ev_dispacher; m_ev_dispacher = nullptr;
}

EModuleRetCode EventModule::Init(void * param)
{
	return EModuleRetCode::EModuleRetCode_Succ;
}

EModuleRetCode EventModule::Awake()
{
	return EModuleRetCode::EModuleRetCode_Succ;
}

EModuleRetCode EventModule::Update()
{
	return EModuleRetCode::EModuleRetCode_Succ;
}

EModuleRetCode EventModule::Release()
{
	return EModuleRetCode::EModuleRetCode_Succ;
}

EModuleRetCode EventModule::Destroy()
{
	return EModuleRetCode::EModuleRetCode_Succ;
}

EventDispacherProxy * EventModule::CreateProxy()
{
	EventDispacherProxy * ret = nullptr;
	if (nullptr != m_ev_dispacher)
	{
		ret = new EventDispacherProxy(m_ev_dispacher);
	}
	return ret;
}
