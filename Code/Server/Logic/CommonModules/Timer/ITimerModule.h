#pragma once

#include "ModuleDef/IModule.h"
#include <memory>
#include <functional>

using TimerAction = std::function<void(void)>;

class ITimerModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EMoudleName_TIMER;
	ITimerModule(ModuleMgr *module_mgr) : IModule(module_mgr, MODULE_NAME) {}
	virtual ~ITimerModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake() = 0;
	virtual EModuleRetCode Update() = 0;
	virtual EModuleRetCode Release() = 0;
	virtual EModuleRetCode Destroy() = 0;

	static const int MS_PER_SEC = 1000;
	static const long long EXECUTE_UNLIMIT_TIMES = -1;
	static const long long INVALID_TIMER_ID = 0;
	virtual long long NowSec() = 0;
	virtual long long NowMs() = 0;
	virtual long long DeltaMs() = 0;
	virtual long long RealNowMs() = 0;

	virtual long long Add(TimerAction action, long start_ts_ms, long long execute_span_ms, long long execute_times) = 0;
	virtual long long AddNext(TimerAction action, long long start_ts_ms) = 0;
	virtual long long AddFirm(TimerAction action, long long execute_span_ms, long long execute_times) = 0;
	virtual void Remove(long long timer_id) = 0;
};
