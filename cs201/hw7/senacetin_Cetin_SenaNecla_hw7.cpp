//Sena Necla Cetin 21120 December 30, 2016

#include <iostream>
#include <fstream> //for filestream
#include <sstream> //for istringstream
#include <string>
#include "prompt.h"
#include "strutils.h"
#include <vector>
using namespace std;

struct word //creating a struct to encapsulate data of one word from the word pool
{
	string wordString; //the word itself
	int correct; //number of times it is spelled correctly
	int typo; //number of times it is spelled with typo(s)
	int total; //sum of correct and typo
};

struct poolMatchingResult //creating a struct to compare matches to make sure the counters of only the "best" match is incremented and not every close match
{
	int index; //index of the pool word
	int match; //number of same character matches
};

//function prototypes:
void OpenWordPoolFile(ifstream & input1);
void OpenTextFile(ifstream & input2);
void OpenOutputFile(ofstream & output);
void Swap(vector<word> & v,int j, int k);
void BubbleSort(vector<word> & a, int n);
void Swap(vector<poolMatchingResult> & v,int j, int k);
void BubbleSort(vector<poolMatchingResult> & a, int n);
void BubbleSortAlphabetically(vector<word> & a, int n);

void OpenWordPoolFile(ifstream & input1) //opens the word pool file
{
	string wordPoolFileName = PromptString("Please enter a filename for the word pool: "); //the user enters the name of the word pool file
	input1.open(wordPoolFileName.c_str()); //word pool file is opened

	while (input1.fail()) //if the word pool file fails to open
	{
		cout << "Cannot open the word pool file." << endl;
		input1.clear(); // error flags are cleared
		input1.seekg(0); 
		wordPoolFileName = PromptString("Please enter a filename for the word pool: "); //the user reenters the name of the word pool file
		input1.open(wordPoolFileName.c_str()); //text file is opened
	}
}
void OpenTextFile(ifstream & input2) //opens the text file
{
	string mainTextFileName = PromptString("Please enter a filename for the main text: "); //the user enters the name of the text file
	input2.open(mainTextFileName.c_str()); //text file is opened

	while (input2.fail())  //if the text file fails to open
	{
		cout << "Cannot open the main text file." << endl;
		input2.clear(); //error flags are cleared
		input2.seekg(0);
		mainTextFileName = PromptString("Please enter a filename for the main text: "); //the user reenters the name of the text file
		input2.open(mainTextFileName.c_str()); //text file is opened
	}
}
void OpenOutputFile(ofstream & output) //opens the output file
{
	string outputFileName = PromptString("Please enter a filename for the output file: "); //the user enters the name of the output file
	output.open(outputFileName.c_str()); //output file is opened
	cout << "You may find the results in " << outputFileName; 
}
void BubbleSort(vector<word> & a, int n) ////bubble sort for the vector of the struct word
	// precondition: n = # of elements in a
	// postcondition: a is sorted
	//                note: this is a dog of a sort     
{
	int j,k;
	for(j=n-1; j > 0; j--)
	{
		// find largest element in 0..k, move to a[j]
		for(k=0; k < j; k++)
		{
			if (a[k+1].total < a[k].total) //number of total matches are compared to list in the correct order in the output
			{
				Swap(a,k,k+1);
			}
		}	
	}
}
void BubbleSort(vector<poolMatchingResult> & a, int n) //bubble sort for the vector of the struct poolMatchingResult
	// precondition: n = # of elements in a
	// postcondition: a is sorted
	//                note: this is a dog of a sort     
{
	int j,k;
	for(j=n-1; j > 0; j--)
	{
		// find largest element in 0..k, move to a[j]
		for(k=0; k < j; k++)
		{
			if (a[k+1].match < a[k].match) //number of character matches are compared; if smaller, then swap
			{
				Swap(a,k,k+1);
			}
		}	
	}
}
void Swap(vector<word> & v,int j, int k)
	// precondition:  v[j] references value A, v[k] references value B 
	// postcondition: v[k] references value B, v[k] references value A 
{
	word temp = v[j];
	v[j] = v[k];
	v[k] = temp;
}
void Swap(vector<poolMatchingResult> & v,int j, int k)
	// precondition:  v[j] references value A, v[k] references value B 
	// postcondition: v[k] references value B, v[k] references value A 
{
	poolMatchingResult temp = v[j];
	v[j] = v[k];
	v[k] = temp;
}
void BubbleSortAlphabetically(vector<word> & a, int n) //alphabetical bubble sort to sort the list alphabetically if the total numbers are equal
	// precondition: n = # of elements in a
	// postcondition: a is sorted
	//                note: this is a dog of a sort     
{
	int j,k;
	for(j=n-1; j > 0; j--)
	{
		// find largest element in 0..k, move to a[j]
		for(k=0; k < j; k++)
		{
			if (a[k+1].wordString > a[k].wordString && a[k+1].total == a[k].total  )
			{
				Swap(a,k,k+1);
			}
		}	
	}
}

