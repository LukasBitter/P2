#include "powerdestroy.h"
#include "node.h"

PowerDestroy::PowerDestroy(int countDown, QObject *parent) :
    Power(countDown, parent)
{
}

PowerDestroy::~PowerDestroy()
{

}

void PowerDestroy::enablePower(Node *n)
{
    if(isReady())
    {
        n->setNbRessources(0);
        Power::enablePower(n);
    }
}

void PowerDestroy::onPowerFinishing()
{
}
