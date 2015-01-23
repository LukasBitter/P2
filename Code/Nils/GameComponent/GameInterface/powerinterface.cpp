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
    return QRectF(0, 0, 50, 185);
}

void PowerInterface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::lightGray);
    painter->drawRect(boundingRect());
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

void PowerInterface::usePower(POWER_NAME name, Node *n1, Node *n2)
{
    switch (name)
    {
    case P_DESTROY:
        if(n1 != 0)usePowerDestroy(n1);
        break;
    case P_INVINCIBILITY:
        if(n1 != 0)usePowerInvincibility(n1);
        break;
    case P_TELEPORTATION:
        if(n1 != 0 && n2 != 0)usePowerTeleportation(n1, n2);
        break;
    case P_ARMORE:
        if(n1 != 0)usePowerArmore(n1);
        break;
    default:
        break;
    }
}

void PowerInterface::btPowerDestroyPressed()
{
    emit powerPressed(P_DESTROY);
}

void PowerInterface::btPowerInvincibilityPressed()
{
    emit powerPressed(P_INVINCIBILITY);
}

void PowerInterface::btPowerTeleportationPressed()
{
    emit powerPressed(P_TELEPORTATION);
}

void PowerInterface::btPowerArmorePressed()
{
    emit powerPressed(P_ARMORE);
}

void PowerInterface::setUpUI()
{
    //INSTANTIATION

    btPowerDestroy = new Button("Destroy", this);
    btPowerInvincibility = new Button("Invincibility", this);
    btPowerTeleportation = new Button("Teleportation", this);
    btPowerArmore = new Button("Armor", this);

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
    btPowerDestroy->setY(25);
    btPowerInvincibility->setY(70);
    btPowerTeleportation->setY(115);
    btPowerArmore->setY(160);
}
