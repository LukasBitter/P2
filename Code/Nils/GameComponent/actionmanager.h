#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>
#include "enumlibrary.h"

class Node;

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
    virtual ~ActionManager();

    /*SIGNALS/SLOTS*/
signals:
    void doAction(ACTIONS action);
    void doAction(ACTIONS action, Node *n);
    void doAction(ACTIONS action, Node *n1, Node *n2);
public slots:
    void selectionChanged(Node *n);
    void actionChanged(ACTIONS action);
    void clear();

private:
    /*OUTIL*/
    Node *currentSelection;
    Node *lastSelection;
    ACTIONS action;

    /*METHODE PRIVE*/
    void reset();
};

#endif // ACTIONMANAGER_H
