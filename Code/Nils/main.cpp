#include "map.h"
#include "gamer.h"
#include "node.h"
#include <QApplication>
#include <qdebug.h>
#include <qthread.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Map m;

    //Créatoin des joueur
    Gamer *nils = new Gamer(Qt::red);
    Gamer *lukas = new Gamer(Qt::green);

    //Création de la map
    Node *campsBaseNils = new Node(180,-150,30,10,nils,0);
    Node *campsBaseLukas = new Node(-200,80,30,100,lukas,0);
    Node *aventageNils = new Node(180,10,10,10,0,0);
    Node *lienLukasNils = new Node(-10,-20,50,110,0,0);

    campsBaseNils->setRessourcesRate(1);
    campsBaseLukas->setRessourcesRate(1);
    aventageNils->setRessourcesRate(1);
    lienLukasNils->setRessourcesRate(0);
    campsBaseNils->setNbRessources(50);
    campsBaseLukas->setNbRessources(5);

    m.addNode(*campsBaseNils);
    m.addNode(*campsBaseLukas);
    m.addNode(*aventageNils);
    m.addNode(*lienLukasNils);
    m.addConnexion(*lienLukasNils, *campsBaseNils);
    m.addConnexion(*lienLukasNils, *campsBaseLukas);
    m.addConnexion(*aventageNils, *campsBaseNils);

    //Action de la partie
    campsBaseNils->sendSquad(1, *aventageNils);
    campsBaseLukas->sendSquad(3, *lienLukasNils);
    campsBaseNils->sendSquad(5, *lienLukasNils);
    campsBaseNils->sendSquad(20, *aventageNils);

    m.show();
    return a.exec();
}
