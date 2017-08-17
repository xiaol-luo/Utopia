#pragma once

#include "Modules/IModule.h"
#include <memory>

using TimerAction = void(*)();

class ITimerModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EMoudleName_TIMER;
	ITimerModule(std::shared_ptr<ModuleMgr> module_mgr) : IModule(module_mgr, MODULE_NAME) {}
	virtual ~ITimerModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake() = 0;
	virtual EModuleRetCode Update() = 0;
	virtual EModuleRetCode Release() = 0;
	virtual EModuleRetCode Destroy() = 0;

	static const int MS_PER_SEC = 1000;
	static const long EXECUTE_UNLIMIT_TIMES = -1;
	virtual long long NowSec() = 0;
	virtual long long NowMs() = 0;
	virtual long long DeltaMs() = 0;

	virtual long long Add(std::weak_ptr<ObjectBase> who, TimerAction action, long start_ts_ms, long long execute_span_ms, long long execute_times) = 0;
	virtual long long AddNext(std::weak_ptr<ObjectBase> who, TimerAction action, long long start_ts_ms) = 0;
	virtual long long AddFirm(std::weak_ptr<ObjectBase> who, TimerAction action, long long execute_span_ms, long long execute_times) = 0;
	virtual void Remove(long long timer_id) = 0;
};
