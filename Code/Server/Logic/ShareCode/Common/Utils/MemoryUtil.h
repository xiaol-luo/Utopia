#pragma once 

#include "MemoryPool/MemoryPoolMgr.h"

class MemoryUtil
{
public:
	static bool Init(MemoryPoolMgr *memory_pool_mgr);
	static bool Init();
	static void Destroy();

	static void * Malloc(size_t size);
	static void Free(void *ptr);
	static void * Realloc(void *ptr, size_t size);
};

void * Malloc(size_t size);
void Free(void *ptr);
void * Realloc(void *ptr, size_t size);