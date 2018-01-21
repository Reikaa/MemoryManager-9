#ifndef D_E_STACK_ALLOCATOR
#define D_E_STACK_ALLOCATOR

#include "Types.h"
#include "Allocator.h"
#include <stdlib.h>
#include <iostream>

class DEStackAllocator : public Allocator
{
	//Pointer to the start of the allocator
	void * p_start = NULL;
	//Pointer to the end of the allocator
	void * p_end = NULL;

	//Amount that has been used in each side of the stack
	U32 m_startOffset, m_endOffset;

public:
	
	//Constants use to choose side of allocation
	static const int START = 1;
	static const int END = 2;

	explicit DEStackAllocator(const U32 totalSize);

	~DEStackAllocator();

	void initialize();

	void * allocateUnaligned(const U32 size, const int side);

	void * allocateAligned(const U32 size, const U32 alignment, const int side = 0);

	void freeUnaligned(void * ptr, const int side);

	void freeAligned(void * ptr, const int side);

	U32 getFreeSize();

	U32 getTotalSize();

	void reset();

};

#endif