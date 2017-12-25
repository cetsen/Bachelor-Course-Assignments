//Sena Necla Çetin 21120	CS201L-A2	HW6		April 21, 2017

#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
	char theBoard[4][4];

public:
	Board();
	void displayBoard() const;
	bool putPiece(char symbol, int row, int col);
	bool movePiece(int initRow, int initCol, int endRow, int endCol);
	char gameOver() const;
	bool destinationIsEmpty(int endRow, int endCol) const;
	char getChar(int row, int col) const;
};


#endif