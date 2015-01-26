#include "node.h"
#include "squad.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include "global.h"
#include "nodecombat.h"
#include "nodemana.h"
#include "enumlibrary.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Node::Node(int x, int y, int radius): QGraphicsItem(0),
    radius(radius), color(BASE_NODE_COLOR)
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
    return QRectF(-radius, -radius,
                      2*radius, 2*radius);
}

void Node::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    bool over= option->state & QStyle::State_MouseOver;

    QPen p = painter->pen();
    p.setWidth(2);
    p.setColor(Qt::black);
    QRadialGradient radialGrad(0, 0, radius);
    radialGrad.setColorAt(0, color.darker());
    radialGrad.setColorAt(1, color.darker());

    //PARAMETRAGE SUIVANT ETAT
    if(isSelected())
    {
        radialGrad.setColorAt(0, color.lighter());
        radialGrad.setColorAt(1, color.darker());
        p.setColor(color.lighter());
    }
    else if(over)
    {
        radialGrad.setColorAt(0, color.lighter());
        radialGrad.setColorAt(1, color.darker());
    }

    //DESSIN DU NOEU DE BASE
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBrush(radialGrad);
    painter->setPen(p);
    painter->drawEllipse(-radius, -radius, 2*radius, 2*radius);

    painter->restore();
}

QColor Node::getColor()
{
    return color;
}

void Node::setColor(QColor c)
{
    color = c;
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
