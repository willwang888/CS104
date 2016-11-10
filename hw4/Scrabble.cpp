/*
 * Scrabble.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <locale>

#include "Tile.h"
#include "Dictionary.h"
#include "Bag.h"
#include "Board.h"
#include "Square.h"
#include "Player.h"

using namespace std;

void readConfigFile (string config_file_name,
					 string & dictionary_file_name,
					 string & board_file_name,
					 string & bag_file_name,
					 unsigned int & hand_size)
{
	ifstream configFile (config_file_name.c_str());
	string line;
    bool number = false, board = false, tiles = false, dictionary = false;

	if (!configFile.is_open())
		throw invalid_argument("Cannot open file: " + config_file_name);
	while (getline (configFile, line))
	{
		stringstream ss (line);
		string parameter;
		ss >> parameter;
		if (parameter == "NUMBER:")
			{ ss >> hand_size; number = true; }
		else if (parameter == "BOARD:")
		    { ss >> board_file_name; board = true; }
		else if (parameter == "TILES:")
			{ ss >> bag_file_name; tiles = true; }
		else if (parameter == "DICTIONARY:")
			{ ss >> dictionary_file_name; dictionary = true; }
	}
	if (!number)
		throw invalid_argument("Hand size not specified in config file");
	if (!board)
		throw invalid_argument("Board file name not specified in config file");
	if (!tiles)
		throw invalid_argument("Bag file name not specified in config file");
	if (!dictionary)
		throw invalid_argument("Dictionary file name not specified in config file");
}

int main (int nargs, char **args)
{
	if (nargs < 2 || nargs > 2)
		cout << "Usage: Scrabble <config-filename>\n";
	try {
		string dictionaryFileName, boardFileName, bagFileName;
		unsigned int numTiles;

		readConfigFile (args[1],
						dictionaryFileName, boardFileName, bagFileName,
						numTiles);

		Dictionary dict (dictionaryFileName);
		Board board (boardFileName);
		Bag bag (bagFileName, 10); // second argument is random seed

// ---------------------------------------------------------------------- //
		int numPlayers;
		int playerTurn = 0;
		string name;
		vector<Player> gamePlayers;
		vector<Tile*> playerTiles;
		bool gameOver = false;
		int passCount = 0;
		bool bagEmpty = false;

		board.printBoard();

		cout << "How many players?:" << endl;
		cin >> numPlayers;

		for(int i = 0; i < numPlayers; ++i) {
			cout << "Player " << i + 1 << "'s name: " << endl;
			cin >> name;

			set<Tile*>::iterator it;
			set<Tile*> temp = bag.drawTiles(numTiles);

			for(it = temp.begin(); it != temp.end(); ++it) {
				playerTiles.push_back(*it);
			}

			Player tempPlayer(name, 0, playerTiles, numTiles);
			gamePlayers.push_back(tempPlayer);
			playerTiles.clear();
		}

		// ------ PLAYERS HAVE BEEN INITIALIZED  ------- //

		while(!gameOver) {
			// Cycle through all game players and ask them for their move
		 	int validMove;
			string currMove;

			cout << "It's " << gamePlayers[playerTurn].getName() << "'s turn: " << endl;
			gamePlayers[playerTurn].printTiles();

			cout << "WHAT MOVE WOULD YOU LIKE TO DO: " << endl;
			cin >> currMove;

			// If current move is != PASS, then just
			if(currMove != "PASS") {
				validMove = gamePlayers[playerTurn].move(currMove, bag, board, dict);
				passCount = 0;

				// After a move, check if bag is empty
				if(bag.tilesRemaining() == 0) {
					bagEmpty = true;
				}

				while(validMove == 2) {
					cout << "Tiles Exchanged." << endl;
					gamePlayers[playerTurn].printTiles();
					cout << "Please enter another move: " << endl;
					cin >> currMove;
					if(currMove == "PASS") {
						passCount++;
						break;
					} else {
						passCount = 0;
					}
					validMove = gamePlayers[playerTurn].move(currMove, bag, board, dict);

					// After a move, check if bag is empty
					if(bag.tilesRemaining() == 0) {
						bagEmpty = true;
					}
				}

				while(validMove == 0) {
					string currMove;
					cout << "Please enter another valid move: " << endl;
					gamePlayers[playerTurn].printTiles();
					cin >> currMove;
					if(currMove != "PASS") {
						validMove = gamePlayers[playerTurn].move(currMove, bag, board, dict);
						passCount = 0;
					} else {
						passCount++;
						break;
					}

					// After a move, check if bag is empty
					if(bag.tilesRemaining() == 0) {
						bagEmpty = true;
					}
				}
			} else {
				passCount++;
			}

			// Print out each player's score
			for(unsigned int j = 0; j < gamePlayers.size(); j++) {
				cout << gamePlayers[j].getName() << ": " << gamePlayers[j].getScore() << endl;
			}

			board.printBoard();

			// Go onto the next player, if more than # of players, wrap around
			playerTurn++;
			if(playerTurn == numPlayers) {
				playerTurn = 0;
			}

			if(passCount == numPlayers) {
				gameOver = true;
			}

			// If bag is empty and player's hand is empty, game is over
			if(bagEmpty && gamePlayers[playerTurn].getPlayerTiles().size() == 0) {
				gameOver = true;
			}

		}

		return 0;
	}
	catch (invalid_argument & e)
	{ cout << "Fatal Error! " << e.what(); }

	return 1;
}
