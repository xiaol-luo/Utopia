#include "TimerUtil.h"

ITimerModule *TimerUtil::module = nullptr;

bool TimerUtil::Init(ITimerModule * _module)
{
	if (nullptr != module)
		return false;

	module = _module;
	return nullptr != module;
}

long long TimerUtil::NowSec()
{
	return module->NowSec();
}

long long TimerUtil::NowMs()
{
	return module->NowMs();
}

long long TimerUtil::DeltaMs()
{
	return module->DeltaMs();
}

long long TimerUtil::RealNowMs()
{
	return module->RealNowMs();
}

long long TimerUtil::Add(TimerAction action, long start_ts_ms, long long execute_span_ms, long long execute_times)
{
	return module->Add(action, start_ts_ms, execute_span_ms, execute_times);
}

long long TimerUtil::AddNext(TimerAction action, long long start_ts_ms)
{
	return module->AddNext(action, start_ts_ms);
}

long long TimerUtil::AddFirm(TimerAction action, long long execute_span_ms, long long execute_times)
{
	return module->AddFirm(action, execute_span_ms, execute_times);
}

void TimerUtil::Remove(long long timer_id)
{
	module->Remove(timer_id);
}
