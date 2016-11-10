// GameCommands.cpp
// 11/5/16
// David Silverstone
// an interface to play the game

#ifndef GAME_INTERFACE_SO_PLAYERS_CAN_PLAY_FFS_CPP
#define GAME_INTERFACE_SO_PLAYERS_CAN_PLAY_FFS_CPP

#include "GameCommands.hpp"
#include <iostream>
#include <sstream>
#include <queue> // std::deque baby
using std::cout;
using std::cerr;
using std::endl;
using std::getline;

// static std::deque<bool> passLog; // breh
// passLog has file scope, will only be initialized once, and is only visible in this file
// All of these functions, as well as this global data structure, act as members of Game, within
// the framework of the public API provided


void printBoard(const Game& game) {
	cout << game.getBoard()->getDisplay();
}

void sayWhoseTurn(const Game& game) {
	cout << game.getCurrentPlayer()->getName() << ", it's your turn." << endl;
}

void scoreBoard(const Game& game) { // originally, was func(const Game&, bool ended = false)
	cout << (game.isFinished() ? "Final" : "Current") << " scores: " << endl;
	auto nameScorePairs = game.getScores();
	for (const auto & thing : nameScorePairs) { // string, int pairs
		cout << thing.first << ": " << thing.second << endl;
	}
	endl(cout);
}

void promptMoves(const Game& game) {
	std::cout << "To pass your turn, type PASS.\n"
			  << "To discard tiles, type EXCHANGE, followed by a string of those tiles.\n"
			  << "To place a word, type PLACE, followed by the following:\n"
			  << "   first, either a | or - for vertical/horizontal placement;\n"
			  << "   second, the row (from the top), the column (from the left),\n"
			  << "   third, a sequence of letters to place;\n"
			  << "   to use a blank tile, type ? followed by the letter you want to use it for.\n"
			  << "Your current tiles: "
			  << game.getCurrentPlayer()->getHand() << std::endl;
} // beautiful

bool getMove(Game& game) {
	std::string action;

	Player* pDude = game.getCurrentPlayer();
	std::string pDudeName = pDude->getName();
	// I use this prvalue several times in the function, so I bind an lvalue by declaring a variable to it

	try { // obtain the move - checks if such a command for a move is illegal, invalid, or otherwise disqualifiable
		// #ifdef STILL_CONSOLE
		getline(std::cin, action);
		action = strtoupper(action);
		Move m(action, *pDude);
		// I could've done this as a reference to prvalue - y u no implement perfect forwarding Dr. Kempe
		// board.executeMove(std::move(m)) more efficient yo
		// y' cain't even move-construct or move-assign Move, ironically. Kempe pls

		// catches at largest encompassing scope logically go here, but it gave me 'm is out of scope' errors

		if (m.isPass()) {
			cout << pDudeName << " passes their turn.\n\n";
			try  {
				game.makeMove(m);
			}
			catch (MoveException & e) {
				cerr << '\t' << e.getMessage() << endl;
				// this particular invocation should be noexcept
				// but this is just in case
			}
			// passLog.push_back(true);
			// passLog.pop_front();
			return true;
		}
		else {
			// auto bagThing = game.getBag(); // type deduction breh
			// it nice yo
			try {
				game.makeMove(m);
			} catch (MoveException & e) { // these only throw if they try to place
				std::string eMessage = e.getMessage();
				#ifdef DEBUG
				cerr << '\t' << eMessage << endl;
				#endif /* DEBUG */
				cerr << "  ";
				if (eMessage.substr(0,4) == "WORD") {
					// invalid word - not in dictionary
					cerr << eMessage.substr(5) + " is not a legal word.";
				}
				else {
					if (eMessage == "OUTOFBOUNDS") {
						cerr << "One or more of your tiles would end up out of bounds.";
					} else if (eMessage == "OCCUPIED") {
						cerr << "You cannot start on an occupied square.";
					} else if (eMessage == "NOSTART") {
						cerr << "The first move must use the start square.";
					} else if (eMessage == "NOWORDS") {
						cerr << "A move must form a word.";
					} else if (eMessage == "NONEIGHBOR") {
						cerr << "At least one of your tiles must be placed adjacent to a previously placed tile.";
					}
				}
				cerr << " Please try another move.\n\n";
				return false;
			}
			if (!game.bagEmpty()) {
				game.refillTiles();
				// pDude deserves his/her/their tiles after a long, hard day at the scrabble mine, yo
				cout << pDudeName << " drew " << game.getRecentDraw() << endl;
			}
			if (m.isWord()) { // PLACE command
				cout << pDudeName << " formed these words: ";
				for (auto&& formations : game.getRecentWords()) {
					cout << formations << '\t';
				}
				endl(cout);
				cout << "Score for this round: " << game.getRecentScore() << endl;
				cout << "Your new score: " << pDude->getPoints() << endl << endl;
			}
		}

		// #endif STILL_CONSOLE
	} catch (MoveException & q) {
		// handle the exception
		std::string qMessage = q.getMessage();
		#ifdef DEBUG
		cerr << '\t' << qMessage << endl;
		#endif /* DEBUG */
		cerr << "  ";
		if (qMessage == "EMPTY") {
			cerr << "Exchange or Place must specify at least one tile.";
		} else if (qMessage == "MALFORMED") {
			cerr << "Command was malformed.";
		} else if (qMessage == "WRONGTILES") {
			cerr << "You do not have these tiles.";
		} else if (qMessage == "NOTLETTER") {
			cerr << "One or more of the tiles you specified was not a letter or '?'.";
		} else {
			cerr << "Did not recognize your command.";
		}
		cerr << " Please try another move.\n\n";
		return false;
	}
	// passLog.push_back(false);
	// passLog.pop_front();
	return true;
}

