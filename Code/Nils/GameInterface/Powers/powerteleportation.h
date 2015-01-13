#ifndef POWERTELEPORTATION_H
#define POWERTELEPORTATION_H

#include "power.h"

class Node;

namespace GameInterface {
    class PowerTeleportation;
}

class PowerTeleportation : public Power
{
    Q_OBJECT
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerTeleportation(int countDown, QObject *parent=0);
    ~PowerTeleportation();

    /*SURCHARGE*/
    void enablePower(Node *n1, Node *n2);
    void onPowerFinishing();
};

#endif // POWERTELEPORTATION_H
