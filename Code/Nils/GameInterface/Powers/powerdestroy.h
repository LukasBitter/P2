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
    PowerDestroy(int countDown, QObject *parent=0);
    ~PowerDestroy();

    /*SURCHARGE*/
    void enablePower(Node *n);
    void onPowerFinishing();

private:
};

#endif // POWERDESTROY_H
