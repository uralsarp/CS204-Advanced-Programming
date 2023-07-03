#include <iostream>
#include "uralsarp_Sipahi_UralSarp_hw4_dynamicstack.h"

using namespace std;

dynamicstack::dynamicstack(){
	top=NULL;
}


//Begin: Function taken from QueenStack.cpp.
void dynamicstack::push(StackNode n)
{
	StackNode *newNode = new StackNode(n.pos); 

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}
//End: Function taken from QueenStack.cpp.


//Begin: Function taken from QueenStack.cpp.
void dynamicstack::pop(StackNode &num)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		num.pos = top->pos;
		temp = top->next;
		delete top;
		top = temp;
	}
}
//End: Function taken from QueenStack.cpp.


//Begin: Function taken from QueenStack.cpp.
bool dynamicstack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}
//End: Function taken from QueenStack.cpp.

dynamicstack::~dynamicstack(){
	StackNode * ptr = top;
	while (ptr != NULL) {
		StackNode * temp = ptr->next;
		 delete ptr;
		 ptr = temp;
	}

}