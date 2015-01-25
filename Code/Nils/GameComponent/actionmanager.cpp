#include "actionmanager.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

ActionManager::ActionManager(QObject *parent) :
    QObject(parent), currentSelection(0), lastSelection(0),
    action(NO_ACTION)
{

}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void ActionManager::selectionChanged(NodeCombat *n)
{
    qDebug()<<"ActionManager : enter 'selectionChanged'";

    if(n == 0)
    {
        reset();
    }
    else
    {
        if(currentSelection == 0)
        {
            currentSelection = n;
            emit doAction(action, currentSelection);
        }
        else
        {
            lastSelection = currentSelection;
            currentSelection = n;

            emit doAction(action, lastSelection, currentSelection);
        }
    }
}

void ActionManager::actionChanged(ACTIONS a)
{
    qDebug()<<"ActionManager : enter 'actionChanged'";

    action = a;
    currentSelection = 0;
    lastSelection = 0;

    if(a == NO_ACTION)
    {
        reset();
    }
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
