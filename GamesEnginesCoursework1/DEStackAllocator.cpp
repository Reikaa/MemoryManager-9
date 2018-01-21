#include "DEStackAllocator.h"

DEStackAllocator::DEStackAllocator(const U32 totalSize)
{
	m_totalSize = totalSize;
}

DEStackAllocator::~DEStackAllocator()
{
	reset();
	free(p_start);
}

void DEStackAllocator::initialize()
{
	p_start = malloc(m_totalSize);
	p_end = (void *)((U32)p_start + m_totalSize);
	reset();
}

void * DEStackAllocator::allocateUnaligned(const U32 size, const int side = 0)
{
	_ASSERT(side != 0 && "Side allocation must be chosen, see DEStackAllocator::START");
	_ASSERT(m_startOffset + m_endOffset + size <= m_totalSize && "Not enough space for allocation");

	U32 currentAddress;

	//Switch based on side of allocation
	switch (side)
	{
	case START:
		//Current free address at the start of stack
		currentAddress = (U32)p_start + m_startOffset;
		m_startOffset += size;
		break;

	case END:
		m_endOffset += size;
		//Current free address at the end of stack
		currentAddress = (U32)p_end - m_endOffset;
		break;
	}

	return (void*)currentAddress;
}

void * DEStackAllocator::allocateAligned(const U32 size, const U32 alignment, const int side)
{
	_ASSERT(alignment >= 1 && "Alignment must be positive");
	_ASSERT(alignment <= 256 && "Alignment must be under 256");
	_ASSERT((alignment & (alignment - 1)) == 0 && "Alignment must be a power of 2");

	//Total bytes aligned
	U32 alignedBytes = size + alignment;

	//Address without alignment returned
	void * p_rawAddress = allocateUnaligned(alignedBytes,side);

	//Compute misalignment by masking raw address with alignment - 1
	U32 misalignment = (U32)p_rawAddress & (alignment - 1);
	//Compute padding to be added
	U8 padding = alignment - misalignment;

	//Compute the aligned address by applying the padding
	U32 alignedAddress = (U32)p_rawAddress + padding;

	//The address where the amount of padding is stored is one address begind the aligned address
	U32 * p_adjustment = (U32 *)(alignedAddress - 1);

	//Store the amount of padding
	*p_adjustment = padding;

	return (void *)alignedAddress;
}

void DEStackAllocator::freeUnaligned(void * ptr, const int side)
{
	//Pop all elements until ptr
	switch (side)
	{
	case START:
		m_startOffset = (U32)ptr - (U32)p_start;
		break;
	case END:
		m_endOffset = (U32)p_end - (U32)ptr;
		break;
	}
}

void DEStackAllocator::freeAligned(void * ptr, const int side)
{
	U32 alignedAddress = (U32)ptr;

	//The address where the amount of padding is stored is one address begind the aligned address
	U8 * p_padding = (U8 *)(alignedAddress - 1);

	//Find the original unaligned address
	U32 rawAddress = alignedAddress - *p_padding;

	freeUnaligned((void *)rawAddress,side);
}

U32 DEStackAllocator::getFreeSize() //Get the remaining free size of the allocator
{
	return m_totalSize - m_startOffset - m_endOffset;
}

U32 DEStackAllocator::getTotalSize() //Get the total size of the allocator
{
	return m_totalSize;
}

void DEStackAllocator::reset() //Reset the allocator offsets
{
	m_endOffset = 0;
	m_startOffset = 0;
}