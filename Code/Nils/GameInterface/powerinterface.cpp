#include "powerinterface.h"
#include "GameComponent/node.h"
#include "GameInterface/button.h"
#include "GameInterface/Powers/power.h"
#include "GameInterface/Powers/powerarmore.h"
#include "GameInterface/Powers/powerdestroy.h"
#include "GameInterface/Powers/powerinvincibility.h"
#include "GameInterface/Powers/powerteleportation.h"


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

    btPowerDestroy->setX(10);
    btPowerInvincibility->setX(10);
    btPowerTeleportation->setX(10);
    btPowerArmore->setX(10);
    btPowerDestroy->setY(0);
    btPowerInvincibility->setY(50);
    btPowerTeleportation->setY(100);
    btPowerArmore->setY(150);
}

PowerInterface::~PowerInterface()
{
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
