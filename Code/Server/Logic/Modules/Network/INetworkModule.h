#pragma once

#include "Modules/IModule.h"
#include <stdint.h>
#include <string>
#include <functional>

using NetId = uint64_t;

enum ENetworkHandlerType
{
	ENetworkHandler_Connect,
	ENetworkHandler_Listen,
	ENetworkHandlerType_Max,
};

class INetConnectHander;
class INetListenHander;

class INetworkHandler
{
public:
	INetworkHandler(ENetworkHandlerType handler_type, NetId netid) : m_handler_type(handler_type) {}
	virtual ~INetworkHandler() {}
	virtual void OnError(int err_num) = 0;
	virtual void OnSucc() = 0;
	virtual void OnClose() = 0;
	ENetworkHandlerType HandlerType() { return m_handler_type; }
	NetId GetNetId() { return m_netid; }

protected:
	ENetworkHandlerType m_handler_type;
	NetId m_netid;
};
class INetConnectHander : public INetworkHandler
{
public:
	INetConnectHander(NetId netid) : INetworkHandler(ENetworkHandler_Connect, netid) {}
	virtual ~INetConnectHander() {}
	virtual void OnRecvData(char *data, uint32_t len) = 0;
	void SetListenHandler(std::weak_ptr<INetListenHander> listen_handler) { m_relate_listen_handler = listen_handler; }
private:
	std::weak_ptr<INetListenHander> m_relate_listen_handler;
};
class INetListenHander : public INetworkHandler
{
public:
	INetListenHander(NetId netid) : INetworkHandler(ENetworkHandler_Listen, netid) {}
	virtual ~INetListenHander() {}
	virtual std::shared_ptr<INetConnectHander> GenConnectorHandler(NetId netid) = 0;
};

class INetworkModule : public IModule
{
public:
	const static EMoudleName MODULE_NAME = EMoudleName_Network;
	INetworkModule(std::shared_ptr<ModuleMgr> module_mgr) : IModule(module_mgr , MODULE_NAME) {}
	virtual ~INetworkModule() {}
	virtual EModuleRetCode Init(void *param) = 0;
	virtual EModuleRetCode Awake() = 0;
	virtual EModuleRetCode Update() = 0;
	virtual EModuleRetCode Release() = 0;
	virtual EModuleRetCode Destroy() = 0;

public:
	virtual NetId Listen(std::string ip, uint16_t port,  void *opt, std::weak_ptr<INetListenHander> handler) = 0;
	virtual NetId Connect(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetConnectHander> handler) = 0;
	virtual void Close(NetId netid) = 0;
	virtual int64_t ListenAsync(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetListenHander> handler,
		std::function<void(NetId, int)> retCb) = 0;
	virtual int64_t ConnectAsync(std::string ip, uint16_t port, void *opt, std::weak_ptr<INetConnectHander> handler,
		std::function<void(NetId, int)> retCb) = 0;
	virtual void CancelAsync(uint64_t async_id) = 0;
	virtual bool Send(NetId netId, char *buffer, uint32_t len) = 0;
};
