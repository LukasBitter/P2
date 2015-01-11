#include <QDialog>
#include <QtWidgets>

#include "index.h"

index::index(QWidget *parent) :
    QDialog(parent)
{
    pbHostGame = new QPushButton(tr("Host Game"));
    pbJoinGame = new QPushButton(tr("Join Game"));
    pbQuit = new QPushButton(tr("Quit"));

    connect(pbHostGame, SIGNAL(clicked()), this, SLOT(hostGame()));
    connect(pbJoinGame, SIGNAL(clicked()), this, SLOT(joinGame()));
    connect(pbQuit, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(pbHostGame);
    buttonLayout->addWidget(pbJoinGame);
    buttonLayout->addWidget(pbQuit);
    buttonLayout->addStretch(1);
    setLayout(buttonLayout);

    setWindowTitle(tr("Home Delete Game"));
}


void index::hostGame()
{
    server = new Server(this);
    //server->setModal(1);
    server->resize(200, 300);
    server->show();
    client = new Client(this, true, server->getPort());
    client->show();
}

void index::joinGame()
{
    client = new Client(this, false, 0);
    client->show();
}
