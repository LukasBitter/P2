#include "map.h"
#include "node.h"
#include "connexion.h"
#include <QGraphicsScene>
#include <QMap>
#include <climits>

#include <QDebug>

using namespace std;


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Map::Map(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setSceneRect(-100,100,200,200);
    // Désactivation des scrollbars
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(updateSelection()));
}

Map::~Map()
{
    //Efface simplement la liste des pointeurs
    lstNode.clear();
    //La scene s'occupe de detruire les noeud et les connexions
    delete scene;
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void Map::addNode(Node &n)
{
    lstNode.append(&n);
    scene->addItem(&n);
}

bool Map::addConnexion(Node &n1, Node &n2)
{
    n1.connect(n2);
    scene->addItem(n1.getConnexion(n2));
}

/*----------------------------------------------------*/
/*DELEGUE*/
/*----------------------------------------------------*/

void Map::advance()
{
    scene->advance();
    update();
    qDebug()<<"test";
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void Map::getPath(Node &n1, Node &n2)const
{
    QList<QPair<int, int>* > weight;
    weight.append(new QPair<int, int>(6,2));
    weight.append(new QPair<int, int>(5,1));
    weight.append(new QPair<int, int>(1,3));
    qDebug()<<weight;
    QMap<int, int> previousLink;
    //qsort(weight.begin(), weight.end(),sortNodeByWight);
    //Initialisation
    /*
    weight.insert(n1.getID(),0);
    previousLink.insert(n1.getID(),n1.getID());


    foreach(Node *n , lstNode)
    {
        weight.insert(n->getID(), INT_MAX);
        previousLink.insert(n->getID(), -1);
    }*/

}

int Map::sortNodeByWight (const QPair<int, int>*a, const QPair<int, int>*b)
{
    if ( a->second < b->second) return -1;
    if ( a->second == b->second) return 0;
    if ( a->second > b->second) return 1;
}
