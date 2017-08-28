#include "NetworkAgent.h"
#include "CommonModules/Network/INetworkModule.h"
#include "Common/Utils/GlobalMemoryMgr.h"

// field-size	       4                       4                   4	
// field		     ctx_len			   protocol_id		      msg
// field value  sizeof(int)+msg_len		val(protocol_id)		val(msg)
bool NetworkAgent::Send(NetId netid, int protocol_id, char *msg, uint32_t msg_len)
{
	if (netid <= 0)
		return false;
	if (msg_len > 0 && nullptr == msg)
		return false;

	uint32_t ctx_len = sizeof(protocol_id) + msg_len;
	*(uint32_t *)m_send_help_buffer = ctx_len;
	*(int *)(m_send_help_buffer + Net::PROTOCOL_LEN_DESCRIPT_SIZE) = protocol_id;
	bool ret = m_network->Send(netid, m_send_help_buffer, sizeof(m_send_help_buffer));
	if (nullptr != msg && msg_len > 0)
		ret = ret && m_network->Send(netid, msg, msg_len);
	return ret;
}

bool NetworkAgent::Send(NetId netid, int protocol_id, google::protobuf::Message *msg)
{
	uint32_t msg_len = msg->ByteSize();
	if (!this->CheckExpendBuffer(msg_len))
		return false;
	msg->SerializePartialToArray(m_buffer, msg_len);
	return this->Send(netid, protocol_id, m_buffer, msg_len);
}

void NetworkAgent::Close(NetId netid)
{
	m_network->Close(netid);
}

bool NetworkAgent::CheckExpendBuffer(uint32_t lower_limit)
{
	if (m_buffer_capacity >= lower_limit)
		return true;
	if (m_buffer_capacity <= 0) m_buffer_capacity = BUFFER_INIT_SIZE;
	while (m_buffer_capacity < lower_limit)
		m_buffer_capacity += BUFFER_INCREASE_STEP;
	if (nullptr == m_buffer)
		m_buffer = (char *)Malloc(m_buffer_capacity);
	else
		m_buffer = (char *)Realloc(m_buffer, m_buffer_capacity);
	assert(m_buffer);
	return NULL != m_buffer;
}

NetworkAgent::~NetworkAgent()
{
	if (nullptr != m_buffer)
	{
		Free(m_buffer);
		m_buffer = nullptr;
	}
}
#include "Common/Utils/GlobalMemoryMgr.h"
NewDelOperaImplement(NetworkAgent);