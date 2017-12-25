//Sena Necla Çetin 21120	CS201L-A2	HW4		March 18, 2017

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "dynintstack.h"
using namespace std;

void OpenFile(istream & input);
void ReadFile (ifstream & input, DynIntStack & d);
void DeleteAll (DynIntStack & d);

/* This function opens the input file.  If the input file fails to open, an error message is displayed and the user 
is asked to enter the file name until the file is successfully opened. */
void OpenFile (ifstream & input)
{
	string fileName;
	cout << "\nEnter the input file name\n";
	cin >> fileName;
	input.open(fileName.c_str());
	while (input.fail())
	{
		input.clear(); // error flags are cleared
		input.seekg(0); 
		cout << "Could not open file " << fileName << endl;
		cin >> fileName;
		input.open(fileName.c_str());
	}
	cout << endl;
}

/* This function reads the file char by char and does appropriate stack operations according to the condition. */
void ReadFile (ifstream & input, DynIntStack & d)
{
	OpenFile(input);
	string line;
	char ch;
	int dummyValue=5, currentLine=1;

	while (!input.eof())
	{
		while (input.get(ch))
		{
			if(ch == '\n')		//if the char is '\n', increment line number
			{
				currentLine++;
			}
			else if (ch == '{')		//if the char is '{', push the line number into the stack
			{
				d.push(currentLine);
			}
			else if (ch == '}')			
			{
				if (d.isEmpty())   //if the char is '} and the stack is empty (unmatched '}' condition), display syntax error message.
				{
					cout << "Syntax error in line " << currentLine << endl;    
					return;
				}
				else	 //if the char is '{' and the stack is not empty, pop the top line number out of the stack and display the code block
				{
					d.pop(dummyValue);
					cout << "Code block: " << dummyValue << " - " << currentLine << endl;
				}
			}
		}
	}
	if(!d.isEmpty())   //if after reading the file, the stack is still not empty (unmatched '{' condition), display error message
	{
		cout << "Syntax error at the end of the program" << endl;
	}
}

/* This function deletes all the remaining data in the stack. Called just before the program terminates. */
void DeleteAll (DynIntStack & d)
{
	int dummy=3;
	while (!d.isEmpty())
	{
		d.pop(dummy);
	}
}

int main()
{
	ifstream input;
	DynIntStack d;
	ReadFile(input, d);
	DeleteAll(d);
	cout << "Press any key to continue..." << endl;

	cin.get();
	cin.ignore();
	return 0;
}
