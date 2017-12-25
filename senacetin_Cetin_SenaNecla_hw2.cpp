// Sena Necla Çetin 21120 - Homework2 - October 23, 2016

#include <iostream>
#include <string>

using namespace std;

//Shows function prototypes:
bool quantityInputCheck (int quantity);
void boughtFood (double amountMoney, string name);
void change (double remainingMoney);
void results (int bottleQuantity, int biscuitQuantity, int chocolateQuantity, double remainingMoney);

/*Function 2:
Input check: If the user types quantities less than 0 or greater than 10, the function returns false (boolean function).  
For quantities greater than or equal to 0, and less than 10, the function returns true (boolean function).
*/
bool quantityInputCheck (int quantity)
{
	if (quantity < 0)
	{ 
		cout << "You can't enter a quantity below 0" << endl;
		return false;
	}

	else if (quantity > 10)
	{
		cout << "You can't request more than 10 of each product" << endl;
		return false;
	}
	else 
	{
		return true;
	}
} 

/*Function1: 
This function gets inputs (amountMoney and name) from the main function.
This function calculates how many items can be bought with the amount of money the user has.
If the money is insufficient, this function calculates how many of that item can be bought and displays the message "you can't buy";
the function does not proceed to the next item.
If the money is sufficient, the function proceeds to the next item.
This function calls Function3 at the end to display the results.
*/
void boughtFood (double amountMoney, string name)
{
	int bottleQuantity, biscuitQuantity, chocolateQuantity;
	double bottleMoney, biscuitMoney, chocolateMoney;

	int bottleBought, chocolateBought, biscuitBought;
	bottleBought=0; 
	chocolateBought=0;
	biscuitBought=0;

	//Positive value should be entered for the amount of money:
	if (amountMoney <= 0)
	{
		cout << "You should enter a positive value" << endl;
		//The function exits if the amount of money isn't positive:
		return;
	}

	//Calculations for bottle quantity:
	cout << name << ", please enter the number of bottled waters you want to buy: ";
	cin >> bottleQuantity;

	if (quantityInputCheck (bottleQuantity))
	{
		bottleMoney = bottleQuantity * 1.00;

		if (amountMoney < bottleMoney)
		{
			bottleBought = amountMoney / 1.00;
			amountMoney = amountMoney - (bottleBought * 1.00);

			cout << "You can't buy " << bottleQuantity << " bottled water(s)." << endl;
			results(bottleBought, biscuitBought, chocolateBought, amountMoney);
			return;
		}
		else
		{
			bottleBought = bottleQuantity;
			amountMoney = amountMoney - (bottleBought*1.00);
		}
	}
	else
	{
		return;
	}

	//Calculations for biscuit quantity:
	cout << name << ", please enter the number of biscuits you want to buy: ";
	cin >> biscuitQuantity;

	if (quantityInputCheck (biscuitQuantity))
	{
		biscuitMoney = biscuitQuantity * 1.75;

		if (amountMoney < biscuitMoney)
		{
			biscuitBought = amountMoney / 1.75;
			amountMoney = amountMoney - (biscuitBought * 1.75);
			cout << "You can't buy " << biscuitQuantity << " biscuit(s)." << endl;
			results(bottleBought, biscuitBought, chocolateBought, amountMoney);
			return;
		}
		else
		{
			biscuitBought = biscuitQuantity;
			amountMoney = amountMoney - (biscuitBought * 1.75);
		}
	}
	else
	{
		return;
	}

	//Calculations for chocolate quantity:
	cout << name << ", please enter the number of chocolate bars you want to buy: ";
	cin >> chocolateQuantity;

	if (quantityInputCheck (chocolateQuantity))
	{
		chocolateMoney = chocolateQuantity * 2.15;

		if (amountMoney < chocolateMoney)
		{
			chocolateBought = amountMoney / 2.15;
			amountMoney = amountMoney - (chocolateBought * 2.15);

			cout << "You can't buy " << chocolateQuantity << " chocolate bar(s)." << endl;
			results(bottleBought, biscuitBought, chocolateBought, amountMoney);
			return;
		}
		else
		{
			chocolateBought = chocolateQuantity;
			amountMoney = amountMoney - (chocolateBought*2.15);
		}
	}
	else
	{
		return;
	}

	results(bottleBought, biscuitBought, chocolateBought, amountMoney);
} 

