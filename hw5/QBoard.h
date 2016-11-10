#ifndef QBOARD_H
#define QBOARD_H

#include <QObject>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <iostream>

#include <string>

#include "Board.h"
#include "Player.h"
#include "myButton.h"
#include "Square.h"

class QBoard : public QWidget, public Board {
  Q_OBJECT
public slots:

public:
  QBoard(std::string board_file_name);
  ~QBoard();
  void setHand(Player currPlayer);
  QPushButton* getPlay();
  QComboBox* getMove();
  QComboBox* getDirection();
  QLineEdit* getTiles();
  MyButton*** getBoard();
  void setScores(int numPlayers, std::vector<Player>* gamePlayers);
  void updateScores(int numPlayers, std::vector<Player>* gamePlayers);
  Square*** getBaseBoard();
  void updateBoard();
  int getMaxX();
  int getMaxY();
  void setPerson(int currPlayer, std::vector<Player>* gamePlayers);
  QWidget* getWindow();

protected:
  MyButton ***niceBoard;
  QLabel *personGoing;
  QPushButton *play;
  QLineEdit *tiles;
  QLabel *hand;
  QLabel *scores;
  QComboBox *moves;
  QComboBox *direction;
  QLabel *scoreShower;
  QWidget *window;
  QHBoxLayout *h1;
  QHBoxLayout *viewScores;
  QHBoxLayout *whoIsNext;
  QVBoxLayout *welcome;
  QLabel *hello;
  QLabel *howToPlay;
  QVBoxLayout *v1;
  QGridLayout *g;
  Board* backBoard;
  std::vector<QLabel*> playerScores;
  int maxX;
  int maxY;
};

#endif // QBOARD_H
