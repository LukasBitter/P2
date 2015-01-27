#include "ressourcesinterface.h"
#include "actionmanager.h"
#include "progressbar.h"
#include "GameComponent/Logic/node.h"
#include "GameComponent/GameInterface/buttonressource.h"


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
        bt25Pressed();
        break;
    }
    case Qt::Key_W:
    {
        bt50Pressed();
        break;
    }
    case Qt::Key_E:
    {
        bt75Pressed();
        break;
    }
    case Qt::Key_R:
    {
        bt100Pressed();
        break;
    }
    default:
        break;
    }
}

void RessourcesInterface::bt25Pressed()
{
    setPercentToSend(25);
    am.actionChanged(GA_SEND);
    resetSelection();
    bt25Percent->setSelected(true);
}

void RessourcesInterface::bt50Pressed()
{
    setPercentToSend(50);
    am.actionChanged(GA_SEND);
    resetSelection();
    bt50Percent->setSelected(true);
}

void RessourcesInterface::bt75Pressed()
{
    setPercentToSend(75);
    am.actionChanged(GA_SEND);
    resetSelection();
    bt75Percent->setSelected(true);
}

void RessourcesInterface::bt100Pressed()
{
    setPercentToSend(100);
    am.actionChanged(GA_SEND);
    resetSelection();
    bt100Percent->setSelected(true);
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void RessourcesInterface::setUpUI()
{
    //INSTANTIATION
    bt25Percent = new ButtonRessource(SET_25, this);
    bt50Percent = new ButtonRessource(SET_50, this);
    bt75Percent = new ButtonRessource(SET_75, this);
    bt100Percent = new ButtonRessource(SET_100, this);

    //CONNEXION
    connect(bt25Percent, SIGNAL(pressed()), this, SLOT(bt25Pressed()));
    connect(bt50Percent, SIGNAL(pressed()), this, SLOT(bt50Pressed()));
    connect(bt75Percent, SIGNAL(pressed()), this, SLOT(bt75Pressed()));
    connect(bt100Percent, SIGNAL(pressed()), this, SLOT(bt100Pressed()));

    //POSITIONNEMENT
    bt25Percent->setX(60);
    bt50Percent->setX(60);
    bt75Percent->setX(60);
    bt100Percent->setX(60);

    bt25Percent->setY(50);
    bt50Percent->setY(110);
    bt75Percent->setY(170);
    bt100Percent->setY(230);
}

void RessourcesInterface::resetSelection()
{
    bt25Percent->setSelected(false);
    bt50Percent->setSelected(false);
    bt75Percent->setSelected(false);
    bt100Percent->setSelected(false);
}
