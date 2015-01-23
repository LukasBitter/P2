#ifndef POWERDESTROY_H
#define POWERDESTROY_H

#include "power.h"

class Node;

namespace GameInterface {
    class PowerDestroy;
}

/**
 * @class PowerDestroy
 * @brief Detruit toutes les ressources d'un noeud
 */
class PowerDestroy : public Power
{

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerDestroy();

    /*SURCHARGE*/
    void powerAction(Node *n);
};

#endif // POWERDESTROY_H
