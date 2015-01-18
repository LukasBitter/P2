#include "GameComponent/map.h"
#include "GameComponent/gamer.h"
#include "GameComponent/node.h"
#include "GameConnexion/server.h"
#include "GameConnexion/client.h"
#include <QtWidgets>
#include <QApplication>
#include <qdebug.h>
#include "GameMenu/gamemenumanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //Créatoin des joueur
//    Gamer *nils = new Gamer();
//    Gamer *lukas = new Gamer();
//    nils->setColor(Qt::red);
//    lukas->setColor(Qt::green);

//    Map m(nils);


    //Création de la map
//    Node *campsBaseNils = new Node(180,0,50,100,nils);
//    Node *campsBaseLukas = new Node(0,0,30,100,lukas);
//    Node *aventageNils = new Node(180,100,10,10,0);
//    Node *lienLukasNils = new Node(90,-90,50,110,0);

//    campsBaseNils->setRessourcesRate(1);
//    campsBaseLukas->setRessourcesRate(1);
//    aventageNils->setRessourcesRate(1);
//    lienLukasNils->setRessourcesRate(1);

//    campsBaseNils->setRessources(50);
//    campsBaseLukas->setRessources(50);
//    lienLukasNils->setRessources(50);

//    m.addNode(*campsBaseNils);
//    m.addNode(*campsBaseLukas);
//    m.addNode(*aventageNils);
//    m.addNode(*lienLukasNils);
//    m.addConnexion(*lienLukasNils, *campsBaseNils);
//    m.addConnexion(*lienLukasNils, *campsBaseLukas);
//    m.addConnexion(*aventageNils, *campsBaseNils);
//    m.addConnexion(*campsBaseNils, *campsBaseLukas);

//    campsBaseLukas->sendSquad(30,*campsBaseNils);
//    //*/
//    QTimer timer;
//    QObject::connect(&timer, SIGNAL(timeout()), &m, SLOT(advance()));
//    timer.start(100);

//    Form s(true);
//    Form c(false);

//    s.show();
//    c.show();

    GameMenuManager l;
    l.show();
    //m.show();
    return a.exec();
}
