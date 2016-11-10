/*
 * Board.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Board.h"

using namespace std;

Board::Board (string board_file_name)
{
	ifstream boardFile (board_file_name.c_str());
	string row;

	_x = _y = _startx = _starty = 0; // to appease compiler
	if (!boardFile.is_open())
		throw invalid_argument("Cannot open file: " + board_file_name);
	getline (boardFile, row);
	stringstream s1 (row);
	s1 >> _x >> _y;
	getline (boardFile, row);
	stringstream s2 (row);
	s2 >> _startx >> _starty;
	_startx --; _starty --;  // coordinates from 0 in array

	// Anything else you need to initialize?

	board = new Square**[_y];

	for (int i = 0 ; i < _y; ++ i)
	{
		board[i] = new Square*[_x];
		getline (boardFile, row);
		for (int j = 0; j < _x; ++ j)
		{
			// Fill in the following based on how you store the board.
			if (i == _starty && j == _startx) {
				board[i][j] = new Square('\0', "2W");
			}
			else switch (row[j]) {
			case '.' :
				board[i][j] = new Square('\0', "...");
			break;
			case '2' :
				board[i][j] = new Square('\0', "2L");
			break;
			case '3' :
				board[i][j] = new Square('\0', "3L");
			break;
			case 'd' :
				board[i][j] = new Square('\0', "2W");
			break;
			case 't' :
				board[i][j] = new Square('\0', "3W");
			break;
			default:
				string error = "Improper character in Board file: ";
				throw invalid_argument(error + row[j]);
			}
		}
	}
	boardFile.close ();
}

Board::~Board() {
	for (int i = 0 ; i < _y; ++ i) {
		for (int j = 0; j < _x; ++ j) {
			delete board[i][j];
		}
		// delete board[i];
	}
	delete board;
}

void Board::printBoard() {

	cout << "   ";
	for(int j = 0; j < _y; j++) {
		if(j < 9) {
			cout << j + 1 << "   ";
		} else {
			cout << j + 1 << "  ";
		}
	}
	cout << endl;

	for(int i = 0; i < _x; ++i) {
		if(i < 9) {
			cout << i + 1 << "  ";
		} else {
			cout << i + 1 << " ";
		}
		for(int j = 0; j < _y; ++j) {
			if(i == _startx && j == _starty) {
				if(board[i][j]->getLetter() != '\0') {
					cout << board[i][j]->getLetter() << board[i][j]->getScore() << "  ";
				} else {
					cout << "***" << " ";
				}
			} else {
				if(board[i][j]->getLetter() != '\0') {
					cout << board[i][j]->getLetter() << board[i][j]->getScore() << "  ";
				} else {
					if(board[i][j]->getMultiplier() != "...") {
						cout << board[i][j]->getMultiplier() << "  ";
					} else {
						cout << board[i][j]->getMultiplier() << " ";
					}
				}
			}
		}
		cout << endl;
	}
}

int Board::getXSize() {
	return _x;
}

int Board::getYSize() {
	return _y;
}

Square* Board::getSquare(int x, int y) {
	return board[x][y];
}

Square*** Board::getBoard() {
	return board;
}

void Board::resetPlacedTiles(vector< pair<int, int> > targetCoordinates, vector<string> savedMult) {
	// Reset all the tiles that were just put down
	for(unsigned int z = 0; z < targetCoordinates.size(); z++) {
		int resetRow = targetCoordinates[z].first;
		int resetCol = targetCoordinates[z].second;

		getSquare(resetRow, resetCol)->setScore(0);
		getSquare(resetRow, resetCol)->setLetter('\0');
		getSquare(resetRow, resetCol)->setOccupied(false);
		getSquare(resetRow, resetCol)->setMult(savedMult[z]);
	}
}
