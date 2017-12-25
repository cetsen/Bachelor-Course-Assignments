//Sena Necla Çetin 21120	CS201L-A2	HW5		April 16, 2017

#include <iostream>
#include "Plot.h"
using namespace std;

Plot::Plot() //default constructor
{
	size = 0;
	arrayptr = new Point[size];
}

Plot::Plot(int number) //constructor: constructs a plot with the given size
{
	size = number;
	arrayptr = new Point[size];
} 

Plot::~Plot()  //destructor: deallocates arrayptr 
{
	delete [] arrayptr;
	arrayptr = NULL;
	size = 0;
}

void Plot::deleteAll()  //deletes dynamic array, called in the function operator=
{
	delete[] arrayptr;
	arrayptr = NULL;
	size = 0;
}

Plot::Plot(const Plot & plot)  //deep copy constructor: calls createClone to create a deep copy of arrayptr
{
	createClone(plot);
}

void Plot::createClone(const Plot & plot)  //creates a deep copy of the object, used in the operator= 
{
	if(plot.arrayptr == NULL)
	{
		size = NULL;
		arrayptr = NULL;
	}
	else
	{
		size = plot.size;
		arrayptr = new Point[size];
		for(int i=0; i<size; i++)
		{
			arrayptr[i] = plot.arrayptr[i];
		}
	}
}

Plot & Plot::operator = (const Plot & rhs)  //assigns the Plot object on the rhs of the operator to the Plot object on the lhs
{
	if (this != &rhs)
	{
		deleteAll();
		createClone(rhs);
	}

	return *this;
}

bool Plot::operator == (const Plot & rhs) //checks two Plot objects for equality; returns true if they are identical, otherwise returns false 
{
	if (size == rhs.size)
	{
		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				if(arrayptr[i].x != rhs.arrayptr[j].x || arrayptr[i].y != rhs.arrayptr[j].y)
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

const Plot & Plot::operator += (const Plot & rhs)  //adds two Plot objects and assigns the resulting Plot object to the Plot object on the lhs of the operator
{
	for(int i=0; i<rhs.size; i++)
	{
		arrayptr[i].x += rhs.arrayptr[i].x;
		arrayptr[i].y += rhs.arrayptr[i].y;
	}
	return *this;
}

Plot Plot::operator - (const Point & point)   //removes a certain point from the Plot object if that point exists in the plot, and returns the resulting plot
{
	int subtractedindex=-1;

	for(int i=0; i<size; i++)  //search for the point inside the array
	{
		if(arrayptr[i].x != point.x && arrayptr[i].y != point.y)
		{
			subtractedindex = i;
		}
	}

	if(subtractedindex != -1)
	{
		Plot newP(size-1);
		for(int j=0; j<subtractedindex; j++)  //create new array with the resulting points
		{
			newP.arrayptr[j] = point;
		}
		for(int k=subtractedindex; k<size; k++)
		{
			newP.arrayptr[k] = arrayptr[k];
		}
		return newP;
	}
	else  //if no elements are deleted, return the plot itself
	{
		return *this;
	}
}

Plot & Plot::operator -= (const Point & rhs)  //subtracts a Point from the plot and assigns the result
{

	*this = *this - rhs;
	return *this;
}

int Plot::GetSize()  //returns the private member size
{
	return size;
}

Point Plot:: GetIndexedPoint(int index) const
{
	return arrayptr[index];
}

int Plot::FindXIndex(const Point & point) const //returns the index of the Point "point" in the plot
{
	for(int i=0; i<size; i++)
	{
		if(arrayptr[i].x == point.x)
			return i;
	}
	return -1; //if there is no x that's the same, returns -1
}

Plot Plot::operator + (const Point & point)  //adds point to plot in a sorted manner
{
	int xIndex = FindXIndex(point);
	if(xIndex!=-1) 
	{
		Plot newPlot(*this);
		newPlot.arrayptr[xIndex].y=(point.y + newPlot.arrayptr[xIndex].y)/2;
		return newPlot;
	}
	else
	{
		Plot newPlot(size+1);

		if(newPlot.size == 1)  //if the plot was initially empty
		{
			newPlot.arrayptr[0] = point;
		}
		else //if the plot wasn't empty, adds the point in a sorted manner
		{
			int middleIndex=0;
			bool flag = true;
			for(int i=0; i<size && flag; i++) 
			{
				if(arrayptr[i].x > point.x)
				{
					middleIndex = i;
					flag=false;
				}
			}

			for(int j=0; j<middleIndex; j++)
			{
				newPlot.arrayptr[j] = arrayptr[j];
			}

			newPlot.arrayptr[middleIndex] = point;

			for(int k=middleIndex+1; k<size+1; k++)
			{
				newPlot.arrayptr[k] = arrayptr[k-1];
			}
		}
		return newPlot;
	}
}