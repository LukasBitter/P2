#include "powerarmore.h"
#include "node.h"

PowerArmore::PowerArmore(int countDown, QObject *parent) :
    Power(countDown, parent), memory(0), armorLvl(20)
{
}

PowerArmore::~PowerArmore()
{

}

void PowerArmore::enablePower(Node *n)
{
    if(isReady())
    {
        memory = n;
        memory->setArmorLvl(armorLvl);
        Power::enablePower(n);
    }
}

void PowerArmore::onPowerFinishing()
{
    memory->setArmorLvl(0);
    memory = 0;
}
