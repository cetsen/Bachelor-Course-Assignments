// Sena Necla Çetin 21120 CS201R-B5 November 18, 2016

#include <string>
#include <iostream>
#include "strutils.h"
using namespace std;

//function prototypes:
bool InputCharCheckForWordPool(string & s);
bool EnglishCharCheck(string & substring);
bool InputCheckAnalyzedWords(string & wordToBeAnalyzed);
string GetWordPool (string & wordPool, string & word);
bool ProcessWords(string & wordPool);
void PerformWordAnalysis(string & wordToBeAnalyzed, string & wordPool);
string FindSimilarWords(int partLength, string & part, string & wordToBeAnalyzed, int analyzedWordLength, int numberOfLettersMatched);
int CalculateNumberOfLettersMatched(int partLength, string & part, string & wordToBeAnalyzed);

//function: input check for word pool
bool InputCharCheckForWordPool(string & s)
{
	ToLower(s); //using strutils.h
	int endingCharacterCount=0; //ending character = @
	int i=0;
	for(i=0; i < s.length(); i++)
	{
		string substring = s.substr(i,1);
		if (substring == "@")
			endingCharacterCount++; 
		if(!EnglishCharCheck(substring) && (substring != "@") && (substring != " ")) 
			//if substring can't pass the English character check, substring isn't equal to @, and isn't space, return false
			return false;
	}
	if (endingCharacterCount > 1) // if there is more than one @, return false
		return false;
	return true;
}
//function English character check: check if the substring is an English letter
bool EnglishCharCheck(string & substring) 
{
	if(substring == "a" || substring == "b" ||substring == "c" ||substring == "d" || substring == "e" ||
		substring == "f" || substring == "g" || substring == "h" ||substring == "i" ||substring == "j" ||
		substring == "k" ||substring == "l" ||substring == "m" ||substring == "n" ||substring == "o" ||
		substring == "p" ||substring == "q" ||substring == "r" ||substring == "s" || substring == "t" ||
		substring == "u" ||substring == "v" ||substring == "w" ||substring == "x" ||substring == "y" || 
		substring == "z") 
		return true;
	return false;
}

//function analyzed word input check: take one character at a time from the analyzed word and 
//check if it is an English character
bool InputCheckAnalyzedWords(string & wordToBeAnalyzed)
{
	ToLower(wordToBeAnalyzed);
	int i=0;
	for(i=0; i < wordToBeAnalyzed.length(); i++)
	{
		string substring = wordToBeAnalyzed.substr(i,1);

		if(!EnglishCharCheck(substring)) //if it can't pass the English character check, return false
			return false;
	}
	return true;
}	

//function getting word pool: user enters the word pool till "@" is entered, word pool is formed by the 
//concatenation of words and spaces in between them
string GetWordPool(string & wordPool, string & word)
{
	word = ""; 
	while(word != "@") //enter till @
	{
		cin >> word; //enter word for word pool
		wordPool += word + " "; //concatenate
	}
	return wordPool; 
}

//function takes analyzed words until "quit"
bool ProcessWords(string & wordPool)
{
	string word;
	while(word != "quit") 
	{
		cout << "Please enter the word to be analyzed: ";
		cin >> word; //enter analyzed word
		ToLower(word); //using strutils.h

		if(word == "quit") //program terminates
			return false;
		while(!InputCheckAnalyzedWords(word)) //input check for analyzed words is called
		{
			cout << "Words can only include letters. Please enter again: "; 
			//if cannot pass then the user enters the analyzed word again
			cin >> word;
		}
		PerformWordAnalysis(word, wordPool);
	}
	return true;
}

