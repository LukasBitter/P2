#include "ressourcesinterface.h"
#include "actionmanager.h"
#include "progressbar.h"
#include "GameComponent/Logic/node.h"
#include "GameComponent/GameInterface/button.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

RessourcesInterface::RessourcesInterface(ActionManager &am, QGraphicsItem * parent) :
    QGraphicsWidget(parent),percentToSend(50), am(am)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setUpUI();
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF RessourcesInterface::boundingRect() const
{
    return QRectF(0, 0, 120, 280);
}

void RessourcesInterface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPixmap buttonBackground(":/ButtonBackground.png");

    QRectF source(0, 0, 502, 1446);
    painter->drawPixmap(boundingRect(), buttonBackground, source);
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void RessourcesInterface::setPercentToSend(double percent)
{
    if(percent>=0 && percent<=100) percentToSend = percent;
}

double RessourcesInterface::getPercentToSend() const
{
    return percentToSend;
}

/*----------------------------------------------------*/
/*SIGNAL/SLOT*/
/*----------------------------------------------------*/

void RessourcesInterface::shortCutPressed(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Q:
    {
        setPercentToSend(25);
        am.actionChanged(GA_SEND);
        break;
    }
    case Qt::Key_W:
    {
        setPercentToSend(50);
        am.actionChanged(GA_SEND);
        break;
    }
    case Qt::Key_E:
    {
        setPercentToSend(75);
        am.actionChanged(GA_SEND);
        break;
    }
    case Qt::Key_R:
    {
        setPercentToSend(100);
        am.actionChanged(GA_SEND);
        break;
    }
    default:
        break;
    }
}
void RessourcesInterface::btIncrasePressed()
{
    if(percentToSend < 75)
    {
        percentToSend += 25;
    }
}

void RessourcesInterface::btDicrasePressed()
{
    if(percentToSend > 25)
    {
        percentToSend -= 25;
    }
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void RessourcesInterface::setUpUI()
{
    //INSTANTIATION
    btIncrase = new Button(INCRASE, this);
    btDicrase = new Button(DICRASE, this);
    txtPercent = new QGraphicsTextItem("",this);

    //CONNEXION

    connect(btIncrase, SIGNAL(pressed()), this, SLOT(btIncrasePressed()));
    connect(btDicrase, SIGNAL(pressed()), this, SLOT(btDicrasePressed()));

    //POSITIONNEMENT
    btIncrase->setX(67);
    btDicrase->setX(67);
    txtPercent->setX(67);

    btIncrase->setY(50);
    btDicrase->setY(110);
    txtPercent->setY(170);

    //PARAMETRAGE
    QFont f = txtPercent->font();
    txtPercent->setDefaultTextColor(Qt::cyan);
    f.setBold(true);
}
