#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>
#include "enumlibrary.h"

class NodeCombat;

namespace GameComponent
{
class ActionManager;
}

class ActionManager : public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    ActionManager(QObject *parent = 0);


    /*SIGNALS/SLOTS*/
signals:
    void doAction(ACTIONS action, NodeCombat *n);
    void doAction(ACTIONS action, NodeCombat *n1, NodeCombat *n2);
public slots:
    void selectionChanged(NodeCombat *n);
    void actionChanged(ACTIONS action);
    void reset();

private:
    /*OUTIL*/
    NodeCombat *currentSelection;
    NodeCombat *lastSelection;
    ACTIONS action;

    /*METHODE PRIVE*/
};

#endif // ACTIONMANAGER_H
