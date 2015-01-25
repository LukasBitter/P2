#ifndef POWER_H
#define POWER_H

#include "enumlibrary.h"
#include "global.h"

class Node;

namespace GameInterface
{
    class PowerCountDown;
}

/**
 * @class PowerCountDown
 * @brief Gestionnaire de temps de recharge pour des actions du joueur
 *
 * Les actions doivent être de type ACTIONS, un signal est émit lorsque l'action
 * débute et arrive à la fin de sont effet. Il n'est pas possible de lancer une action étant en cour de recharge
 */
class PowerCountDown : public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerCountDown(QObject * parent = 0);

    /*ASSESSEUR / MUTATEUR*/
    void addCountDown(int countDownTime, int powerDuration, ACTIONS powerName, Node *n1, Node *n2);
    double percentReload(ACTIONS powerName) const;
    void advence();
    bool isReady(ACTIONS a) const;

signals:
    void powerFinishing(ACTIONS a, Node* n1, Node* n2);
    void powerStarting(ACTIONS a, Node* n1, Node* n2);

private:
    /*OUTIL*/
    QHash<ACTIONS, int> lstCountDownTime; ///< Liste des temps de recharge par pouvoir
    QHash<ACTIONS, int> lstPowerDuration; ///< Liste de la durée des pouvoirs (par pouvoir)
    QHash<ACTIONS, int> lstPowerCurentTime; ///< Liste de l'ecoulement des pouvoirs (par pouvoir)
    QHash<ACTIONS, bool> lstPowerFinish; ///< Liste des flag "pouvoir fini" par pouvoir
    QHash<ACTIONS, QPair<Node *, Node *> > lstContext; ///< Liste des contexts des pouvoirs (par pouvoir)

    /*METHODE PRIVE*/
    void deletePower(ACTIONS a);
    void signalPower(ACTIONS a);
};

#endif // POWER_H
