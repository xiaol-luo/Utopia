#include "NetworkModule.h"
#include "Modules/ModuleMgr.h"
#include "Modules/Log/LogModule.h"
#include "NetWorker.h"

#ifdef WIN32
#include <winsock2.h>
#endif

struct ConnectTaskThread
{
	using ThreadAction = void(*)(ConnectTaskThread *);
	ConnectTaskThread(std::function<void(ConnectTaskThread *)> _action, std::mutex *_task_mutex,
		std::queue<Net::ConnectTask *> *_cnn_tasks, std::mutex *_result_mutex,
		std::queue<Net::ConnectResult> *_cnn_results) :
		task_mutex(_task_mutex), cnn_tasks(_cnn_tasks), result_mutex(_result_mutex),
		cnn_results(_cnn_results), action(_action)
	{
		int a = 0; 
		++a;
	}

	~ConnectTaskThread()
	{

	}

	bool Start()
	{
		bool ret = false;
		if (nullptr == self_thread && !is_exit)
		{
			if (nullptr != action)
			{
				self_thread = new std::thread(action, this);
				ret = true;
			}
		}
		return ret;
	}
	void Exit()
	{
		is_exit = true;
	}
	void Join()
	{
		this->Exit();
		self_thread->join();
		action = nullptr;
		delete self_thread; self_thread = nullptr;
	}

	bool is_exit = false;
	std::mutex *task_mutex;
	std::queue<Net::ConnectTask *> *cnn_tasks;
	std::mutex *result_mutex;
	std::queue<Net::ConnectResult> *cnn_results;
	std::function<void(ConnectTaskThread *)> action = nullptr;
	std::thread *self_thread = nullptr;
};

void CnnTaskWorker(ConnectTaskThread *task_thread)
{
	if (nullptr == task_thread) return;

	bool is_exit = false;
	std::mutex *task_mutex = task_thread->task_mutex;
	std::queue<Net::ConnectTask *> *cnn_tasks = task_thread->cnn_tasks;
	std::mutex *result_mutex = task_thread->result_mutex;
	std::queue<Net::ConnectResult> *cnn_results = task_thread->cnn_results;

	while (!task_thread->is_exit)
	{
		if (cnn_tasks->empty())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			continue;
		}
		Net::ConnectTask *task = nullptr;
		if (task_mutex->try_lock())
		{
			if (!cnn_tasks->empty())
			{
				task = cnn_tasks->front();
				cnn_tasks->pop();
			}
			task_mutex->unlock();
		}
		if (nullptr == task)
			continue;
		task->Process();
		result_mutex->lock();
		cnn_results->push(task->GetResult());
		result_mutex->unlock();
		delete task; task = nullptr;
	}
}

NetworkModule::NetworkModule(std::shared_ptr<ModuleMgr> module_mgr) : INetworkModule(module_mgr)
{
	m_cnn_task_mutex = new std::mutex();
	m_cnn_results_mutex = new std::mutex();

	if (m_cnn_task_thread_num <= 0)
		m_cnn_task_thread_num = 1;
	int malloc_size = sizeof(ConnectTaskThread *) * m_cnn_task_thread_num;
	m_cnn_task_threads = (ConnectTaskThread **)malloc(malloc_size);
	memset(m_cnn_task_threads, 0, malloc_size);
	for (int i = 0; i < m_cnn_task_thread_num; ++i)
	{
		m_cnn_task_threads[i] = new ConnectTaskThread(
			CnnTaskWorker, m_cnn_task_mutex, &m_cnn_tasks,
			m_cnn_results_mutex, &m_cnn_results);
	}

	if (m_net_worker_num <= 0)
		m_net_worker_num = 1;
	malloc_size = sizeof(Net::INetWorker *) * m_net_worker_num;
	m_net_workers = (Net::INetWorker **)malloc(malloc_size);
	memset(m_net_workers, 0, malloc_size);
	for (int i = 0; i < m_net_worker_num; ++i)
	{
		m_net_workers[i] = new Net::NetWorker();
	}
}

NetworkModule::~NetworkModule()
{
	if (nullptr != m_cnn_task_threads)
	{
		for (int i = 0; i < m_cnn_task_thread_num; ++i)
		{
			if (nullptr != m_cnn_task_threads[i])
			{
				delete m_cnn_task_threads[i];
				m_cnn_task_threads[i] = nullptr;
			}
		}
		free(m_cnn_task_threads); 
		m_cnn_task_threads = nullptr;
	}

	if (nullptr != m_cnn_task_mutex)
	{
		delete 	m_cnn_task_mutex;
		m_cnn_task_mutex = nullptr;
	}
	if (nullptr != m_cnn_results_mutex)
	{
		delete m_cnn_results_mutex;
		m_cnn_results_mutex = nullptr;
	}
	if (nullptr != m_net_workers)
	{
		for (int i = 0; i < m_net_worker_num; ++i)
		{
			delete m_net_workers[i];
			m_net_workers[i] = nullptr;
		}
		free(m_net_workers);
		m_net_workers = nullptr;
	}
}

