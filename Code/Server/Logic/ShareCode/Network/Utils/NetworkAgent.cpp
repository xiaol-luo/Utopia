#include "NetworkAgent.h"
#include "CommonModules/Network/INetworkModule.h"

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

void NetworkAgent::Close(NetId netid)
{
	m_network->Close(netid);
}
