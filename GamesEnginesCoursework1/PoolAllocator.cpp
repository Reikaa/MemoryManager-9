#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(const U32 totalSize, const U32 chunkSize)
{
	_ASSERT(chunkSize <= totalSize && "Total size must be larger or equal to chunk size");
	_ASSERT(totalSize % chunkSize == 0 && "Total size must be a multiple of chunk size");

	m_totalSize = totalSize;
	m_chunkSize = chunkSize;
}

PoolAllocator::~PoolAllocator()
{
	reset();
	free(p_start);
}

void PoolAllocator::initialize()
{
	p_start = malloc(m_totalSize);
	reset();
}

void * PoolAllocator::allocateAligned(const U32 size, const U32 alignment, const int side)
{
	_ASSERT(m_chunkSize == alignment && "Alignment must be equal to chunk size");
	_ASSERT(m_chunksList.getHead() != NULL && "Not enough space for allocation");

	//Current free chunk of pool
	LinkedList::Node * freeChunk = m_chunksList.getAndDeleteStart();

	//Reduce the number of free chunks
	--m_freeChunksNum;

	return (void *)freeChunk;
}

void PoolAllocator::freeAligned(void * ptr, const int side)
{
	//Add the chunk to the list of free chunks
	m_chunksList.insertStart((LinkedList::Node *) ptr);

	//Increase the number of free chunks
	++m_freeChunksNum;
}

U32 PoolAllocator::getFreeSize()	//Get the remaining free size of the allocator
{
	return m_freeChunksNum * m_chunkSize;
}

U32 PoolAllocator::getTotalSize()	//Get the total size of the allocator
{
	return m_totalSize;
}

void PoolAllocator::reset()
{
	//Compute the number of chunks
	m_chunksNum = m_totalSize / m_chunkSize;
	m_freeChunksNum = m_chunksNum;

	//Add each chunk to the linked list
	for (int i = 0; i < m_chunksNum; i++)
	{
		U32 chunkAddress = (U32)p_start + i * m_chunkSize;
		m_chunksList.insertStart((LinkedList::Node *)chunkAddress);
	}
}