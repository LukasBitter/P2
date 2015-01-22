#ifndef POWERARMORE_H
#define POWERARMORE_H

#include "power.h"

class Node;

namespace GameInterface {
    class PowerArmore;
}

/**
 * @class PowerArmore
 * @brief Ajoute de l'armure à un noeud pendant une durée limité
 */
class PowerArmore : public Power
{

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerArmore();

    /*SURCHARGE*/
    void powerAction(Node *n);
    void onPowerFinishing();

private:
    /*OUTIL*/
    Node *memory; ///< Memoire temporaire -> reset à la fin de pouvoir
    const int armorLvl; ///< Niveau d'armure à rajouter
};

#endif // POWERARMORE_H
