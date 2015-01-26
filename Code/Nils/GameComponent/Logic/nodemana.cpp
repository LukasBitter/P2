#include "nodemana.h"
#include "squad.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include "global.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

NodeMana::NodeMana(int x, int y, int radius, const GamerList &gl)
    : Node(x,y,radius), lstGamer(gl)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    setNextId();
    setX(x);
    setY(y);
    setZValue(10);
}

NodeMana::NodeMana(QString &create, GamerList &gl) : NodeMana(0,0,0,gl)
{
    QStringList nodeStr = create.split(",");
    if(nodeStr.size() == 5)
    {
        nodeStr.pop_front();
        setId(nodeStr.first().toInt());
        nodeStr.pop_front();
        setX(nodeStr.first().toInt());
        nodeStr.pop_front();
        setY(nodeStr.first().toInt());
        nodeStr.pop_front();
        radius = nodeStr.first().toInt();
    }
    else
    {
        qCritical()<<"NodeMana : unexpected case in 'NodeMana'";
    }
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

const Gamer* NodeMana::getOwner() const
{
    return 0;
}

void NodeMana::setOwner(const Gamer *g)
{
    Q_UNUSED(g);
}

void NodeMana::incoming(Squad s)
{
    Q_UNUSED(s);
}

void NodeMana::sendSquad(int ressource, int nodeId)
{
    Q_UNUSED(ressource);
    Q_UNUSED(nodeId);
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString NodeMana::getUpdateString() const
{
    return "";
}

QString NodeMana::getCreationString() const
{
    return QString("M,%1,%2,%3,%4").arg(getId()).arg(x()).arg(y()).
           arg(radius);
}

void NodeMana::updateFromString(QString &s)
{
    Q_UNUSED(s);
}

QString NodeMana::normalizeSpawn()
{
    return "";
}

bool NodeMana::isContainsPrivateChar(QString &s)
{
    return s.contains(",");
}
