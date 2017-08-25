#include "NetProtocolParser.h"
#include <assert.h>

NetProtocolParser::NetProtocolParser(char *parse_buffer, uint32_t parse_buffer_len) 
	: m_parse_buffer(parse_buffer), m_parse_buffer_capacity(parse_buffer_len)
{
	assert(nullptr != parse_buffer);
	assert(parse_buffer_len >= Net::PROTOCOL_MAX_SIZE);
}

NetProtocolParser::~NetProtocolParser()
{
	if (nullptr != m_buffer)
	{
		free(m_buffer);
		m_buffer = nullptr;
	}
}

bool NetProtocolParser::AppendBuffer(char *data, uint32_t data_len)
{
	m_last_input_data = data;
	m_last_input_len = data_len;

	if (m_input_data_p != m_input_data_q)
		return false;

	m_input_data_p = m_input_data_q = nullptr;
	if (nullptr == data || data_len <= 0)
		return false;

	m_input_data_p = data;
	m_input_data_q = data + data_len;
	return true;
}

bool NetProtocolParser::ParseNext()
{
	m_parse_result = nullptr;
	m_parse_result_len = 0;

	if (nullptr == m_input_data_p || m_input_data_p == m_input_data_q)
	{
		m_input_data_p = m_input_data_q = nullptr;
		return false;
	}

	bool is_ok = false;
	do
	{
		if (m_buffer_len + m_input_data_q - m_input_data_p <= Net::PROTOCOL_LEN_DESCRIPT_SIZE)
		{
			uint32_t data_left_len = m_input_data_q - m_input_data_p;
			this->CheckExpendBuffer(Net::PROTOCOL_LEN_DESCRIPT_SIZE);
			memcpy(m_buffer + m_buffer_len, m_input_data_p, data_left_len);
			m_buffer_len += data_left_len;
			m_input_data_p = m_input_data_q = nullptr;
			break;
		}

		char *parse_p = nullptr;
		uint32_t parse_len = 0;

		if (m_buffer_len >= Net::PROTOCOL_LEN_DESCRIPT_SIZE)
		{
			uint32_t ctx_len = *(uint32_t *)m_buffer;
			uint32_t protocol_len = Net::PROTOCOL_LEN_DESCRIPT_SIZE + ctx_len;
			uint32_t data_left_len = m_input_data_q - m_input_data_p;
			if (m_buffer_len + data_left_len < protocol_len)
			{
				this->CheckExpendBuffer(m_buffer_len + data_left_len);
				memcpy(m_buffer + m_buffer_len, m_input_data_p, data_left_len);
				m_buffer_len += data_left_len;
				m_input_data_p = m_input_data_q = nullptr;
				break;
			}

			uint32_t data_copy_len = protocol_len - m_buffer_len;
			assert(m_parse_buffer_capacity >= protocol_len);
			memcpy(m_parse_buffer, m_buffer, m_buffer_len);
			memcpy(m_parse_buffer + m_buffer_len, m_input_data_p, data_copy_len);
			m_buffer_len = 0;
			m_input_data_p += data_copy_len;
			parse_p = m_parse_buffer;
			parse_len = protocol_len;
		}
		else // m_buffer_len < Net::PROTOCOL_LEN_DESCRIPT_SIZE
		{
			if (m_buffer_len > 0)
			{
				uint32_t old_buffer_len = m_buffer_len;
				uint32_t data_copy_len = Net::PROTOCOL_LEN_DESCRIPT_SIZE - m_buffer_len;
				memcpy(m_parse_buffer, m_buffer, m_buffer_len);
				m_buffer_len = 0;
				memcpy(m_parse_buffer + old_buffer_len, m_input_data_p, data_copy_len);
				m_input_data_p += data_copy_len;

				uint32_t ctx_len = *(uint32_t *)m_parse_buffer;
				uint32_t data_left_len = m_input_data_q - m_input_data_p;
				if (data_left_len < ctx_len)
				{
					this->CheckExpendBuffer(old_buffer_len + data_left_len + data_copy_len);
					memcpy(m_buffer + old_buffer_len, m_input_data_p - data_copy_len, data_copy_len + data_left_len);
					m_buffer_len = old_buffer_len + data_left_len + data_copy_len;
					m_input_data_p = m_input_data_q = nullptr;
					break;
				}
				else
				{
					memcpy(m_parse_buffer + Net::PROTOCOL_LEN_DESCRIPT_SIZE, m_input_data_p, ctx_len);
					m_input_data_p += ctx_len;
					parse_p = m_parse_buffer;
					parse_len = Net::PROTOCOL_LEN_DESCRIPT_SIZE + ctx_len;
				}
			}
			else // m_buffer_len = 0
			{
				uint32_t ctx_len = *(uint32_t *)m_input_data_p;
				uint32_t data_left_len = m_input_data_q - m_input_data_p;
				if (data_left_len < ctx_len + Net::PROTOCOL_LEN_DESCRIPT_SIZE)
				{
					this->CheckExpendBuffer(data_left_len);
					memcpy(m_buffer, m_input_data_p, data_left_len);
					m_buffer_len = data_left_len;
					m_input_data_p = m_input_data_q = nullptr;
					break;
				}

				parse_p = m_input_data_p;
				parse_len = Net::PROTOCOL_LEN_DESCRIPT_SIZE + ctx_len;
				m_input_data_p += parse_len;
			}
		}

		if (nullptr != parse_p && parse_len > Net::PROTOCOL_LEN_DESCRIPT_SIZE)
		{
			is_ok = true;
			m_parse_result = parse_p + Net::PROTOCOL_LEN_DESCRIPT_SIZE;
			m_parse_result_len = parse_len - Net::PROTOCOL_LEN_DESCRIPT_SIZE;
		}
	} while (false);

	return is_ok;
}

void NetProtocolParser::CheckExpendBuffer(uint32_t lower_limit)
{
	assert(lower_limit <= Net::PROTOCOL_MAX_SIZE);

	if (m_buffer_capacity >= lower_limit)
		return;
	while (m_buffer_capacity < lower_limit)
		m_buffer_capacity += BUFFER_INCREASE_STEP;
	if (nullptr == m_buffer)
		m_buffer = (char *)malloc(m_buffer_capacity);
	else
		m_buffer = (char *)realloc(m_buffer, m_buffer_capacity);

	assert(m_buffer);
}



