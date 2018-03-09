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
	m_memory_pool_fast_idx = (MemoryPoolData **)malloc(sizeof(MemoryPoolData *) * (m_max_block_size / BLOCK_SIZE_MULTI_BASE + 1));
	m_memory_pool_fast_idx[0] = nullptr;
	uint32_t used_pool_idx = 0;
	for (uint32_t block_size : block_sizes)
	{
		MemoryPool *memory_pool = new MemoryPool(block_size + BLOCK_SIZE_DESCRIPT_LEN, memory_page_size, expect_working_block_set_num, min_block_num_per_block_set);
		MemoryPoolData *memory_pool_data = new MemoryPoolData(memory_pool);
		m_memory_pools.push_back(memory_pool_data);
		for (uint32_t i = used_pool_idx + 1; i <= block_size / BLOCK_SIZE_MULTI_BASE; ++i)
		{
			m_memory_pool_fast_idx[i] = memory_pool_data;
			used_pool_idx = i;
		}
	}
}

MemoryPoolMgr::~MemoryPoolMgr()
{
	for (MemoryPoolData *memory_pool : m_memory_pools)
	{
		delete memory_pool;
	}
	m_memory_pools.clear();
	free(m_memory_pool_fast_idx);
	m_memory_pool_fast_idx = nullptr;
}

void * MemoryPoolMgr::Malloc(uint32_t malloc_size)
{
	assert(malloc_size > 0);
	void *ret_ptr = nullptr;
	if (malloc_size > m_max_block_size)
		ret_ptr = malloc(malloc_size + BLOCK_SIZE_DESCRIPT_LEN);
	else
	{
		uint32_t pool_idx = malloc_size / BLOCK_SIZE_MULTI_BASE;
		pool_idx += (malloc_size % BLOCK_SIZE_MULTI_BASE) > 0 ? 1 : 0;
		MemoryPoolData *data = m_memory_pool_fast_idx[pool_idx];
		data->mtx.lock();
		ret_ptr = data->memory_pool->Malloc();
		data->mtx.unlock();
	}
	assert(nullptr != ret_ptr);
	*(uint32_t *)ret_ptr = malloc_size;
	return (char *)ret_ptr + BLOCK_SIZE_DESCRIPT_LEN;
}

void MemoryPoolMgr::Free(void *ptr)
{
	if (nullptr == ptr)
		return;
	void *real_ptr = (char *)ptr - BLOCK_SIZE_DESCRIPT_LEN;
	ptr = nullptr;
	uint32_t malloc_size = *(uint32_t *)real_ptr;
	if (malloc_size > m_max_block_size)
		free(real_ptr);
	else
	{
		uint32_t pool_idx = malloc_size / BLOCK_SIZE_MULTI_BASE;
		pool_idx += (malloc_size % BLOCK_SIZE_MULTI_BASE) > 0 ? 1 : 0;
		MemoryPoolData *data = m_memory_pool_fast_idx[pool_idx];
		data->mtx.lock();
		data->memory_pool->Free(real_ptr);
		data->mtx.unlock();
	}
	real_ptr = nullptr;
}
