#pragma once

#include <memory>
#include <queue>
#include <stdint.h>
#include <assert.h>
#include "Common/Utils/MemoryUtil.h"
#include "Utils/PlatformCompat.h"

template <typename T, int LenDescriptSize>
struct StreamLenPraser
{
	const static int LEN_DESCRIPT_SIZE = LenDescriptSize;
	static_assert(LenDescriptSize > 0, "LenDescriptSize should greater than 0");

	inline static uint32_t Prase(char *data, uint32_t data_len)
	{
		if (data_len < LEN_DESCRIPT_SIZE)
			return 0;

		T val = *(T *)data;
		return (uint32_t)val;
	}
};

#ifndef WIN32
extern uint64_t htonll(uint64_t val);
extern uint64_t ntohll(uint64_t val);
#endif

template <typename T, int LenDescriptSize>
struct NetSteamLenPraser
{
	const static int LEN_DESCRIPT_SIZE = LenDescriptSize;
	static_assert(LenDescriptSize > 0, "LenDescriptSize should greater than 0");

	inline static uint32_t Prase(char *data, uint32_t data_len)
	{
		if (data_len < LEN_DESCRIPT_SIZE)
			return 0;
		if (LEN_DESCRIPT_SIZE <= sizeof(uint16_t))
			return (uint32_t)(ntohs(*(T*)data));
		if (LEN_DESCRIPT_SIZE <= sizeof(uint32_t))
			return (uint32_t)(ntohl(*(T*)data));
		if (LEN_DESCRIPT_SIZE <= sizeof(uint64_t))
			return (uint32_t)(ntohll(*(T*)data));
		assert(false);
		return 0;
	}
};

template <typename T, typename LenParseType = StreamLenPraser<T, sizeof(T)>>
class LenCtxStreamParserEx
{
public:
	LenCtxStreamParserEx(uint32_t max_buffer_size)
		: m_max_buffer_size(max_buffer_size)
	{
		assert(max_buffer_size >= BUFFER_INIT_SIZE);
	}

	~LenCtxStreamParserEx()
	{
		if (nullptr != m_buffer)
		{
			Free(m_buffer);
			m_buffer = nullptr;
		}
	}

	inline bool AppendBuffer(char *data, uint32_t data_len)
	{
		if (m_input_data_p != m_input_data_q || m_is_fail)
			return false;

		m_input_data_p = m_input_data_q = nullptr;
		if (nullptr == data || data_len <= 0)
			return false;

		m_input_data_p = data;
		m_input_data_q = data + data_len;
		return true;
	}

	bool ParseNext()
	{
		m_parse_result = nullptr;
		m_parse_result_len = 0;

		if (nullptr == m_input_data_p || m_input_data_p == m_input_data_q || m_is_fail)
		{
			m_input_data_p = m_input_data_q = nullptr;
			return false;
		}

		bool is_ok = false;
		do
		{
			const static uint32_t PROTOCOL_LEN_DESCRIPT_SIZE = LenParseType::LEN_DESCRIPT_SIZE;

			if (m_buffer_len + m_input_data_q - m_input_data_p < PROTOCOL_LEN_DESCRIPT_SIZE)
			{
				if (!this->CheckExpendBuffer(PROTOCOL_LEN_DESCRIPT_SIZE))
				{
					m_is_fail = true;
					break;
				}
				uint32_t copy_data_len = m_input_data_q - m_input_data_p;
				memcpy(m_buffer + m_buffer_len, m_input_data_p, copy_data_len);
				m_buffer_len += copy_data_len;
				m_input_data_p = m_input_data_q = nullptr;
				break;
			}
			if (m_buffer_len <= 0)
			{
				uint32_t ctx_len = LenParseType::Prase(m_input_data_p, m_input_data_q - m_input_data_p);
				if (ctx_len <= 0)
				{
					m_is_fail = true;
					break;
				}
				if (uint32_t(m_input_data_q - m_input_data_p) >= ctx_len + PROTOCOL_LEN_DESCRIPT_SIZE)
				{
					is_ok = true;
					m_parse_result = m_input_data_p + PROTOCOL_LEN_DESCRIPT_SIZE;
					m_parse_result_len = ctx_len;
					m_input_data_p += (ctx_len + PROTOCOL_LEN_DESCRIPT_SIZE);
					break;
				}
			}
			if (m_buffer_len < PROTOCOL_LEN_DESCRIPT_SIZE)
			{
				uint32_t copy_data_len = PROTOCOL_LEN_DESCRIPT_SIZE - m_buffer_len;
				if (!this->CheckExpendBuffer(PROTOCOL_LEN_DESCRIPT_SIZE))
				{
					m_is_fail = true;
					break;
				}

				memcpy(m_buffer + m_buffer_len, m_input_data_p, copy_data_len);
				m_buffer_len += copy_data_len;
				m_input_data_p += copy_data_len;
				assert(m_input_data_p <= m_input_data_q);
				if (m_input_data_p >= m_input_data_q)
					break;
			}
			if (m_buffer_len >= PROTOCOL_LEN_DESCRIPT_SIZE)
			{
				uint32_t ctx_len = LenParseType::Prase(m_buffer, m_buffer_len);
				uint32_t protocol_len = PROTOCOL_LEN_DESCRIPT_SIZE + ctx_len;
				if (!this->CheckExpendBuffer(protocol_len) || ctx_len <= 0)
				{
					m_is_fail = true;
					break;
				}

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
				m_parse_result_len = ctx_len;
				m_buffer_len = 0;
			}
		} while (false);

		if (!is_ok && m_input_data_p != m_input_data_q)
			m_is_fail = true;

		return is_ok;
	}

	inline char * Content() { return m_parse_result; }
	inline uint32_t ContentLen() { return m_parse_result_len; }
	inline bool IsFail() { return m_is_fail; }
	void * operator new(size_t size) { return MemoryUtil::Malloc(size); }
	void operator delete(void *ptr) { MemoryUtil::Free(ptr); }
	void * operator new[](size_t size) { return MemoryUtil::Malloc(size); }
	void operator delete[](void *ptr) { MemoryUtil::Free(ptr); }

protected:
	bool CheckExpendBuffer(uint32_t lower_limit)
	{
		if (lower_limit > m_max_buffer_size)
			return false;
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

	char *m_buffer = nullptr;
	uint32_t m_buffer_len = 0;
	uint32_t m_buffer_capacity = 0;
	uint32_t m_max_buffer_size = 0;
	static const int BUFFER_INIT_SIZE = 64;
	static const int BUFFER_INCREASE_STEP = 16;

	char *m_input_data_p = nullptr;
	char *m_input_data_q = nullptr;
	bool m_is_fail = false;

	char *m_parse_result = nullptr;
	uint32_t m_parse_result_len = 0;
};