EModuleRetCode NetworkModule::Init(void *param)
{
	return EModuleRetCode_Succ;
}

EModuleRetCode NetworkModule::Awake()
{
	bool ret = true;
	if (ret)
	{
		for (int i = 0; i < m_net_worker_num; ++i)
		{
			if (!m_net_workers[i]->Start())
			{
				ret = false;
				break;
			}
		}
	}
	if (ret)
	{
		for (int i = 0; i < m_cnn_task_thread_num; ++i)
		{
			if (!m_cnn_task_threads[i]->Start())
			{
				ret = false;
				break;
			}
		}
	}

	return ret ? EModuleRetCode_Succ : EModuleRetCode_Failed;
}

EModuleRetCode NetworkModule::Update()
{
	this->ProcessConnectResult();
	this->ProcessNetDatas();
	return EModuleRetCode_Succ;
}

EModuleRetCode NetworkModule::Release()
{
	for (int i = 0; i < m_cnn_task_thread_num; ++i)
	{
		m_cnn_task_threads[i]->Exit();
	}
	for (int i = 0; i < m_cnn_task_thread_num; ++i)
	{
		m_cnn_task_threads[i]->Join();
	}
	while (!m_cnn_results.empty())
		m_cnn_results.pop();
	while (!m_cnn_tasks.empty())
	{
		delete m_cnn_tasks.front();
		m_cnn_tasks.pop();
	}

	return EModuleRetCode_Succ;
}

EModuleRetCode NetworkModule::Destroy()
{
	for (int i = 0; i < m_net_worker_num; ++i)
	{
		m_net_workers[i]->Stop();
	}
	m_async_network_handlers.clear();

	return EModuleRetCode_Succ;
}

NetId NetworkModule::Listen(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetListenHander> handler)
{
	std::shared_ptr<INetworkHandler> sp_handler = handler.lock();
	if (nullptr == sp_handler) return 0;

	NetId netid = 0;
	Net::ConnectTaskListen task(0, ip, port, opt);
	task.Process();
	const Net::ConnectResult &ret = task.GetResult();
	int err_num = ret.err_num;
	std::string err_msg = ret.err_msg;
	if (0 == err_num)
	{
		netid = this->GenNetId();
		if (!ChoseWorker(netid)->AddCnn(netid, ret.fd, handler))
		{
			err_num = 1;
			if (ret.fd >= 0)
				close(ret.fd);
			err_msg = "NetWorker::Add fail";
		}
	}

	sp_handler->OnOpen(err_num);
	if (0 != err_num)
	{
		netid = 0;
		std::shared_ptr<LogModule> log = m_module_mgr->GetModule<LogModule>();
		log->Error(this->LogId(), "NetworkModule::Listen {0}:{1} fail, errno {2}", ip, port, err_num);
	}
	return netid;
}

NetId NetworkModule::Connect(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetConnectHander> handler)
{
	std::shared_ptr<INetworkHandler> sp_handler = handler.lock();
	if (nullptr == sp_handler) return 0;

	NetId netid = 0;
	Net::ConnectTaskConnect task(0, ip, port, opt);
	task.Process();
	const Net::ConnectResult &ret = task.GetResult();
	int err_num = ret.err_num;
	std::string err_msg = ret.err_msg;
	if (0 == err_num)
	{
		netid = this->GenNetId();
		if (!ChoseWorker(netid)->AddCnn(netid, ret.fd, handler))
		{
			err_num = 1;
			if (ret.fd >= 0)
				close(ret.fd);
			err_msg = "NetWorker::Add fail";
		}
	}

	sp_handler->OnOpen(err_num);
	if (0 != err_num)
	{
		netid = 0;
		std::shared_ptr<LogModule> log = m_module_mgr->GetModule<LogModule>();
		log->Error(this->LogId(), "NetworkModule::Connect {0}:{1} fail, errno {2}", ip, port, err_num);
	}
	return netid;
}

void NetworkModule::Close(NetId netid)
{
	this->ChoseWorker(netid)->RemoveCnn(netid);
}

int64_t NetworkModule::ListenAsync(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetListenHander> handler)
{
	if (nullptr == handler.lock()) return 0;

	int64_t async_id = this->GenAsyncId();
	m_async_network_handlers[async_id] = handler;
	Net::ConnectTaskListen *task = new Net::ConnectTaskListen(
		async_id, ip, port, opt);
	m_cnn_task_mutex->lock();
	m_cnn_tasks.push(task);
	m_cnn_task_mutex->unlock();
	return async_id;
}

