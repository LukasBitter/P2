#include "powerarmore.h"
#include "GameComponent/node.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerArmore::PowerArmore() : Power(5,5), memory(0),
    armorLvl(20)
{
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void PowerArmore::powerAction(Node *n)
{
    if(n != 0)
    {
        memory = n;
        memory->setArmorLvl(armorLvl);
    }
}

void PowerArmore::onPowerFinishing()
{
    if(memory != 0)
    {
        memory->setArmorLvl(0);
        memory = 0;
    }
}
