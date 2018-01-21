#include "LinkedList.h"

LinkedList::LinkedList()
{

}

LinkedList::~LinkedList()
{

}

void LinkedList::insertStart(Node * node)
{
	//Add the current head to new node
	node->next = head;
	//Make new node the head
	head = node;
}

LinkedList::Node * LinkedList::getAndDeleteStart()
{
	_ASSERT(head != NULL && "Cannot access empty list");
	Node * start = head;
	//Make head the next node
	head = head->next;

	return start;
}

bool LinkedList::contains(void * ptr)
{
	Node * current = head;
		
	while(current != NULL)
	{
		if (current == ptr) return true;
		current = head->next;
	} 

	return false;
}