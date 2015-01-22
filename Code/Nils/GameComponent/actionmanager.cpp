#include "actionmanager.h"

ActionManager::ActionManager(QObject *parent) :
    QObject(parent), currentSelection(0), lastSelection(0),
    action(NO_ACTION)
{

}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void ActionManager::selectionChanged(Node *n)
{
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
        }
    }
}

void ActionManager::actionChanged(ACTIONS a)
{
    if(a != NO_ACTION)
    {
        action = a;
        if(currentSelection != 0)
            emit doAction(action, currentSelection);

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
