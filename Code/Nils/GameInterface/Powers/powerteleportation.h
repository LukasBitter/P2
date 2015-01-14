#ifndef POWERTELEPORTATION_H
#define POWERTELEPORTATION_H

#include "power.h"

class Node;

namespace GameInterface {
    class PowerTeleportation;
}

/**
 * @class PowerTeleportation
 * @brief Téléporte des unités d'un noeud a un autre
 */
class PowerTeleportation : public Power
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerTeleportation(QObject *parent=0);

    /*SURCHARGE*/
    void powerAction(Node *n1, Node *n2);
};

#endif // POWERTELEPORTATION_H