//function where the main word analysis takes place
void PerformWordAnalysis(string & wordToBeAnalyzed, string & wordPool)
{
	//defining local variables
	#pragma region local variables
	int wordPoolLength = wordPool.length();
	int spacePos = wordPool.find(" ");  //position of the white space
	string remainingWordPool = wordPool; //word pool left after white space
	string similarMatches=""; //output of similar matches
	int analyzedWordLength = wordToBeAnalyzed.length();
	int numberOfLettersMatched=0; //how many characters are matched
	int partLength = 0; //part: meaningful substring of word pool
	#pragma endregion 

	//dividing word pool according to position of white space and trying to match each word of the word pool with word to be analyzed
	while(spacePos > 0 && spacePos < remainingWordPool.length() )
	{	
		string part = remainingWordPool.substr(0,spacePos); //find the substring
		partLength = part.length(); //update the substring length 
		if(partLength == analyzedWordLength && part == wordToBeAnalyzed) //if both length and words are matched, the word is correct
		{
			cout << "The word is correct!" << endl; //print successful result and return
			return; 
		}
		//if there is no exact match but a similar word (and lengths are the same)
		if (partLength == analyzedWordLength)
		{
			int bestMatch = CalculateNumberOfLettersMatched(partLength, part, wordToBeAnalyzed); //print the best match
			if(bestMatch == numberOfLettersMatched) //if there is more than one best match, then concatenate similar matches
			{
				numberOfLettersMatched = bestMatch;
				similarMatches += FindSimilarWords(partLength, part, wordToBeAnalyzed, analyzedWordLength, numberOfLettersMatched);
			}
			else if (bestMatch > numberOfLettersMatched) //if there is only one best match, then print only one result
			{
				numberOfLettersMatched = bestMatch;
				similarMatches = FindSimilarWords(partLength, part, wordToBeAnalyzed, analyzedWordLength, numberOfLettersMatched);
			}
		}
		remainingWordPool = remainingWordPool.substr(spacePos+1, wordPoolLength);//update the remaining word pool for next iteration
		spacePos = remainingWordPool.find(" "); //update the white space position according to remaining word pool
	}
	if (similarMatches != "" && numberOfLettersMatched > 0) //if there is any match, similar match shouldn't be empty string and number of letters matched should be greater than zero
	{	
		int numberOfSpellingMistakes = (analyzedWordLength - numberOfLettersMatched);
		cout << "Spelling Mistake(s): " << numberOfSpellingMistakes << endl;
		cout << "Possible Correction(s): " << similarMatches << endl;
	}
	//if there is no match, print the message below
	else if (partLength == 0 || partLength != analyzedWordLength || numberOfLettersMatched < analyzedWordLength/2)
	{
		cout << "There are no close matches for the word." << endl;
	}
}

//for the same length of words, check number of characters matched
int CalculateNumberOfLettersMatched(int partLength, string & part, string & wordToBeAnalyzed)
{
	int numberOfLettersMatched=0;
	int i=0;
	while(i < partLength)
	{
		if(part.substr(i,1) == wordToBeAnalyzed.substr(i,1))
			numberOfLettersMatched++;
		i++;
	}
	return numberOfLettersMatched;
}

//if the (number of letters matched)*2 is greater than or equal to the length of the word, return similar words. Otherwise return empty string.
string FindSimilarWords(int partLength, string & part, string & wordToBeAnalyzed, int analyzedWordLength, int numberOfLettersMatched)
{
	if(numberOfLettersMatched*2 >= analyzedWordLength)
	{
		return part + " ";
	}
	return "";
}

int main()
{
	cout << "This program detects spelling mistakes in given words with" << endl; //opening message
	cout << "respect to the given word pool." << endl << endl;
	string word;
	string wordPool = "";

	cout << "Enter the word pool with @ at the end:" << endl;
	wordPool = GetWordPool(wordPool, word); //takes word pool from user 

	while(!InputCharCheckForWordPool(wordPool)) //if input check fails, asks for a new word pool
	{
		cout << "Word pool can only include letters. Please enter again: " << endl;
		wordPool = "";
		GetWordPool (wordPool, word);
	}

	//takes the word to be analyzed, processes and prints the result
	if(ProcessWords(wordPool)==false) //if the word to be analyzed is quit(case insensitive), program returns
		return 0;

	cin.get();
	cin.ignore();
	return 0;
}

