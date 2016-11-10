#ifndef SQUARE_H_
#define SQUARE_H_

#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "Bag.h"
#include "Tile.h"

class Square {
private:
	char letter;
	// string wordMultiplier;
	// string letterMultiplier;
	std::string multiplier;
	bool isOccupied;
	int squareScore;
public:
	Square(char squareLetter, std::string currMult);
	bool isEmpty();
	char getLetter();
	int getScore();
	void setScore(int score);
	void setOccupied(bool filled);
	void setLetter(int newLetter);
	void setMult(std::string mult);
	void clear();
	int assignTile(Tile* tile);
	std::string getMultiplier();
};

#endif /* SQUARE_H_ */
