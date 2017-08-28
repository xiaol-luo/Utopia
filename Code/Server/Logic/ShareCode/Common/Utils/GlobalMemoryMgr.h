#pragma once

#include "MemoryPool/MemoryPoolMgr.h"

extern MemoryPoolMgr *global_memory_pool;

void InitGlobalMemoryPool();
void DestoryGlobalMemoryPool();

void *Malloc(size_t size);
void Free(void *ptr);
void *Realloc(void *ptr, size_t size);

