#pragma once

#include <vector>
#include "Common/Macro/MemoryPoolMacro.h"
#include "Common/Utils/MemoryUtil.h"
#include "MemoryPool/StlAllocator.h"

class IAutoReleaseObject
{
	NewDelDeclarationForTemplate
public:
	IAutoReleaseObject() {}
	virtual ~IAutoReleaseObject() {}
};

template <typename T>
class AutoReleaseObject : public IAutoReleaseObject
{
	NewDelDeclarationForTemplate;
public:
	AutoReleaseObject(T *_ptr) : ptr(_ptr) {}
	virtual ~AutoReleaseObject() 
	{ 
		if (nullptr != ptr)
			delete ptr; 
	}

protected:
	T *ptr;
};

class AutoReleaseUtil
{
public:
	AutoReleaseUtil() {}
	~AutoReleaseUtil()
	{
		for (IAutoReleaseObject *aro : m_ptrs)
		{
			delete aro;
		}
		m_ptrs.clear();
	}

	template <typename T>
	void Add(T *obj)
	{
		IAutoReleaseObject *aro = new AutoReleaseObject<T>(obj);
		m_ptrs.push_back(aro);
	}

	std::vector<IAutoReleaseObject *, StlAllocator<IAutoReleaseObject *>> m_ptrs;
};


