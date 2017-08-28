#pragma once

class INetworkModule;
#include <stdint.h>
#include "Common/Define/NetworkDefine.h"
#include "Common/Macro/MemoryPoolMacro.h"
#include <google/protobuf/message.h>

class NetworkAgent
{
	NewDelOperaDeclaration;
public:
	NetworkAgent(INetworkModule *network) : m_network(network) {}
	~NetworkAgent();

	bool Send(NetId netid, int protocol_id, char *msg, uint32_t msg_len);
	bool Send(NetId netid, int protocol_id, google::protobuf::Message *msg);
	void Close(NetId netid);

private:
	INetworkModule *m_network = nullptr;
	char m_send_help_buffer[Net::PROTOCOL_LEN_DESCRIPT_SIZE + sizeof(int)];
	char *m_buffer = nullptr;
	uint32_t m_buffer_capacity = 0;
	static const int BUFFER_INIT_SIZE = 64;
	static const int BUFFER_INCREASE_STEP = 16;
	bool CheckExpendBuffer(uint32_t lower_limit);
};