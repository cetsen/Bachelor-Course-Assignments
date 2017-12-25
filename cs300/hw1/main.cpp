//Sena Necla Cetin 21120 CS300-HW1

#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

int numRows, numCols, startRow, startCol;
int ** maze;

struct node
{
	int xCoor;
	int yCoor;
	node * next;
	bool visited;
	node(const int & x, const int & y, node * n = NULL, bool v=0)
		: xCoor(x), yCoor(y), next(n), visited(v) { }
};

int input(istream& in=cin) //to get the input maze easily
{
	int x;
	in >> x;
	return x;
}

void createArray()
{
	cout << "Please enter the number of rows and columns of the maze:" << endl;
	cin >> numRows >> numCols;
	cout << "Please enter the entry point of the maze in rows and columns:" << endl;
	cin>> startRow >> startCol;

	//creates a dynamic array of given size to store the input maze
	maze = new int*[numRows];
	for (int i = 0;i<numRows;i++)
	{
		maze[i] = new int[numCols];
	}

	cout << "Please enter the maze as a matrix:" << endl;

	//loops on the input maze and fills the 2d array with this input
	for(int i=0; i<numRows; i++)    
	{
		for(int j=0; j<numCols; j++) 
		{
			maze[i][j] = input();
		}
	}
	cout << endl;

	//prints the 2d array
	for(int i=0; i<numRows; i++) 
	{
		for(int j=0; j<numCols; j++) 
		{
			cout << maze[i][j]  << " ";
		}
		cout << endl;
	}
}

void deleteArray()
{
	//deletes the dynamic array to prevent memory leak
	for (int i = 0;i<numRows;i++)
	{
		delete[] maze[i];
	}
	delete[] maze;
}

bool isBoundary(const int x,  const int y)
{
	//checks if the cell is a boundary cell
	if(x==0 || y==0 || x==numRows-1 || y ==numCols-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isEntryPoint(const int x, const int y)
{
	//checks if we are on the entry point
	if(x==startRow && y==startCol)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	createArray();

	stack path; //create the path
	node * myNode = new node(startRow, startCol);
	path.push(myNode); //push the entry point onto the stack
	int row, col;
	bool done = 0;
	row = myNode->xCoor;
	col = myNode->yCoor;

	int ** visitedCells; 
	visitedCells = new int*[numRows];
	for (int i = 0;i<numRows;i++)
	{
		visitedCells[i] = new int[numCols];
	}
	for(int i=0; i<numRows; i++)    
	{
		for(int j=0; j<numCols; j++) 
		{
			visitedCells[i][j] = 0;
		}
	}

	visitedCells[row][col]=1;

	while(!done) //while the exit hasn't been found yet
	{
		if (isBoundary(row,col) && !isEntryPoint(row,col)) //if we found the solution
		{
			done = true;
			break;
		}
		else
		{
			if (col != numCols-1) //to not exceed the limits of the maze
			{
				if (maze[row][col+1]==0 && visitedCells[row][col+1]==0) //checks the right cell
				{
					node * newNode = new node(row, col+1, path.getNode());
					visitedCells[row][col+1]=1;
					path.push(newNode);
					col++; //moves to the right cell
					continue;
				}
			}
			if (row != numRows-1) //to not exceed the limits of the maze
			{
				if (maze[row+1][col]==0 && visitedCells[row+1][col]==0) //checks the downward cell
				{
					node * newNode = new node(row+1, col, path.getNode());
					visitedCells[row+1][col]=1;
					path.push(newNode);
					row++; //moves to the downward cell
					continue;
				}
			}
			if (col != 0) //to not exceed the limits of the maze
			{
				if (maze[row][col-1]==0 && visitedCells[row][col-1]==0) //checks the left cell
				{
					node * newNode = new node(row, col-1, path.getNode());
					visitedCells[row][col-1]=1;
					path.push(newNode);
					col--; //moves to the left cell
					continue;
				}
			}
			if (row != 0) //to not exceed the limits of the maze
			{
				if (maze[row-1][col]==0 && visitedCells[row-1][col]==0) //checks the upper cell
				{
					node * newNode = new node(row-1, col, path.getNode());
					visitedCells[row-1][col]=1;
					path.push(newNode);
					row--; //moves to the upper cell
					continue;
				}
			} 
			if(!path.isEmpty()) //if we did not make it to the exit
			{
				maze[row][col] = 1; //change the last cell to "1", so that we don't visit it again(since it is the wrong path)
				path.pop(); //return to the previous cell
				continue;
			}
		}
	}

	//reverse the stack so that the output is printed in the correct order
	stack reversedPath;
	while(!path.isEmpty())
	{
		node * n = new node (path.getNode()->xCoor, path.getNode()->yCoor, NULL);
		reversedPath.pushNode(n);
		path.pop();
	}
	reversedPath.printMaze();

	//delete dynamic objects
	reversedPath.makeEmpty();
	deleteArray();

	cin.get();
	cin.ignore();
	return 0;
}