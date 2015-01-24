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
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void ActionManager::selectionChanged(Node *n)
{
    qDebug()<<"ActionManager : enter 'selectionChanged'";

    if(n == 0)
    {
        qDebug()<<"1-1";
        reset();
    }
    else
    {
        qDebug()<<"1-2";
        lastSelection = currentSelection;
        currentSelection = n;

        if(action != NO_ACTION)
        {
            emit doAction(action, currentSelection);
            if(lastSelection != 0)
            {
                emit doAction(action, lastSelection, currentSelection);
                action = NO_ACTION;
            }
        }
    }
}

void ActionManager::actionChanged(ACTIONS a)
{
    qDebug()<<"ActionManager : enter 'actionChanged' : "<<a;

    action = a;
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
