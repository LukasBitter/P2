#include "node.h"
#include "squad.h"
#include "connexion.h"
#include "gamer.h"
#include <QPainter>
#include <QtWidgets>
#include <QStringBuilder>

#include <QDebug>


/*----------------------------------------------------*/
/*STATIC*/
/*----------------------------------------------------*/

QHash<int,Node *> lstNodes;
Node *Node::getNode(int idNode)
{
    if(lstNodes.contains(idNode))
    {
        return lstNodes.value(idNode);
    }
    else
    {
        return 0;
    }
}

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Node::Node(int x, int y, int radius, int ressourcesMax, Gamer *g, QGraphicsItem *parent)
    : QGraphicsObject(parent), posX(x), posY(y), radius(radius), owner(g),
      ressourcesMax(ressourcesMax), nbRessources(0), counterAdvance(0), armorLvl(0)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    setNextId();
    lstNodes.insert(getId(), this);
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
    if(owner != 0)
    {
        painter->setBrush(owner->getColor());
    }
    if(isSelected())
    {
        painter->setPen(Qt::DashLine);
    }
    else
    {
        painter->setPen(Qt::SolidLine);
    }

    painter->drawEllipse(posX - radius, posY - radius,
                             2* radius, 2* radius);
    if(armorLvl > 0)
    {
        painter->drawText(QPoint(posX , posY),QString("%1 + %2").arg(nbRessources).arg(armorLvl));
    }
    else
    {
        painter->drawText(QPoint(posX , posY),QString("%1").arg(nbRessources));
    }
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

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    setCursor(Qt::ArrowCursor);
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
    setCursor(Qt::ClosedHandCursor);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseReleaseEvent(event);
    setCursor(Qt::ArrowCursor);
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

int Node::getArmorLvl() const
{
    return armorLvl;
}

void Node::setArmorLvl(int a)
{
    armorLvl = a;
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

int Node::getRessourcesMax() const
{
    return ressourcesMax;
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
/*PARSING*/
/*----------------------------------------------------*/

QString Node::getUpdateString()
{
    int id  = -1;
    if(owner != 0)id = owner->getId();
    return QString("%1,%2,%3,%4").arg(nbRessources).
            arg(ressourcesRate).arg(id).arg(armorLvl);
}

void Node::updateFromString(QString &s)
{
    QStringList nodeStr = s.split(",");
    if(nodeStr.size() == 3)
    {
        nbRessources = nodeStr.first().toInt();
        nodeStr.pop_front();
        ressourcesRate = nodeStr.first().toInt();
        nodeStr.pop_front();
        owner = Gamer::getGamer(nodeStr.first().toInt());
        nodeStr.pop_front();
        armorLvl = nodeStr.first().toInt();
    }
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
        ressource = dealDamageOnArmor(ressource);
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
        if(nbToSend > 0)
        {
            nbRessources -= nbToSend;
            Squad *s = new Squad(*owner);
            s->setNbRessources(nbToSend);
            mapConnexion.value(&n)->sendSquad(s, *this);
        }
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
