#include "actionmanager.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

ActionManager::ActionManager(QObject *parent) :
    QObject(parent), currentSelection(0), lastSelection(0),
    action(NO_ACTION)
{

}

ACTIONS ActionManager::getCurrentAction() const
{
    return action;
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void ActionManager::selectionChanged(Node *n)
{
    qDebug()<<"ActionManager : enter 'selectionChanged'";

    if(n == 0)
    {
        qDebug()<<"ActionManager : selection changed to 0";
        reset();
    }
    else
    {
        qDebug()<<"ActionManager : selection changed to another node";

        if(currentSelection == 0)
        {
            currentSelection = n;
            qDebug()<<"ActionManager : emit doAction( x , x )";
            emit doAction(action, currentSelection);
        }
        else
        {
            lastSelection = currentSelection;
            currentSelection = n;

            qDebug()<<"ActionManager : emit doAction( x , x , x )";
            emit doAction(action, lastSelection, currentSelection);
        }
    }
}

void ActionManager::actionChanged(ACTIONS a)
{
    qDebug()<<"ActionManager : enter 'actionChanged'";
    qDebug()<<"ActionManager : action number "<<a;

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
    qDebug()<<"ActionManager : enter 'reset'";
    currentSelection = 0;
    lastSelection = 0;
    action = NO_ACTION;

    qDebug()<<"ActionManager : emit doAction( x )";
    emit doAction(action);
}
