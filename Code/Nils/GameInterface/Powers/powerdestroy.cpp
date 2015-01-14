#include "powerdestroy.h"
#include "GameComponent/node.h"

#include <QDebug>

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerDestroy::PowerDestroy(QObject *parent) :
    Power(30000,0, parent)
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
