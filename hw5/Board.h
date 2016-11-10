/*
 * Board.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include "Square.h"
#include "Player.h"
#include "Dictionary.h"
#include "Square.h"

class Board {
public:
	Board (std::string board_file_name);
	~Board();
	void printBoard();
	// What else will this need?
	// friend void Player::place(Board& playedBoard, Dictionary myDict);
	int getXSize();
	int getYSize();
	Square*** getBoard();
	Square* getSquare(int x, int y);
	void resetPlacedTiles(std::vector< std::pair<int, int> > targetCoordinates, std::vector<std::string> savedMult);

protected:
	int _x, _y;
	int _startx, _starty;
	Square*** board;
	// Tile*** boardTiles;

	// What else will this need?


};


#endif /* BOARD_H_ */
