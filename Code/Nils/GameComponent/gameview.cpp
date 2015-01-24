#include "gameview.h"
#include "node.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include "gamescene.h"
#include "GameInterface/powerinterface.h"
#include "global.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameView::GameView(GamerList &gl, Gamer *g, QWidget *parent) :
    QGraphicsView(parent), owner(g), scene(0), powerUi(0),
    percentToSend(100)
{
    scene = new GameScene(gl, g, 0);
    setUpUI();
}

GameView::GameView(QString create, GamerList &gl, Gamer *g, QWidget *parent):
    QGraphicsView(parent), owner(g), scene(0), powerUi(0),
    percentToSend(100)
{
    scene = new GameScene(create, gl, g, 0);
    setUpUI();
}

GameView::~GameView()
{
    qDebug()<<"GameView : destroy";
    delete scene;
}

/*----------------------------------------------------*/
/*DELEGUES*/
/*----------------------------------------------------*/

QString GameView::getUpdateString()
{
    return scene->getUpdateString();
}

void GameView::updateFromString(QString s)
{
    scene->updateFromString(s);
    powerUi->advence();
    scene->update(scene->sceneRect());
}

QString GameView::getCreationString()
{
    return scene->getCreationString();
}

void GameView::advance()
{
    scene->advance();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void GameView::setUpUI()
{
    powerUi = new PowerInterface();
    powerUi->setX(0);
    powerUi->setY(0);
    powerUi->setMana(1000);

    // Désactivation des scrollbars
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );
    setRenderHint( QPainter::Antialiasing, true );

    setScene(scene);
    connect(scene,SIGNAL(selectionChanged()),this,SLOT(selectionChange()));
    connect(&actionManager,SIGNAL(doAction(ACTIONS)),this,SLOT(onDoAction(ACTIONS)));
    connect(&actionManager,SIGNAL(doAction(ACTIONS,Node*)),this,SLOT(onDoAction(ACTIONS,Node*)));
    connect(&actionManager,SIGNAL(doAction(ACTIONS,Node*,Node*)),this,SLOT(onDoAction(ACTIONS,Node*,Node*)));
    connect(powerUi,SIGNAL(powerPressed(POWER_NAME)),this,SLOT(onPowerPressed(POWER_NAME)));


    scene->addItem(powerUi);
}


//if(e->button()== Qt::LeftButton)
//{
//    Node *nodeTo = dynamic_cast <Node*>(itemAt(e->pos()));
//    action.selectionChanged(nodeTo);
//}

/*====================================================*/

/*CAPTURE ACTIONS CLIENT*/

/*====================================================*/


/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void GameView::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Q:
    {
        setPercentToSend(25);
        actionManager.actionChanged(GA_SEND);

        break;
    }
    case Qt::Key_W:
    {
        setPercentToSend(50);
        actionManager.actionChanged(GA_SEND);

        break;
    }
    case Qt::Key_E:
    {
        setPercentToSend(75);
        actionManager.actionChanged(GA_SEND);

        break;
    }
    case Qt::Key_R:
    {
        setPercentToSend(100);
        actionManager.actionChanged(GA_SEND);

        break;
    }
    default:
        powerUi->shortCutPressed(e);
        break;
    }

    QGraphicsView::keyPressEvent(e);
}

void GameView::dropEvent(QDropEvent *event)
{
    actionManager.actionChanged(NO_ACTION);
    if(event->mimeData()->hasText())
    {
        //Ordre déplacement via drag&drop
        event->accept();
        Node *nodeFrom = scene->getNode(qvariant_cast<QString>(event->mimeData()->text()).toInt());
        Node *nodeTo = dynamic_cast <Node*>(this->itemAt(event->pos()));
        sendSquad(nodeFrom, nodeTo);
    }
    QGraphicsView::dropEvent(event);
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

void GameView::setPercentToSend(int percent)
{
    if(percent>=0 && percent<=100) percentToSend = percent;
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameView::selectionChange()
{
    QList<QGraphicsItem *> lst = scene->selectedItems();

    Node *nodeTo = 0;

    if(!lst.isEmpty())
    {
        nodeTo = dynamic_cast <Node*>(lst.first());
    }
    actionManager.selectionChanged(nodeTo);
}

void GameView::onDoAction(ACTIONS action)
{
    qDebug()<<"GameView : enter 'onDoAction' do "<<action;
}

void GameView::onDoAction(ACTIONS action, Node *n)
{
    qDebug()<<"GameView : enter 'onDoAction' do "<<action;

    usePower(n->getId(),0, ActionManager::actionToPower(action));
}

void GameView::onDoAction(ACTIONS action, Node *n1, Node *n2)
{
    qDebug()<<"GameView : enter 'onDoAction' do "<<action;

    switch (action)
    {
    case GA_SEND:
    {
        sendSquad(n1, n2);
        scene->clearSelection();
        actionManager.clear();
        break;
    }
    case GA_USEPOWER_DESTROY:
    case GA_USEPOWER_INVINCIBILITY:
    case GA_USEPOWER_ARMORE:
    case GA_USEPOWER_TELEPORTATION:
    {
        usePower(n1->getId(),n2->getId(),ActionManager::actionToPower(action));
        break;
    }
    default:
        break;
    }
}

void GameView::onPowerPressed(POWER_NAME name)
{
    qDebug()<<"GameView : enter 'onPowerPressed'";

    actionManager.actionChanged(ActionManager::powerToAction(name));
}


/*====================================================*/

/*RECEPTION ACTIONS SERVEUR*/

/*====================================================*/


/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameView::applyGamerAction(QString s)
{
    QStringList msgStr = s.split(".");
    if(msgStr.size() != 5) return;
    ACTIONS cmd = (ACTIONS)msgStr.first().toInt();
    msgStr.pop_front();
    int gamerId = msgStr.first().toInt(); //Identifiant du joueur
    msgStr.pop_front();
    Node *nodeFrom = scene->getNode(msgStr.first().toInt()); //noeud source
    msgStr.pop_front();
    Node *nodeTo = scene->getNode(msgStr.first().toInt()); //noeud cible
    msgStr.pop_front();
    int param = msgStr.first().toInt(); //Parametre de l'action (nb ressource / pouvoir id)

    switch (cmd)
    {
    case GA_SEND:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_SEND";

        if(nodeFrom != 0 && nodeTo != 0 && nodeFrom->getOwner()->getId() == gamerId)
        {
            nodeFrom->sendSquad(param, nodeTo->getId());
        }
        break;
    }
    case GA_USEPOWER_DESTROY:
    case GA_USEPOWER_INVINCIBILITY:
    case GA_USEPOWER_ARMORE:
    case GA_USEPOWER_TELEPORTATION:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_USEPOWER";

        powerUi->usePower(ActionManager::actionToPower(cmd),nodeFrom, nodeTo);
        break;
    }
    default:
        qCritical()<<"GameView : unexpected case in 'applyGamerAction'";
        break;
    }

}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void GameView::sendSquad(Node *from, Node *to)
{
    if(from == 0 || to == 0 || from->getOwner() != owner) return;

    emit gamerAction(QString("%1.%2.%3.%4.%5").arg(GA_SEND).
                     arg(owner->getId()).arg(from->getId()).
                     arg(to->getId()).
                     arg((int)(from->getRessources()*(percentToSend/100))));
}

void GameView::usePower(int nodeFromId, int nodeToId, POWER_NAME p)
{
    emit gamerAction(QString("%1.%2.%3.%4.%5").arg(ActionManager::powerToAction(p)).
                     arg(owner->getId()).arg(nodeFromId).
                     arg(nodeToId).arg(p));
}
