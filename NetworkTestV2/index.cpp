#include <QDialog>
#include <QtWidgets>

#include "index.h"

index::index(QWidget *parent) :
    QDialog(parent)
{
    pbNewGame = new QPushButton(tr("New Game"));
    pbJoinGame = new QPushButton(tr("Join Game"));
    pbQuit = new QPushButton(tr("Quit"));

    connect(pbNewGame, SIGNAL(clicked()), this, SLOT(initNewgame()));
    connect(pbJoinGame, SIGNAL(clicked()), this, SLOT(joinGame()));
    connect(pbQuit, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(pbNewGame);
    buttonLayout->addWidget(pbJoinGame);
    buttonLayout->addWidget(pbQuit);
    buttonLayout->addStretch(1);
    setLayout(buttonLayout);

    setWindowTitle(tr("Home Delete Game"));
}


void index::initNewgame(){

    server = new Server();
    //server->setModal(1);
    server->resize(200, 300);
    server->show();
}

void index::joinGame(){
    client = new Client();
    client->show();
}
