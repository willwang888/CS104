#include "scrabble.h"

using namespace std;

Scrabble::Scrabble(QApplication *app, string dictionaryFileName, string boardFileName,
	string bagFileName, unsigned int numTiles)
	: 	dict(dictionaryFileName), bag(bagFileName, 10)
{

  this->app = app;

  gameBoard = new QBoard(boardFileName);

  numPlayersWindow = new NumberWindow(gameBoard, &bag, &gamePlayers, numTiles);

	passCount = 0;
	playerTurn = 0;
	bagEmpty = false;
	underBoard = gameBoard;
	gameOver = false;
}

Scrabble::~Scrabble() {
	delete inputPlayersWindow;
	delete numPlayersWindow;
	delete gameBoard;
}

void Scrabble::playGame() {
	QObject::connect(gameBoard->getPlay(), SIGNAL(clicked()), this, SLOT(enter()));
	for(int i = 0; i < gameBoard->getMaxX(); i++) {
		for(int j = 0; j < gameBoard->getMaxY(); j++) {
			QObject::connect(gameBoard->getBoard()[i][j], SIGNAL(clicked()), this, SLOT(start()));
		}
	}
  numPlayersWindow->show();
}

void Scrabble::start() {
	QString str = gameBoard->getTiles()->text();
	MyButton *called = (MyButton*) QObject::sender();
	for (int x = 0; x < gameBoard->getMaxX(); x++) {
		for (int y = 0; y < gameBoard->getMaxY(); y++) {
		if (gameBoard->getBoard()[x][y] == called) {
			placedRow = x + 1;
			placedCol = y + 1;
			}
		}
	}
}

void Scrabble::enter() {
	// cout << "ENTERING IN SCRABBLE" << endl;

	int validMove;
	string choice;
	string currMove;
	string dir;

	numPlayers = numPlayersWindow->getNumPlayers();
	// cout << "NUMBER OF PLAYERS: " << numPlayers << endl;
	// cout << "IT IS PLAYER " << playerTurn << "'s turn" << endl;
	currMove = gameBoard->getMove()->currentText().toStdString();
	// cout << "CURRENT MOVE IS: " << currMove << endl;
	// cout << "CUREENT DIRECTION IS: " << dir << endl;

	// If current move is != PASS, then just
	if(currMove != "PASS") {
		choice = gameBoard->getTiles()->text().toStdString();
		dir = gameBoard->getDirection()->currentText().toStdString();
		// cout << "CHOICE IS: " << choice << endl;
		// cout << "PLACED ROW: " <<placedRow << endl;
		// cout << "PLACED COL: " << placedCol << endl;
		// cout << "DIRECTION IS: " << dir << endl;

		if(currMove == "PLACE" && choice == "") {
			QMessageBox::information(this, "Error", "Enter Tiles in Selection!");
		} else if(currMove == "PLACE" && placedRow == 1000) {
			QMessageBox::information(this, "Error", "Select a Tile to Start On!");
		} else if(currMove == "EXCHANGE" && choice == "") {
			QMessageBox::information(this, "Error", "Enter Tiles to Exchange!");
		} else {
			validMove = gamePlayers[playerTurn].move(currMove, choice, bag, underBoard, dict, dir,
			placedRow, placedCol);

			if(validMove == 2) {
				QMessageBox::information(this, "Success!", "Tiles Exchanged!");
				gamePlayers[playerTurn].printTiles();
				gameBoard->setHand(gamePlayers[playerTurn]);
				playerTurn++;
			} else if(validMove == 1) {
					// Player places
					gamePlayers[playerTurn].printTiles();
					gameBoard->setHand(gamePlayers[playerTurn]);
					underBoard->printBoard();
					playerTurn++;
				}

			// After a move, check if bag is empty
			if(bag.tilesRemaining() == 0) {
				bagEmpty = true;
			}

			if(validMove == 0 && currMove == "EXCHANGE") {
				QMessageBox::information(this, "Error", "Invalid exchange, please try again!");
			} else if(validMove == 0 && currMove == "PLACE") {
				QMessageBox::information(this, "Error", "Invalid place, please try again!");
			}

			// After a move, check if bag is empty
			if(bag.tilesRemaining() == 0) {
				bagEmpty = true;
			}
		}
		} else {
			passCount++;
			playerTurn++;
		}

		// Print out each player's score
		for(unsigned int j = 0; j < gamePlayers.size(); j++) {
			cout << gamePlayers[j].getName() << ": " << gamePlayers[j].getScore() << endl;
		}

		// Go onto the next player, if more than # of players, wrap around
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

		// If game is over, quit the game
		if(gameOver == true) {
			cout << "CLOSE" << endl;
			QMessageBox msgBox;
			string temp = "";
			msgBox.setText("Thanks for playing! Here are the final scores:");
			for(int i = 0; i < numPlayers; i++) {
				string finScore = to_string(gamePlayers[i].getScore());
				temp += gamePlayers[i].getName();
				temp += ": ";
				temp += finScore;
				temp += "  ";
			}
			QString qstr = QString::fromStdString(temp);
			msgBox.setInformativeText(qstr);
			msgBox.setDefaultButton(QMessageBox::Save);
			msgBox.exec();
			QApplication::quit();
		}

		close();
		gameBoard->setPerson(playerTurn, &gamePlayers);
		gameBoard->updateScores(numPlayers, &gamePlayers);
		gameBoard->setHand(gamePlayers[playerTurn]);
		gameBoard->updateBoard();
		gameBoard->getWindow()->show();
	}
	// close();
	// gameBoard->getWindow()->show();
