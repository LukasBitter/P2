#ifndef POWER_H
#define POWER_H

#include "enumlibrary.h"
#include <QObject>

class NodeCombat;

namespace GameInterface
{
    class PowerCountDown;
}

class PowerCountDown : public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    PowerCountDown(QObject * parent = 0);

    /*ASSESSEUR / MUTATEUR*/
    void addCountDown(int countDownTime, int powerDuration, ACTIONS powerName, NodeCombat *n1, NodeCombat *n2);
    double percentReload(ACTIONS powerName) const;
    void advence();
    bool isReady(ACTIONS a) const;

signals:
    void powerFinishing(ACTIONS a, NodeCombat* n1, NodeCombat* n2);
    void powerStarting(ACTIONS a, NodeCombat* n1, NodeCombat* n2);

private:
    /*OUTIL*/
    QHash<ACTIONS, int> lstCountDownTime;
    QHash<ACTIONS, int> lstPowerDuration;
    QHash<ACTIONS, int> lstPowerCurentTime;
    QHash<ACTIONS, bool> lstPowerFinish;
    QHash<ACTIONS, QPair<NodeCombat *, NodeCombat *> > lstContext;

    /*METHODE PRIVE*/
    void deletePower(ACTIONS a);
    void signalPower(ACTIONS a);
};

#endif // POWER_H