void finalizeMove(Game& g) {
	endl(cout);
	g.finalizeMove();
}

void finalSubtractionWrapper(Game& game) {
	std::string winName = game.getCurrentPlayer()->getName();
	cout << winName << " played all tiles in their hand!" << endl;
	auto container = game.finalSubtraction();
	for (auto&& information : container) { // I love modern C++
		cout << information.first << " gave " << winName
		<< ' ' << information.second << " points." << endl;
		// perhaps game.getCurrentPlayer()->addPoints(information.second); ?
		// no, it does it for me :)
	}
}


void operator<< (Game& g, void (*pf)(Game&)) {
	/*return*/ pf(g);
}

void operator<< (const Game& g, void (*pf)(const Game&)) {
	/*return*/ pf(g);
} // void functions don't return anything, hence template specialization

void operator>> (Game& g, void (*pf)(Game&)) {
	pf(g);
} // semantically the same as the above, but inline (no pun intended) with
// the convention of operator<< representing output, and >> representing input,
// produces more readable code.

template <typename T>
T operator<< (const Game& g, T (*pf)(const Game&)) {
	return pf(g);
}

template <typename T>
T operator<< (Game& g, T (*pf)(Game&)) {
	return pf(g);
}

template <typename T>
T operator>> (Game& g, T (*pf)(Game&)) {
	return pf(g);
} // T is instantiated as bool for getMove

void play(Game& game) {
	bool validMoveFlag = false;
	do {
		game << sayWhoseTurn;
		game << scoreBoard;
		game << printBoard;
		//TODO: play lol
		game << promptMoves;
		validMoveFlag = game >> getMove;
	} while (!validMoveFlag);
	if (game.getCurrentPlayer()->numberofTiles() == 0) {
		game << finalSubtractionWrapper;
	}
	game << finalizeMove;
}

void endDialog(Game& game) {
	if (!game.isFinished()) return;
	game << scoreBoard;
	// keep mouthful_t Game::finalSubtraction() in mind
	// see if I need to call it, or at least for
	cout << "Winners are: " << endl;
	for (auto&& winners : game.getWinners()) {
		cout << winners << endl;
	}
}

void init(Game& game, int& numPl) {
	static bool b = false; // static to assure this function runs only once
	if (b) return; // breh you can't initialize the number of players twice
	// static std::deque<bool> passLog{}; // default-construct me an empty deque<bool> baby
	bool flag = false;
	int pCt = 0;
	std::string s;
	int thatMany = 0;
	while (!flag) {
		cout << "Please enter the number of players (1-8): ";
		std::cin >> s;
		std::cin.ignore();
        std::stringstream ss(s);
        flag = (bool) (ss >> pCt); // true iff s (text entered) could extract int
        if (!flag) { // if they fail to enter a number 1-8
			thatMany++;
			cout << "Incorrect number of players." << std::endl;
            if (thatMany >= 4 && thatMany <= 8) {
				cout << "I'm giving up on you." << std::endl;
			}
			else if (thatMany >= 9) {
				cout << "Seriously, how does it take someone "
				<< thatMany << " tries to enter a number from 1 to 8?"
				<< std::endl;
			}
			continue;
        } // if they don't succeed to enter an int 1-8
		// by now they've succeeded to type a number. Wow;
		if (pCt < 1 || pCt > 8){
			cout << "Incorrect number of players." << std::endl;
			flag = false;
			thatMany++;
			if (thatMany >= 4 && thatMany <= 8) {
				cout << "I'm giving up on you." << std::endl;
			}
			else if (thatMany >= 9) {
				cout << "Seriously, how does it take someone "
				<< thatMany << " tries to enter a number from 1 to 8?"
				<< std::endl;
			}
			continue;
		}
		else if (thatMany >= 12) {
			cout << "Gee, it only took you " << thatMany << " tries."
			<< std::endl;
		}
    }
	// by now they've succeeded to type a number. Wow
	s.clear(); // recycle the string
	for (int i = 1; i <= pCt; i++) {
		cout << "Enter name of player " << i << ": ";
		getline(std::cin,s);
		game.addPlayer(s);
		// passLog.push_back(false); // default to all players "haven't passed" on the before 0 move
	}
	b = true;
	numPl = pCt;
	endl(cout);
}


#endif /* GAME_INTERFACE_SO_PLAYERS_CAN_PLAY_FFS_CPP */
