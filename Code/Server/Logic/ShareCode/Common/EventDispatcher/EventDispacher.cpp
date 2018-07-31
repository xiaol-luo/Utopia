#include "EventDispacher.h"

const uint64_t EventDispacher::INVALID_ID = 0;
const uint32_t EventDispacher::SubcribeDataBase::INVALID_ID = 0;

EventDispacher::EventDispacher()
{
}

EventDispacher::~EventDispacher()
{
	for (auto kv_pair : m_subscribes)
	{
		delete kv_pair.second;
	}
	m_subscribes.clear();
}
