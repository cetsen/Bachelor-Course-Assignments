//Sena Necla Çetin		21120		 CS204L-A2			HW1			 Feb. 22, 2017

//This program performs median filtering operation on an input matrix given in a text file.

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "prompt.h"  
#include <vector>
#include <iomanip>    //for setw(4): to format the matrix
#include <algorithm>  //for CalcMatrixMedian function to calculate the median of a vector

using namespace std;

//function prototypes:
int EnterFilterSize ();
void OpenInputFile (ifstream & input);
bool IsMatrix (vector<vector<int>> mat);
void MedianFiltering (int filterSize, vector<vector<int>> mat);
double CalcMatrixMedian(vector<int> filteredMat);

int EnterFilterSize ()   //This function asks the user to enter the filter size until the entry is successful and returns the filter size.
{
	int filterSize;
	cout << "Enter the filter size (must be a positive odd integer) \n";  //the user is asked to enter the filter size
	cin >> filterSize; //the user enters the filter size

	while (cin.fail() || (filterSize <= 0 || filterSize%2 == 0)) //if the input value from the user is not an integer or not a positive odd integer
	{
		if(cin.fail()) //if the input value is not of integer type
		{
			cout << "\nError. You did not enter an integer. \n";	//display appropriate message
			cin.clear();	//clear the error state
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			cout << "Enter the filter size (must be a positive odd integer) \n";  //the user is asked to enter the filter size again
			cin >> filterSize;	  //the user enters the filter size again
		}

		else if(filterSize <= 0 || filterSize%2 == 0)   //if the input value is not a positive odd integer
		{
			cout << "\nError. Enter the filter size (must be a positive odd integer) \n";	  //display appropriate message
			cin >> filterSize;   //user enters the filter size again
		}
	}
	return filterSize;   //this function returns the filter size to later be used by the function MedianFiltering
}

void OpenInputFile (ifstream & input) //This function asks the user to enter the file name until the entry is successful.
{
	string fileName = PromptString("\nEnter the name of the file \n"); //the user enters the file name
	input.open(fileName.c_str()); //file is opened

	while (input.fail()) //if the file fails to open, this loop functions until the file name is entered correctly
	{
		cout << "\nError: Could not open the file " << fileName << endl; //error message is shown to indicate that the file name is entered incorrectly
		input.clear(); // error flags are cleared
		input.seekg(0); 
		fileName = PromptString("\nEnter the name of the file \n"); //the user reenters the file name
		input.open(fileName.c_str()); //text file is opened
	}
}

bool IsMatrix (vector<vector<int>> mat)   //This function checks if the vector called as parameter is in matrix format (if all the rows have the same number of elements/columns).
{
	int rows = mat.size();
	int cols = mat[0].size();

	//check if consecutive rows of the matrix contain the same number of elements to see if all the rows are of equal size
	for (int i=0; i < rows-1; )
	{
		if (mat[i].size() == mat[i+1].size())	//if the consecutive rows of the matrix contain same number of elements
		{
			i++;	//increment i to check if the rest of the rows consist of the same number of elements
		}
		else	//if the file is not in matrix form
		{
			cout << "Input file is not in matrix format \nProgram Exiting... \n";	//display appropriate message
			cin.get();
			cin.ignore();
			return false;		//exit program
		}
	}
	return true;
}

double CalcMatrixMedian(vector<int> filteredMat)   //This function calculates the median of a vector called as parameter(which contains the elements of a submatrix)
{
	double median;
	size_t size = filteredMat.size();  

	sort(filteredMat.begin(), filteredMat.end());  //Sort the vector from the beginning of the vector till the end 

	if (size  % 2 == 0)   //If the vector contains even number of elements
	{
		median = (filteredMat[size / 2 - 1] + filteredMat[size / 2]) / 2;   //The median is the average of the two middle elements
	}
	else   //Else if the vector contains odd number of elements
	{
		median = filteredMat[size / 2];   //The median is the element in the middle
	}

	return median;   //returns the median of the vector
}

