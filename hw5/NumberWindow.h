#ifndef NUMBERWINDOW_H
#define NUMBERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QCloseEvent>

#include "inputPlayers.h"

class NumberWindow : public QWidget
{
  Q_OBJECT

    public:
    NumberWindow (QBoard* actualBoard, Bag* bag, std::vector<Player>* players, int handSize, QWidget *parent = 0);
    ~NumberWindow();
    void closeEvent (QCloseEvent *event);

    public slots:
    void confirmPressed ();
    void quitPressed ();
    int getNumPlayers();

 protected:
    QPushButton *quitButton, *confirmButton;
    QSpinBox *number;
    InputPlayers *newInputPlayerWindow;
    QBoard* playerBoard;
    std::vector<Player>* currentPlayers;
    int numTiles;
    int numPlayers;
    Bag* gameBag;
};

#endif // NUMBERWINDOW_H
