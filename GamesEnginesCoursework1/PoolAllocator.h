#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include "Types.h"
#include "Allocator.h"
#include "LinkedList.h"
#include <stdlib.h>
#include <iostream>

class PoolAllocator : public Allocator
{
	//Pointer to the start of the allocator
	void * p_start = NULL;

	//Size of each chunk
	U32 m_chunkSize;

	//Linked list used to store chunks
	LinkedList m_chunksList;
	
	//Number of total and free chunks
	int m_freeChunksNum,m_chunksNum;

public: 

	PoolAllocator(const U32 totalSize, const U32 chunkSize);

	~PoolAllocator();

	void initialize();

	void * allocateAligned(const U32 size, const U32 alignment, const int side = 0);

	void freeAligned(void * ptr, const int side = 0);

	U32 getFreeSize();

	U32 getTotalSize();

	void reset();
};

#endif