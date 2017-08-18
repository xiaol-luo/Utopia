#include "Modules/Network/INetworkModule.h"

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
	virtual NetId Listen(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler);
	virtual NetId Connect(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler);
	virtual void Close(NetId net_id);
	virtual int64_t ListenAsync(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler,
		std::function<void(NetId, int)> retCb);
	virtual int64_t ConnectAsync(std::string ip, uint16_t port, std::weak_ptr<NetListenHander> handler,
		std::function<void(NetId, int)> retCb);
	virtual void CancelAsync(uint64_t async_id);
	virtual bool Send(NetId netId, char *buffer, uint32_t len);
};
