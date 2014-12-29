#include "node.h"
#include "squad.h"
#include "connexion.h"
#include "gamer.h"
#include <QPainter>
#include <QtWidgets>

#include <QDebug>

/*
 * - Rendez thread safe toutes méthodes public implémentées
 */


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Node::Node(int x, int y, int radius, int ressourcesMax, Gamer *g, QGraphicsItem *parent)
    : QGraphicsItem(parent), posX(x), posY(y), radius(radius), owner(g), ressourcesMax(ressourcesMax)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    startTimer(1000);
}

Node::~Node()
{
    QMutexLocker l(&lockMapConnexion);

    foreach(Connexion *c, mapConnexion)
    {
        if(c->getNode1().getId() == this->getId())
        {
            c->getNode2().removeConnexion(this->getId());
        }
        else if(c->getNode2().getId() == this->getId())
        {
            c->getNode1().removeConnexion(this->getId());
        }
    }
    qDeleteAll(mapConnexion);
    mapConnexion.clear();
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void Node::tic()
{
    QMutexLocker l(&lockRessource);

    if(nbRessources < ressourcesMax)
    {
        nbRessources += ressourcesRate;
        if(nbRessources > ressourcesMax)
        {
            nbRessources = ressourcesMax;
        }
    }
    l.unlock();

    QGraphicsItem::update();
}

QRectF Node::boundingRect() const
{
    return QRectF(posX - radius, posY - radius,
                  posX + radius, posY + radius);
}

void Node::paint(QPainter *painter,
                const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->setPen(Qt::black);
    //painter->setBrush(QBrush(owner->getColor()));
    painter->drawEllipse(posX - radius, posY - radius,
                             2* radius, 2* radius);
    //Acces concurent ne posant pas de problème
    painter->drawText(QPoint(posX , posY),QString("%1").arg(nbRessources) );
}

void Node::timerEvent(QTimerEvent *event)
{
    tic();
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //Deplacement inferieur au seuil de drag&drop
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

int Node::getNbRessources() const
{
    return nbRessources;
}

int Node::getRessourcesRate() const
{
    return ressourcesRate;
}

int Node::getPosX() const
{
    return posX;
}

int Node::getRadius() const
{
    return radius;
}
int Node::getPosY() const
{
    return posY;
}
const Gamer* Node::getOwner()
{
    return owner;
}

void Node::setRessourcesRate(int r)
{
    ressourcesRate = r;
}

void Node::setNbRessources(int r)
{
    QMutexLocker l(&lockRessource);
    nbRessources = r;
    l.unlock();

    QGraphicsItem::update();
}

void Node::connect(Node &n)
{
    QMutexLocker l(&lockMapConnexion);

    if(!mapConnexion.contains(n.getId()) &&
            n.getId() != this->getId())
    {
        Connexion *c = new Connexion(*this,n);
        mapConnexion.insert(n.getId(), c);
        n.addConnexion(c);
    }
}

bool Node::isConnected(Node &n) const
{
    QMutexLocker l(&lockMapConnexion);
    return mapConnexion.contains(n.getId());
}

Connexion * Node::getConnexion(Node &n) const
{
    QMutexLocker l(&lockMapConnexion);

    Connexion *c = 0;
    if(mapConnexion.contains(n.getId()))
    {
        c = mapConnexion.value(n.getId());
    }
    return c;
}

/*----------------------------------------------------*/
/*EVENEMENT*/
/*----------------------------------------------------*/

void Node::incoming(Squad &s)
{
    QMutexLocker l(&lockRessource);

    const Gamer &g = s.getOwner();
    int ressource = s.getNbRessources();
    delete &s;

    if(g.getId() == owner->getId())
    {
        //Entrée d'allier
        nbRessources += ressource;
    }
    else
    {
        //Entrée d'ennemis
        if (nbRessources < ressource)
        {
            //Changement de propriétaire
            ressource -= nbRessources;
            nbRessources = ressource;
            owner = &g;
        }
        else
        {
            nbRessources -= ressource;
        }
    }
    l.unlock();

    QGraphicsItem::update();
}

void Node::sendSquad(int ressource, Node &n)
{
    QMutexLocker lr(&lockRessource);
    QMutexLocker lm(&lockMapConnexion);

    if(n.getId() != this->getId() && mapConnexion.contains(n.getId()))
    {
        int nbToSend = ressource > nbRessources ? nbRessources : ressource;
        Squad *s = new Squad(*owner);
        s->setNbRessources(nbToSend);
        mapConnexion.value(n.getId())->sendSquad(*s, *this);
    }
    lr.unlock();
    lm.unlock();

    QGraphicsItem::update();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void Node::addConnexion(Connexion *c)
{
    QMutexLocker l(&lockMapConnexion); //Acces via autre noeud externe

    if(c->getNode1().getId() == this->getId() &&
            !mapConnexion.contains(c->getNode2().getId()) &&
            c->getNode2().getId() != this->getId())
    {
        mapConnexion.insert(c->getNode2().getId(), c);
    }
    else if(c->getNode2().getId() == this->getId() &&
            !mapConnexion.contains(c->getNode1().getId()) &&
            c->getNode1().getId() != this->getId())
    {
        mapConnexion.insert(c->getNode1().getId(), c);
    }
}

void Node::removeConnexion(int nodeID)
{
    QMutexLocker l(&lockMapConnexion);  //Acces via autre noeud externe

    mapConnexion.remove(nodeID);
}
