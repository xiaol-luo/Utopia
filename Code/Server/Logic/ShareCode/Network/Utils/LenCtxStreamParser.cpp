#include "LenCtxStreamParser.h"
#include <assert.h>

LenCtxStreamParser::LenCtxStreamParser(uint32_t max_buffer_size)
	: m_max_buffer_size(max_buffer_size)
{
	assert(max_buffer_size >= BUFFER_INIT_SIZE);
}

LenCtxStreamParser::~LenCtxStreamParser()
{
	if (nullptr != m_buffer)
	{
		free(m_buffer);
		m_buffer = nullptr;
	}
}

bool LenCtxStreamParser::AppendBuffer(char *data, uint32_t data_len)
{
	if (m_is_fail)
		return false;

	m_input_data_p = m_input_data_q = nullptr;
	if (nullptr == data || data_len <= 0)
		return false;

	m_input_data_p = data;
	m_input_data_q = data + data_len;
	return true;
}

bool LenCtxStreamParser::ParseNext()
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
		const static uint32_t PROTOCOL_LEN_DESCRIPT_SIZE = sizeof(uint32_t);

		if (m_buffer_len + m_input_data_q - m_input_data_p < PROTOCOL_LEN_DESCRIPT_SIZE)
		{
			if (!this->CheckExpendBuffer(PROTOCOL_LEN_DESCRIPT_SIZE))
				break;
			uint32_t copy_data_len = m_input_data_q - m_input_data_p;
			memcpy(m_buffer + m_buffer_len, m_input_data_p, copy_data_len);
			m_buffer_len += copy_data_len;
			m_input_data_p = m_input_data_q = nullptr;
			break;
		}
		
		if (m_buffer_len < PROTOCOL_LEN_DESCRIPT_SIZE)
		{
			uint32_t copy_data_len = PROTOCOL_LEN_DESCRIPT_SIZE - m_buffer_len;
			if (!this->CheckExpendBuffer(PROTOCOL_LEN_DESCRIPT_SIZE))
				break;

			memcpy(m_buffer + m_buffer_len, m_input_data_p, copy_data_len);
			m_buffer_len += copy_data_len;
			m_input_data_p += copy_data_len;
			assert(m_input_data_p <= m_input_data_q);
			if (m_input_data_p >= m_input_data_q)
				break;
		}
		if (m_buffer_len >= PROTOCOL_LEN_DESCRIPT_SIZE)
		{
			uint32_t ctx_len = *(uint32_t *)m_buffer;
			uint32_t protocol_len = PROTOCOL_LEN_DESCRIPT_SIZE + ctx_len;
			if (!this->CheckExpendBuffer(protocol_len))
				break;

			uint32_t data_left_len = m_input_data_q - m_input_data_p;
			if (m_buffer_len + data_left_len < protocol_len)
			{
				memcpy(m_buffer + m_buffer_len, m_input_data_p, data_left_len);
				m_buffer_len += data_left_len;
				m_input_data_p = m_input_data_q = nullptr;
				break;
			}

			uint32_t copy_data_len = protocol_len - m_buffer_len;
			memcpy(m_buffer + m_buffer_len, m_input_data_p, copy_data_len);
			m_buffer_len += copy_data_len;
			m_input_data_p += copy_data_len;
			is_ok = true;
			m_parse_result = m_buffer + PROTOCOL_LEN_DESCRIPT_SIZE;
			m_parse_result_len = m_buffer_len - PROTOCOL_LEN_DESCRIPT_SIZE;
			m_buffer_len = 0;
		}
	} while (false);

	if (m_input_data_p != m_input_data_q)
		m_is_fail = true;

	return is_ok;
}

bool LenCtxStreamParser::CheckExpendBuffer(uint32_t lower_limit)
{
	if (lower_limit > m_max_buffer_size)
		return false;
	if (m_buffer_capacity >= lower_limit)
		return true;
	if (m_buffer_capacity <= 0) m_buffer_capacity = BUFFER_INIT_SIZE;
	while (m_buffer_capacity < lower_limit)
		m_buffer_capacity += BUFFER_INCREASE_STEP;
	if (nullptr == m_buffer)
		m_buffer = (char *)malloc(m_buffer_capacity);
	else
		m_buffer = (char *)realloc(m_buffer, m_buffer_capacity);
	assert(m_buffer);
	return NULL != m_buffer;
}



