#include "powerinterface.h"
#include "GameComponent/node.h"
#include "GameComponent/GameInterface/button.h"
#include "GameComponent/GameInterface/Powers/power.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerInterface::PowerInterface(QGraphicsItem * parent) : QGraphicsWidget(parent),mana(0)
{
    setUpUI();
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF PowerInterface::boundingRect() const
{
    return QRectF(0, 0, 100, 195);
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
    powerDestroy.advence();
    powerInvincibility.advence();
    powerTeleportation.advence();
    powerArmore.advence();
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
    switch (a)
    {
    case GA_USEPOWER_DESTROY:
        if(n1 != 0)usePowerDestroy(n1);
        break;
    case GA_USEPOWER_INVINCIBILITY:
        if(n1 != 0)usePowerInvincibility(n1);
        break;
    case GA_USEPOWER_TELEPORTATION:
        if(n1 != 0 && n2 != 0)usePowerTeleportation(n1, n2);
        break;
    case GA_USEPOWER_ARMORE:
        if(n1 != 0)usePowerArmore(n1);
        break;
    default:
        break;
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
    txtCdPowerDestroy->setY(25);
    txtCdPowerInvincibility->setY(70);
    txtCdPowerTeleportation->setY(115);
    txtCdPowerArmore->setY(160);
    txtMana->setY(190);

}

void PowerInterface::usePowerDestroy(Node *n)
{
    qDebug()<<"PowerInterface : enter 'usePowerDestroy'";

    const int cost = 80;
    if(mana >= cost)
    {
        mana -= cost;
        powerDestroy.enablePower(n);
    }
}

void PowerInterface::usePowerInvincibility(Node *n)
{
    qDebug()<<"PowerInterface : enter 'usePowerInvincibility'";

    const int cost = 50;
    if(mana >= cost)
    {
        mana -= cost;
        powerInvincibility.enablePower(n);
    }
}

void PowerInterface::usePowerTeleportation(Node *from, Node *to)
{
    qDebug()<<"PowerInterface : enter 'usePowerTeleportation'";

    const int cost = 40;
    if(mana >= cost)
    {
        mana -= cost;
        powerTeleportation.enablePower(from, to);
    }
}

void PowerInterface::usePowerArmore(Node *n)
{
    qDebug()<<"PowerInterface : enter 'usePowerArmore'";

    const int cost = 10;
    if(mana >= cost)
    {
        mana -= cost;
        powerArmore.enablePower(n);
    }
}
