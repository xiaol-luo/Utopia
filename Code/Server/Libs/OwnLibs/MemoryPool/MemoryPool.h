#pragma once
#include <stdint.h>
#include <set>
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
	std::set<uint32_t> m_recycle_ids;
	std::vector<BlockSet *> m_block_sets;
	uint32_t m_free_block_set_min_id = 0;
	uint32_t m_valid_bolck_set_max_id = 0;
	uint32_t m_block_size = 0;
	const uint32_t EXPECT_BLOCK_SET_NUM = 10;
	const uint32_t PAGE_SIZE = 10240;
};
