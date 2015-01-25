#include "powercountdown.h"
#include "global.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

PowerCountDown::PowerCountDown(QObject *parent): QObject(parent)
{
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void PowerCountDown::addCountDown(int countDownTime, int powerDuration, ACTIONS powerName, NodeCombat *n1, NodeCombat *n2)
{
    if(!isReady(powerName)) return;

    if(powerDuration > countDownTime) powerDuration = countDownTime;

    lstContext.insert(powerName, QPair <NodeCombat *, NodeCombat * >(n1,n2));
    lstCountDownTime.insert(powerName, countDownTime);
    lstPowerDuration.insert(powerName, powerDuration);
    lstPowerCurentTime.insert(powerName, countDownTime);
    lstPowerFinish.insert(powerName, false);

    emit powerStarting(powerName, n1, n2);
}

double PowerCountDown::percentReload(ACTIONS powerName) const
{
    int countDownTime = lstCountDownTime.value(powerName);
    int powerCurentTime = lstPowerCurentTime.value(powerName);
    double percent = ((double)(countDownTime-powerCurentTime)/(double)(countDownTime))*100;
    return isnan(percent)? 100 : percent;
}

void PowerCountDown::advence()
{
    foreach (ACTIONS a, lstPowerCurentTime.keys())
    {
        if(lstCountDownTime.value(a)-lstPowerCurentTime.value(a) == lstPowerDuration.value(a) &&
                !lstPowerFinish.value(a))
            signalPower(a);

        if(lstPowerCurentTime.value(a) > 0)
            lstPowerCurentTime.insert(a,lstPowerCurentTime.value(a)-1);
        else
            deletePower(a);
    }
}

bool PowerCountDown::isReady(ACTIONS a) const
{
    return !lstCountDownTime.contains(a);
}

void PowerCountDown::deletePower(ACTIONS a)
{
    lstContext.remove(a);
    lstCountDownTime.remove(a);
    lstPowerDuration.remove(a);
    lstPowerCurentTime.remove(a);
    lstPowerFinish.remove(a);
}

void PowerCountDown::signalPower(ACTIONS a)
{
    lstPowerFinish.insert(a, true);
    QPair<NodeCombat *, NodeCombat *> context = lstContext.value(a);
    emit powerFinishing(a, context.first, context.second);
}
