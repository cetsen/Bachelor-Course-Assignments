/*
Sena Necla Çetin 21120 CS 201R-B5 

     This program calculates the total number of all medals awarded in the Olympics and the percentage of 
	 medals won by a given country.   

*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
	//Input: Name of country
	string  countryName;
	
	//Input: Total number of gold, silver, and bronze medals in the olympics
	int totalNumberOfGoldMedals; 
	int totalNumberOfSilverMedals;
	int totalNumberOfBronzeMedals;

	//Input: Number of gold, silver, and bronze medals won by a given country
	int numberOfGoldMedalsWonByGivenCountry;
	int numberOfSilverMedalsWonByGivenCountry;
	int numberOfBronzeMedalsWonByGivenCountry;
	
	/* These are all float type variables in order to calculate the percentage of medals won by a given country
	    in decimal numbers(instead of integers): */
	float sumAllMedals; //Output: Total number of all medals 
	float sumMedalsWonByGivenCountry;  //Output: Total number of medals won by the given country
	float percentageOfMedalsWonByGivenCountry; //Output: Percentage of medals won by the given country
	
	cout <<  "This program calculates the total number of all medals awarded and the percentage of medals won by a given country." << endl;

	cout << "Please enter the name of your country: ";
	cin >> countryName;

	cout << "Please enter total number of gold medals awarded during the Olympics: ";
	cin >> totalNumberOfGoldMedals;

	cout << "Please enter total number of silver medals awarded during the Olympics: ";
	cin >> totalNumberOfSilverMedals;

	cout << "Please enter total number of bronze medals awarded during the Olympics: ";
	cin >> totalNumberOfBronzeMedals;

	cout << "Please enter the number of gold medals won by " << countryName << ": ";
	cin >> numberOfGoldMedalsWonByGivenCountry;

	cout << "Please enter the number of silver medals won by " << countryName << ": ";
	cin >> numberOfSilverMedalsWonByGivenCountry;

	cout << "Please enter the number of bronze medals won by " << countryName << ": ";
	cin >> numberOfBronzeMedalsWonByGivenCountry;

	sumAllMedals = totalNumberOfGoldMedals + totalNumberOfSilverMedals + totalNumberOfBronzeMedals;
	sumMedalsWonByGivenCountry = numberOfGoldMedalsWonByGivenCountry + numberOfSilverMedalsWonByGivenCountry + numberOfBronzeMedalsWonByGivenCountry;
	percentageOfMedalsWonByGivenCountry = (sumMedalsWonByGivenCountry / sumAllMedals) * 100;

	cout << "Total number of medals awarded during the Olympics: " << sumAllMedals << endl;

	cout << "Total number of medals won by " << countryName << ": " << sumMedalsWonByGivenCountry << endl;

	cout << "Percentage of medals won by " << countryName << ": " << percentageOfMedalsWonByGivenCountry << endl;

	cin.get();
	cin.ignore();
	return 0;
}

