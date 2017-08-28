#pragma once

#include <memory>
#include <queue>
#include "Common/Macro/MemoryPoolMacro.h"

class LenCtxStreamParser
{
	NewDelOperaDeclaration;
public:
	LenCtxStreamParser(uint32_t max_buffer_size);
	~LenCtxStreamParser();
	bool AppendBuffer(char *data, uint32_t data_len);
	bool ParseNext();
	char * Content() { return m_parse_result; }
	uint32_t ContentLen() { return m_parse_result_len; }
	bool IsFail() { return m_is_fail; }

protected:
	char *m_buffer = nullptr;
	uint32_t m_buffer_len = 0;
	uint32_t m_buffer_capacity = 0;
	uint32_t m_max_buffer_size = 0;
	static const int BUFFER_INIT_SIZE = 64;
	static const int BUFFER_INCREASE_STEP = 16;
	bool CheckExpendBuffer(uint32_t lower_limit);

	char *m_input_data_p = nullptr;
	char *m_input_data_q = nullptr;
	bool m_is_fail = false;

	char *m_parse_result = nullptr;
	uint32_t m_parse_result_len = 0;
};