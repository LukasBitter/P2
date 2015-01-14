#include <QDialog>
#include <QtWidgets>

#include "gamemenu.h"
#include "GameInterface/clientaffichage.h"

GameMenu::GameMenu(QWidget *parent) :
    QDialog(parent), port(10243)
{
    pbHostGame = new QPushButton(tr("Host Game"));
    pbJoinGame = new QPushButton(tr("Join Game"));
    pbQuit = new QPushButton(tr("Quit"));

    connect(pbHostGame, SIGNAL(clicked()), this, SLOT(hostGame()));
    connect(pbJoinGame, SIGNAL(clicked()), this, SLOT(joinGame()));
    connect(pbQuit, SIGNAL(clicked()), this, SLOT(close()));

    QGridLayout *buttonLayout = new QGridLayout;
    buttonLayout->addWidget(pbHostGame,0,0);
    buttonLayout->addWidget(pbJoinGame,1,0);
    buttonLayout->addWidget(pbQuit,2,0);
    setLayout(buttonLayout);

    setWindowTitle(tr("Basic RTS"));
}


void GameMenu::hostGame()
{
    affichage = new ClientAffichage(port, this, true);
    affichage->show();
}

void GameMenu::joinGame()
{
    affichage = new ClientAffichage(port, this, false);
    affichage->show();
}
