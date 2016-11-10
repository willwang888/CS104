#ifndef INPUTPLAYERS_H
#define INPUTPLAYERS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "Player.h"
#include "QBoard.h"

class InputPlayers : public QWidget
{
	Q_OBJECT
public:
	InputPlayers(QBoard* actualBoard, Bag* bag, std::vector<Player>* currentPlayers, int handSize, int num);
	~InputPlayers();

private slots:
	void makePlayers();
	// void displayQuote(int quoteIndex);

protected:
	// // UI
	// Layouts
	QHBoxLayout* overallLayout;

	// // Displayed quote
	// // QVBoxLayout* quoteDisplayLayout;
	// // QLabel* quoteDisplay;
	// QLabel* personDisplay;

	// List of quotes
	QListWidget* quoteListWidget;

	// Form for new quote
	QVBoxLayout* formLayout;
	QLabel* personLabel;
	QLineEdit* personInput;
	QPushButton* addButton;

	// List of people quoted, used to be people
	std::vector<QLineEdit*> personInputs;
	std::vector<Tile*> playerTiles;
	std::vector<Player>* players;
	std::vector<std::string> names;
	int numPlayers;
	int numTiles;
	Bag* gameBag;

	// Scrabble Board
	QBoard *playerBoard;
};

#endif // INPUTPLAYERS_H
