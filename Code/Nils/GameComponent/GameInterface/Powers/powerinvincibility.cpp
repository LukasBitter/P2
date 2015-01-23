#include "powerinvincibility.h"
#include "GameComponent/node.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerInvincibility::PowerInvincibility() :
    Power(200,50), memory(0)
{
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void PowerInvincibility::powerAction(Node *n)
{
    if(n != 0)
    {
        memory = n;
        memory->setInvicibility(true);
    }
}

void PowerInvincibility::onPowerFinishing()
{
    if(memory != 0)
    {
        memory->setInvicibility(false);
        memory = 0;
    }
}
