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
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerArmore(QObject *parent=0);

    /*SURCHARGE*/
    void powerAction(Node *n);
    void onPowerFinishing();

private:
    /*OUTIL*/
    Node *memory;
    const int armorLvl;
};

#endif // POWERARMORE_H
