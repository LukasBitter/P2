#include "map.h"
#include "node.h"
#include "connexion.h"
#include <QGraphicsScene>
#include <QMap>
#include <climits>
#include <QKeyEvent>

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
    scene->setSceneRect(-1000,-1000,2000,2000);

    connect(scene,SIGNAL(selectionChanged()),this,SLOT(selectionChange()));
    // Désactivation des scrollbars
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing, true);
    //setDragMode(QGraphicsView::RubberBandDrag);

    currentSelection = 0;
    lastSelection = 0;
}

Map::~Map()
{
    //Efface simplement la liste des pointeurs
    lstNode.clear();
    //La scene s'occupe de detruire les noeud et les connexions
    delete scene;
}

void Map::keyPressEvent(QKeyEvent *e)
{
    QGraphicsView::keyPressEvent(e);
    if(e->key() == Qt::Key_Space &&
            currentSelection != 0 && lastSelection != 0 &&
            currentSelection != lastSelection)
    {
        lastSelection->sendSquad(lastSelection->getNbRessources()/2,*currentSelection);
    }
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
    Connexion *c = n1.getConnexion(n2);
    lstConnexion.append(c);
    scene->addItem(c);
}

int Map::getTotalRessources(Gamer &g)
{
    int total = 0;
    foreach (Node *n, lstNode)
    {
        if(n->getOwner() == &g)total += n->getNbRessources();
    }
    return total;
}

int Map::getAvrageRessourcesRate(Gamer &g)
{
    int sum = 0;
    int nb = 0;
    foreach (Node *n, lstNode)
    {
        if(n->getOwner() == &g)sum += n->getRessourcesRate();
        ++nb;
    }
    return sum / nb;
}

int Map::getTotalRessources()
{
    int total = 0;
    foreach (Node *n, lstNode)
    {
        total += n->getNbRessources();
    }
    return total;
}

int Map::getAvrageRessourcesRate()
{
    int sum = 0;
    foreach (Node *n, lstNode)
    {
        sum += n->getRessourcesRate();
    }
    return sum / lstNode.size();
}

const QList<Connexion *> &Map::getLstConnexion() const
{
    return lstConnexion;
}

const QList<Node *> &Map::getLstNode() const
{
    return lstNode;
}

/*----------------------------------------------------*/
/*DELEGUE*/
/*----------------------------------------------------*/

void Map::advance()
{
    scene->advance();
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

void Map::selectionChange()
{
    lastSelection = currentSelection;
    QList<QGraphicsItem *> lst = scene->selectedItems();
    if(!lst.isEmpty())
    {
        currentSelection = static_cast<Node*>(lst.first());
    }
    else
    {
        currentSelection = 0;
    }
}
