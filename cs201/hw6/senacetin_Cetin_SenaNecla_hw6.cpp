//Sena Necla Cetin 21120 December 18, 2016

#include <iostream>
#include <fstream> //for filestream
#include <sstream> //for istringstream
#include <string>
#include "prompt.h"
#include "strutils.h"
using namespace std;

//function prototypes:
void OpenWordPoolFile(ifstream & input1);
void OpenTextFile(ifstream & input2);
void OpenOutputFile(ofstream & output);

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


int main()
{
	ifstream input1, input2;
	ofstream output;
	OpenWordPoolFile(input1); //function is called to open word pool file
	OpenTextFile(input2); //function is called to open text file
	OpenOutputFile(output); //function is called to open output file

	string line1 = "", wordPool = "", word1, line2 = "", text="", word2; 
	//one word of the text file is compared with all the words of the word pool file to find the closest match(es):
	while(getline(input2,line2)) //the text file is traced line by line 
	{
		ToLower(line2); //letters are converted to lowercase 
		istringstream strStream(line2); //line is converted from string to stream
		while (strStream >> word2) //the lines of the text file are traced word by word
		{
			input1.clear(); //error flags are cleared
			input1.seekg(0);
			int numMatchedChars = 0, maxNumMatchedChars=0, numSimilarWords=0;
			string outputString; //the closest match(es)
			while(getline(input1,line1)) //the word pool file is traced line by line 
			{
				ToLower(line1); //letters are converted to lowercase 
				istringstream strStream(line1); //line is converted from string to stream
				while (strStream >> word1) //the lines of the word pool file are traced word by word
				{	
					if(maxNumMatchedChars <= numMatchedChars) //if the number of matched characters in the current word pool word are greater than the number of maximum number
					{										//of matched characters, than the current max number of matched characters is updated
						maxNumMatchedChars = numMatchedChars; 
					}
					numMatchedChars = 0;
					if(word1.length() == word2.length()) //the first criteria for being a match is having the same length
					{
						for(int i=0; i < word1.length(); i++) //the letters of the words are traced character by character
						{
							if(word1.at(i) == word2.at(i)) //if the characters at the same index are the same
								numMatchedChars++; //number of matched characters is increased
						}
						
						if(numMatchedChars*2 >= word1.length()  &&  numMatchedChars >= maxNumMatchedChars) //if the word is more or the same similar compared to the other words of the word pool 
						{
							if(numMatchedChars == maxNumMatchedChars && maxNumMatchedChars != 0) //if the word is the same similar with a previous word of the word pool
							{	
								numSimilarWords++; //number of similar words(close matches) are increased
								outputString += "," + word1; //a comma is put between the close matches
							}
							else if(numMatchedChars > maxNumMatchedChars) //if the number of matched characters in the current word is greater than the max number of matched characters, than the current word is the closest match
							{
								outputString = word1;
							}
							else //if it's not a match
								outputString += word1;
						}
					}
				}
				if(outputString == "") //if no matches are found throughout the word pool
				{
					outputString = "{" + word2 + "}"; //put curly brackets in front of and at the end of the word 
				}
			}
			if(numSimilarWords >= 1) //if multiple matches are found
				output << "(" << outputString << ")"; //put parantheses in front of and at the end of the matches

			else //if multiple matches are not found
				output << outputString; //print out the output string defined above

			output << " "; //put a space between words
		}
		output << endl; //put a space between lines
	}
	

	input1.close(); //all files are closed
	input2.close();
	output.close();
	cin.get();
	cin.ignore();
	return 0;
}