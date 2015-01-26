#include "nodecombat.h"
#include "squad.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include "enumlibrary.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

NodeCombat::NodeCombat(int x, int y, int radius, int ressourcesMax, const GamerList &gl, Gamer *g)
    : NodeConnectable(x,y,radius), owner(0), invicible(false), ressourcesRate(0),
      ressourcesMax(ressourcesMax), nbRessources(0), counterAdvance(0),
      armorLvl(0), lstGamer(gl)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    setNextId();
    setX(x);
    setY(y);
    setZValue(10);
    setOwner(g);
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
        setOwner(lstGamer.getGamer(nodeStr.first().toInt()));
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
    int extendRadius = radius + 5;
    return QRectF(-extendRadius, -extendRadius,
                      2*extendRadius, 2*extendRadius);
}

void NodeCombat::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Node::paint(painter, option, widget);

    //PARAMETRAGE
    QColor invert;
    invert.setBlue(255 - color.blue());
    invert.setRed(255 - color.red());
    invert.setGreen(255 - color.green());

    QString ressourceTxt = QString::number(nbRessources);
    QString armorTxt = QString("+%1").arg(armorLvl);

    QFont f = painter->font();
    f.setBold(invicible);
    QFontMetrics fm(f);
    int centre = (fm.height()/2)-2;

    //DESSIN DU NOEU
    painter->setPen(invert);
    painter->setFont(f);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRectF r = boundingRect();
    QRectF source(0.0, 0.0, 389.0, 389.0);
    QPixmap *powerImg;

    if(armorLvl > 0)
    {
        powerImg = new QPixmap(":/NodeRingGreenH.png");
        int l2 = fm.width(ressourceTxt, -1);
        painter->drawText(-(l2/2), centre-(fm.height()/2)+2 , ressourceTxt);
        int l1 = fm.width(armorTxt, -1);
        painter->drawText(-(l1/2), centre+(fm.height()/2)+2, armorTxt);
        painter->drawPixmap(r, *powerImg,source);
    }
    else if (this->invicible)
    {
        qDebug() << "------------------------------";
        powerImg = new QPixmap(":/NodeRingOrangeH.png");
        painter->drawPixmap(r, *powerImg,source);
    }
    else
    {
        int l = fm.width(ressourceTxt, -1);
        painter->drawText(-(l/2), centre, ressourceTxt);
    }
}

void NodeCombat::advance(int step)
{
    if(step == 0) return;

    //Wait number of tic
    if(counterAdvance < 20)
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
    if(owner != 0)
    {
        setColor(owner->getColor());
    }
    else
    {
        setColor(VACANT_COLOR);
    }
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
            setOwner(&g);
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
        setOwner(lstGamer.getGamer(nodeStr.first().toInt()));
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
