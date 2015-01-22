#include "actionmanager.h"

ActionManager::ActionManager(QObject *parent) :
    QObject(parent), currentSelection(0), lastSelection(0),
    action(NO_ACTION)
{

}

ActionManager::~ActionManager()
{

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
            if(currentSelection == 0) qDebug()<<"TROOOOOOOOOOOOLLLLLL";
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
