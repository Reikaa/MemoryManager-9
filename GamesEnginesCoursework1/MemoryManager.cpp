#include "MemoryManager.h"

MemoryManager::MemoryManager()
{
	//do nothing
}

MemoryManager::~MemoryManager()
{
	//do nothing
}

void MemoryManager::startup(const int allocatorType, const U32 totalSize, const U32 chunkSize)
{
	//Switch based on type of allocator
	switch (allocatorType)
	{
	case ALLOCATOR_TYPE_STACK:
		p_allocator = new StackAllocator(totalSize);
		break;
	case ALLOCATOR_TYPE_DE_STACK:
		p_allocator = new DEStackAllocator(totalSize);
		break;
	case ALLOCATOR_TYPE_POOL:
		p_allocator = new PoolAllocator(totalSize, chunkSize);
		break;
	}
	
	//Initialize allocator
	p_allocator->initialize();
}

MemoryManager& MemoryManager::get()
{
	//Get the singleton instance
	static MemoryManager* instance = NULL;
	if (instance == NULL)
	{
		instance = new MemoryManager();
	}
	_ASSERT(instance);
	return *instance;
}

void MemoryManager::freeAligned(void * ptr)
{
	p_allocator->freeAligned(ptr);
}

U32 MemoryManager::getFreeSize()
{
	return p_allocator->getFreeSize();
}

void MemoryManager::shutdown()
{
	delete(p_allocator);
}