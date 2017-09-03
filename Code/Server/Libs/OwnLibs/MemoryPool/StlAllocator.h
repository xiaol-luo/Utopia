#pragma once

#include "ShareCode/Common/Utils/MemoryUtil.h"
#include <memory>

template <typename T>
class StlAllocator : public std::allocator<T>
{
public:
	typedef size_t   size_type;
	typedef typename allocator<T>::pointer              pointer;
	typedef typename allocator<T>::value_type           value_type;
	typedef typename allocator<T>::const_pointer        const_pointer;
	typedef typename allocator<T>::reference            reference;
	typedef typename allocator<T>::const_reference      const_reference;

	pointer allocate(size_type _Count, const void* _Hint = NULL)
	{
		void *ptr = NULL;
		ptr = MemoryUtil::Malloc(sizeof(value_type) * _Count);
		return (pointer)ptr;
	}

	void deallocate(pointer _Ptr, size_type _Count)
	{
		MemoryUtil::Free(_Ptr); 
	}

	template<class _Other>
	struct rebind
	{
		typedef StlAllocator<_Other> other;
	};

	StlAllocator() throw() {}
	StlAllocator(const StlAllocator& __a) throw() : allocator<T>(__a) {}
	template<typename _Tp1> StlAllocator(const StlAllocator<_Tp1>&) throw() {}
	~StlAllocator() throw() {}
};