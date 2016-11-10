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
#include "Player.h"
#include "Dictionary.h"
#include "Board.h"
#include <utility>

using namespace std;

Player::Player(string name, int score, vector<Tile*> tiles, int totalTiles) {
	_name = name;
	_score = score;
	playerTiles = tiles;
	maxTiles = totalTiles;
}

string Player::getName() {
	return _name;
}

int Player::getScore() {
	return _score;
}

vector<Tile*> Player::getPlayerTiles() {
	return playerTiles;
}

void Player::printTiles() {
	cout << "Tiles available: ";
	// Print out all tiles available
	cout << "[";
	for(unsigned int j = 0; j < playerTiles.size(); j++) {
		if(j < playerTiles.size() - 1) {
			cout << "[" << playerTiles[j]->getLetter() << ", " <<
			playerTiles[j]->getPoints() << "]" << ",";
		} else {
			cout << "[" << playerTiles[j]->getLetter() << ", " <<
			playerTiles[j]->getPoints() << "]";
		}
	}
	cout << "]";
	cout << endl;
}

// fills players hand
void Player::fillHand(Bag& bag) {
	int missing = maxTiles - playerTiles.size();

	set<Tile*>::iterator it;

	set<Tile*> temp = bag.drawTiles(missing);

	for(it = temp.begin(); it != temp.end(); ++it) {
		playerTiles.push_back(*it);
	}
}

bool Player::checkTiles(vector<char> targetTiles) {
	vector<int> isFound;

	for(unsigned int i = 0; i < playerTiles.size(); ++i) {
		isFound.push_back(0);
	}

	for(unsigned int i = 0; i < targetTiles.size(); i++) {
		for(unsigned int j = 0; j < playerTiles.size(); j++) {
			if(isFound[j] != 1) {
				if(targetTiles[i] == playerTiles[j]->getUse()) {
					isFound[j] = 1;
					break;
				}
			}

			if(j == playerTiles.size() - 1) {
				return false;
			}
		}
	}
	return true;
}

void Player::eraseFromHand(vector<Tile*> targetTiles) {
	for(unsigned int i = 0; i < targetTiles.size(); i++) {
		for(unsigned int j = 0; j < playerTiles.size(); ++j) {
			if(playerTiles[j]->getUse() == targetTiles[i]->getUse()) {
				playerTiles.erase(playerTiles.begin() + j);
				// targetTiles.erase(targetTiles.begin(), targetTiles.begin() + i);
			}
		}
	}
}

