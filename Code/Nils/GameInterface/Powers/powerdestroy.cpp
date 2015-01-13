#include "powerdestroy.h"
#include "GameComponent/node.h"

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
        n->setRessources(0);
        Power::enablePower(n);
    }
}

void PowerDestroy::onPowerFinishing()
{
}
