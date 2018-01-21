#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Types.h"

class Allocator	//Abstract allocator class
{

protected:

	U32 m_totalSize;

public:

	Allocator() { };

	~Allocator() { };

	virtual void initialize() = 0;

	virtual void * allocateAligned(const U32 size, const U32 alignment, const int side = 0) = 0;

	virtual void freeAligned(void * ptr, const int side = 0) = 0;

	virtual U32 getFreeSize() = 0;

	virtual U32 getTotalSize() = 0;

};

#endif