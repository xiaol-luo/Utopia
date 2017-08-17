#pragma once

#include "ITimerModule.h"
#include "DataStructure/RBTree/srv_rbtree.h"
#include <vector>
#include <map>

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
	virtual long long Add(std::shared_ptr<ObjectBase> who, TimerAction action, long start_ts_ms, long long execute_span_ms, long long execute_times);
	virtual long long AddNext(std::shared_ptr<ObjectBase> who, TimerAction action, long long start_ts_ms);
	virtual long long AddFirm(std::shared_ptr<ObjectBase> who, TimerAction action, long long execute_span_ms, long long execute_times);
	virtual void Remove(long long timer_id);

private:
	struct TimerItem
	{
		long long id = INVALID_TIMER_ID;
		bool is_firm = false;
		long long execute_ms = 0;
		long long span_ms = 0;
		long long execute_times = 0;
		std::weak_ptr<ObjectBase> who;
		TimerAction action = nullptr;
	};

	srv_rbtree_node_t *m_rbtree_sentinel_node;
	srv_rbtree_t *m_rbtree_timer_items;

	long long m_now_ms = 0;
	long long m_now_sec = 0;
	long long m_delta_ms = 0;
	std::vector<srv_rbtree_node_t *> m_nodes_execute_now;
	void TryExecuteNode(srv_rbtree_node_t *node);

	std::map<long long, srv_rbtree_node_t *> m_id_to_timer_node;
	long long m_last_timer_id = 0;
	long long GenTimerId();
};