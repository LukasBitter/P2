#include "powerteleportation.h"
#include "node.h"
#include "squad.h"

PowerTeleportation::PowerTeleportation(int countDown, QObject *parent) :
    Power(countDown, parent)
{
}

PowerTeleportation::~PowerTeleportation()
{

}

void PowerTeleportation::enablePower(Node *n1, Node *n2)
{
    if(isReady())
    {
        int ressources = n1->getNbRessources()/2;
        n1->setNbRessources(n1->getNbRessources() - ressources);
        Squad *s = new Squad(*n1->getOwner());
        s->setNbRessources(ressources);
        n2->incoming(*s);
        Power::enablePower(n1, n2);
    }
}

void PowerTeleportation::onPowerFinishing()
{

}
