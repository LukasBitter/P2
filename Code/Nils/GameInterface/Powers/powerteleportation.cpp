#include "powerteleportation.h"
#include "GameComponent/node.h"
#include "GameComponent/squad.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerTeleportation::PowerTeleportation(QObject *parent) :
    Power(15000,0, parent)
{
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void PowerTeleportation::powerAction(Node *n1, Node *n2)
{
    if(n1 != 0 && n2 != 0)
    {
        int ressources = n1->getRessources()/2;
        n1->setRessources(n1->getRessources() - ressources);
        Squad *s = new Squad(*n1->getOwner());
        s->setNbRessources(ressources);
        n2->incoming(*s);
    }
}
