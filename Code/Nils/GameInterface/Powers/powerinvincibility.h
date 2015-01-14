#ifndef POWERINVINCIBILITY_H
#define POWERINVINCIBILITY_H

#include "power.h"

class Node;

namespace GameInterface {
    class PowerInvincibility;
}

/**
 * @class PowerInvincibility
 * @brief Rend un noeud invulnérable durant un court instant
 */
class PowerInvincibility : public Power
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerInvincibility(QObject *parent=0);

    /*SURCHARGE*/
    void powerAction(Node *n);
    void onPowerFinishing();

private:
    /*OUTIL*/
    Node *memory;
};

#endif // POWERINVINCIBILITY_H
