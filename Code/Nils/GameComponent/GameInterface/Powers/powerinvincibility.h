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

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerInvincibility();

    /*SURCHARGE*/
    void powerAction(Node *n);
    void onPowerFinishing();

private:
    /*OUTIL*/
    Node *memory; ///< Memoire temporaire -> reset à la fin de pouvoir
};

#endif // POWERINVINCIBILITY_H
