#include "power.h"
#include "global.h"

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Power::Power(int countDownTime, int powerTime):
    reloadCD(0), powerCD(0)
{
    if(countDownTime >= powerTime)
    {
        this->countDownTime = countDownTime;
        this->powerTime = powerTime;
    }
    else
    {
        this->countDownTime = countDownTime;
        this->powerTime = countDownTime;
    }
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void Power::enablePower()
{
    if(!isReady()) return;
    powerAction();
    activateCountDown();
}

void Power::enablePower(Node *n)
{
    if(!isReady()) return;
    powerAction(n);
    activateCountDown();
}

void Power::enablePower(Node *n1, Node *n2)
{
    if(!isReady()) return;
    powerAction(n1,n2);
    activateCountDown();
}

void Power::enablePower(int v, Node *n)
{
    if(!isReady()) return;
    powerAction(v,n);
    activateCountDown();
}

void Power::enablePower(int v, Node *n1, Node *n2)
{
    if(!isReady()) return;
    powerAction(v,n1,n2);
    activateCountDown();
}

void Power::powerAction()
{
    qDebug()<<"powerAction not override";
}

void Power::powerAction(Node *n)
{
    Q_UNUSED(n);
    qDebug()<<"powerAction not override";
}

void Power::powerAction(Node *n1, Node *n2)
{
    Q_UNUSED(n1);
    Q_UNUSED(n2);
    qDebug()<<"powerAction not override";
}

void Power::powerAction(int v, Node *n)
{
    Q_UNUSED(v);
    Q_UNUSED(n);
    qDebug()<<"powerAction not override";
}

void Power::powerAction(int v, Node *n1, Node *n2)
{
    Q_UNUSED(v);
    Q_UNUSED(n1);
    Q_UNUSED(n2);
    qDebug()<<"powerAction not override";
}

void Power::onPowerFinishing()
{
    qDebug()<<"onPowerFinishing not override";
}

void Power::onPowerReady()
{
    qDebug()<<"onPowerReady not override";
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

bool Power::isReady() const
{
    return powerCD <= 0;
}

double Power::percentReload() const
{
    return ((double)(countDownTime-reloadCD)/(double)(countDownTime))*100;
}

void Power::advence()
{
    if(reloadCD > 0) --reloadCD;
    if(powerCD > 0) --powerCD;

    if(reloadCD == 0)
    {
        onPowerReady();
        reloadCD = -1;
    }

    if(powerCD == 0)
    {
        onPowerFinishing();
        powerCD = -1;
    }
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void Power::activateCountDown()
{
    powerCD = powerTime;
    reloadCD = countDownTime;
}


