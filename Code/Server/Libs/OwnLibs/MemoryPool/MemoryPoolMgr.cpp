#include "MemoryPoolMgr.h"
#include "MemoryPool.h"
#include <algorithm>
#include <assert.h>
#include <set>

MemoryPoolMgr::MemoryPoolMgr(const std::vector<uint32_t> block_sizes, uint32_t memory_page_size, uint32_t expect_working_block_set_num, uint32_t min_block_num_per_block_set)
{
	assert(block_sizes.size() > 0);
	std::vector<uint32_t> tmp_block_sizes(block_sizes);
	std::sort(tmp_block_sizes.begin(), tmp_block_sizes.end());
	std::set<uint32_t> repeat_cheker;
	for (uint32_t block_size : block_sizes)
	{
		assert(repeat_cheker.count(block_size) <= 0);
		repeat_cheker.insert(block_size);
		assert(block_size > 0);
		assert(0 == block_size % BLOCK_SIZE_MULTI_BASE);
	}
	m_max_block_size = tmp_block_sizes.back();
	m_memory_pool_fast_idx = (MemoryPool **)malloc(sizeof(MemoryPool *) * (m_max_block_size / BLOCK_SIZE_MULTI_BASE + 1));
	m_memory_pool_fast_idx[0] = nullptr;
	uint32_t used_pool_idx = 0;
	for (uint32_t block_size : block_sizes)
	{
		MemoryPool *memory_pool = new MemoryPool(block_size + BLOCK_SIZE_DESCRIPT_LEN, memory_page_size, expect_working_block_set_num, min_block_num_per_block_set);
		m_memory_pools.push_back(memory_pool);
		for (uint32_t i = used_pool_idx + 1; i <= block_size / BLOCK_SIZE_MULTI_BASE; ++i)
			m_memory_pool_fast_idx[i] = memory_pool;
	}
}

MemoryPoolMgr::~MemoryPoolMgr()
{
	for (MemoryPool *memory_pool : m_memory_pools)
	{
		delete memory_pool;
	}
	m_memory_pools.clear();
	free(m_memory_pool_fast_idx);
	m_memory_pool_fast_idx = nullptr;
}

void * MemoryPoolMgr::Malloc(uint32_t malloc_size)
{
	return nullptr;
}

void MemoryPoolMgr::Free(void *ptr)
{

}
