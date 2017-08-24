#pragma once

#include "CommonModules/Network/INetworkModule.h"
#include <memory>
#include <queue>

class IMessage
{
public:
	~IMessage() 
	{
		if (nullptr != data)
			free(data);
	}

	char *data = nullptr;
	uint32_t len;
};

class NetProtocolParser
{
public:
	NetProtocolParser(char *parse_buffer, uint32_t parse_buffer_len);
	~NetProtocolParser();
	void AppendBuffer(char *data, uint32_t data_len);
	bool ParseNext();
	char * Content() { return m_parse_result; }
	uint32_t ContentLen() { return m_parse_result_len; }

protected:
	char *m_buffer = nullptr;
	uint32_t m_buffer_len = 0;
	uint32_t m_buffer_capacity = 0;
	static const int BUFFER_INCREASE_STEP = 16;
	void CheckExpendBuffer(uint32_t lower_limit);

	std::queue<std::shared_ptr<IMessage>> m_results;

	char *m_parse_buffer = nullptr;		// 外部提供的用于作为解析数据的临时数组
	uint32_t m_parse_buffer_capacity = 0;

	char *data_p = nullptr;
	char *data_q = nullptr;

	char *m_last_input_data = nullptr;
	uint32_t m_last_input_len = 0;

	char *m_parse_result = nullptr;
	uint32_t m_parse_result_len = 0;
};

