#include "powerinterface.h"
#include "node.h"
#include <QPushButton>


PowerInterface::PowerInterface(QWidget * parent) : QWidget(parent),mana(0),
    cdPowerArmore(0),cdPowerDestroy(0),cdPowerInvincibility(0),
    cdPowerTeleportation(0)
{
    btPowerDestroy = new QPushButton("Destroy", this);
    btPowerInvincibility = new QPushButton("Invincibility", this);
    btPowerTeleportation = new QPushButton("Teleportation", this);
    btPowerArmore = new QPushButton("Armor", this);
}

PowerInterface::~PowerInterface()
{

}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/


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
    const int cd = 3000;
    if(mana >= cost)
    {
        mana -= cost;
        n->setNbRessources(0);
        cdPowerDestroy = cd;

    }
}

void PowerInterface::usePowerInvincibility(Node *n)
{
    n->setInvicibility(true);
}

void PowerInterface::usePowerTeleportation(Node *from, Node *to, int nbUnit)
{

}

void PowerInterface::usePowerArmore(Node *n, int nbArmore)
{

}
