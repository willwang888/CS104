#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "Board.h"
#include "Bag.h"
#include "Tile.h"
#include "Dictionary.h"

class Board;
class Dictionary;

class Player {
private:
	std::string _name;
	int _score;
	std::vector<Tile*> playerTiles;
	int maxTiles;

public:
	Player(std::string name, int score, std::vector<Tile*> tiles, int totalTiles);	//constructor
	void fillHand(Bag& bag);
	void printTiles();
	std::string getName();
	int getScore();
	std::vector<Tile*> getPlayerTiles();
	bool placeTiles(int row, int col, int addedScore, std::string dir, std::string buffer, std::vector<Tile*> tilesUsed,
		std::vector< std::pair<int, int> > targetCoordinates, std::vector<std::string> savedMult,
		std::set<Square*> checkedSquares, Board* playedBoard, Dictionary myDict, Bag* bag);
	bool place(Board* playedBoard, std::string choice, Dictionary myDict, Bag& bag, std::string dir,
	int row, int col);
	void pass();
	bool exchange(Bag& bag, std::string letters);
	int move(std::string currentMove, std::string choice, Bag& bag, Board* playedBoard, Dictionary myDict, std::string dir,
	int row, int col);
	bool checkTiles(std::vector<char> usedTiles);
	void eraseFromHand(std::vector<Tile*> targetTiles);
};

#endif /* PLAYER_H_ */
