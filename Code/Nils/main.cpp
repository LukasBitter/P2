#include "widget.h"
#include "map.h"
#include "gamer.h"
#include "node.h"
#include <QApplication>
#include <qdebug.h>
#include <qthread.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    Widget w;
    w.show();
    */

    Map m;

    //Créatoin des joueur
    Gamer *nils = new Gamer(Qt::red);
    Gamer *lukas = new Gamer(Qt::red);

    //Création de la map
    Node *campsBaseNils = new Node(180,-150,30,10,nils,0);
    Node *campsBaseLukas = new Node(-200,80,30,15,lukas,0);
    Node *aventageNils = new Node(180,10,10,10,0,0);
    Node *lienLukasNils = new Node(-10,-20,50,110,0,0);

    campsBaseNils->setRessourcesRate(1);
    campsBaseLukas->setRessourcesRate(1);
    aventageNils->setRessourcesRate(1);
    lienLukasNils->setRessourcesRate(0);
    campsBaseNils->setNbRessources(5);
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
    m.show();





    /*
    Node *n1 = new Node(150,0,10,0);
    Node *n2 = new Node(50,50,110,0);
    n1->connect(*n2);

    delete n1;
    delete n2;
    return 0;*/

    qDebug()<<"test";
    return a.exec();
}
