#include "map.h"
#include "gamer.h"
#include "node.h"
#include <QtWidgets>
#include <QApplication>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //Créatoin des joueur
    Gamer *nils = new Gamer(Qt::red);
    Gamer *lukas = new Gamer(Qt::green);
    Map m(nils);


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

    campsBaseNils->sendSquad(30,*lienLukasNils);

    QString s = m.getUpdateString();

    campsBaseNils->setRessourcesRate(0);
    campsBaseLukas->setRessourcesRate(0);
    aventageNils->setRessourcesRate(0);
    lienLukasNils->setRessourcesRate(0);

    campsBaseNils->setNbRessources(0);
    campsBaseLukas->setNbRessources(0);

    m.updateFromString(s);

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &m, SLOT(advance()));
    timer.start(200);

    m.show();
    return a.exec();
}
