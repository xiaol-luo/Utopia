#include "MemoryUtil.h"
#include <algorithm>

static MemoryPoolMgr *memory_pool_mgr = nullptr;

void WrapFree(void *ptr, size_t size)
{
	MemoryUtil::Free(ptr);
}

bool MemoryUtil::Init(MemoryPoolMgr * _memory_pool_mgr)
{
	if (nullptr != memory_pool_mgr)
		return false;
	memory_pool_mgr = _memory_pool_mgr;
	return nullptr != memory_pool_mgr;
}

bool MemoryUtil::Init()
{
	if (nullptr != memory_pool_mgr)
		return false;

	std::vector<uint32_t> block_sizes;
	for (int i = 0 + 8; i <= 128; i = i + 8) // (0, 128]
	{
		block_sizes.push_back(i);
	}
	for (int i = 128 + 16; i <= 512; i = i + 16) // (128, 512]
	{
		block_sizes.push_back(i);
	}
	for (int i = 512 + 32; i <= 4096; i = i + 64) // (512, 4096)
	{
		block_sizes.push_back(i);
	}

	memory_pool_mgr = new MemoryPoolMgr(block_sizes, 4 * 1024, 8, 64);
	return nullptr != memory_pool_mgr;
}

void MemoryUtil::Destroy()
{
	delete memory_pool_mgr; memory_pool_mgr = nullptr;
	memory_pool_mgr = nullptr;
}

void * MemoryUtil::Malloc(size_t size)
{
	if (nullptr == memory_pool_mgr)
		return nullptr;
	return memory_pool_mgr->Malloc(size);
}

void MemoryUtil::Free(void * ptr)
{
	if (nullptr == memory_pool_mgr)
		return;
	memory_pool_mgr->Free(ptr);
}

void * MemoryUtil::Realloc(void * ptr, size_t size)
{
	if (nullptr == memory_pool_mgr)
		return nullptr;
	void *new_ptr = memory_pool_mgr->Malloc(size);
	if (nullptr != ptr)
	{
		void *real_ptr = (char *)ptr - MemoryPoolMgr::BLOCK_SIZE_DESCRIPT_LEN;
		uint32_t old_size = *(uint32_t *)real_ptr;
		uint32_t copy_size = std::min(old_size, size);
		memcpy(new_ptr, ptr, copy_size);
		memory_pool_mgr->Free(ptr);
	}
	return new_ptr;
}

google::protobuf::Arena * MemoryUtil::NewArena()
{
	google::protobuf::ArenaOptions option;
	option.block_alloc = MemoryUtil::Malloc;
	option.block_dealloc = WrapFree;
	return new google::protobuf::Arena(option);
}

void * Malloc(size_t size)
{
	return MemoryUtil::Malloc(size);
}

void Free(void *ptr)
{
	return MemoryUtil::Free(ptr);
}

void * Realloc(void *ptr, size_t size)
{
	return MemoryUtil::Realloc(ptr, size);
}

