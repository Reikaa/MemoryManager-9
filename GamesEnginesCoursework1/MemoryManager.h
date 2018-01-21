#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "StackAllocator.h"
#include "DEStackAllocator.h"
#include "PoolAllocator.h"
#include "SmartPointer.h"
#include <iostream>

class MemoryManager
{
	//Pointer to the current allocator
	Allocator * p_allocator;

public:

	//Constants use to choose type of allocator
	static const int ALLOCATOR_TYPE_STACK = 1;
	static const int ALLOCATOR_TYPE_DE_STACK = 2;
	static const int ALLOCATOR_TYPE_POOL = 3;

	MemoryManager();

	~MemoryManager();

	void startup(const int allocatorType, const U32 totalSize, const U32 chunkSize = 0);

	static MemoryManager& get();

	template<typename T> SmartPointer<T> allocateAligned(const U32 alignment, const int side = 0)
	{
		//Allocate using the current allocator and return the smart pointer
		SmartPointer<T> sp((T*)p_allocator->allocateAligned(sizeof(T), alignment,side));

		if (((float)(p_allocator->getFreeSize())) / ((float)(p_allocator->getTotalSize())) < 0.05)
		{
			//LOG: WARNING Memory below 5%
		}

		return sp;
	};

	void freeAligned(void * ptr);

	U32 getFreeSize();

	void shutdown();
};


#endif