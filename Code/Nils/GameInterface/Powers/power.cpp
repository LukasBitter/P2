#include "power.h"
#include <QTimer>

#include <QDebug>

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

Power::Power(int countDownTime, int powerTime, QObject *parent): QObject(parent),
    ready(true)
{
    countDown = new QTimer(this);
    endPower = new QTimer(this);
    countDown->setInterval(countDownTime);
    endPower->setInterval(powerTime);
    connect(countDown, SIGNAL(timeout()), this, SLOT(restorCountDown()));
    connect(endPower, SIGNAL(timeout()), this, SLOT(powerEnd()));
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void Power::enablePower()
{
    if(!ready) return;
    powerAction();
    activateCountDown();
}

void Power::enablePower(Node *n)
{
    if(!ready) return;
    powerAction(n);
    activateCountDown();
}

void Power::enablePower(Node *n1, Node *n2)
{
    if(!ready) return;
    powerAction(n1,n2);
    activateCountDown();
}

void Power::enablePower(int v, Node *n)
{
    if(!ready) return;
    powerAction(v,n);
    activateCountDown();
}

void Power::enablePower(int v, Node *n1, Node *n2)
{
    if(!ready) return;
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
    return ready;
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void Power::restorCountDown()
{
    onPowerReady();
    countDown->stop();
    ready = true;
}

void Power::powerEnd()
{
    onPowerFinishing();
    endPower->stop();
}

/*----------------------------------------------------*/
/*PRIVATES METHODS*/
/*----------------------------------------------------*/

void Power::activateCountDown()
{
    ready = false;
    endPower->start();
    countDown->start();
}


