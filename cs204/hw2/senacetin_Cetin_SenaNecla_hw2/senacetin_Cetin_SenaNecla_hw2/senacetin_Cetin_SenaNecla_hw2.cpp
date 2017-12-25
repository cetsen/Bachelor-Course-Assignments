//Sena Necla Çetin	21120	CS204L-A2	March 1, 2017
//This program represents drivers and their points as a linked list.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct node
{
	string name; 
	int points;   
	node * next;  

	//default constructor
	node::node ()
		:name(""), points(0), next(NULL)
	{}

	//constructor
	node::node (string s, int p, node *n)
		:name(s), points(p), next(n)
	{}	
};

void Menu (ifstream & input, node* head, node* temp, node* prev);
void Operation1 (ifstream & input, node* head, node* temp, node* prev);
void Operation2 (ifstream & input, node* head, node* temp, node* prev);
void Operation3 (ifstream & input, node* head, node* temp, node* prev);
bool SearchList (node* head, string driverName);
void DeleteList (node* head);
node* ReturnNode (node* head, string driverName);
void OpenFile (ifstream & input);
void AddOrRemoveFromList (node* head, node* temp, node* prev, string driverName, int driverPoints);
node* ReturnPrevNode (node* head, node* currentNode);

// This function adds or removes nodes regarding their position in the list (head, middle, end) and their points (positive, non-positive).
void AddOrRemoveFromList (node* head, node* temp, node* prev, string driverName, int driverPoints)
{
	node* prev2;
	if (head == NULL)  //if the list is empty
	{
		if (driverPoints > 0)  //if the points are positive, a new node is added to the linked list.
		{
			cout << endl << driverName << " has been added to the list with initial points " << driverPoints << endl;
			temp = new node (driverName, driverPoints, NULL);
			head = temp; 
			prev = temp;
		}
		else    //if the points are non-positive, the driver isn't added to the list
			cout << driverName << " has not been added"<< endl << "since the initial points cannot be non-positive." << endl;
	}
	else if (driverPoints > 0 && !SearchList (head, driverName))   
	{
		// else if the list isn't empty, the driver name hasn't been entered before and the points are positive, a new node is added to the list.
		temp = new node (driverName, driverPoints, NULL);
		prev->next = temp;
		prev = temp;
		cout << driverName << " has been added to the list with initial points " << driverPoints << endl;
	}
	else if (driverPoints <= 0 && !SearchList (head, driverName))   
	{
		cout << driverName << " has not been added " << endl << "since the initial points cannot be non-positive." << endl;
	}
	else   //else if the list isn't empty and the driver name has been repeated
	{
		temp = ReturnNode (head, driverName);
		temp->points += driverPoints;
		if ( temp->points > 0 )   // if the sum of the points is positive, the points of the driver is updated
		{
			cout << driverName << " has been updated and new point is " << temp->points << endl;
		}
		else    // if the sum of points is non-positive, the new value isn't added to the driver's points.
		{
			if (temp == head)
			{
				head = temp->next;
				delete temp;
			}
			else if (temp->next == NULL)
			{
				prev2 = ReturnPrevNode (head, temp);
				prev2->next = NULL;
				delete temp;
			}
			else
			{
				prev2 = ReturnPrevNode (head, temp);
				prev2->next = temp->next;
				delete temp;
			}
			cout << driverName << " has been removed from the list"<< endl << "since his points became non-positive." << endl;
		}
	}
}

//This function deletes every node in the list using recursion.
void DeleteList (node* head)  
{
	if (head != NULL)
	{
		DeleteList(head->next);
		delete head;
	}
}

/* This function searches the list to find if the driver name has been repeated, returns true if the driver is already on the list, 
returns false if the driver isn't on the list yet. */
bool SearchList (node* head, string driverName)	
{
	node* temp = head;
	while (temp != NULL)
	{
		if(temp->name == driverName)			//if the node with the given name is found
		{
			return true;		
		}
		temp = temp->next;						//go onto the next node
	}
	return false;
}

//This function is called if SearchList function returns true, and returns the node that has been repeated.
node* ReturnNode (node* head, string driverName)
{
	node* temp = head;
	while (temp != NULL)
	{
		if(temp->name == driverName)	//if the node with the given name is found
		{
			return temp;				//return the node
		}
		temp = temp->next;				//go onto the next node
	}
	return NULL;
}

// This function returns the previous node of the current node
node* ReturnPrevNode (node* head, node* currentNode)  
{
	node* temp = head;
	node* prev = head;
	while (temp != NULL)
	{
		if(temp == currentNode)			//if the node with the given name is found
		{
			return prev;				//return the previous node
		}
		prev = temp;
		temp = temp->next;				//go onto the next node
	}
	return NULL;
}

