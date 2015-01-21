#include "node.h"
#include "squad.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include <QPainter>
#include <QtWidgets>
#include <QDebug>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Node::Node(int x, int y, int radius, int ressourcesMax, GamerList &gl, Gamer *g)
    : QGraphicsItem(0), radius(radius), owner(g), invicible(false),
      ressourcesMax(ressourcesMax), nbRessources(0), counterAdvance(0),
      armorLvl(0), lstGamer(gl)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    setNextId();
    setX(x);
    setY(y);
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

    if(owner != 0)
    {
        painter->setBrush(owner->getColor());
    }
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
    if(armorLvl > 0)
    {
        if(armorLvl<10)
            painter->drawText(QPoint(-12 , +15),QString("+%1").arg(armorLvl));
        else if(armorLvl<100)
            painter->drawText(QPoint(-15 , +15),QString("+%1").arg(armorLvl));
        else
            painter->drawText(QPoint(-19 , +15),QString("+%1").arg(armorLvl));
    }
    if(nbRessources<10)
        painter->drawText(QPoint(-4 , +4),QString("%1").arg(nbRessources));
    else if(nbRessources<100)
        painter->drawText(QPoint(-7 , +4),QString("%1").arg(nbRessources));
    else
        painter->drawText(QPoint(-11 , +4),QString("%1").arg(nbRessources));
}

void Node::advance(int step)
{
    if(step == 0) return;

    update();
    //Wait number of tic
    if(counterAdvance < 10)
    {
        ++counterAdvance;
        return;
    }
    counterAdvance = 0;

    if(owner != 0)
    {
        nbRessources += ressourcesRate;
    }
    if(nbRessources > ressourcesMax && ressourcesMax > 0)
    {
        nbRessources = ressourcesMax;
    }

}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
            .length() < QApplication::startDragDistance()) {
        return;
    }

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    mime->setText(QString("%1").arg(getId()));

    drag->exec();
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

int Node::getRessources() const
{
    return nbRessources;
}

int Node::getRessourcesRate() const
{
    return ressourcesRate;
}

int Node::getRadius() const
{
    return radius;
}

int Node::getArmorLvl() const
{
    return armorLvl;
}

void Node::setArmorLvl(int a)
{
    armorLvl = a;
}

bool Node::getInvicibility() const
{
    return invicible;
}

void Node::setInvicibility(bool b)
{
    invicible = b;
}

const Gamer* Node::getOwner() const
{
    return owner;
}

void Node::setRessourcesRate(int r)
{
    ressourcesRate = r;
}

int Node::getRessourcesMax() const
{
    return ressourcesMax;
}

void Node::setRessources(int r)
{
    nbRessources = r;

    if(nbRessources < 0)
    {
        nbRessources = 0;
    }
    if(nbRessources > ressourcesMax)
    {
        nbRessources = ressourcesMax;
    }
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

bool Node::isConnected(int nodeId) const
{
    return mapConnexion.contains(nodeId);
}

void Node::incoming(Squad *s)
{
    if(s == 0) return;

    const Gamer &g = s->getOwner();
    int ressource = s->getNbRessources();
    delete &s;

    if(&g == owner)
    {
        //Entrée d'allier
        setRessources(nbRessources+ressource);
    }
    else
    {
        //Entrée d'ennemis
        if(invicible) ressource = 0;
        ressource = dealDamageOnArmor(ressource);
        if (nbRessources < ressource)
        {
            //Changement de propriétaire
            ressource -= nbRessources;
            setRessources(ressource);
            owner = &g;
        }
        else
        {
            setRessources(nbRessources-ressource);
        }
    }

    update();
}

void Node::sendSquad(int ressource, int nodeId)
{
    if(nodeId != getId() && mapConnexion.contains(nodeId))
    {
        int nbToSend = ressource > nbRessources ? nbRessources : ressource;
        if(nbToSend > 0)
        {
            nbRessources -= nbToSend;
            Squad *s = new Squad(*owner);
            s->setNbRessources(nbToSend);
            mapConnexion.value(nodeId)->sendSquad(s, *this);
        }
    }

    update();
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString Node::getUpdateString()
{
    int idGamer  = -1;
    if(owner != 0)idGamer = owner->getId();
    return QString("%1,%2,%3,%4,%5").arg(nbRessources).
           arg(ressourcesRate).arg(idGamer).arg(armorLvl).
            arg(invicible);
}

void Node::updateFromString(QString &s)
{
    QStringList nodeStr = s.split(",");
    if(nodeStr.size() == 5)
    {
        nbRessources = nodeStr.first().toInt();
        nodeStr.pop_front();
        ressourcesRate = nodeStr.first().toInt();
        nodeStr.pop_front();
        owner = lstGamer.getGamer(nodeStr.first().toInt());
        nodeStr.pop_front();
        armorLvl = nodeStr.first().toInt();
        nodeStr.pop_front();
        invicible = nodeStr.first().toInt();
    }
    else
    {
        qCritical()<<"Node : unexpected case in 'updateFromString'";
    }
    update();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

int Node::dealDamageOnArmor(int damage)
{
    if(damage <= armorLvl)
    {
        armorLvl -= damage;
        return 0;
    }
    else
    {
        int tmp = damage - armorLvl;
        armorLvl = 0;
        return tmp;
    }
}
