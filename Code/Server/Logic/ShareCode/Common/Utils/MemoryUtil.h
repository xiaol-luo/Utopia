#pragma once 

#include "MemoryPool/MemoryPoolMgr.h"
#include "google/protobuf/arena.h"

class MemoryUtil
{
public:
	static bool Init(MemoryPoolMgr *memory_pool_mgr);
	static bool Init();
	static void Destroy();

	static void * Malloc(size_t size);
	static void Free(void *ptr);
	static void * Realloc(void *ptr, size_t size);
	static google::protobuf::Arena * NewArena();
};

void * Malloc(size_t size);
void Free(void *ptr);
void * Realloc(void *ptr, size_t size);