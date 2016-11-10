#include "inputPlayers.h"

using namespace std;

InputPlayers::InputPlayers(QBoard* actualBoard, Bag* bag, std::vector<Player>* currentPlayers, int handSize, int num)
{
	numPlayers  = num;
	playerBoard = actualBoard;
	players = currentPlayers;
	numTiles = handSize;
	gameBag = bag;

	// Overall layout
	overallLayout = new QHBoxLayout();

	// // Form to add quotes
	// Layout
	formLayout = new QVBoxLayout();
	overallLayout->addLayout(formLayout);

	// Display people's name textboxes
	for(int i = 0; i < num; i++) {
		std::stringstream ss;
		ss << i + 1;
		std::string str = ss.str();

		std::string output = "Person " + str + "'s Name:";
		QString qstr = QString::fromStdString(output);

		personLabel = new QLabel();
		personLabel->setText(qstr);
		formLayout->addWidget(personLabel);

		personInput = new QLineEdit();
		personInputs.push_back(personInput);
		formLayout->addWidget(personInput);
	}

	// Add button
	addButton = new QPushButton("Continue");
	connect(addButton, SIGNAL(clicked()), this, SLOT(makePlayers()));
	formLayout->addWidget(addButton);

	// Set overall layout
	setLayout(overallLayout);
}

InputPlayers::~InputPlayers()
{
	//TODO delete everything
	delete  overallLayout;
	delete formLayout;
	for(int i = 0; i < numPlayers; i++) {
		delete personLabel;
	}

	for(int i = 0; i < personInputs.size(); i++) {
		delete personInputs[i];
	}
	delete addButton;
}

void InputPlayers::makePlayers()
{

	for (int i = 0; i < numPlayers; ++i)
	{
		names.push_back(personInputs[i]->text().toStdString());
	}

	for (int i = 0; i < names.size(); ++i)
	{
		set<Tile*>::iterator it;
		set<Tile*> temp = gameBag->drawTiles(numTiles);

		for(it = temp.begin(); it != temp.end(); ++it) {
			playerTiles.push_back(*it);
		}

		Player tempPlayer(names[i], 0, playerTiles, numTiles);
		(*players).push_back(tempPlayer);

		playerTiles.clear();
	}

	for(unsigned int i = 0; i < players->size(); i++) {
		std::cout << (*players)[i].getName() << std::endl;
	}

	// Clear the form inputs
	for (int i = 0; i < numPlayers; ++i)
	{
		personInputs[i]->setText("");
	}

	close();

	playerBoard->setPerson(0, players);
	playerBoard->setScores(numPlayers, players);
	playerBoard->setHand((*players)[0]);
	playerBoard->getWindow()->show();
}
