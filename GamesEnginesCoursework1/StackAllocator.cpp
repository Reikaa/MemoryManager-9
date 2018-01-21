#include "StackAllocator.h"

StackAllocator::StackAllocator(const U32 totalSize)
{
	m_totalSize = totalSize;
}

StackAllocator::~StackAllocator()
{
	reset();
	free(p_start);
}

void StackAllocator::initialize()
{
	p_start = malloc(m_totalSize);
	reset();
}

void * StackAllocator::allocateUnaligned(const U32 size)
{
	_ASSERT(m_offset + size <= m_totalSize && "Not enough space for allocation");

	//Current free address of stack
	const U32 currentAddress = (U32)p_start + m_offset;

	//Increase offset
	m_offset += size;

	return (void *)currentAddress;

}

void * StackAllocator::allocateAligned(const U32 size,const U32 alignment, const int side)
{
	_ASSERT(alignment >= 1 && "Alignment must be positive");
	_ASSERT(alignment <= 256 && "Alignment must be under 256");
	_ASSERT((alignment & (alignment - 1)) == 0 && "Alignment must be a power of 2");

	//Total bytes aligned
	U32 alignedBytes = size+alignment;

	//Address without alignment returned
	void * p_rawAddress = allocateUnaligned(alignedBytes);

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

void StackAllocator::freeUnaligned(void * ptr)
{
	//Pop all elements until ptr
	m_offset = (U32) ptr - (U32) p_start;
}

void StackAllocator::freeAligned(void * ptr, const int side)
{
	U32 alignedAddress = (U32)ptr;

	//The address where the amount of padding is stored is one address begind the aligned address
	U8 * p_padding = (U8 *) (alignedAddress - 1);

	//Find the original unaligned address
	U32 rawAddress = alignedAddress - *p_padding;

	freeUnaligned((void *)rawAddress);
}

U32 StackAllocator::getFreeSize()	//Get the remaining free size of the allocator
{
	return m_totalSize - m_offset;
}

U32 StackAllocator::getTotalSize()	//Get the total size of the allocator
{
	return m_totalSize;
}

void StackAllocator::reset()	//Reset the allocator offset
{
	m_offset = 0;
}

