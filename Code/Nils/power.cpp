#include "power.h"
#include <QTimer>

Power::Power(int countDown, QObject *parent): QObject(parent),
    ready(true)
{
    timer = new QTimer(this);
    timer->setInterval(countDown);
    connect(timer, SIGNAL(timeout()), this, SLOT(restorCountDown()));
}

Power::~Power()
{
}

void Power::enablePower()
{

}
bool Power::isReady() const
{
    return ready;
}


void Power::enablePower(Node *n)
{
    activateCountDown();
}

void Power::enablePower(Node *n1, Node *n2)
{
    activateCountDown();
}

void Power::enablePower(int v, Node *n)
{
    activateCountDown();
}

void Power::enablePower(int v, Node *n1, Node *n2)
{
    activateCountDown();
}

void Power::onPowerFinishing()
{

}

void Power::activateCountDown()
{
    ready = false;
    timer->start();
}

void Power::restorCountDown()
{
    onPowerFinishing();
    ready = true;
}
