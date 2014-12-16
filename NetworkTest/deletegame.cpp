#include "deletegame.h"
//#include "server.h"
#include <QtWidgets>
#include <QString>
#include <QDebug>

deleteGame::deleteGame(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setColumnStretch(1, 50);
    gridLayout->setColumnStretch(2, 50);
    gridLayout->setRowStretch(1, 25);
    gridLayout->setRowStretch(2, 25);
    gridLayout->setRowStretch(3, 25);
    gridLayout->setRowStretch(4, 25);


    lPlayer1Text = new QLCDNumber(this);
    lPlayer2Text = new QLCDNumber(this);
    lPlayer1Text->setDigitCount(2);
    lPlayer2Text->setDigitCount(2);
    bAdd = new QPushButton("Ajouter");
    bDel = new QPushButton("Supprimer");

    gridLayout->addWidget(lPlayer1Text, 2, 1);
    gridLayout->addWidget(lPlayer2Text, 2, 2);
    gridLayout->addWidget(bAdd, 3, 1);
    gridLayout->addWidget(bDel, 3, 2);

    connect(bAdd, SIGNAL(clicked()), this, SLOT(addPts()));
    connect(bDel, SIGNAL(clicked()), this, SLOT(delPts()));

    connect(this, SIGNAL(endGame(int)), this, SLOT(gameEnds(int)));

    maxPts = 20;
    init();
}

deleteGame::~deleteGame()
{

}

void deleteGame::init(){
    pts = maxPts;
    lPlayer1Text->display(pts);
}

void deleteGame::delPts()
{
    if( pts!= 0)
        pts--;
    else
        emit endGame(0);
}

void deleteGame::addPts()
{
     qDebug()<<"addPts: "<<pts;
     pts++;
    if(pts<maxPts)
        pts++;

    lPlayer1Text->display(pts);
}

void deleteGame::delPtsOponent()
{

}

void deleteGame::gameEnds(int winner)
{
    QString msg;

    switch(winner)
    {
    case 0: msg= "You loose";
        break;
    case 1: msg = "You win";
            break;
    default: msg = "Unknown winner";
    }

}


