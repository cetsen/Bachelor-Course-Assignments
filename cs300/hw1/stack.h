#include <iostream>
using namespace std;
extern struct node;

class stack
{ 
public:
	stack::stack() //constructor
	{  
		topOfStack=NULL;
	}
	stack(const stack & rhs);
	~stack();
	void push(node *n);
	void printMaze();
	bool isEmpty() const;
	void makeEmpty();
	void pop();
	node * getNode()const;
	void pushNode(node * ptr);

private:  
	node * topOfStack; 
};




