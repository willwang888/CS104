#include "QBoard.h"

using namespace std;

QBoard::QBoard(string board_file_name) : Board(board_file_name) {
  // backBoard = board;
  maxX = _y;
  maxY = _x;

  h1 = new QHBoxLayout;
  viewScores = new QHBoxLayout;
  whoIsNext = new QHBoxLayout;
  welcome = new QVBoxLayout;
  v1 = new QVBoxLayout;
  moves = new QComboBox;
  direction = new QComboBox;
  window = new QWidget;
  g = new QGridLayout;
  g->setSpacing(0);
  // g->setMargin(0);
  niceBoard = new MyButton**[_y];

  for (int i = 0; i < _y; i++) {
    niceBoard[i] = new MyButton*[_x];
    for (int j = 0; j < _x; j++) {
      niceBoard[i][j] = new MyButton(board[i][j], i, j, _startx, _starty);
      niceBoard[i][j]->setDisplay(i, j);
      niceBoard[i][j]->setFixedSize(30, 30);
      g->addWidget(niceBoard[i][j],i+1,j+1);
      // QObject::connect(niceBoard[i][j], SIGNAL(clicked()), this, SLOT(start()));
    }
  }

  window->setLayout(v1);
  v1->addLayout(welcome);
  scoreShower = new QLabel("Scores: ");
  personGoing = new QLabel(" ");
  hello = new QLabel("Welcome to Scrabble!");
  hello->setAlignment(Qt::AlignCenter);
  howToPlay = new QLabel("To play: please choose a move from the drop\
  down menu, as well as a direction for your move if you would like to PLACE your tiles on the board.\
  To place, please choose a direction and letters from your hand that you would to place. Then, click on\
  the board to choose a square to start from. To exchange, please input the tiles you would like to exchange\
  and press enter. To pass your turn, please select pass and press enter.");
  howToPlay->setWordWrap(true);
  welcome->addWidget(hello);
  welcome->addWidget(howToPlay);
  viewScores->addWidget(scoreShower);
  whoIsNext->addWidget(personGoing);
  v1->addLayout(viewScores);
  v1->addLayout(whoIsNext);
  v1->addLayout(g);
  moves->addItem("PLACE");
  moves->addItem("EXCHANGE");
  moves->addItem("PASS");
  direction->addItem("HORIZONTAL");
  direction->addItem("VERTICAL");
  tiles = new QLineEdit();
  hand = new QLabel(" ");
  scores = new QLabel(" ");
  play = new QPushButton("Enter");
  // QObject::connect(play, SIGNAL(clicked()), this, SLOT(enter()));
  v1->addLayout(h1);
  h1->addWidget(hand);
  h1->addWidget(moves);
  h1->addWidget(direction);
  h1->addWidget(tiles);
  h1->addWidget(play);
  window->setWindowTitle("Scrabble");
}

QBoard::~QBoard() {
  delete h1;
  delete viewScores;
  delete whoIsNext;
  delete welcome;
  delete v1;
  delete moves;
  delete direction;
  delete window;
  delete g;
  for (int i = 0; i < _y; i++) {
    for (int j = 0; j < _x; j++) {
      delete niceBoard[i][j];
    }
    delete niceBoard[i];
  }
  delete niceBoard;

  delete scoreShower;
  delete personGoing;
  delete hello;
  delete howToPlay;
  delete tiles;
  delete hand;
  delete scores;
  delete play;
}

void QBoard::setHand(Player currPlayer) {
  vector<Tile*> currTiles = currPlayer.getPlayerTiles();
  string temp = "";
  temp += "[";
	for(unsigned int j = 0; j < currTiles.size(); j++) {
		if(j < currTiles.size() - 1) {
			temp += "[";
      temp += currTiles[j]->getLetter();
      temp += ", ";
      string c = to_string(currTiles[j]->getPoints());
      cout << "CHAR C IS: " << c << endl;
			temp += c;
      temp += "]";
      temp += ",";
		} else {
			temp += "[";
      temp += currTiles[j]->getLetter();
      temp += ", ";
      string c = to_string(currTiles[j]->getPoints());
			temp += c;
      temp += "]";
		}
	}
	temp += "]";

  QString qstr = QString::fromStdString(temp);

  hand->setText(qstr);
  temp = "";
}

void QBoard::setScores(int numPlayers, vector<Player>* gamePlayers) {
  vector<QString> output;
  string temp = "";

  for(int i = 0; i < numPlayers; i++) {
    temp += (*gamePlayers)[i].getName();
    temp += ": ";
    temp += to_string((*gamePlayers)[i].getScore());

    QString qstr = QString::fromStdString(temp);
    output.push_back(qstr);
    temp = "";
  }

  for(unsigned int i = 0; i < output.size(); i++) {
    QLabel* label = new QLabel(output[i]);
    playerScores.push_back(label);
  }
  for(unsigned int i = 0; i < playerScores.size(); i++) {
    viewScores->addWidget(playerScores[i]);
  }
}

void QBoard::setPerson(int currPlayer, vector<Player>* gamePlayers) {
  string temp = "It is " + (*gamePlayers)[currPlayer].getName() + "'s turn";
  QString qstr = QString::fromStdString(temp);

  personGoing->setText(qstr);
}

void QBoard::updateScores(int numPlayers, vector<Player>* gamePlayers) {
  vector<QString> output;
  string temp = "";

  for(int i = 0; i < numPlayers; i++) {
    temp += (*gamePlayers)[i].getName();
    temp += ": ";
    temp += to_string((*gamePlayers)[i].getScore());

    QString qstr = QString::fromStdString(temp);
    output.push_back(qstr);
    temp = "";
  }

  for(unsigned int i = 0; i < output.size(); i++) {
    playerScores[i]->setText(output[i]);
    // viewScores->addWidget(scores);
  }
}

void QBoard::updateBoard() {
  for (int i = 0; i < _y; i++) {
    for (int j = 0; j < _x; j++) {
      niceBoard[i][j]->setDisplay(i, j);
    }
  }
}

MyButton*** QBoard::getBoard() {
  return niceBoard;
}

int QBoard::getMaxX() {
  return maxX;
}

int QBoard::getMaxY() {
  return maxY;
}

QWidget* QBoard::getWindow() {
  return window;
}

QPushButton* QBoard::getPlay() {
  return play;
}

QComboBox* QBoard::getMove() {
  return moves;
}

QComboBox* QBoard::getDirection() {
  return direction;
}

QLineEdit* QBoard::getTiles() {
  return tiles;
}

Square*** QBoard::getBaseBoard() {
  return board;
}
