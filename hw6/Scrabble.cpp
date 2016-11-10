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
// #include <ctime>
#include "Game.h"
#include "Util.h"
#include "Exceptions.h"
// #include "Qt/manager.hpp"
#include "GameCommands.hpp"
#include "ScorePlayer.h"

#ifndef DEBUG
#define NDEBUG 1
#else
#include <cassert>
#endif /* DEBUG */

using namespace std;

int main (int argc, char **argv)
{
	if (argc < 2 || argc > 2) {
		cout << "Usage: Scrabble <config-filename>\n";
		return -1;
	}

	try {
		Game game(argv[1]);
		int numPl = 0;

		ScorePlayer test;
		Dictionary* dict = game.getDictionary();
		test.initialize(dict);
		test.printPrefix();
		if(test.checkPrefix("AARDVAR")) {
			cout << "GOOD" << endl;
		}

		init(game, numPl);

		#ifdef DEBUG
		std::cout << "Starting game with " << numPl << " players." << std::endl << std::endl;
		#endif

		set<Tile*> currentHand = game.getCurrentPlayer()->getHandTiles();
		test.createMap(currentHand);

		cout << "SIZE OF THE MAP IS: " << test.getMap().size() << endl;

		while (!game.isFinished()) {
			play(game);
		}

		endDialog(game);

		return 0;
	}
	catch (invalid_argument& e) {
		cerr << "Fatal Error! " << e.what() << endl;
	} catch (ConfigParameterException& q) {
		string qMessage = q.getMessage();
		cerr << "Config parameter error! " << qMessage << endl;
		cerr << "The config file did not specify ";
		if 		(qMessage == "NUMBER") cerr << "the number of tiles for a hand." << endl;
		else if (qMessage == "BOARD")  cerr << "a file to read the board from." << endl;
		else if (qMessage == "TILES")  cerr << "a file to read the bag from." << endl;
		else 	/* DICTIONARY */ 	   cerr << "a file to read the dictionary from." << endl;
	} catch (FileException& q) {
		string qMessage = q.getMessage();
		cerr << "File error! " << qMessage << endl;
		if (qMessage == "CONFIG")
			cerr << "The config file ";
		else if (qMessage == "BAG")
			cerr << "The bag file ";
		else if (qMessage == "BOARD" || qMessage == "BOARDCONTENT")
			cerr << "The board file ";
		else if (qMessage == "INIT" || qMessage == "INITCONTENT")
			cerr << "The initialization file ";
		else /* DICTIONARY */
			cerr << "The dictionary file ";
		if (qMessage == "INITCONTENT" || qMessage == "BOARDCONTENT")
			cerr << "contained a wrong symbol." << endl;
		else
			cerr << "could not be opened." << endl;
	}


	return 1;
}
