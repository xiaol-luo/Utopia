#pragma once

#include <vector>

class MemoryPool;

class MemoryPoolMgr
{
public:
	MemoryPoolMgr(std::vector<uint32_t> block_sizes, uint32_t memory_page_size, uint32_t expect_working_block_set_num, uint32_t min_block_num_per_block_set);
	~MemoryPoolMgr();

	void * Malloc(uint32_t malloc_size);
	void Free(void *ptr);

private:
	std::vector<MemoryPool *> m_memory_pools;
	uint32_t m_max_block_size = 0;
	MemoryPool **m_memory_pool_fast_idx = nullptr;

	const static int BLOCK_SIZE_MULTI_BASE = 8; // block must be times of 8
	const static uint32_t BLOCK_SIZE_DESCRIPT_LEN = sizeof(uint32_t);
};