bool Player::place(Board* playedBoard, string letters, Dictionary myDict, Bag& bag, string dir,
int row, int col) {
	string buffer = "";
	vector<Tile*> tilesUsed;
	vector< pair<int, int> > targetCoordinates;
	vector<string> savedMult;
	set<Square*> checkedSquares;
	int addedScore = 0;
	// bool firstTile = false;

	if(row > playedBoard->getYSize() || col > playedBoard->getXSize() ||
			row < 0 || col < 0) {
		return false;
	}

	// if(row + 1 < playedBoard->getYSize() && row - 1 > 0 && col + 1 < playedBoard->getXSize() && col - 1 > 0) {
	//
	// 	if(playedBoard->getSquare(row + 1, col)->isEmpty() || playedBoard->getSquare(row - 1, col)->isEmpty()
	// 		|| playedBoard->getSquare(row, col + 1)->isEmpty() || playedBoard->getSquare(row, col - 1)->isEmpty()) {
	// 			cout <<"DAMDMNADNDAMNDAMNADMND" << endl;
	// 			return false;
	// 		}
	//
	// }

	// Put the letters that are cin into a vector of strings to check
	vector<char> checkVector;
	for(unsigned int i = 0; i < letters.length(); ++i) {
		if(letters[i] == '?') {
			break;
		}
		checkVector.push_back(letters[i]);
	}

	// If player doesn't have all the tiles, return
	if(!checkTiles(checkVector)) {
		return false;
	}

	// IF THE PLAYER HAS ALL THE TILES.......
	// Find tiles corresponding to the characters that the player entered
	// and push them into a tiles vector

	// NOTE: DOES NOT DELETE TILES FROM PLAYER'S HAND
	for(unsigned int i = 0; i < letters.length(); ++i) {
		if(letters[i] == '?') {

			// Find the tile in hand that associates with '?', and set the use as
			for(unsigned int j = 0; j < playerTiles.size(); j++) {
				if(playerTiles[j]->isBlank()) {
					//Makes the tile be used as the one specified by the user
					playerTiles[j]->useAs(letters[i + 1]);
					tilesUsed.push_back(playerTiles[j]);
					break;
				}
			}
			i++;
			break;
		}

		for(unsigned int j = 0; j < playerTiles.size(); ++j) {
			if(playerTiles[j]->getUse() == letters[i]) {
				tilesUsed.push_back(playerTiles[j]);
				break;
			}
		}
	}

	cout << endl;


// ------------------------------ //
	// If player direction is vertical & have all tiles
	if(dir == "VERTICAL") {
		bool seen = false;
		int wordMult = 1;
		// Place all the letters that user wanted into white space on the board, vertically
		int j = 0;
		for(unsigned int i = 0; i < tilesUsed.size(); i++) {
			if(row + i + j - 1 < 0 || col - 1 < 0 || unsigned(row + i + j - 1) >= playedBoard->getYSize()
			 		|| unsigned(col - 1) >= playedBoard->getXSize()) {
						return false;
			}

			if(playedBoard->getSquare(row + i + j - 1, col - 1)->isEmpty() == true) {
				savedMult.push_back(playedBoard->getSquare(row + i + j - 1, col - 1)->getMultiplier());
				wordMult = wordMult * playedBoard->getSquare(row + i + j - 1, col - 1)->assignTile(tilesUsed[i]);

				targetCoordinates.push_back(make_pair(row + i + j - 1, col - 1));
			} else {
				addedScore += playedBoard->getSquare(row + i + j - 1, col - 1)->getScore();
				i--;
				j++;
			}
		}

// --------------- For coordinates of every letter that was placed, check top, left, bottom, right ---------- //
		for(unsigned int i = 0; i < targetCoordinates.size(); i++) {
			int checkRow = targetCoordinates[i].first;
			int checkCol = targetCoordinates[i].second;
			int staticCheckRow = checkRow;
			int staticCheckCol = checkCol;
			int leftRightCount = 0;

			// If left square is not empty, go all the way to the left until empty square and back to right
			while(checkCol - 1 >= 0) {
				if(playedBoard->getSquare(checkRow, checkCol - 1)->isEmpty() == false) {
					checkCol--;
				} else break;
			}

			// When get all the way to the left, go all the way back to the right
			while(checkCol + 1 < playedBoard->getXSize()) {
				if(playedBoard->getSquare(checkRow, checkCol + 1)->isEmpty() == false) {
					buffer += playedBoard->getSquare(checkRow, checkCol)->getLetter();
					addedScore += playedBoard->getSquare(checkRow, checkCol)->getScore();
					leftRightCount++;
					checkCol++;
				} else break;
			}

			// Add last character into the buffer to check against dictionary
			buffer += playedBoard->getSquare(checkRow, checkCol)->getLetter();
			if(leftRightCount > 0) {
				addedScore += playedBoard->getSquare(checkRow, checkCol)->getScore();
			}

			// If the buffer at the end is not a word, reset squares and return;
			if((buffer.length() > 0 && !(myDict.isWord(buffer)))) {
				if(buffer.length() != 1) {
					// // Reset all the tiles that were just put down
					playedBoard->resetPlacedTiles(targetCoordinates, savedMult);
					return false;
				}
			}

			buffer = "";

			// If the top square is not empty, go all the way to the top and back down
			while(staticCheckRow - 1 >= 0) {
				if(playedBoard->getSquare(staticCheckRow - 1, staticCheckCol)->isEmpty() == false) {
					staticCheckRow--;
				} else break;
			}

			// When get all the way to the top, go all the way back down
			while(staticCheckRow + 1 < playedBoard->getYSize()) {
				if(playedBoard->getSquare(staticCheckRow + 1, staticCheckCol)->isEmpty() == false) {
					buffer += playedBoard->getSquare(staticCheckRow, staticCheckCol)->getLetter();

					if(!seen) {
						addedScore += playedBoard->getSquare(staticCheckRow, staticCheckCol)->getScore();
					}

					staticCheckRow++;
				} else break;
			}

			// Add the last letter to the buffer
			buffer += playedBoard->getSquare(staticCheckRow, staticCheckCol)->getLetter();
			if(!seen) {
				addedScore += playedBoard->getSquare(staticCheckRow, staticCheckCol)->getScore();

				if(wordMult > 1) {
					addedScore = addedScore * wordMult;
				}
				seen = true;
			}

			if((buffer.length() > 0 && !(myDict.isWord(buffer)))) {
				if(buffer.length() != 1) {
					// Reset squares to original
					playedBoard->resetPlacedTiles(targetCoordinates, savedMult);

					return false;
				}
			}

			buffer = "";
		}

		// Reset square multipliers to 0 and score to what it was before
		for(unsigned int i = 0; i < tilesUsed.size(); i++) {
			// Now square has no multiplier and same points as before
			playedBoard->getSquare(row + i + j - 1, col - 1)->setMult("...");
			playedBoard->getSquare(row + i + j - 1, col - 1)->setScore(tilesUsed[i]->getPoints());
		}
	}

	else if(dir == "HORIZONTAL") {
		bool seen = false;
		int wordMult = 1;

		// Place all the letters that user wanted into white space on the board, horizontally
		int j = 0;
		for(unsigned int i = 0; i < tilesUsed.size(); i++) {
			if(row - 1 < 0 || col + i + j - 1 < 0 || unsigned(row - 1) >= playedBoard->getYSize()
					|| unsigned(col + i + j - 1) >= playedBoard->getXSize()) {
						playedBoard->resetPlacedTiles(targetCoordinates, savedMult);
						return false;
			}
			if(playedBoard->getSquare(row - 1, col + i + j - 1)->isEmpty() == true) {
				savedMult.push_back(playedBoard->getSquare(row - 1, col + i + j - 1)->getMultiplier());
				wordMult = playedBoard->getSquare(row - 1, col + i + j - 1)->assignTile(tilesUsed[i]);
				targetCoordinates.push_back(make_pair(row - 1, col + i + j - 1));
			} else {
				addedScore += playedBoard->getSquare(row - 1, col + i + j - 1)->getScore();
				i--;
				j++;
			}
		}

		// For coordinates of every letter that was placed, check top, left, bottom, right
		for(unsigned int i = 0; i < targetCoordinates.size(); i++) {

			// CheckRow and CheckCol represent the x and y coord of the tile that was places
			int checkRow = targetCoordinates[i].first;
			int checkCol = targetCoordinates[i].second;
			int staticCheckRow = checkRow;
			int staticCheckCol = checkCol;
			bool topBottomCount = 0;

			// If left square is not empty, go all the way to the left and back to right
			while(checkCol - 1 >= 0) {
				if(playedBoard->getSquare(checkRow, checkCol - 1)->isEmpty() == false) {
					checkCol--;
				} else break;
			}

			// When get all the way to the left, go all the way back to the right
			while(checkCol + 1 < playedBoard->getXSize()) {
				if(playedBoard->getSquare(checkRow, checkCol + 1)->isEmpty() == false) {
					buffer += playedBoard->getSquare(checkRow, checkCol)->getLetter();

					if(!seen) {
						addedScore += playedBoard->getSquare(checkRow, checkCol)->getScore();
					}

					checkCol++;
				} else break;
			}

			// Add last character into the buffer to check against dictionary
			buffer += playedBoard->getSquare(checkRow, checkCol)->getLetter();
			if(!seen) {
				addedScore += playedBoard->getSquare(checkRow, checkCol)->getScore();

				if(wordMult > 1) {
					addedScore = addedScore * wordMult;
				}
				seen = true;
			}

			// If the buffer at the end is not a word, clear squares and return;
			if((buffer.length() > 0 && !(myDict.isWord(buffer)))) {
				if(buffer.length() != 1) {
					// Reset the squares that were changed
					playedBoard->resetPlacedTiles(targetCoordinates, savedMult);
					return false;
				}
			}

			buffer = "";

			// If the top square is not empty, go all the way to the top and back down
			while(staticCheckRow - 1 >= 0) {
				if(playedBoard->getSquare(staticCheckRow - 1, staticCheckCol)->isEmpty() == false) {
					staticCheckRow--;
				} else break;
			}

			// When get all the way to the top, go all the way back down
			while(staticCheckRow + 1 < playedBoard->getYSize()) {
				if(playedBoard->getSquare(staticCheckRow + 1, staticCheckCol)->isEmpty() == false) {
					buffer += playedBoard->getSquare(staticCheckRow, staticCheckCol)->getLetter();
					addedScore += playedBoard->getSquare(staticCheckRow, staticCheckCol)->getScore();
					topBottomCount++;
					staticCheckRow++;
				} else break;
			}

			// Add the last letter to the buffer
			buffer += playedBoard->getSquare(staticCheckRow, staticCheckCol)->getLetter();
			if(topBottomCount > 0) {
				addedScore += playedBoard->getSquare(staticCheckRow, staticCheckCol)->getScore();
			}
			if((buffer.length() > 0 && !(myDict.isWord(buffer)))) {
				if(buffer.length() != 1) {
					// Reset squares that were changed
					playedBoard->resetPlacedTiles(targetCoordinates, savedMult);
					return false;
				}
			}

			buffer = "";
		}

		// Reset square multipliers to 0 and score to what it was before
		for(unsigned int i = 0; i < tilesUsed.size(); i++) {
			// Now square has no multiplier and same points as before
			playedBoard->getSquare(row - 1, col + i + j - 1)->setMult("...");
			playedBoard->getSquare(row - 1, col + i + j - 1)->setScore(tilesUsed[i]->getPoints());
		}

	}

	// Add the total square together
	_score += addedScore;

	eraseFromHand(tilesUsed);
	fillHand(bag);
	targetCoordinates.clear();

	return true;
}

