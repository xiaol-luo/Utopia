#include "TimerModule.h"
#include <chrono>
#include <queue>
#include "ModuleDef/ModuleMgr.h"
#include "CommonModules/Log/LogModule.h"

TimerModule::TimerModule(std::shared_ptr<ModuleMgr> module_mgr) : ITimerModule(module_mgr)
{

}

TimerModule::~TimerModule()
{

}

EModuleRetCode TimerModule::Init(void *param)
{
	this->UpdateTime();
	m_rbtree_sentinel_node = new srv_rbtree_node_t;
	memset(m_rbtree_sentinel_node, 0, sizeof(srv_rbtree_node_t));
	m_rbtree_timer_items = new srv_rbtree_t;
	memset(m_rbtree_timer_items, 0, sizeof(srv_rbtree_t));
	srv_rbtree_init(m_rbtree_timer_items, m_rbtree_sentinel_node, srv_rbtree_insert_value);
	return EModuleRetCode_Succ;
}

EModuleRetCode TimerModule::Awake()
{
	this->UpdateTime();
	return EModuleRetCode_Succ;
}

void TimerModule::TryExecuteNode(srv_rbtree_node_t *node)
{
	++m_execute_times;

	// 每个进入到这里的node，只被m_id_to_timer_node有效引用
	TimerItem *timer_item = (TimerItem *)node->data;
	if (nullptr == timer_item)
	{
		long long timer_id = INVALID_TIMER_ID;
		for (auto kvPair : m_id_to_timer_node)
		{
			if (kvPair.second == node)
			{
				timer_id = kvPair.first;
				break;
			}
		}
		if (INVALID_TIMER_ID != timer_id)
			m_to_remove_nodes.insert(timer_id);
		else
			delete node;
		return;
	}
	if (m_to_remove_nodes.count(timer_item->id) > 0)
		return;

	// timer_item->action();
	if (!timer_item->is_firm)
		--timer_item->execute_times;
	if (timer_item->is_firm || timer_item->execute_times > 0)
	{
		timer_item->execute_ms = m_now_ms + timer_item->span_ms;
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
	this->UpdateTime();
	this->ChekRemoveNodes();

	if (!m_nodes_execute_now.empty())
	{
		for (srv_rbtree_node_t *node : m_nodes_execute_now)
		{
			this->TryExecuteNode(node);
		}
		m_nodes_execute_now.clear();
	}

	int loop = 0;
	while (loop ++ < 10000000 && m_rbtree_timer_items->root != m_rbtree_timer_items->sentinel)
	{
		srv_rbtree_node_t *node = srv_rbtree_min(m_rbtree_timer_items->root, m_rbtree_timer_items->sentinel);
		if (m_rbtree_timer_items->sentinel == node)
			break;
		if (node->key > m_now_ms)
			break;
		srv_rbtree_delete(m_rbtree_timer_items, node);
		this->TryExecuteNode(node);
	}
	this->ChekRemoveNodes();

	m_module_mgr->GetModule<LogModule>()->Debug(2, "{0} {1} {2} {3} {4} {5}"
		, m_now_ms, m_delta_ms, m_add_times, m_remove_times, m_id_to_timer_node.size(), m_execute_times);
	m_execute_times = 0;

	return EModuleRetCode_Pending;
}

EModuleRetCode TimerModule::Release()
{
	this->UpdateTime();
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
	m_now_ms = this->RealNowMs();
	return EModuleRetCode_Succ;
}

long long TimerModule::NowSec()
{
	return m_now_sec;
}

long long TimerModule::NowMs()
{
	return m_now_ms;
}

long long TimerModule::DeltaMs()
{
	return m_delta_ms;
}

long long TimerModule::RealNowMs()
{
	std::chrono::high_resolution_clock::time_point tp = std::chrono::high_resolution_clock::now();
	long long now = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();
	return now;
}

long long TimerModule::Add(TimerAction action, long start_ts_ms, long long execute_span_ms, long long execute_times)
{
	if (nullptr == action || execute_span_ms < 0)
		return INVALID_TIMER_ID;
	if (execute_times == EXECUTE_UNLIMIT_TIMES && execute_span_ms <= 0)
		return INVALID_TIMER_ID;
	if (execute_times != EXECUTE_UNLIMIT_TIMES && execute_times < 0)
		return INVALID_TIMER_ID;

	++ m_add_times;

	TimerItem *timer_item = new TimerItem();
	timer_item->id = this->GenTimerId();
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

long long TimerModule::AddNext(TimerAction action, long long start_ts_ms)
{
	return this->Add(action, start_ts_ms, 0, 1);
}

long long TimerModule::AddFirm(TimerAction action, long long execute_span_ms, long long execute_times)
{

	return this->Add(action, m_now_ms + execute_span_ms, execute_span_ms, execute_times);
}

void TimerModule::Remove(long long timer_id)
{
	m_to_remove_nodes.insert(timer_id);
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

void TimerModule::ChekRemoveNodes()
{
	if (m_to_remove_nodes.empty())
		return;

	for (long long timer_id : m_to_remove_nodes)
	{
		auto it = m_id_to_timer_node.find(timer_id);
		if (m_id_to_timer_node.end() == it)
			continue;;
		srv_rbtree_node_t *node = it->second;
		if (node->parent)
			srv_rbtree_delete(m_rbtree_timer_items, node);
		delete (TimerItem *)node->data;
		delete node;
		m_id_to_timer_node.erase(it);
		++ m_remove_times;
	}
	m_to_remove_nodes.clear();
}

void TimerModule::UpdateTime()
{
	long long old_ms = m_now_ms;
	m_now_ms = this->RealNowMs();
	m_now_sec = m_now_ms / 1000;
	m_delta_ms = m_now_ms - old_ms;
}