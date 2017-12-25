//Sena Necla Çetin 21120	CS201L-A2	HW6		April 21, 2017

#include "Player.h"
#include "Board.h"
#include <iostream>
using namespace std;

bool Player::put(int row, int col)   //returns true if the piece is placed successfully, otherwise returns false
{
	return theBoard.putPiece(symbol, row, col);
}

//moves the game piece if the source cell belongs to the player's character
bool Player::move(int initRow, int initCol, int endRow, int endCol)
{
	if(theBoard.getChar(initRow, initCol) == symbol)
	{
		if(theBoard.movePiece(initRow, initCol, endRow, endCol))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(theBoard.getChar(initRow, initCol) == '-')
		{
			cout << "The source cell is empty! Try again!" << endl;
			return false;
		}
		else
		{
			cout << "The game piece at source coordinates isn't yours! Try again!" << endl;
			return false;
		}	
	}
}

bool Player::isWinner() //returns true if the player has won the game, returns false otherwise
{
	if(theBoard.gameOver() == symbol) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

char Player::getSymbol()  //returns the player's game piece character
{
	return symbol;
}

