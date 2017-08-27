#include "MemoryPool/MemoryPool.h"
#include <assert.h>

struct BlockLink
{
	void *next = nullptr;
};

struct BlockSet
{
	static const uint32_t MIN_BLOCK_NUM = 16;

	uint32_t id = 0;
	uint32_t block_size = 0;
	uint32_t total_num = 0;
	uint32_t used_num = 0;
	BlockLink free_block;
	char blocks_begin[0];
};

MemoryPool::MemoryPool(uint32_t block_size) : m_block_size(block_size)
{
	m_block_sets.clear();
	m_block_sets.push_back(nullptr);
}

MemoryPool::~MemoryPool()
{
	for (auto block_set: m_block_sets)
	{
		if (nullptr != block_set)
			delete block_set;
	}
	m_block_sets.clear();
}

void * MemoryPool::Malloc()
{

}

void MemoryPool::Free(void *)
{

}