void MedianFiltering (int filterSize, vector<vector<int>> mat)	 //This function does median filtering of a matrix, given the filter size and the matrix.
{
	int rowSize = mat.size();
	int colSize = mat[0].size();
	vector<int> filteredMat;	//the submatrix of an element in the matrix stored as a vector(in order to be able to sort it later in CalcMatrixMedian to find its median)
	int boundary = filterSize/2;	//the interval allowed for the element (if the element is on the border, in the corner, etc.) 
	int temp;  //the element in the matrix to be added to the filteredMat vector

	for (int row = 0; row < rowSize; row++)   //traversing the rows starting from the 0th
	{
		for (int col = 0; col < colSize; col++)		//traversing the columns starting from the 0th
		{
			filteredMat.clear();   //after printing out the median for the previous submatrix, delete it so that a new submatrix can be formed
			for (int i = -boundary; i <= boundary; i++)    //traversing elements in the boundary limits in the submatrix for the rows
			{
				for (int j = -boundary; j <= boundary; j++)  //traversing elements in the boundary limits in the submatrix for the colums
				{
					if ( (row + i >= 0) && (col + j >= 0)  && (row + i < rowSize) && (col + j < colSize) )   //if the submatrix element is inside the matrix
					{
						temp = mat[row+i][col+j];    
						filteredMat.push_back(temp);   //add it to the filteredMat matrix which contains the submatrix elements
					}
				}
			}
			cout << setw(4) << CalcMatrixMedian(filteredMat) << " ";   //call the CalcMatrixMedian function to print the median of the submatrix
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	cout << "This program performs median filtering operation \non an input matrix given in a text file \n\n";		//opening message is displayed

	ifstream input; 
	int filterSize = EnterFilterSize();		//EnterFilterSize function is called 
	OpenInputFile(input);	//OpenInputFile function is called

	vector<vector<int>> mat;	//a matrix is created to store the values from the input file
	string line;	//the lines of the file
	bool flag = 1;   //to check if there is any error(invalid(non-integer) characters) while reading the elements of the file

	while( !input.eof() && flag )		//while it is not yet the end of the file(there are lines to read) and there are no errors(no invalid characters)
	{
		getline(input, line);	//get lines of the function
		stringstream ss(line);	//convert lines from string to stream

		int num;   //integer values inside the matrix
		vector<int> temp;	//a temporary vector is created to later push back the value inside it to the storage matrix

		while(ss >> num)   //getting numbers from the file
		{
			if(num >= 0 && num <= 255)     //if numbers are in the range [0,255]
			{
				temp.push_back(num);		//push back the vector to contain the value
			}
			else if (num < 0 || num > 255)		//else if the number is not in range
			{
				cout << "Pixel with value: " << num << " is not in range [0, 255] \nProgram Exiting...\n";		//display appropriate error message
				cin.get();
				cin.ignore();
				return 0;		//exit program
			}
		}

		if ( ss.fail() && !ss.eof() )  //if there are invalid characters in the file
		{ 
			flag = 0;   //change the value of boolean flag to 0
		}
		else   //if there are no invalid characters found
		{
			mat.push_back(temp);	//when the end of the line is reached, push back the values from the temporary vector to the matrix

		}
	}

	if (flag)	 //if no invalid characters are found
	{
		if(IsMatrix (mat))		//IsMatrix function is called to check if the elements are in matrix format.  If they are in matrix format,
		{
			cout << "\n\nFILTERED MATRIX \n\n";
			MedianFiltering (filterSize, mat);		//MedianFiltering function is called to do median filtering and to display the filtered matrix.
		}
	}
	else	//if invalid characters are found in the file
	{
		cout << "\nError: Input file contains invalid characters \nProgram Exiting...";   //display appropriate message
	}

	input.close();		//input file is closed
	cin.get();
	cin.ignore();
	return 0;
}