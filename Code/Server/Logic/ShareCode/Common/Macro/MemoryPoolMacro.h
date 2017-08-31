#pragma once

#define NewDelOperaDeclaration			\
public:									\
	void * operator new(size_t size);	\
	void operator delete(void *ptr);	\
	void * operator new[](size_t size); \
	void operator delete[](void *ptr)

#define NewDelOperaImplement(class_name) \
void * class_name::operator new(size_t size) {	return MemoryUtil::Malloc(size); } \
void class_name::operator delete(void *ptr) { MemoryUtil::Free(ptr); } \
void * class_name::operator new[](size_t size) { return MemoryUtil::Malloc(size); } \
void class_name::operator delete[](void *ptr) { MemoryUtil::Free(ptr); } 
