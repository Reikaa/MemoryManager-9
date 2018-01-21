#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include "Types.h"

template<typename T>
class SmartPointer
{
	//Pointer to the data
	T * p_data;
	//Pointer to the references counter
	U32 * p_refs;

public:

	SmartPointer(T * p)
	{
		p_data = p;
		p_refs = new U32();
		*p_refs = 1;
	}

	SmartPointer(const SmartPointer<T> &sp)
	{
		//Copy data and references pointers and increment references
		p_data = sp.p_data;
		p_refs = sp.p_refs;
		++*p_refs;
	}

	~SmartPointer() { clear(); }

	SmartPointer<T> * operator=(const SmartPointer<T> * sp)
	{
		if (this != sp)
		{
			//Delete current data and copy the given ones
			clear();

			p_data = sp.p_data;
			p_refs = sp.p_refs;
			++*p_refs;
		}		

		return this;
	}

	T& operator* ()
	{
		return *p_data;
	}

	T * operator-> ()
	{
		return p_data;
	}

	U32 getReferences() 
	{
		return *p_refs;
	}

	void clear()
	{
		//If there is no more references to the data free the memory through the memory manager
		if (--*p_refs == 0)
		{
			MemoryManager::get().freeAligned(p_data);
		}
	}
 
};

#endif