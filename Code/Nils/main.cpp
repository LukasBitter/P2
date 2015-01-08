#include "map.h"
#include "gamer.h"
#include "node.h"
#include <QtWidgets>
#include <QApplication>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Map m;

    //Créatoin des joueur
    Gamer *nils = new Gamer(Qt::red);
    Gamer *lukas = new Gamer(Qt::green);

    //Création de la map
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

    m.addNode(*campsBaseNils);
    m.addNode(*campsBaseLukas);
    m.addNode(*aventageNils);
    m.addNode(*lienLukasNils);
    m.addConnexion(*lienLukasNils, *campsBaseNils);
    m.addConnexion(*lienLukasNils, *campsBaseLukas);
    m.addConnexion(*aventageNils, *campsBaseNils);
    m.addConnexion(*campsBaseNils, *campsBaseLukas);
    Connexion *c = m.getLstConnexion().value(2);

    //Action de la partie
    campsBaseNils->sendSquad(1, *aventageNils);
    campsBaseLukas->sendSquad(3, *lienLukasNils);
    campsBaseNils->sendSquad(10, *lienLukasNils);
    campsBaseNils->sendSquad(20, *aventageNils);
    campsBaseLukas->sendSquad(20, *campsBaseNils);
    campsBaseNils->sendSquad(20, *campsBaseLukas);
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &m, SLOT(advance()));
    timer.start(200);

    m.show();
    return a.exec();
}
