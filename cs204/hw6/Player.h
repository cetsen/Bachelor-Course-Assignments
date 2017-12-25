//Sena Necla Çetin 21120	CS201L-A2	HW6		April 21, 2017

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Board.h"

class Player
{
private:
	Board &theBoard;
	char symbol;

public:
	Player::Player(char symbol, Board &theBoard)
		:symbol(symbol), theBoard(theBoard)
	{}
	bool put(int row, int col);
	bool move(int initRow, int initCol, int endRow, int endCol);
	bool isWinner();
	char getSymbol();
};

#endif