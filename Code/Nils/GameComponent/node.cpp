#include "node.h"
#include "squad.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include "global.h"
#include "nodecombat.h"
#include "nodemana.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Node::Node(int x, int y, int radius): QGraphicsItem(0),
    radius(radius)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    setNextId();
    setX(x);
    setY(y);
    setZValue(10);
}

/*----------------------------------------------------*/
/*FABRIQUE*/
/*----------------------------------------------------*/

Node *Node::createNode(QString &create, GamerList &gl)
{
    if(create.size() > 0)
    {
        if(create.at(0) == 'C')
        {
            return new NodeCombat(create,gl);
        }
        else if(create.at(0) == 'M')
        {
            return new NodeMana(create,gl);
        }
    }
    qCritical()<<"Node : unexpected case in 'createNode'";

    return 0;
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF Node::boundingRect() const
{
    return QRectF(-radius-3, -radius-3,
                      2*radius+7, 2*radius+6);
}

void Node::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::black);

    if(isSelected() || isUnderMouse())
    {
        QPen pen(Qt::gray);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(5);
        painter->setPen(pen);
        painter->drawEllipse(QPoint(0,0),radius+3,radius+3);
    }
    painter->setPen(Qt::black);
    painter->drawEllipse(QPoint(0,0),radius,radius);
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

int Node::getRadius() const
{
    return radius;
}

void Node::connect(int nodeId, Connexion *c)
{
    if(!mapConnexion.contains(nodeId) && nodeId != getId() &&
            (&c->getNode1() == this || &c->getNode2() == this))
    {
        mapConnexion.insert(nodeId, c);
    }
}

void Node::disconnect(int nodeId)
{
    mapConnexion.remove(nodeId);
}

Connexion *Node::getConnexion(int nodeId) const
{
    return mapConnexion.value(nodeId, 0);
}

QMap<int, Connexion *> Node::getConnexions() const
{
    return mapConnexion;
}

bool Node::isConnected(int nodeId) const
{
    return mapConnexion.contains(nodeId);
}
