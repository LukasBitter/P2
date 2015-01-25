#include "nodecombat.h"
#include "squad.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include "global.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

NodeCombat::NodeCombat(int x, int y, int radius, int ressourcesMax, const GamerList &gl, Gamer *g)
    : Node(x,y,radius), owner(g), invicible(false), ressourcesRate(0),
      ressourcesMax(ressourcesMax), nbRessources(0), counterAdvance(0),
      armorLvl(0), lstGamer(gl)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    setNextId();
    setX(x);
    setY(y);
    setZValue(10);
}

NodeCombat::NodeCombat(QString &create, GamerList &gl) : NodeCombat(0,0,0,0,gl,0)
{
    QStringList nodeStr = create.split(",");
    if(nodeStr.size() == 7)
    {
        nodeStr.pop_front();
        setId(nodeStr.first().toInt());
        nodeStr.pop_front();
        setX(nodeStr.first().toInt());
        nodeStr.pop_front();
        setY(nodeStr.first().toInt());
        nodeStr.pop_front();
        radius = nodeStr.first().toInt();
        nodeStr.pop_front();
        ressourcesMax = nodeStr.first().toInt();
        nodeStr.pop_front();
        owner = lstGamer.getGamer(nodeStr.first().toInt());
    }
    else
    {
        qCritical()<<"NodeCombat : unexpected case in 'NodeCombat'";
    }
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF NodeCombat::boundingRect() const
{
    return QRectF(-radius-3, -radius-3,
                      2*radius+7, 2*radius+6);
}

void NodeCombat::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    QColor ownerColor = QColor(Qt::white);
    QPixmap nodeImg;

    if(owner != 0)
    {
        //painter->setBrush(owner->getColor());
        ownerColor = owner->getColor();

        if(ownerColor == QColor(Qt::darkRed))
        {
            nodeImg = QPixmap(":/NodeRedN.png");
        }
        else if(ownerColor == QColor(Qt::green))
        {
            nodeImg = QPixmap(":/NodeGreenN.png");
        }
        else if(ownerColor == QColor(Qt::red))
        {
            nodeImg = QPixmap(":/NodeOrangeN.png");
        }
        else if(ownerColor == QColor(Qt::yellow))
        {
            nodeImg = QPixmap(":/NodeYellowN.png");
        }
    }
    else
    {
        nodeImg = QPixmap(":/NodeWhiteN.png");
    }

    if(isSelected() || isUnderMouse())
    {
        QPen pen(Qt::gray);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(5);
        painter->setPen(pen);
        painter->drawEllipse(QPoint(0,0),radius+3,radius+3);
    }
    //painter->setPen(Qt::black);
    //painter->drawEllipse(QPoint(0,0),radius,radius);


    //QRectF target(0, 0, radius, radius);
    QRectF source(0.0, 0.0, 212.0, 212.0);
    painter->drawPixmap(Node::boundingRect(), nodeImg, source);

    if(invicible)
    {
        QFont f = painter->font();
        f.setBold(true);
        painter->setFont(f);
    }
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

void NodeCombat::advance(int step)
{
    if(step == 0) return;

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

void NodeCombat::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

int NodeCombat::getRessources() const
{
    return nbRessources;
}

int NodeCombat::getRessourcesRate() const
{
    return ressourcesRate;
}

int NodeCombat::getRadius() const
{
    return radius;
}

int NodeCombat::getArmorLvl() const
{
    return armorLvl;
}

void NodeCombat::setArmorLvl(int a)
{
    armorLvl = a;
}

bool NodeCombat::getInvicibility() const
{
    return invicible;
}

void NodeCombat::setInvicibility(bool b)
{
    invicible = b;
}

void NodeCombat::setOwner(const Gamer *g)
{
    owner = g;
}

const Gamer* NodeCombat::getOwner() const
{
    return owner;
}

void NodeCombat::setRessourcesRate(int r)
{
    ressourcesRate = r;
}

int NodeCombat::getRessourcesMax() const
{
    return ressourcesMax;
}

void NodeCombat::setRessources(int r)
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

void NodeCombat::incoming(Squad s)
{
    const Gamer &g = s.getOwner();
    int ressource = s.getNbRessources();

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
}

void NodeCombat::sendSquad(int ressource, int nodeId)
{
    if(nodeId != getId() && mapConnexion.contains(nodeId))
    {
        int nbToSend = ressource > nbRessources ? nbRessources : ressource;
        if(nbToSend > 0)
        {
            nbRessources -= nbToSend;
            Squad s = Squad(*owner);
            s.setNbRessources(nbToSend);
            mapConnexion.value(nodeId)->sendSquad(s, getId());
        }
    }
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString NodeCombat::getUpdateString() const
{
    int idGamer  = -1;
    if(owner != 0)idGamer = owner->getId();

    return QString("%1,%2,%3,%4,%5").arg(nbRessources).
           arg(ressourcesRate).arg(idGamer).arg(armorLvl).
            arg(invicible);
}

QString NodeCombat::getCreationString() const
{
    int idGamer  = -1;
    if(owner != 0)idGamer = owner->getId();

    return QString("C,%1,%2,%3,%4,%5,%6").arg(getId()).arg(x()).arg(y()).
           arg(radius).arg(ressourcesMax).arg(idGamer);
}

void NodeCombat::updateFromString(QString &s)
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
        qCritical()<<"NodeCombat : unexpected case in 'updateFromString'";
    }
}

QString NodeCombat::normalizeSpawn()
{
    QString s = QString("%1,%2,%3,%4,%5").arg(nbRessources).
               arg(ressourcesRate).arg("@").arg(armorLvl).
                arg(invicible);
    s.replace(s.indexOf("@"),1,"%1");
    return s;
}

bool NodeCombat::isContainsPrivateChar(QString &s)
{
    return s.contains(",");
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

int NodeCombat::dealDamageOnArmor(int damage)
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
