#pragma once

#include "Common/Define/NetworkDefine.h"
#include <memory>
#include "Common/Macro/AllMacro.h"

enum ENetworkHandlerType
{
	ENetworkHandler_Connect,
	ENetworkHandler_Listen,
	ENetworkHandlerType_Max,
};

class INetworkHandler
{
	NewDelOperaDeclaration;
public:
	INetworkHandler(ENetworkHandlerType handler_type) : m_handler_type(handler_type) {}
	virtual ~INetworkHandler() {}
	virtual void OnClose(int err_num) = 0;
	virtual void OnOpen(int err_num) = 0;
	ENetworkHandlerType HandlerType() { return m_handler_type; }
	NetId GetNetId() { return m_netid; }
	void SetNetId(NetId netid) { m_netid = netid; }

protected:
	ENetworkHandlerType m_handler_type = ENetworkHandlerType_Max;
	NetId m_netid = 0;
};
class INetConnectHander : public INetworkHandler
{
	NewDelOperaDeclaration;
public:
	INetConnectHander() : INetworkHandler(ENetworkHandler_Connect) {}
	virtual ~INetConnectHander() {}
	virtual void OnRecvData(char *data, uint32_t len) = 0;
};
class INetListenHander : public INetworkHandler
{
	NewDelOperaDeclaration;
public:
	INetListenHander() : INetworkHandler(ENetworkHandler_Listen) {}
	virtual ~INetListenHander() {}
	virtual std::shared_ptr<INetConnectHander> GenConnectorHandler(NetId netid) = 0;
};

