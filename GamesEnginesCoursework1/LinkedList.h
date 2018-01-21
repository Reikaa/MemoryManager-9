#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream> //For NULL

class LinkedList
{

public:

	struct Node
	{
		Node *next;
	};

	LinkedList();

	~LinkedList();

	void insertStart(Node * node);
	
	Node * getAndDeleteStart();

	Node * getHead() { return head; };

	bool contains(void * ptr);

private:

	Node *head;

};

#endif