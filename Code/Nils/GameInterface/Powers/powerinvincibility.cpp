#include "powerinvincibility.h"
#include "GameComponent/node.h"

PowerInvincibility::PowerInvincibility(int countDown, QObject *parent) :
    Power(countDown, parent), memory(0)
{
}

PowerInvincibility::~PowerInvincibility()
{

}

void PowerInvincibility::enablePower(Node *n)
{
    if(isReady())
    {
        memory = n;
        memory->setInvicibility(true);
        Power::enablePower(n);
    }
}

void PowerInvincibility::onPowerFinishing()
{
    memory->setInvicibility(false);
    memory = 0;
}
