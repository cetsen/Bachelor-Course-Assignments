#include <iostream>
#include "stack.h"
using namespace std;

struct node
{
	int xCoor;
	int yCoor;
	node * next;
	bool visited;
	node(const int & x, const int & y, node * n = NULL, bool v=0)
		: xCoor(x), yCoor(y), next(n), visited(v) { }
};

stack::~stack() //destructor
{
	makeEmpty();
}

void stack::push(node * ptr)
{
	topOfStack = ptr;
}

void stack::pushNode(node * ptr) //pushes and connects the nodes 
{
	node * temp = ptr;
	temp->next = topOfStack;
	topOfStack = temp;
}

void stack::pop() 
{
	if(isEmpty())
		return;

	node * oldTop = topOfStack;
	topOfStack = topOfStack->next;
	delete oldTop;
}

bool stack::isEmpty() const
{
	return topOfStack == NULL;
}

void stack::makeEmpty( )
{
	while(!isEmpty())
		pop();
}

node * stack::getNode() const
{
	if(isEmpty())
		return NULL;
	return topOfStack;
}

void stack::printMaze()  
{
	cout << endl << "The solution to the puzzle is:" << endl;
	node * ptr = topOfStack;
	while(ptr != NULL)
	{ 
		cout << ptr->xCoor << " " << ptr->yCoor << endl;
		ptr=ptr->next;
	}	
}












