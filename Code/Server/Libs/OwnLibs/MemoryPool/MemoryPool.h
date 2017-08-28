#pragma once
#include <stdint.h>
#include <queue>
#include <vector>
struct BlockSet;

class MemoryPool
{
public:
	MemoryPool(uint32_t block_size);
	~MemoryPool();

	void * Malloc();
	void Free(void *);

private:
	uint32_t m_last_id = 0;
	std::priority_queue<uint32_t> m_recycle_ids;
	std::vector<BlockSet *> m_block_sets;
	uint32_t m_free_block_set_min_id = 0;
	uint32_t m_valid_bolck_set_max_id = 0;
	uint32_t m_block_size = 0;
	const uint32_t PAGE_SIZE = 10240;
	const uint32_t EXPECT_WORKING_BLOCK_SET_NUM = 1;
	uint32_t m_working_block_set_num = 0;

private: 
	uint32_t GenBlockId();
};
