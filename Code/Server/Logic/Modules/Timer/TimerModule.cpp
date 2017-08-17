#include "TimerModule.h"
#include <chrono>
#include <queue>

long long GetNowMs();
TimerModule::TimerModule(std::shared_ptr<ModuleMgr> module_mgr) : ITimerModule(module_mgr)
{

}

TimerModule::~TimerModule()
{

}

EModuleRetCode TimerModule::Init(void *param)
{
	long long old_ms = m_now_ms;
	m_now_ms = GetNowMs();
	m_now_sec = m_now_ms / 1000;
	m_delta_ms = m_now_ms - old_ms;

	if (EModuleState_Error == m_state)
		return EModuleRetCode_Failed;
	if (EModuleState_Inited == m_state)
		return EModuleRetCode_Succ;

	m_rbtree_sentinel_node = new srv_rbtree_node_t;
	memset(m_rbtree_sentinel_node, 0, sizeof(srv_rbtree_node_t));
	m_rbtree_timer_items = new srv_rbtree_t;
	memset(m_rbtree_timer_items, 0, sizeof(srv_rbtree_t));
	srv_rbtree_init(m_rbtree_timer_items, m_rbtree_sentinel_node, srv_rbtree_insert_value);

	m_state = EModuleState_Inited;
	return EModuleRetCode_Succ;
}

EModuleRetCode TimerModule::Awake()
{
	return EModuleRetCode_Succ;
}

void TimerModule::TryExecuteNode(srv_rbtree_node_t *node)
{
	TimerItem *timer_item = (TimerItem *)node->data;
	if (nullptr == timer_item)
	{
		delete node;
		return;
	}
	if (!timer_item->who.expired())
		timer_item->action();
	if (!timer_item->is_firm)
		--timer_item->execute_times;
	if (!timer_item->who.expired() && (timer_item->is_firm || timer_item->execute_times > 0))
	{
		timer_item->execute_ms += timer_item->span_ms;
		node->key = timer_item->execute_ms;
		srv_rbtree_insert(m_rbtree_timer_items, node);
	}
	else
	{
		long timer_id = timer_item->id;
		timer_item = nullptr;
		node = nullptr;
		this->Remove(timer_id);
	}
}

EModuleRetCode TimerModule::Update()
{
	long long old_ms = m_now_ms;
	m_now_ms = GetNowMs();
	m_now_sec = m_now_ms / 1000;
	m_delta_ms = m_now_ms - old_ms;

	if (!m_nodes_execute_now.empty())
	{
		for (srv_rbtree_node_t *node : m_nodes_execute_now)
		{
			this->TryExecuteNode(node);
		}
		m_nodes_execute_now.clear();
	}

	int loop = 0;
	while (++ loop < 10000000)
	{
		if (m_rbtree_timer_items->root != m_rbtree_timer_items->sentinel)
		{
			srv_rbtree_node_t *node = srv_rbtree_min(m_rbtree_timer_items->root, m_rbtree_timer_items->sentinel);
			if (m_rbtree_timer_items->sentinel == node)
				break;
			if (node->key > m_now_ms)
				break;
			srv_rbtree_delete(m_rbtree_timer_items, node);

			this->TryExecuteNode(node);
		}
	}

	return EModuleRetCode_Pending;
}

EModuleRetCode TimerModule::Release()
{
	std::queue<srv_rbtree_node_t *> node_queue;
	if (m_rbtree_timer_items->root != m_rbtree_timer_items->sentinel)
		node_queue.push(m_rbtree_timer_items->root);
	while (!node_queue.empty())
	{
		srv_rbtree_node_t *node = node_queue.front();
		node_queue.pop();
		if (node->left != m_rbtree_timer_items->sentinel)
			node_queue.push(node->left);
		if (node->right != m_rbtree_timer_items->sentinel)
			node_queue.push(node->right);
		if (nullptr != node->data)
			delete (TimerItem *)node->data;
		delete node;
	}
	delete m_rbtree_sentinel_node; m_rbtree_sentinel_node = nullptr;
	delete m_rbtree_timer_items; m_rbtree_timer_items = nullptr;


	return EModuleRetCode_Succ;
}

EModuleRetCode TimerModule::Destroy()
{
	return EModuleRetCode_Succ;
}

long long TimerModule::NowSec()
{
	return m_now_sec;
}

long long TimerModule::NowMs()
{
	return m_delta_ms;
}

long long TimerModule::DeltaMs()
{
	return m_delta_ms;
}

long long TimerModule::Add(std::shared_ptr<ObjectBase> who, TimerAction action, long start_ts_ms, long long execute_span_ms, long long execute_times)
{
	if (nullptr == who || nullptr == action || execute_span_ms < 0)
		return INVALID_TIMER_ID;
	if (execute_times == EXECUTE_UNLIMIT_TIMES && execute_span_ms <= 0)
		return INVALID_TIMER_ID;
	if (execute_times != EXECUTE_UNLIMIT_TIMES && execute_times < 0)
		return INVALID_TIMER_ID;

	std::weak_ptr<ObjectBase> weak_who(who);
	TimerItem *timer_item = new TimerItem();
	timer_item->id = this->GenTimerId();
	timer_item->who = who;
	timer_item->span_ms = execute_span_ms;
	timer_item->execute_times = execute_times;
	timer_item->is_firm = execute_times == EXECUTE_UNLIMIT_TIMES;
	timer_item->action = action;
	timer_item->execute_ms = (start_ts_ms >= m_now_ms) ? start_ts_ms : m_now_ms;
	srv_rbtree_node_t *node = new srv_rbtree_node_t();
	memset(node, 0, sizeof(srv_rbtree_node_t));
	node->key = timer_item->execute_ms;
	node->data = timer_item;
	m_id_to_timer_node[timer_item->id] = node;
	if (timer_item->execute_ms <= m_now_ms)
		m_nodes_execute_now.push_back(node);
	else
		srv_rbtree_insert(m_rbtree_timer_items, node);
	return timer_item->id;
}

long long TimerModule::AddNext(std::shared_ptr<ObjectBase> who, TimerAction action, long long start_ts_ms)
{
	return this->Add(who, action, start_ts_ms, 0, 1);
}

long long TimerModule::AddFirm(std::shared_ptr<ObjectBase> who, TimerAction action, long long execute_span_ms, long long execute_times)
{

	return this->Add(who, action, m_now_sec + execute_span_ms, execute_span_ms, execute_times);
}

void TimerModule::Remove(long long timer_id)
{
	auto it = m_id_to_timer_node.find(timer_id);
	if (m_id_to_timer_node.end() == it)
		return;
	srv_rbtree_node_t *node = it->second;
	if (node->parent)
		srv_rbtree_delete(m_rbtree_timer_items, node);
	delete (TimerItem *)node->data;
	delete node;
	m_id_to_timer_node.erase(it);
}

long long GetNowMs()
{
	std::chrono::high_resolution_clock::time_point tp = std::chrono::high_resolution_clock::now();
	long long now = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();
	return now;
}

long long TimerModule::GenTimerId() 
{ 
	do
	{
		++m_last_timer_id;
		m_last_timer_id <= 0 ? (m_last_timer_id = 1) : 0;
		
	} while(m_id_to_timer_node.count(m_last_timer_id) > 0);

	return m_last_timer_id;
}