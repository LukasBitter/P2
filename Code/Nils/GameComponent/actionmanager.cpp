#include "actionmanager.h"
#include "global.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

ActionManager::ActionManager(QObject *parent) :
    QObject(parent), currentSelection(0), lastSelection(0),
    action(NO_ACTION)
{

}

ActionManager::~ActionManager()
{

}

/*----------------------------------------------------*/
/*CONVERTION*/
/*----------------------------------------------------*/

ACTIONS ActionManager::powerToAction(POWER_NAME p)
{
    switch (p)
    {
    case P_DESTROY:
    {
        return GA_USEPOWER_DESTROY;
    }
    case P_INVINCIBILITY:
    {
        return GA_USEPOWER_INVINCIBILITY;
    }
    case P_TELEPORTATION:
    {
        return GA_USEPOWER_TELEPORTATION;
    }
    case P_ARMORE:
    {
        return GA_USEPOWER_ARMORE;
    }
    default:
        return NO_ACTION;
    }
}

POWER_NAME ActionManager::actionToPower(ACTIONS p)
{
    switch (p)
    {
    case GA_USEPOWER_DESTROY:
    {
        return P_DESTROY;
    }
    case GA_USEPOWER_INVINCIBILITY:
    {
        return P_INVINCIBILITY;
    }
    case GA_USEPOWER_TELEPORTATION:
    {
        return P_TELEPORTATION;
    }
    case GA_USEPOWER_ARMORE:
    {
        return P_ARMORE;
    }
    default:
        return P_NONE;
    }
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void ActionManager::selectionChanged(Node *n)
{
    qDebug()<<"ActionManager : enter 'selectionChanged'";

    if(n == 0)
    {
        reset();
    }
    else
    {
        lastSelection = currentSelection;
        currentSelection = n;

        if(lastSelection != 0 && action != NO_ACTION)
        {
            emit doAction(action, lastSelection, currentSelection);
            action = NO_ACTION;
        }
    }
}

void ActionManager::actionChanged(ACTIONS a)
{
    qDebug()<<"ActionManager : enter 'actionChanged'";

    if(a != NO_ACTION)
    {
        action = a;
        if(currentSelection != 0)
        {
            emit doAction(action, currentSelection);
        }
    }
}

void ActionManager::clear()
{
    reset();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void ActionManager::reset()
{
    currentSelection = 0;
    lastSelection = 0;
    action = NO_ACTION;
}
