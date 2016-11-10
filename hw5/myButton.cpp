#include "myButton.h"

using namespace std;

MyButton::MyButton(Square* currSquare, int _y, int _x, int SX, int SY, QWidget *parent)
: QPushButton(parent) {
  mySquare = currSquare;
  row = _y;
  col = _x;
  _startx = SX;
  _starty = SY;
  this->setFixedSize(40, 40);
}

void MyButton::setDisplay(int row, int col) {
  string temp = "";

  // Create a pushbutton with a constructor
  if(row == _startx && col == _starty) {
    if(mySquare->getLetter() != '\0') {
      cout << "THE SCORE IS: " << mySquare->getScore() << endl;
      string c = to_string(mySquare->getScore());
      cout << "THE CHAR FOR THE SCORE IS: " << c << endl;
      temp += mySquare->getLetter();
      temp += c;
      setStyleSheet("background-color: tan");
    } else {
      temp = "***";
      setStyleSheet("background-color: gray");
    }
  } else {
    if(mySquare->getLetter() != '\0') {
      cout << "THE SCORE IS: " << mySquare->getScore() << endl;
      string c = to_string(mySquare->getScore());
      cout << "THE CHAR FOR THE SCORE IS: " << c << endl;
      temp += mySquare->getLetter();
      temp += c;
      setStyleSheet("background-color: tan");
    } else {
      if(mySquare->getMultiplier() != "...") {
        temp = mySquare->getMultiplier();
        if(temp == "2L") {
          setStyleSheet("background-color: yellow");
        } else if(temp == "3L") {
          setStyleSheet("background-color: lightgreen");
        } else if(temp == "2W") {
          setStyleSheet("background-color: lightblue");
        } else if(temp == "3W") {
          setStyleSheet("background-color: red");
        }
      } else {
        temp = mySquare->getMultiplier();
        setStyleSheet("background-color: white");
      }
    }
  }

  QString qstr = QString::fromStdString(temp);
  this->setText(qstr);
}
