#ifndef POWERINVINCIBILITY_H
#define POWERINVINCIBILITY_H

#include "power.h"

namespace GameInterface {
    class PowerInvincibility;
}

class PowerInvincibility : public Power
{
    Q_OBJECT
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerInvincibility(int countDown, QObject *parent=0);
    ~PowerInvincibility();

    /*SURCHARGE*/
    void enablePower(Node *n);
    void onPowerFinishing();

private:
    Node *memory;
};

#endif // POWERINVINCIBILITY_H
