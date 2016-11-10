#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <iostream>

#include "Tile.h"
#include "Dictionary.h"
#include "Bag.h"
#include "Board.h"
#include "Square.h"
#include "Player.h"
#include "QBoard.h"
#include "inputPlayers.h"
#include "NumberWindow.h"

class Scrabble : public QWidget {
  Q_OBJECT
public slots:
  void enter();
  void start();
public:
  Scrabble(QApplication *app, std::string dictionaryFileName, std::string boardFileName,
    std::string bagFileName, unsigned int numTiles);
  ~Scrabble();
  void playGame();
  QBoard* getBoard();
protected:
  QApplication *app;
  QBoard *gameBoard;
  Board* underBoard;
  Dictionary dict;
  Bag bag;
  InputPlayers *inputPlayersWindow;
  NumberWindow *numPlayersWindow;
  std::vector<Player> gamePlayers;
  bool gameOver;
  int passCount;
  bool bagEmpty;
  int numPlayers;
  int playerTurn;
  int placedRow = 1000;
  int placedCol = 1000;
};

#endif // SCRABBLE_H
