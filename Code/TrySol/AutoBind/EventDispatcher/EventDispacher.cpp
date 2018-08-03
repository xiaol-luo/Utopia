#include "EventDispacher.h"

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
