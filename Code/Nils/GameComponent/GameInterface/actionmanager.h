#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include "global.h"
#include "enumlibrary.h"

class Node;

namespace GameComponent
{
    class ActionManager;
}

/**
 * @class ActionManager
 * @brief Récupère les changements d'action et les selections du joueur pour déterminer
 * l'action à appliquer
 */
class ActionManager : public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    ActionManager(QObject *parent = 0);


    /*SIGNALS/SLOTS*/
signals:
    void doAction(ACTIONS action);
    void doAction(ACTIONS action, Node *n);
    void doAction(ACTIONS action, Node *n1, Node *n2);
public slots:
    void selectionChanged(Node *n);
    void actionChanged(ACTIONS action);
    void reset();

private:
    /*OUTIL*/
    Node *currentSelection; ///< Selection du noeud actuel
    Node *lastSelection; ///< Selection du noeud précédent
    ACTIONS action; ///< Action en cours

    /*METHODE PRIVE*/
};

#endif // ACTIONMANAGER_H
