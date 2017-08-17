#include "TimerModule.h"
#include <chrono>

TimerModule::TimerModule(std::shared_ptr<ModuleMgr> module_mgr) : ITimerModule(module_mgr)
{
	m_rbtree_sentinel_node = new srv_rbtree_node_t;
	m_rbtree_timer_items = new srv_rbtree_t;
}

TimerModule::~TimerModule()
{
	delete m_rbtree_sentinel_node; m_rbtree_sentinel_node = nullptr;
	delete m_rbtree_timer_items; m_rbtree_timer_items = nullptr;
}

long long GetNowMs()
{
	std::chrono::high_resolution_clock::time_point tp = std::chrono::high_resolution_clock::now();
	long long now = std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch()).count();
	return now;
}

EModuleRetCode TimerModule::Init(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode TimerModule::Awake()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode TimerModule::Update()
{
	return EModuleRetCode_Pending;
}

EModuleRetCode TimerModule::Release()
{
	return EModuleRetCode_Succ;
}

EModuleRetCode TimerModule::Destroy()
{
	return EModuleRetCode_Succ;
}

long long TimerModule::TimerModule::NowSec()
{
	return 0;
}

long long TimerModule::NowMs()
{
	return 0;
}

long long TimerModule::DeltaMs()
{
	return 0;
}

long long TimerModule::Add(std::weak_ptr<ObjectBase> who, TimerAction action, long start_ts_ms, long long execute_span_ms, long long execute_times)
{
	return 0;
}

long long TimerModule::AddNext(std::weak_ptr<ObjectBase> who, TimerAction action, long long start_ts_ms)
{
	return 0;
}

long long TimerModule::AddFirm(std::weak_ptr<ObjectBase> who, TimerAction action, long long execute_span_ms, long long execute_times)
{
	return 0;
}

void TimerModule::Remove(long long timer_id)
{

}