int main()
{
	ifstream wordPoolInput, textInput; 
	ofstream output;
	OpenWordPoolFile(wordPoolInput); //function is called to open word pool file
	OpenTextFile(textInput); //function is called to open text file
	OpenOutputFile(output); //function is called to open output file
	vector<word> wordPool;
	string wordPoolLine = "", poolWord, textLine = "", textWord; 

	while(getline(wordPoolInput,wordPoolLine)) //getting the word pool file line by line
	{
		ToLower(wordPoolLine); //converting the word pool to lower case
		istringstream strStream(wordPoolLine); //converting the word pool file from string to stream
		while (strStream >> poolWord) //getting the word pool file word by word
		{	
			word w; //creating the struct word object w
			w.wordString=poolWord; //word pool string
			w.typo=0; //initialize number of typo matches to 0
			w.correct=0; //initialize number of correct matches to 0
			w.total=0; //initialize number of total matches to 0
			wordPool.push_back(w); //push back the size of the vector as we get a new element in the vector
		}
	}

	textInput.clear(); //error flags are cleared
	textInput.seekg(0);
	while(getline(textInput,textLine)) //the text file is traced line by line 
	{
		ToLower(textLine); //letters are converted to lowercase 
		istringstream strStream(textLine); //line is converted from string to stream
		while (strStream >> textWord) //the lines of the text file are traced word by word
		{
			vector <poolMatchingResult> numberOfMatchCharsList; //creating a vector of the struct poolMatchingResult 
			for(int i=0; i < wordPool.size(); i++) //tracing the word pool file word by word
			{
				string poolWordTemp=wordPool[i].wordString; //current word in the vector of word pool words
				int numMatchedChars = 0; //initially, no chars are matched
				if(poolWordTemp == textWord) //if the word pool word is the same as the text word
				{
					wordPool[i].correct++; //increment correct
					wordPool[i].total++; //increment total
				}
				if(poolWordTemp.length() == textWord.length() && poolWordTemp != textWord) //the first criteria for being a match is having the same length
				{
					for(int k=0; k < poolWordTemp.length(); k++) //the letters of the words are traced character by character
					{
						if(poolWordTemp.at(k) == textWord.at(k)) //if the characters at the same index are the same
							numMatchedChars++; //number of matched characters is increased
					}

					if(numMatchedChars*2 >= poolWordTemp.length()) //if at least half of the words are the same
					{
						poolMatchingResult result; //create vector of matching results
						result.index=i; 
						result.match=numMatchedChars;
						numberOfMatchCharsList.push_back(result); //push back to create the needed size of vector
					}
				}
			}
			if(numberOfMatchCharsList.size()>0) //if there exists a matching word create the vector of matching words
			{
				vector<poolMatchingResult> tempResult=numberOfMatchCharsList;
				BubbleSort(tempResult, tempResult.size()); //order the words by their "total" number
				for(int j=0; j<numberOfMatchCharsList.size(); j++) 
				{
					if(tempResult[tempResult.size()-1].match==numberOfMatchCharsList[j].match) //if the number of matches match
					{
						wordPool[numberOfMatchCharsList[j].index].typo++; //increment typo
						wordPool[numberOfMatchCharsList[j].index].total++; //increment total
					}
				}
			}
		}
	}

	BubbleSort(wordPool, wordPool.size()); //bubble sort the word pool
	BubbleSortAlphabetically(wordPool,wordPool.size()); //bubble sort the word pool alphabetically after sorting by "total"
	if(wordPool.size() > 0) //if the size of the word pool is greater than zero
	{
		output << "RANK,WORD,CORRECT,TYPO,TOTAL" << endl; //print 
		for(int i=wordPool.size()-1; i >= 0; i--) //print out the results in reverse order since bubble sort sorts by ascending order and we want to have descending order
		{
			output << wordPool.size()-i << "," << wordPool[i].wordString << "," << wordPool[i].correct << "," << wordPool[i].typo << "," << wordPool[i].total << endl;
		}
	}

	wordPoolInput.close(); //all files are closed
	textInput.close();
	output.close();
	cin.get();
	cin.ignore();
	return 0;
}
