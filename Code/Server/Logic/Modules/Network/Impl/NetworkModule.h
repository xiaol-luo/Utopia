#pragma once

#include <thread>
#include <queue>
#include <thread>
#include <mutex>
#include <unordered_map>
#include "Modules/Network/INetworkModule.h"
#include "NetConnectTask.h"

struct ConnectTaskThread;
namespace Net
{
	class INetWorker;
}

enum ENetWorkDataAction
{
	ENetWorkDataAction_Close = 0,
	ENetWorkDataAction_Read,
	ENetWorkDataAction_Error,
	ENetWorkDataAction_Max,
};

struct NetWorkData
{
	NetWorkData() {}
	NetWorkData(NetId _netid, int _fd, std::weak_ptr<INetworkHandler> _handle, 
		ENetWorkDataAction _action, int _err_num, int _new_fd, char *_binary, uint32_t _binary_len) 
		: netid(_netid), fd(_fd), handler(_handle), action(_action), err_num(_err_num), 
		new_fd(_new_fd), binary(_binary), binary_len(_binary_len) {}
	NetId netid = 0;
	int fd = 0;
	std::weak_ptr<INetworkHandler> handler;
	ENetWorkDataAction action = ENetWorkDataAction_Max;
	int err_num = 0;
	int new_fd = 0;
	char *binary = nullptr;
	uint32_t binary_len = 0;
};

class NetworkModule : public INetworkModule
{
public:
	NetworkModule(std::shared_ptr<ModuleMgr> module_mgr);
	virtual ~NetworkModule();
	virtual EModuleRetCode Init(void *param);
	virtual EModuleRetCode Awake();
	virtual EModuleRetCode Update();
	virtual EModuleRetCode Release();
	virtual EModuleRetCode Destroy();

public:
	virtual NetId Listen(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetListenHander> handler);
	virtual NetId Connect(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetConnectHander> handler);
	virtual void Close(NetId netid);
	virtual int64_t ListenAsync(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetListenHander> handler,
		std::function<void(NetId, int)> retCb);
	virtual int64_t ConnectAsync(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetConnectHander> handler,
		std::function<void(NetId, int)> retCb);
	virtual void CancelAsync(uint64_t async_id);
	virtual bool Send(NetId netId, char *buffer, uint32_t len);
	int LogId() { return m_log_Id; }

protected:
	std::mutex *m_cnn_task_mutex = nullptr;
	std::queue<Net::ConnectTask *> m_cnn_tasks;
	std::mutex *m_cnn_results_mutex = nullptr;
	std::queue<Net::ConnectResult> m_cnn_results;
	std::queue<Net::ConnectResult> m_cnn_results_swap;
	int m_cnn_task_thread_num = 3;
	ConnectTaskThread **m_cnn_task_threads = nullptr;
	void ProcessConnectResult();

protected:
	std::unordered_map<int64_t, std::weak_ptr<INetworkHandler>> m_async_network_handlers;
	NetId m_last_netid = 0;
	int64_t m_last_async_id = 0;
	NetId GenNetId();
	int64_t GenAsyncId();
	int m_log_Id = 3;

protected:
	int m_net_worker_num = 3;
	Net::INetWorker **m_net_workers;
	Net::INetWorker * ChoseWorker(NetId netid);
	void ProcessNetDatas();
};
