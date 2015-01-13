#ifndef POWERARMORE_H
#define POWERARMORE_H

#include "power.h"

class Node;

namespace GameInterface {
    class PowerArmore;
}

class PowerArmore : public Power
{
    Q_OBJECT
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerArmore(int countDown, QObject *parent=0);
    ~PowerArmore();

    /*SURCHARGE*/
    void enablePower(Node *n);
    void onPowerFinishing();

private:
    Node *memory;
    const int armorLvl;
};

#endif // POWERARMORE_H
