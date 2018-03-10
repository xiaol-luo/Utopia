#pragma once
#include <stdint.h>
#include <queue>
#include <vector>
#include <functional>
#include <string.h>

struct BlockSet;

class MemoryPool
{
public:
	MemoryPool(uint32_t block_size, uint32_t memory_page_size);
	MemoryPool(uint32_t block_size, uint32_t memory_page_size, uint32_t expect_working_block_set_num, uint32_t min_block_num_per_block_set);
	~MemoryPool();

	void * Malloc();
	void Free(void *);

private:
	uint32_t m_last_id = 0;
	std::priority_queue<uint32_t, std::vector<uint32_t>, std::greater<uint32_t>> m_recycle_ids;
	std::vector<BlockSet *> m_block_sets;
	uint32_t m_free_block_set_min_id = 0;
	uint32_t m_valid_bolck_set_max_id = 0;
	uint32_t m_block_size = 0;
	uint32_t m_memory_page_size = 4 * 1024;
	uint32_t m_expect_working_block_set_num = 8;
	uint32_t m_working_block_set_num = 0;
	uint32_t m_min_block_num_per_block_set = 16;

private: 
	uint32_t GenBlockId();
};
