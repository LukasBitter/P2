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
    Q_UNUSED(n);
    activateCountDown();
}

void Power::enablePower(Node *n1, Node *n2)
{
    Q_UNUSED(n1);
    Q_UNUSED(n2);
    activateCountDown();
}

void Power::enablePower(int v, Node *n)
{
    Q_UNUSED(v);
    Q_UNUSED(n);
    activateCountDown();
}

void Power::enablePower(int v, Node *n1, Node *n2)
{
    Q_UNUSED(v);
    Q_UNUSED(n1);
    Q_UNUSED(n2);
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
