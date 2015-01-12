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
    //server->show();
    client = new Client(this, true, server->getPort());
    client->show();


    //Création de la map
    Map m = new Map(0);
    Node *campsBaseNils = new Node(180,-150,50,100,nils,0);
    Node *campsBaseLukas = new Node(-0,-200,30,100,lukas,0);
    Node *aventageNils = new Node(180,10,10,10,0,0);
    Node *lienLukasNils = new Node(-10,-20,50,110,0,0);

    campsBaseNils->setRessourcesRate(1);
    campsBaseLukas->setRessourcesRate(1);
    aventageNils->setRessourcesRate(1);
    lienLukasNils->setRessourcesRate(1);

    campsBaseNils->setNbRessources(50);
    campsBaseLukas->setNbRessources(50);
    lienLukasNils->setNbRessources(50);

    m.addNode(*campsBaseNils);
    m.addNode(*campsBaseLukas);
    m.addNode(*aventageNils);
    m.addNode(*lienLukasNils);
    m.addConnexion(*lienLukasNils, *campsBaseNils);
    m.addConnexion(*lienLukasNils, *campsBaseLukas);
    m.addConnexion(*aventageNils, *campsBaseNils);
    m.addConnexion(*campsBaseNils, *campsBaseLukas);
}

void index::joinGame()
{
    client = new Client(this, false, 0);
    client->show();
}