/*Function3:
This function displays the amount of items the user has bought and the remaining money.
It calls Function4 at the end to display the amount of change the user will receive.
*/
void results (int bottleQuantity, int biscuitQuantity, int chocolateQuantity, double remainingMoney)
{
	//Displays the quantity of water bottles bought:
	cout << "You bought:" << endl;
	if (bottleQuantity > 0)
	{
		cout << bottleQuantity << " bottled water(s)" << endl;
	}	

	//Displays the quantity of biscuits bought:
	if (biscuitQuantity > 0)
	{
		cout << biscuitQuantity << " biscuit(s)" << endl;
	}	

	//Displays the quantity of chocolate bars bought:
	if (chocolateQuantity > 0)
	{
		cout << chocolateQuantity << " chocolate bar(s)" << endl;
	}

	//If no items are bought, this function displays the message "no items":
	if(bottleQuantity==0 && biscuitQuantity==0 && chocolateQuantity==0)
	{
		cout << "no items." << endl;
	}

	//Displays the remaining money:
	cout << "Remaining Money: " << remainingMoney << endl;

	//Function4 is called to calculate and display coins that will be given as change:
	change(remainingMoney);
}

/* Function4:
This function calculates the amount of change the user will receive as 1TL, 50kr, 25kr, 10kr, 5kr, and 1kr.
If the user receives no change, it displays the message "You will receive: no change".
*/
void change (double remainingMoney)
{
	cout << "You will receive: " ;
	if (remainingMoney > 0)
	{
		//Calculates the amount of 1TL coins that will be given as change:
		if (remainingMoney >= 1.00)
		{
			int coinLira = remainingMoney / 1.00;
			cout << endl << coinLira << " 1TL coin(s)";
			remainingMoney = remainingMoney - (coinLira * 1.00);
		}

		//Calculates the amount of 50 kurus coins that will be given as change:
		if (remainingMoney >= 0.50)
		{
			int coin50kr = remainingMoney / 0.50;
			cout << endl << coin50kr << " 50 kurus coin(s)";
			remainingMoney = remainingMoney - (coin50kr * 0.50);
		}

		//Calculates the amount of 25 kurus coins that will be given as change:
		if (remainingMoney >= 0.25)
		{
			int coin25kr = remainingMoney / 0.25;
			cout << endl << coin25kr << " 25 kurus coin(s)";
			remainingMoney = remainingMoney - (coin25kr * 0.25);
		}

		//Calculates the amount of 10 kurus coins that will be given as change:
		if (remainingMoney >= 0.10)
		{
			int coin10kr = remainingMoney / 0.10;
			cout << endl << coin10kr << " 10 kurus coin(s)";
			remainingMoney = remainingMoney - (coin10kr * 0.10);
		}

		//Calculates the amount of 5 kurus coins that will be given as change:
		if (remainingMoney >= 0.05)
		{
			int coin5kr = remainingMoney / 0.05;
			cout << endl << coin5kr << " 5 kurus coin(s)";
			remainingMoney = remainingMoney - (coin5kr * 0.05);
		}

		//Calculates the amount of 1 kurus coins that will be given as change:
		if (remainingMoney >= 0.01)
		{
			int coin1kr = remainingMoney / 0.01;
			cout << endl << coin1kr << " 1 kurus coin(s)";
			remainingMoney = remainingMoney - (coin1kr * 0.01);
		}
	}
	else
	{
		//If the remaining money is equal to zero, then the function displays the following message:
		cout << "no change" << endl;
	}
}

/*Main Function:
This function gets the name and money input from the first user and calls Function1.
Then, it gets the name and money input from the second user and calls Function1 again with those as parameters.
*/
int main()

{
	string name1, name2;
	double amountMoney1, amountMoney2;

	//Welcome message
	cout << "This program calculates whether the requested number of each item can be "<< endl;
	cout << "bought from a vending machine; calculates the remaining amount of money and "<< endl; 
	cout << "displays how many coins will be received as change for two users. The" << endl; 
	cout << "items that can be bought from this vending machine are bottled water," << endl;
	cout << "biscuits and chocolate bars. Now please proceed to enter your name," << endl;
	cout << "total amount of money you have, and the quantity of each requested item." << endl << endl;
	
	//Name input is taken from the first user
	cout << "Please enter your name: ";
	cin >> name1 ;

	//Amount of money input is taken from the first user
	cout << "Hello " << name1 << ", please enter the amount of money you have: " ;
	cin >> amountMoney1;

	//Function1 is called for the first user
	boughtFood (amountMoney1, name1);

	//Name input is taken from the second user
	cout << endl << endl;
	cout << "Please enter your name: ";
	cin >> name2 ;

	//Amount of money input is taken from the second user
	cout << "Hello " << name2 << ", please enter the amount of money you have: " ;
	cin >> amountMoney2;

	//Function1 is called for the second user
	boughtFood (amountMoney2, name2);

	cin.get();
	cin.ignore();
	return 0;

}


