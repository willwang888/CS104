#include "NumberWindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QLabel>
#include <QString>
#include <iostream>

using namespace std;

NumberWindow::NumberWindow (QBoard* actualBoard, Bag* bag, vector<Player>* players,
  int handSize, QWidget *parent) : QWidget (parent)
{
  playerBoard = actualBoard;
  currentPlayers = players;
  numTiles = handSize;
  gameBag = bag;

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget (new QLabel ("Please enter the number of players"));

  number = new QSpinBox;
  number->setMinimum (0); number->setMaximum(13);
  number->setValue(1); number->setSingleStep(1);
  QFormLayout *fl = new QFormLayout;
  fl->addRow ("Num&ber", number);
  mainLayout->addLayout (fl);

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  quitButton = new QPushButton ("&Quit");
  confirmButton = new QPushButton ("&Confirm");
  buttonLayout->addWidget (confirmButton);
  buttonLayout->addWidget (quitButton);

  connect (confirmButton, SIGNAL(clicked()), this, SLOT(confirmPressed()));
  connect (quitButton, SIGNAL(clicked()), this, SLOT(quitPressed()));

  mainLayout->addLayout (buttonLayout);
  setLayout (mainLayout);
}

NumberWindow::~NumberWindow() {
  delete number;
  delete quitButton;
  delete confirmButton;
  delete newInputPlayerWindow;
}

void NumberWindow::closeEvent (QCloseEvent *event)
{
  std::cout << "Bye Bye.\n";
  QWidget::closeEvent (event);
}

void NumberWindow::confirmPressed ()
{
  close();
  numPlayers = number->value();
  newInputPlayerWindow = new InputPlayers(playerBoard, gameBag, currentPlayers, numTiles, numPlayers);
  newInputPlayerWindow->show();
}

int NumberWindow::getNumPlayers() {
  return numPlayers;
}

void NumberWindow::quitPressed ()
{
  std::cout << "Quit was pressed!\n";
  close ();
}
