#include "Square.h"

using namespace std;

Square::Square(char squareLetter, string currMult) {
	letter = squareLetter;

	// if(currMult == "2L" || currMult == "3L") {
	// 	letterMultiplier = currMult;
	// } else if(currMult == "2W" || currMult == "3W") {
	// 	wordMultiplier = currMult;
	// }

	multiplier = currMult;
	squareScore = 0;
	isOccupied = false;
}

void Square::clear() {
	letter = '\0';
	multiplier = "";
	squareScore = 0;
	isOccupied = false;
}

int Square::assignTile(Tile* tile) {
	cout << "HELLO THERE" << endl;
	if(isOccupied == false) {
		cout << "HELLO THERE" << endl;

		letter = tile->getUse();
		squareScore = tile->getPoints();
		isOccupied = true;

		if(multiplier == "2L" || multiplier == "3L") {
			if(multiplier == "2L") {
				squareScore = squareScore * 2;
			} else {
				squareScore = squareScore * 3;
			}
		} else if (multiplier == "2W" || multiplier == "3W") {
			if(multiplier == "2W") {
				return 2;
			} else if(multiplier == "3W") {
				return 3;
			}
		}
		isOccupied = true;

		return 1;
	} else {
		cout << "CANNOT ASSIGN TILE. TILE IS ALREADY OCCUPIED" << endl;
		return 1;
	}
}

bool Square::isEmpty() {
	return !isOccupied;
}

void Square::setOccupied(bool filled) {
	isOccupied = filled;
}

char Square::getLetter() {
	return letter;
}

int Square::getScore() {
	return squareScore;
}

void Square::setScore(int score) {
	squareScore = score;
}

void Square::setLetter(int newLetter) {
	letter = newLetter;
}

void Square::setMult(string mult) {
	multiplier = mult;
}

string Square::getMultiplier() {
	return multiplier;
}
