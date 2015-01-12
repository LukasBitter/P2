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

bool Power::isReady() const
{
    return ready;
}

void Power::activateCountDown()
{
    ready = false;
    timer->start();
}

void Power::restorCountDown()
{
    ready = true;
}
