#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H	

#include "Types.h"
#include "Allocator.h"
#include <stdlib.h>
#include <iostream>

class StackAllocator : public Allocator 
{
	//Pointer to the start of the allocator
	void * p_start = NULL;

	//Amount that has been used in the allocator
	U32 m_offset;

public:

	explicit StackAllocator(const U32 totalSize);

	~StackAllocator();

	void initialize();

	void * allocateUnaligned(const U32 size);

	void * allocateAligned(const U32 size, const U32 alignment, const int side = 0);

	void freeUnaligned(void * ptr);

	void freeAligned(void * ptr, const int side = 0);

	U32 getFreeSize();

	U32 getTotalSize();

	void reset();

};

#endif
