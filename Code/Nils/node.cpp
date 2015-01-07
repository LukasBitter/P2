#include "node.h"
#include "squad.h"
#include "connexion.h"
#include "gamer.h"
#include <QPainter>
#include <QtWidgets>

#include <QDebug>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Node::Node(int x, int y, int radius, int ressourcesMax, Gamer *g, QGraphicsItem *parent)
    : QGraphicsObject(parent), posX(x), posY(y), radius(radius), owner(g), ressourcesMax(ressourcesMax), nbRessources(0)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

Node::~Node()
{
    foreach(Connexion *c, mapConnexion)
    {
        if(&c->getNode1() == this)
        {
            c->getNode2().removeConnexion(*this);
        }
        else if(&c->getNode2() == this)
        {
            c->getNode1().removeConnexion(*this);
        }
    }
    qDeleteAll(mapConnexion);
    mapConnexion.clear();
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF Node::boundingRect() const
{
    return QRectF(posX - radius, posY - radius,
                  2* radius, 2* radius);
}

void Node::paint(QPainter *painter,
                const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->setPen(Qt::black);
    if(owner != 0)painter->setBrush(QBrush(owner->getColor()));

    painter->drawEllipse(posX - radius, posY - radius,
                             2* radius, 2* radius);
    //Acces concurent ne posant pas de problème
    painter->drawText(QPoint(posX , posY),QString("%1").arg(nbRessources) );
}

void Node::advance(int step)
{
    if(nbRessources < ressourcesMax)
    {
        nbRessources += ressourcesRate;
        if(nbRessources > ressourcesMax)
        {
            nbRessources = ressourcesMax;
        }
    }

    update();
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
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
    nbRessources = r;

    update();
}

void Node::connect(Node &n)
{
    if(!mapConnexion.contains(&n) && &n != this)
    {
        Connexion *c = new Connexion(*this,n);
        mapConnexion.insert(&n, c);
        n.addConnexion(c);
    }
}

bool Node::isConnected(Node &n) const
{
    return mapConnexion.contains(&n);
}

Connexion * Node::getConnexion(Node &n) const
{
    Connexion *c = 0;
    if(mapConnexion.contains(&n))
    {
        c = mapConnexion.value(&n);
    }
    return c;
}

/*----------------------------------------------------*/
/*EVENEMENT*/
/*----------------------------------------------------*/

void Node::incoming(Squad &s)
{
    const Gamer &g = s.getOwner();
    int ressource = s.getNbRessources();
    delete &s;

    if(&g == owner)
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

    update();
}

void Node::sendSquad(int ressource, Node &n)
{
    if(&n != this && mapConnexion.contains(&n))
    {
        int nbToSend = ressource > nbRessources ? nbRessources : ressource;
        Squad *s = new Squad(*owner);
        s->setNbRessources(nbToSend);
        mapConnexion.value(&n)->sendSquad(*s, *this);
    }

    update();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void Node::addConnexion(Connexion *c)
{
    if(&c->getNode1() == this &&
            !mapConnexion.contains(&c->getNode2()) &&
            &c->getNode2() != this)
    {
        mapConnexion.insert(&c->getNode2(), c);
    }
    else if(&c->getNode2() == this &&
            !mapConnexion.contains(&c->getNode1()) &&
            &c->getNode1() != this)
    {
        mapConnexion.insert(&c->getNode1(), c);
    }
}

void Node::removeConnexion(Node &n)
{
    mapConnexion.remove(&n);
}
