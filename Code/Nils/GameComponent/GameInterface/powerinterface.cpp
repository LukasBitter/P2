#include "powerinterface.h"
#include "GameComponent/node.h"
#include "GameComponent/GameInterface/button.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerInterface::PowerInterface(QGraphicsItem * parent) : QGraphicsWidget(parent),mana(0)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setUpUI();
    startTimer(1000);
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF PowerInterface::boundingRect() const
{
    return QRectF(0, 0, 90, 210);
}

void PowerInterface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::lightGray);
    painter->drawRect(boundingRect());
}

void PowerInterface::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    pcd.advence();
    updateCD();
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void PowerInterface::setMana(int mana)
{
    if(mana > 0)this->mana = mana;
}

void PowerInterface::addMana(int mana)
{
    if(mana > 0)this->mana += mana;
}

int PowerInterface::getMana() const
{
    return mana;
}

const PowerCountDown &PowerInterface::getCountDownManager() const
{
    return pcd;
}

/*----------------------------------------------------*/
/*SIGNAL/SLOT*/
/*----------------------------------------------------*/

void PowerInterface::shortCutPressed(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_1:
    {
        btPowerDestroyPressed();
        break;
    }
    case Qt::Key_2:
    {
        btPowerInvincibilityPressed();
        break;
    }
    case Qt::Key_3:
    {
        btPowerTeleportationPressed();
        break;
    }
    case Qt::Key_4:
    {
        btPowerArmorePressed();
        break;
    }
    default:
        break;
    }
}

void PowerInterface::usePower(ACTIONS a, Node *n1, Node *n2)
{
    if(!pcd.isReady(a)) return;

    int cost = 0;
    int countDownTime = 0;
    int powerDuration = 0;

    switch (a)
    {
    case GA_USEPOWER_DESTROY:
    {
        cost = 80;
        countDownTime = 30;
        powerDuration = 0;
        break;
    }
    case GA_USEPOWER_INVINCIBILITY:
    {
        cost = 50;
        countDownTime = 30;
        powerDuration = 5;
        break;
    }
    case GA_USEPOWER_TELEPORTATION:
    {
        cost = 40;
        countDownTime = 20;
        powerDuration = 0;
        break;
    }
    case GA_USEPOWER_ARMORE:
    {
        countDownTime = 5;
        powerDuration = 5;
        cost = 10;
        break;
    }
    default:
        break;
    }

    if(mana >= cost)
    {
        mana -= cost;
        pcd.addCountDown(countDownTime, powerDuration, a, n1, n2);
    }
}

void PowerInterface::btPowerDestroyPressed()
{
    emit powerPressed(GA_USEPOWER_DESTROY);
}

void PowerInterface::btPowerInvincibilityPressed()
{
    emit powerPressed(GA_USEPOWER_INVINCIBILITY);
}

void PowerInterface::btPowerTeleportationPressed()
{
    emit powerPressed(GA_USEPOWER_TELEPORTATION);
}

void PowerInterface::btPowerArmorePressed()
{
    emit powerPressed(GA_USEPOWER_ARMORE);
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void PowerInterface::setUpUI()
{
    //INSTANTIATION
    txtMana = new QGraphicsTextItem("Mana : ",this);
    btPowerDestroy = new Button("D", this);
    btPowerInvincibility = new Button("I", this);
    btPowerTeleportation = new Button("T", this);
    btPowerArmore = new Button("A", this);
    txtCdPowerDestroy = new QGraphicsTextItem("",this);
    txtCdPowerInvincibility = new QGraphicsTextItem("",this);
    txtCdPowerTeleportation = new QGraphicsTextItem("",this);
    txtCdPowerArmore = new QGraphicsTextItem("",this);

    //CONNEXION

    connect(btPowerDestroy, SIGNAL(pressed()), this, SLOT(btPowerDestroyPressed()));
    connect(btPowerInvincibility, SIGNAL(pressed()), this, SLOT(btPowerInvincibilityPressed()));
    connect(btPowerTeleportation, SIGNAL(pressed()), this, SLOT(btPowerTeleportationPressed()));
    connect(btPowerArmore, SIGNAL(pressed()), this, SLOT(btPowerArmorePressed()));

    //POSITIONNEMENT
    btPowerDestroy->setX(25);
    btPowerInvincibility->setX(25);
    btPowerTeleportation->setX(25);
    btPowerArmore->setX(25);
    txtCdPowerDestroy->setX(50);
    txtCdPowerInvincibility->setX(50);
    txtCdPowerTeleportation->setX(50);
    txtCdPowerArmore->setX(50);
    txtMana->setX(5);

    btPowerDestroy->setY(25);
    btPowerInvincibility->setY(70);
    btPowerTeleportation->setY(115);
    btPowerArmore->setY(160);
    txtCdPowerDestroy->setY(17);
    txtCdPowerInvincibility->setY(62);
    txtCdPowerTeleportation->setY(107);
    txtCdPowerArmore->setY(152);
    txtMana->setY(185);

}

void PowerInterface::updateCD()
{
    txtCdPowerDestroy->setPlainText(QString("%1 %").arg((int)pcd.percentReload(GA_USEPOWER_DESTROY)));
    txtCdPowerInvincibility->setPlainText(QString("%1 %").arg((int)pcd.percentReload(GA_USEPOWER_INVINCIBILITY)));
    txtCdPowerTeleportation->setPlainText(QString("%1 %").arg((int)pcd.percentReload(GA_USEPOWER_TELEPORTATION)));
    txtCdPowerArmore->setPlainText(QString("%1 %").arg((int)pcd.percentReload(GA_USEPOWER_ARMORE)));

    txtMana->setPlainText(QString("Mana : %1").arg(mana));
}