int64_t NetworkModule::ConnectAsync(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetConnectHander> handler)
{
	if (nullptr == handler.lock()) return 0;

	int64_t async_id = this->GenAsyncId();
	m_async_network_handlers[async_id] = handler;
	Net::ConnectTaskConnect *task = new Net::ConnectTaskConnect(
		async_id, ip, port, opt);
	m_cnn_task_mutex->lock();
	m_cnn_tasks.push(task);
	m_cnn_task_mutex->unlock();
	return async_id;
}

void NetworkModule::CancelAsync(uint64_t async_id)
{
	m_async_network_handlers.erase(async_id);
}

bool NetworkModule::Send(NetId netId, char *buffer, uint32_t len)
{
	return 0;
}

NetId NetworkModule::GenNetId()
{
	++ m_last_netid;
	if (m_last_netid <= 0) m_last_netid = 1;
	return m_last_netid;
}

int64_t NetworkModule::GenAsyncId()
{
	++ m_last_async_id;
	if (m_last_netid <= 0) m_last_async_id = 1;
	return m_last_async_id;
}

Net::INetWorker * NetworkModule::ChoseWorker(NetId netid)
{
	return m_net_workers[netid % m_net_worker_num];
}

void NetworkModule::ProcessConnectResult()
{
	std::queue<Net::ConnectResult> cnn_results_swap;
	m_cnn_results_mutex->lock();
	cnn_results_swap.swap(m_cnn_results);
	m_cnn_results_mutex->unlock();
	if (cnn_results_swap.empty())
		return;

	while (!cnn_results_swap.empty())
	{
		Net::ConnectResult ret = cnn_results_swap.front();
		cnn_results_swap.pop();
		auto it = m_async_network_handlers.find(ret.id);
		if (m_async_network_handlers.end() == it || it->second.expired())
		{
			if (ret.fd >= 0)
				close(ret.fd);
		}
		else
		{
			std::shared_ptr<INetworkHandler> handler = it->second.lock();
			int err_num = ret.err_num;
			std::string err_msg = ret.err_msg;
			if (0 == err_num)
			{
				NetId netid = this->GenNetId();
				if (!ChoseWorker(netid)->AddCnn(netid, ret.fd, handler))
				{
					err_num = 1;
					if (ret.fd >= 0)
						close(ret.fd);
					err_msg = "NetWorker::Add fail";
				}
			}
			if (0 != err_num)
			{
				handler->OnOpen(err_num);
				std::shared_ptr<LogModule> log = m_module_mgr->GetModule<LogModule>();
				log->Error(this->LogId(), "NetworkModule::ProcessConnectResult errno {0}", err_num);
			}
		}
		m_async_network_handlers.erase(ret.id);
	}
}

void NetworkModule::ProcessNetDatas()
{
	for (int i = 0; i < m_net_worker_num; ++i)
	{
		std::set<NetId> to_remove_netids;
		std::queue<NetWorkData> *net_datas = nullptr;
		if (m_net_workers[i]->GetNetDatas(net_datas))
		{
			while (!net_datas->empty())
			{
				NetWorkData &data = net_datas->front();
				std::shared_ptr<INetworkHandler> handler = data.handler.lock();
				if (nullptr == handler)
				{
					to_remove_netids.insert(data.netid);
				}
				else
				{
					if (ENetworkHandler_Connect == handler->HandlerType())
					{
						std::shared_ptr<INetConnectHander> tmp_handler = std::dynamic_pointer_cast<INetConnectHander>(handler);
						if (ENetWorkDataAction_Close == data.action)
							tmp_handler->OnClose(data.err_num);
						if (ENetWorkDataAction_Read == data.action)
						{
							tmp_handler->OnRecvData(data.binary, data.binary_len);
							free(data.binary); data.binary = nullptr; 
							data.binary_len = 0;
						}
					}
					if (ENetworkHandler_Listen == handler->HandlerType())
					{
						std::shared_ptr<INetListenHander> tmp_handler = std::dynamic_pointer_cast<INetListenHander>(handler);
						if (ENetWorkDataAction_Close == data.action)
							tmp_handler->OnClose(data.err_num);
						if (ENetWorkDataAction_Read == data.action)
						{
							NetId netid = this->GenNetId();
							std::shared_ptr<INetConnectHander> new_handler = tmp_handler->GenConnectorHandler(netid);
							int err_num = 0;
							if (nullptr == new_handler || 
								!ChoseWorker(netid)->AddCnn(netid, data.new_fd, new_handler))
								err_num = 1;
							if (0 != err_num)
							{
								if (nullptr != new_handler)
									new_handler->OnOpen(err_num);
								if (data.new_fd >= 0)
									close(data.new_fd);
							}
						}
					}
				}
				net_datas->pop();
			}
		}
		for (NetId netid : to_remove_netids)
		{
			m_net_workers[i]->RemoveCnn(netid);
		}
	}
}
