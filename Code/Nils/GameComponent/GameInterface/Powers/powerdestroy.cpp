#include "powerdestroy.h"
#include "GameComponent/node.h"

#include <QDebug>

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerDestroy::PowerDestroy() :
    Power(300,0)
{
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void PowerDestroy::powerAction(Node *n)
{
    if(n != 0)
    {
        n->setRessources(0);
    }
}
