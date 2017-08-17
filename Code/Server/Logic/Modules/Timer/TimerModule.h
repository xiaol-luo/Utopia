#pragma once

#include "ITimerModule.h"
#include "DataStructure/RBTree/srv_rbtree.h"

class TimerModule : public ITimerModule
{
public:
	TimerModule(std::shared_ptr<ModuleMgr> module_mgr);
	virtual ~TimerModule();
	virtual EModuleRetCode Init(void *param);
	virtual EModuleRetCode Awake();
	virtual EModuleRetCode Update();
	virtual EModuleRetCode Release();
	virtual EModuleRetCode Destroy();

	virtual long long NowSec();
	virtual long long NowMs();
	virtual long long DeltaMs();
	virtual long long Add(std::weak_ptr<ObjectBase> who, TimerAction action, long start_ts_ms, long long execute_span_ms, long long execute_times);
	virtual long long AddNext(std::weak_ptr<ObjectBase> who, TimerAction action, long long start_ts_ms);
	virtual long long AddFirm(std::weak_ptr<ObjectBase> who, TimerAction action, long long execute_span_ms, long long execute_times);
	virtual void Remove(long long timer_id);

private:
	struct TimerItem
	{
		bool is_firm;
		bool execute_ms;
		bool span_ms;
		bool execute_times;
		std::weak_ptr<ObjectBase> who;
		TimerAction action;
	};

	srv_rbtree_node_t *m_rbtree_sentinel_node;
	srv_rbtree_t *m_rbtree_timer_items;

	long long m_now_ms = 0;
	long long m_delta_ms = 0;


};