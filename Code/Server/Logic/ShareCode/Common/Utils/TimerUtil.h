#pragma once

#include "CommonModules/Timer/ITimerModule.h"

class TimerUtil
{
public:
	static bool Init(ITimerModule *_module);
	static void Destroy() { module = nullptr; }

public:
	static long long NowSec();
	static long long NowMs();
	static long long DeltaMs();
	static long long RealNowMs();

	static long long Add(TimerAction action, long start_ts_ms, long long execute_span_ms, long long execute_times);
	static long long AddNext(TimerAction action, long long start_ts_ms);
	static long long AddFirm(TimerAction action, long long execute_span_ms, long long execute_times);
	static void Remove(long long timer_id);

private:
	static ITimerModule *module;
};