#include "powerinterface.h"
#include "GameComponent/node.h"
#include "GameInterface/button.h"
#include "GameInterface/Powers/power.h"
#include "GameInterface/Powers/powerarmore.h"
#include "GameInterface/Powers/powerdestroy.h"
#include "GameInterface/Powers/powerinvincibility.h"
#include "GameInterface/Powers/powerteleportation.h"
#include <QPainter>

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerInterface::PowerInterface(QGraphicsItem * parent) : QGraphicsWidget(parent),mana(0)
{
    btPowerDestroy = new Button("Destroy", this);
    btPowerInvincibility = new Button("Invincibility", this);
    btPowerTeleportation = new Button("Teleportation", this);
    btPowerArmore = new Button("Armor", this);

    powerArmore = new PowerArmore(this);
    powerDestroy = new PowerDestroy(this);
    powerInvincibility = new PowerInvincibility(this);
    powerTeleportation = new PowerTeleportation(this);

    connect(btPowerDestroy, SIGNAL(pressed()), this, SLOT(btPowerDestroyPressed()));
    connect(btPowerInvincibility, SIGNAL(pressed()), this, SLOT(btPowerInvincibilityPressed()));
    connect(btPowerTeleportation, SIGNAL(pressed()), this, SLOT(btPowerTeleportationPressed()));
    connect(btPowerArmore, SIGNAL(pressed()), this, SLOT(btPowerArmorePressed()));

    btPowerDestroy->setX(75);
    btPowerInvincibility->setX(75);
    btPowerTeleportation->setX(75);
    btPowerArmore->setX(75);
    btPowerDestroy->setY(25);
    btPowerInvincibility->setY(75);
    btPowerTeleportation->setY(125);
    btPowerArmore->setY(175);
}

PowerInterface::~PowerInterface()
{
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

QRectF PowerInterface::boundingRect() const
{
    return QRectF(0, 0, 100, 200);
}

void PowerInterface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
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
    const int cost = 80;
    if(mana >= cost)
    {
        mana -= cost;
        powerDestroy->enablePower(n);
    }
}

void PowerInterface::usePowerInvincibility(Node *n)
{
    const int cost = 50;
    if(mana >= cost)
    {
        mana -= cost;
        powerInvincibility->enablePower(n);
    }
}

void PowerInterface::usePowerTeleportation(Node *from, Node *to)
{
    const int cost = 40;
    if(mana >= cost)
    {
        mana -= cost;
        powerTeleportation->enablePower(from, to);
    }
}

void PowerInterface::usePowerArmore(Node *n)
{
    const int cost = 10;
    if(mana >= cost)
    {
        mana -= cost;
        powerArmore->enablePower(n);
    }
}

void PowerInterface::btPowerDestroyPressed() const
{
    emit powerPressed(Destroy);
}

void PowerInterface::btPowerInvincibilityPressed() const
{
    emit powerPressed(Invincibility);
}

void PowerInterface::btPowerTeleportationPressed() const
{
    emit powerPressed(Teleportation);
}

void PowerInterface::btPowerArmorePressed() const
{
    emit powerPressed(Armore);
}
