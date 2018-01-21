#include <iostream>
#include <vector> // for testing
#include "StackAllocator.h"
#include "DEStackAllocator.h"
#include "PoolAllocator.h"
#include "SmartPointer.h"
#include "MemoryManager.h"

void testStack()
{

	//-----	STACK ALLOCATOR -----//

	//Memory manager initialization
	MemoryManager::get().startup(MemoryManager::ALLOCATOR_TYPE_STACK, 64);

	//Normal allocation case 
	SmartPointer<U32> spStack = MemoryManager::get().allocateAligned<U32>(12);
	
	//Automatic free case
	{
		SmartPointer<U32> spStack1 = MemoryManager::get().allocateAligned<U32>(16);
	}

	//Not enough space case
	//MemoryManager::get().startup(MemoryManager::ALLOCATOR_TYPE_STACK, 4);
	//spStack = MemoryManager::get().allocateAligned<U32>(16);

	//Stress case
	MemoryManager::get().startup(MemoryManager::ALLOCATOR_TYPE_STACK, 2000000);
	std::vector<SmartPointer<U32>> v;
	for (int i = 0; i < 100000; i++)
	{
		v.push_back(MemoryManager::get().allocateAligned<U32>(16));
	}
}

void testDEStack()
{
	//----- DOUBLE ENDED STACK ALLOCATOR -----//

	//Memory manager initialization
	MemoryManager::get().startup(MemoryManager::ALLOCATOR_TYPE_DE_STACK, 128);

	//Normal allocation case
	SmartPointer<U32> spStart = MemoryManager::get().allocateAligned<U32>(16, DEStackAllocator::START);
	SmartPointer<U32> spEnd = MemoryManager::get().allocateAligned<U32>(16, DEStackAllocator::END);

	//Automatic free case
	{
		SmartPointer<U32> spStack1 = MemoryManager::get().allocateAligned<U32>(16, DEStackAllocator::START);
	}

	//Not enough space case
	//MemoryManager::get().startup(MemoryManager::ALLOCATOR_TYPE_STACK, 4);
	//spStack = MemoryManager::get().allocateAligned<U32>(16, DEStackAllocator::START);

	//Stress case
	MemoryManager::get().startup(MemoryManager::ALLOCATOR_TYPE_DE_STACK, 2000000);
	std::vector<SmartPointer<U32>> v;
	for (int i = 0; i < 100000; i++)
	{
		if(i % 2 == 0)	v.push_back(MemoryManager::get().allocateAligned<U32>(16,DEStackAllocator::START));
		else v.push_back(MemoryManager::get().allocateAligned<U32>(16, DEStackAllocator::END));
	}

}

void testPool()
{
	//----- POOL ALLOCATOR -----//

	//Memory Manager initialization
	MemoryManager::get().startup(MemoryManager::ALLOCATOR_TYPE_POOL, 400, 16);

	//Normal allocation case
	SmartPointer<U32> spPool = MemoryManager::get().allocateAligned<U32>(16);

	//Automatic free case
	{
		SmartPointer<U32> spStack1 = MemoryManager::get().allocateAligned<U32>(16);
	}

	//Not enough space case
	//MemoryManager::get().startup(MemoryManager::ALLOCATOR_TYPE_POOL, 16, 16);
	//SmartPointer<U32> spPool1 = MemoryManager::get().allocateAligned<U32>(16);
	//SmartPointer<U32> spPool2 = MemoryManager::get().allocateAligned<U32>(16);

	//Stress case
	MemoryManager::get().startup(MemoryManager::ALLOCATOR_TYPE_POOL, 2000000,16);
	std::vector<SmartPointer<U32>> v;
	for (int i = 0; i < 100000; i++)
	{
		v.push_back(MemoryManager::get().allocateAligned<U32>(16));
	}
}

int main()
{
	testStack();
	//testDEStack();
	//testPool();

	return 0;
}


