#include "powerinterface.h"
#include "node.h"
#include "button.h"
#include "power.h"
#include "powerarmore.h"
#include "powerdestroy.h"
#include "powerinvincibility.h"
#include "powerteleportation.h"


PowerInterface::PowerInterface(QGraphicsItem * parent) : QGraphicsWidget(parent),mana(0)
{
    btPowerDestroy = new Button("Destroy", this);
    btPowerInvincibility = new Button("Invincibility", this);
    btPowerTeleportation = new Button("Teleportation", this);
    btPowerArmore = new Button("Armor", this);

    powerArmore = new PowerArmore(5000, this);
    powerDestroy = new PowerDestroy(30000, this);
    powerInvincibility = new PowerInvincibility(20000, this);
    powerTeleportation = new PowerTeleportation(15000, this);

    connect(btPowerDestroy, SIGNAL(clicked()), this, SLOT(btPowerDestroyPressed()));
    connect(btPowerInvincibility, SIGNAL(clicked()), this, SLOT(btPowerInvincibilityPressed()));
    connect(btPowerTeleportation, SIGNAL(clicked()), this, SLOT(btPowerTeleportationPressed()));
    connect(btPowerArmore, SIGNAL(clicked()), this, SLOT(btPowerArmorePressed()));

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

void PowerInterface::usePowerTeleportation(Node *from, Node *to, int nbUnit)
{
    const int cost = 40;
    if(mana >= cost)
    {
        mana -= cost;
        powerTeleportation->enablePower(nbUnit, from, to);
    }
}

void PowerInterface::usePowerArmore(Node *n, int nbArmore)
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
    emit powerDestroyPressed();
}

void PowerInterface::btPowerInvincibilityPressed() const
{
    emit powerInvincibilityPressed();
}

void PowerInterface::btPowerTeleportationPressed() const
{
    emit powerTeleportationPressed();
}

void PowerInterface::btPowerArmorePressed() const
{
    emit powerArmorePressed();
}
