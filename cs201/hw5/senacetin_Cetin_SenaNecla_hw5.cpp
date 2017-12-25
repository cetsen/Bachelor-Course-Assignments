// Sena Necla Çetin 21120 CS201 HW5 December 4, 2016

//including the necessary libraries
#include <iostream>
#include "MiniFW_Modified.h"
#include "randgen.h"
#include "Robots_Modified.h"
#include "strutils.h"
using namespace std;

//function prototypes:
void ControlPlayer2 (Robot & p);
void ControlPlayer(Robot & p);
void MonsterMovement(Robot & m1, Robot & m2, Robot & m3, Robot & m4);
void ObjectPlanting();
void ResurrectAll(Robot & p, Robot & m1, Robot & m2, Robot & m3, Robot & m4);
void ProgramFlow(Robot & p, Robot & m1, Robot & m2, Robot & m3, Robot & m4);

void ControlPlayer2(Robot & p)
{ /* This function moves the player robot and makes the robot either put(if it's a corner cell) or pick(if it's not a corner cell) 
	things on the cell. */
	p.Move();
	if((p.GetXCoordinate()==0 && p.GetYCoordinate()==0) || (p.GetXCoordinate()==0 && p.GetYCoordinate()==12) || //if it's a corner cell, put things until they are 10
		(p.GetXCoordinate()==12 && p.GetYCoordinate()==0) || (p.GetXCoordinate()==12 && p.GetYCoordinate()==12)) 
			p.PutManyThings(); 
	else //if it's not a corner cell, pick all things
		p.PickAllThings();
}

void ControlPlayer(Robot & p)
{ /* This function utilizes the IsPressed function to move the player robot according to the pressed key and calls the ControlPlayer2 
	function after each pressed key to decide which action to do depending on the cell it is on.*/
	if(p.IsAlive())
	{	
		if(IsPressed(keyRightArrow)) //if right arrow key is pressed, turn face to the east
		{				
			p.TurnFace(east); 
			ControlPlayer2(p);
		}
		else if(IsPressed(keyLeftArrow)) //if left arrow key is pressed, turn face to the west
		{
			p.TurnFace(west);
			ControlPlayer2(p);
		}
		else if(IsPressed(keyUpArrow)) //if up arrow key is pressed, turn face to the north
		{
			p.TurnFace(north);
			ControlPlayer2(p);
		}
		else if(IsPressed(keyDownArrow)) //if down arrow key is pressed, turn face to the south
		{
			p.TurnFace(south);		
			ControlPlayer2(p); 
		}
	}
}

void MonsterMovement(Robot & m1, Robot & m2, Robot & m3, Robot & m4)
{ /* This function picks a monster robot randomly and turns it to a random direction.*/
	RandGen m;
	int k=m.RandInt(1,4); //pick a random integer in [1,4] 
	if(k==1)
		m1.TurnRandom(); //if the picked integer is 1, call TurnRandom function to turn monster robot 1 to a random direction
	else if(k==2)
		m2.TurnRandom(); //if the picked integer is 2, call TurnRandom function to turn monster robot 2 to a random direction
	else if(k==3)
		m3.TurnRandom(); //if the picked integer is 3, call TurnRandom function to turn monster robot 3 to a random direction
	else if(k==4)
		m4.TurnRandom(); //if the picked integer is 4, call TurnRandom function to turn monster robot 4 to a random direction
}

void ObjectPlanting()
{ /* This function plants random number of objects in [1,4] to random cells. */
	RandGen r;
	for(int i=0; i<100;)
	{
		int a=r.RandInt(0,12); //a random x-coordinate in [0,12]
		int b=r.RandInt(0,12); //a random y-coordinate in [0,12]
		if(GetCellCount(a,b)==0) //if the random cell is empty
		{	
			int c=r.RandInt(1,4); //create a random number of objects in [1,4]
			PutThings(a,b,c); //put c many obhects onto that random cell
			i+=c; //increase the counter c many
		}
	}
}

void ResurrectAll(Robot & p, Robot & m1, Robot & m2, Robot & m3, Robot & m4)
{ /* This function resurrects all robots in the game. */
	p.Resurrect();
	m1.Resurrect();
	m2.Resurrect();
	m3.Resurrect();
	m4.Resurrect();
}

void ProgramFlow(Robot & p, Robot & m1, Robot & m2, Robot & m3, Robot & m4)
{ /* This function provides the main flow of the program. */
	int playerLives = 3; //the number of lives of the player robot is set to 3 at the beginning of the game
	while(p.IsAlive() && (GetCellCount(0,0)<10 || GetCellCount(0,12)<10 || GetCellCount(12,0)<10 || GetCellCount(12,12)<10))
	{ //while the player robot is alive and the corner cells aren't full, the game continues
		ControlPlayer(p); //ControlPlayer function is called to move the player robot
		if(!p.IsAlive()) //if the player  robot dies
		{
			playerLives--; //decrease its life by 1
			if(playerLives==2) //if the remaining lives is equal to 2
				ShowMessage("You have 2 lives left!"); 
			if(playerLives==1) //if the remaining lives is equal to 1
				ShowMessage("You have only 1 life left!");
			if(playerLives==0) //if the remaining lives is equal to 0
				ShowMessage("You have no lives left!");
			if(playerLives > 0) //if the player robot hasn't ran out of lives, all robots are resurrected in case any died during a collision
				ResurrectAll(p, m1, m2, m3, m4);
			else //if the player robot has ran out of lives the program terminates
			{	
				ShowMessage("You just lost the game!");
				return;
			}
		}
		MonsterMovement(m1, m2, m3, m4); //after the player robot moves, a random monster robot moves to a random direction by calling the MonsterMovement function
		ResurrectAll(p, m1, m2, m3, m4); //all robots are resurrected in case any died
		if(!p.IsAlive()) //if by the end of the monster robot movement the player robot dies
		{
			playerLives--; //decrease its life by 1
			if(playerLives==2) //if the remaining lives is equal to 2
				ShowMessage("You have 2 lives left!");
			if(playerLives==1) //if the remaining lives is equal to 1
				ShowMessage("You have 1 life left!");
			if(playerLives==0) //if the remaining lives is equal to 0
				ShowMessage("You have no lives left!");
			if(playerLives > 0) //if the player robot hasn't ran out of lives, all robots are resurrected in case any died during a collision
				ResurrectAll(p, m1, m2, m3, m4);
			else //if the player robot has ran out of lives the program terminates
			{	
				ShowMessage("You just lost the game!");
				return;
			}
		}
	}
}

int main()
{
	Robot p(6,6,east,0); //player robot is created at (6,6) facing east and with an empty bag
	Robot m1(6,2); //monster robot 1 is created at (6,2)
	m1.SetColor(red); //set color of m1 to red
	Robot m2(2,6); //monster robot 2 is created at (2,6)
	m2.SetColor(red); //set color of m2 to red
	Robot m3(10,6); //monster robot 3 is created at (10,6)
	m3.SetColor(red); //set color of m3 to red
	Robot m4(6,10); //monster robot 4 is created at (6,10)
	m4.SetColor(red); //set color of m4 to red
	ObjectPlanting(); //call the ObjectPlanting function to randomly plant objects to the game field
	ProgramFlow(p, m1, m2, m3, m4); //call the program flow function to move robots
	if(p.IsAlive()) //at the end, if the player robot is alive and there are 10 items at each corner, display a message
	{
		ShowMessage("Congratulations! You win!");
	}
	return 0;
}
