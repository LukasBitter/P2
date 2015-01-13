#ifndef POWERDESTROY_H
#define POWERDESTROY_H

#include "power.h"

class Node;

namespace GameInterface {
    class PowerDestroy;
}

class PowerDestroy : public Power
{
    Q_OBJECT
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerDestroy(QObject *parent=0);

    /*SURCHARGE*/
    void powerAction(Node *n);

private:
};

#endif // POWERDESTROY_H
