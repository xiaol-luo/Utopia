#include "MemoryPool/MemoryPool.h"
#include <assert.h>

struct BlockLink
{
	void *next = nullptr;
};

struct BlockSet
{
	static const uint32_t ID_DESCRIPT_LEN = sizeof(uint32_t);

	uint32_t id = 0;
	uint32_t block_size = 0;
	uint32_t total_num = 0;
	uint32_t used_num = 0;
	BlockLink free_block;
	char blocks_begin[0];
};

MemoryPool::MemoryPool(uint32_t block_size, uint32_t memory_page_size) : m_block_size(block_size), m_memory_page_size(memory_page_size)
{
	m_block_sets.clear();
	m_block_sets.push_back(nullptr);
}

MemoryPool::MemoryPool(uint32_t block_size, uint32_t memory_page_size, uint32_t expect_working_block_set_num, uint32_t min_block_num_per_block_set)
	: m_block_size(block_size), m_memory_page_size(memory_page_size), m_expect_working_block_set_num(expect_working_block_set_num), m_min_block_num_per_block_set(min_block_num_per_block_set)
{

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
	BlockSet *block_set = m_block_sets[m_free_block_set_min_id];
	if (nullptr == block_set || nullptr == block_set->free_block.next)
	{
		block_set = nullptr;
		for (uint32_t i = 1; i <= m_valid_bolck_set_max_id; ++ i)
		{
			BlockSet *tmp_block_set = m_block_sets[i];
			if (nullptr != tmp_block_set && nullptr != tmp_block_set->free_block.next)
			{
				block_set = tmp_block_set;
				break;
			}
		}
	}
	if (nullptr == block_set)
	{
		uint32_t block_id = this->GenBlockId();
		assert(m_block_sets.size() >= block_id);
		if (block_id < m_block_sets.size())
			assert(nullptr == m_block_sets[block_id]);

		uint32_t malloc_size = 0;
		uint32_t real_block_size = BlockSet::ID_DESCRIPT_LEN + m_block_size;
		{
			uint32_t tmp_malloc_size = sizeof(BlockSet) + real_block_size * m_min_block_num_per_block_set;
			uint32_t page_num = tmp_malloc_size / m_memory_page_size;
			page_num += tmp_malloc_size % m_memory_page_size > 0 ? 1 : 0;
			malloc_size = page_num * m_memory_page_size;
		}

		block_set = (BlockSet *)malloc(malloc_size);
		{
			++m_working_block_set_num;
			memset(block_set, 0, sizeof(BlockSet));
			block_set->id = block_id;
			block_set->block_size = real_block_size;
			block_set->total_num = (malloc_size - sizeof(BlockSet)) / block_set->block_size;
			block_set->free_block.next = &block_set->blocks_begin;
			{
				char *p = (char *)block_set->free_block.next;
				char *q = (char *)block_set + malloc_size;
				while (p < q)
				{
					BlockLink *block_link = (BlockLink *)p;
					if (p + 2 * real_block_size < q)
					{
						block_link->next = p + real_block_size;
						p += real_block_size;
					}
					else
					{
						block_link->next = nullptr;
						break;
					}
				}
			}
			if (m_block_sets.size() == block_id)
				m_block_sets.push_back(block_set);
			else
				m_block_sets[block_id] = block_set;
			if (block_id > m_valid_bolck_set_max_id)
				m_valid_bolck_set_max_id = block_id;
		}
	}
	assert(nullptr != block_set);
	assert(nullptr != block_set->free_block.next);

	m_free_block_set_min_id = block_set->id;
	char *mem_ptr = (char *)block_set->free_block.next;
	block_set->free_block.next = ((BlockLink *)block_set->free_block.next)->next;
	++block_set->used_num;
	*(uint32_t *)mem_ptr = block_set->id;
	return mem_ptr + BlockSet::ID_DESCRIPT_LEN;
}

void MemoryPool::Free(void *ptr)
{
	void *real_ptr = (char *)ptr - BlockSet::ID_DESCRIPT_LEN;
	uint32_t block_id = *(uint32_t *)real_ptr;
	assert(m_valid_bolck_set_max_id >= block_id);
	BlockSet *block_set = m_block_sets[block_id];
	assert(nullptr != block_set);
	((BlockLink *)real_ptr)->next = block_set->free_block.next;
	block_set->free_block.next = real_ptr;
	real_ptr = nullptr;
	--block_set->used_num;

	if (m_working_block_set_num > m_expect_working_block_set_num)
	{
		if (block_set->used_num <= 0)
		{
			m_block_sets[block_id] = nullptr;
			m_recycle_ids.push(block_id);
			free(block_set);
			block_set = nullptr;
			--m_working_block_set_num;
		}
	}
}

uint32_t MemoryPool::GenBlockId()
{
	uint32_t ret_id = 0;
	if (!m_recycle_ids.empty())
	{
		ret_id = m_recycle_ids.top();
		m_recycle_ids.pop();
	}
	else
	{
		ret_id = ++m_last_id;
	}
	return ret_id;
}