/* This function opens the input file.  If the input file fails to open, an error message is displayed and the user 
is asked to enter the file name until the file is successfully opened. */
void OpenFile (ifstream & input)
{
	string fileName;
	cout << "\nEnter the name of the file\n";
	cin >> fileName;
	input.open(fileName.c_str());

	while ( input.fail() )
	{
		input.clear(); // error flags are cleared
		input.seekg(0); 
		cout << "\nError: Could not open the file " << fileName << endl;
		cout << "\nEnter the name of the file \n" ;
		cin >> fileName;
		input.open(fileName.c_str());
	}
}

/* This function displays the opening message. For the option number, while a non-integer value or an integer out of range is entered, 
the user is asked to re-enter a value between 1-4.  After the user successfully enters the option number, the operations are done according to 
the entered number by calling the individual functions. */
void Menu (ifstream & input, node* head, node* temp, node* prev)
{
	cout << "\nFormula 1 Points Table System" << endl << "-----------------------------------" << endl << "Please select one option [1..4]:" << endl;
	cout << "1. Load driver names and points from a file" << endl << "2. Insert a new driver / Modify points of an existing driver" << endl;
	cout << "3. Display points table in alphabetical order" << endl << "4. Exit" << endl;
	int option;
	cin >> option;
	while ( cin.fail() || ((option != 0) && (option != 1) && (option != 2) && (option != 3) && (option != 4)) )
	{
		cout << "\nError: Please enter an integer in range [1, 4]." << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		cin >> option;
	}
	if (option == 1)
		Operation1 (input, head, temp, prev);
	else if (option == 2)
		Operation2 (input, head, temp, prev);
	else if (option == 3)
		Operation3 (input, head, temp, prev);
	else if (option == 4)
	{
		DeleteList(head);
		return;
	}
}

/* This function calls OpenFile to open the file and loads driver names and points from it by stringstream.  Driver names and points are 
displayed on the screen accordingly by calling LinkedList function. */
void Operation1 (ifstream & input, node* head, node* temp, node* prev) 
{
	OpenFile (input);
	string line;
	string driverName;
	int driverPoints;
	node* prev2;
	while ( !input.eof() )
	{
		getline (input, line);
		stringstream ss(line);
		while ( ss >> driverName >> driverPoints )
		{
			AddOrRemoveFromList (head, temp, prev, driverName, driverPoints);
		}
	}
	Menu(input, head, temp, prev);  //the Menu function is called for the user to enter an option [1-4]
}

// This function inserts a new driver or modifies points of an existing driver by calling the LinkedList function.
void Operation2 (ifstream & input, node* head, node* temp, node* last)
{
	string driverName;
	int driverPoints;
	node* prev;
	cout << "Please enter the name of the driver you wish to add/modify: ";
	cin >> driverName;
	cout << endl << "Please enter how many points you wish to initialize/add/remove: ";
	cin >> driverPoints;
	for(unsigned int i=0; i<driverName.length(); i++)  //if the entered name is lowercase, convert to uppercase so that the alphabetical order doesn't go wrong
	{
		if(driverName[i]<=122 && driverName[i]>=97)
			driverName[i]-=32;
	}

	AddOrRemoveFromList (head, temp, prev, driverName, driverPoints);
	Menu (input, head, temp, last);   //the Menu function is called for the user to enter an option [1-4]
}

// This function displays points table in alphabetical order.
void Operation3 (ifstream & input, node* head, node* temp, node* prev)
{
	string name;
	int points;
	node* temp1 = head;
	node* temp2;

	if (temp1 == NULL)
		cout << "The points table is empty" << endl << endl;
	else 
		cout << endl << "Points Table" << endl << "-----------------------------------" << endl;

	//comparing each consecutive name in the list and printing out each driver name (and their points) alphabetically in ascending order
	while (temp1 != NULL)
	{
		temp2 = temp1->next;
		while (temp2 != NULL)
		{
			if ( temp1->name.compare(temp2->name) > 0 )  //if the current name is greater than the next name, switch their order
			{
				points = temp1->points;
				name = temp1->name;

				temp1->name = temp2->name;
				temp1->points = temp2->points;

				temp2->name = name;
				temp2->points = points;
			}
			temp2 =  temp2->next;  //go onto the next name
		}
		cout << temp1->name << " " << temp1->points << endl;
		temp1 = temp1->next;  //go onto the next name
	}
	Menu(input, head, temp, prev);  //the Menu function is called for the user to enter an option [1-4]
}

int main()
{
	ifstream input;
	node* head = NULL;  
	node* temp = NULL;
	node* prev = NULL;
	Menu(input, head, temp, prev);

	input.close();
	return 0;
}