bool Player::exchange(Bag& bag, string letters) {

	string buffer = "";
	vector<Tile*> tilesUsed;

	// cin >> letters;

	// Put the letters that are cin into a vector of strings to check
	vector<char> checkVector;
	for(unsigned int i = 0; i < letters.length(); i++) {
		checkVector.push_back(letters[i]);
	}

	// If player doesn't have all the tiles, return
	if(!checkTiles(checkVector)) {
		// cout << "DIDN'T PASS THE CHECK" << endl;
		return false;
	}

	// IF THE PLAYER HAS ALL THE TILES.......
	// Find tiles corresponding to the characters that the player entered
	// and push them into a temp vector

	vector<Tile*> temp;

	// NOTE: DOES NOT DELETE TILES FROM PLAYER'S HAND
	for(unsigned int i = 0; i < letters.length(); i++) {
		for(unsigned int j = 0; j < playerTiles.size(); j++) {
			if(playerTiles[j]->getUse() == letters[i]) {
				temp.push_back(playerTiles[j]);
				break;
			}
		}
	}

// GOOD ----------------------------------------- //
	int tempSize = temp.size();
	int playerTilesSize = playerTiles.size();

	for(int i = 0; i < tempSize; ++i) {
		for(int j = 0; j < playerTilesSize; ++j) {
			if(playerTiles[j]->getUse() == temp[i]->getUse()) {
				playerTiles.erase(playerTiles.begin() + j);
				bag.addTile(playerTiles[j]);
				break;
			}
		}
	}

	set<Tile*>::iterator it;
	set<Tile*> drawnTiles = bag.drawTiles(tempSize);

	for(it = drawnTiles.begin(); it != drawnTiles.end(); ++it) {
		playerTiles.push_back(*it);
	}

	return true;
}

int Player::move(string currentMove, string choice, Bag& bag, Board* playedBoard, Dictionary myDict, string dir,
int row, int col) {

	if(currentMove == "PLACE") {
		if(place(playedBoard, choice, myDict, bag, dir,
		row, col)) return 1;
			else {
				cout << "Invalid Place. Please try again." << endl;
				return 0;
			}
	} else {
			if(exchange(bag, choice)) return 2;
			else {
				cout << "Invalid Exchange. Please try again." << endl;
				return 0;
			}
		}
}
