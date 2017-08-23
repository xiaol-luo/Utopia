#include "NetProtocolParser.h"
#include <assert.h>

NetProtocolParser::NetProtocolParser(char *parse_buffer, uint32_t parse_buffer_len) 
	: m_parse_buffer(parse_buffer), m_parse_buffer_capacity(parse_buffer_len)
{
	assert(nullptr != parse_buffer);
	assert(parse_buffer_len > Net::PROTOCOL_LEN_DESCRIPT_SIZE);
}

NetProtocolParser::~NetProtocolParser()
{
	if (nullptr != m_buffer)
	{
		free(m_buffer);
		m_buffer = nullptr;
	}
}

void NetProtocolParser::Parse(char *data, uint32_t data_len)
{
	if (nullptr == data || data_len <= 0)
		return;

	char *data_p = data;
	char *data_q = data + data_len;

	while (data_p < data_q)
	{
		uint32_t data_left_len = data_q - data_p;
		if (data_left_len + m_buffer_len <= Net::PROTOCOL_LEN_DESCRIPT_SIZE)
		{
			this->CheckExpendBuffer(Net::PROTOCOL_LEN_DESCRIPT_SIZE);
			memcpy(m_buffer + m_buffer_len, data_p, data_left_len);
			m_buffer_len += data_left_len;
			data_p = data_q;
			break;
		}


		char *parse_p = nullptr;
		uint32_t parse_len = 0;

		if (m_buffer_len >= Net::PROTOCOL_LEN_DESCRIPT_SIZE)
		{
			uint32_t ctx_len = *(uint32_t *)m_buffer;
			if (m_buffer_len + data_left_len < Net::PROTOCOL_LEN_DESCRIPT_SIZE + ctx_len)
			{
				this->CheckExpendBuffer(m_buffer_len + data_left_len);
				memcpy(m_buffer + m_buffer_len, data_p, data_left_len);
				m_buffer_len += data_left_len;
				data_p = data_q;
				break;
			}

			uint32_t protocol_len = Net::PROTOCOL_LEN_DESCRIPT_SIZE + ctx_len;
			uint32_t data_copy_len = protocol_len - m_buffer_len;
			assert(m_parse_buffer_capacity >= protocol_len);
			memcpy(m_parse_buffer, m_buffer, m_buffer_len);
			memcpy(m_parse_buffer + m_buffer_len, data_p, data_copy_len);
			m_buffer_len = 0;
			data_p += data_copy_len;
			parse_p = m_parse_buffer;
			parse_len = protocol_len;
		}
		else
		{
			if (m_buffer_len > 0)
			{
				uint32_t old_buffer_len = m_buffer_len;
				uint32_t data_copy_len = Net::PROTOCOL_LEN_DESCRIPT_SIZE - m_buffer_len;
				memcpy(m_parse_buffer, m_buffer, m_buffer_len);
				memcpy(m_parse_buffer + m_buffer_len, data_p, data_copy_len);
				m_buffer_len = 0;
				data_p += data_copy_len;

				uint32_t ctx_len = *(uint32_t *)m_parse_buffer;
				uint32_t data_left_len = data_q - data_p;
				if (ctx_len > data_left_len)
				{
					this->CheckExpendBuffer(old_buffer_len + data_left_len + data_copy_len);
					memcpy(m_buffer + old_buffer_len, data_p - data_copy_len, data_copy_len + data_left_len);
					m_buffer_len = old_buffer_len + data_left_len + data_copy_len;
					data_p = data_q;
					break;
				}
				else
				{
					memcpy(m_parse_buffer + old_buffer_len + data_copy_len, data_p, ctx_len);
					m_buffer_len = ctx_len + Net::PROTOCOL_LEN_DESCRIPT_SIZE;
					data_p += ctx_len;
					parse_p = m_parse_buffer;
					parse_len = m_buffer_len;
				}
			}
			else
			{
				uint32_t ctx_len = *(uint32_t *)data_p;
				uint32_t data_left_len = data_q - data_p;
				if (uint32_t(data_q - data_p) < ctx_len)
				{
					this->CheckExpendBuffer(m_buffer_len + data_left_len);
					memcpy(m_buffer, data_p, data_left_len);
					m_buffer_len += data_left_len;
					data_p = data_q;
					break;
				}
				parse_p = data_p;
				parse_len = Net::PROTOCOL_LEN_DESCRIPT_SIZE + ctx_len;
				data_p += parse_len;
			}
		}

		if (nullptr != parse_p && parse_len > 0)
		{
			std::shared_ptr<IMessage> msg = std::make_shared<IMessage>();
			msg->len = parse_len;
			msg->data = (char *)malloc(msg->len);
			memcpy(msg->data, parse_p, msg->len);
			m_results.push(msg);
		}
	}
}

void NetProtocolParser::CheckExpendBuffer(uint32_t lower_limit)
{
	if (m_buffer_capacity >= lower_limit)
		return;

	if (m_buffer_capacity <= 0) m_buffer_capacity;
	while (m_buffer_capacity < lower_limit)
		m_buffer_capacity += BUFFER_INCREASE_STEP;
	if (nullptr == m_buffer)
		m_buffer = (char *)malloc(m_buffer_capacity);
	else
		m_buffer = (char *)realloc(m_buffer, m_buffer_capacity);
}

std::queue<std::shared_ptr<IMessage>> NetProtocolParser::AllResult()
{
	std::queue<std::shared_ptr<IMessage>> swap_queue;
	swap_queue.swap(m_results);
	return swap_queue;
}

std::shared_ptr<IMessage> NetProtocolParser::NextResult()
{
	std::shared_ptr<IMessage> ret = nullptr;
	if (!m_results.empty())
	{
		ret = m_results.front();
		m_results.pop();
	}
	return ret;
}


