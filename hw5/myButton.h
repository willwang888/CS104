#ifndef MYBUTTON_H
#define MYBUTTON_H

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

// #include "Player.h"
#include "Square.h"
#include "Board.h"

class MyButton : public QPushButton {
public:
  MyButton(Square* currSquare, int _y, int _x, int SX, int SY, QWidget *parent = 0);
  void setDisplay(int row, int col);
protected:
  Square* mySquare;
  int row;
  int col;
  int _startx;
  int _starty;
};

#endif // MYBUTTON_H
