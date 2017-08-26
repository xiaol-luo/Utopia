#pragma once

class INetworkModule;
#include <stdint.h>
#include "Common/Define/NetworkDefine.h"

class NetworkAgent
{
public:
	NetworkAgent(INetworkModule *network) : m_network(network) {}
	~NetworkAgent() { m_network = nullptr; }

	bool Send(NetId netid, int protocol_id, char *msg, uint32_t msg_len);
	void Close(NetId netid);

private:
	INetworkModule *m_network = nullptr;
	char m_send_help_buffer[Net::PROTOCOL_LEN_DESCRIPT_SIZE + sizeof(int)];
};