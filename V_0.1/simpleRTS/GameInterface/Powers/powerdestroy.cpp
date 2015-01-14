#include "powerdestroy.h"
#include "GameComponent/node.h"

#include <QDebug>

PowerDestroy::PowerDestroy(QObject *parent) :
    Power(30000,0, parent)
{
}

void PowerDestroy::powerAction(Node *n)
{
    if(n != 0)
    {
        n->setRessources(0);
    }
}
