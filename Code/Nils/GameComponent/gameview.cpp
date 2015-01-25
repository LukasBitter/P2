#include "gameview.h"
#include "nodecombat.h"
#include "connexion.h"
#include "gamer.h"
#include "squad.h"
#include "gamerlist.h"
#include "gamescene.h"
#include "GameInterface/powerinterface.h"
#include "global.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

void GameView::initialize()
{
    scene = 0;
    powerUi = 0;
    percentToSend = 50;
    gameFinished = false;
}

GameView::GameView(GamerList &gl, Gamer *g, QWidget *parent) :
    QGraphicsView(parent), owner(g)
{
    initialize();
    scene = new GameScene(gl, g, 0);
    setUpUI();
}

GameView::GameView(QString create, GamerList &gl, Gamer *g, QWidget *parent):
    QGraphicsView(parent), owner(g)
{
    initialize();
    scene = new GameScene(create, gl, g, 0);
    setUpUI();
}

GameView::~GameView()
{
    qDebug()<<"GameView : destroy";
    delete scene;
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void GameView::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Escape:
        emit returnToMenu();
        break;
    case Qt::Key_Q:
        setPercentToSend(25);
        am.actionChanged(GA_SEND);
        break;
    case Qt::Key_W:
        setPercentToSend(50);
        am.actionChanged(GA_SEND);
        break;
    case Qt::Key_E:
        setPercentToSend(75);
        am.actionChanged(GA_SEND);
        break;
    case Qt::Key_R:
        setPercentToSend(100);
        am.actionChanged(GA_SEND);
        break;
    default:
        am.actionChanged(NO_ACTION);
        powerUi->shortCutPressed(e);
        break;
    }
}

void GameView::mousePressEvent(QMouseEvent *e)
{
    if(e->button()!= Qt::LeftButton) return;

    NodeCombat *n = dynamic_cast <NodeCombat*>(itemAt(e->pos()));

    if(n == 0)
    {
        am.reset();
    }
    else
    {
        am.selectionChanged(n);
    }

    QGraphicsView::mousePressEvent(e);
}

void GameView::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasText())
    {
        //Ordre déplacement via drag&drop
        event->accept();
        NodeCombat *nodeFrom = scene->getNode(qvariant_cast<QString>(event->mimeData()->text()).toInt());
        NodeCombat *nodeTo = dynamic_cast <NodeCombat*>(this->itemAt(event->pos()));
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

bool GameView::isContainsPrivateChar(QString &s)
{
    return NodeCombat::isContainsPrivateChar(s) || Connexion::isContainsPrivateChar(s) ||
            GameScene::isContainsPrivateChar(s);
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
    scene->update(scene->sceneRect());
}

QString GameView::getCreationString()
{
    return scene->getCreationString();
}

void GameView::advance()
{
    scene->advance();
    if(!gameFinished)
    {
        const Gamer *g = scene->isVictory();
        if(g != 0)
        {
            gameFinished = true;
            sendAction(GA_GAME_FINISHED, -1,-1, g->getId());
        }
    }
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameView::onPowerPressed(ACTIONS action)
{
    qDebug()<<action;
    am.actionChanged(action);
}

void GameView::onPowerStarting(ACTIONS a, NodeCombat *n1,NodeCombat *n2)
{
    qDebug()<<"GameView : enter 'onPowerStarting'";

    switch (a)
    {
    case GA_USEPOWER_TELEPORTATION:
    {
        if(n1 != 0 && n2 != 0)
        {
            sendAction(a, n1->getId(), n2->getId(), 0);
        }
        break;
    }
    case GA_USEPOWER_DESTROY:
    {
        if(n1 != 0)
            sendAction(a, n1->getId(), -1, 0);
        break;
    }
    case GA_USEPOWER_ARMORE:
    {
        if(n1 != 0)
            sendAction(a, n1->getId(), -1, 20);
        break;
    }
    case GA_USEPOWER_INVINCIBILITY:
    {
        if(n1 != 0)
            sendAction(a, n1->getId(), -1, 1);
        break;
    }
    default:
        break;
    }
}

void GameView::onPowerFinishing(ACTIONS a, NodeCombat *n1,NodeCombat *n2)
{
    qDebug()<<"GameView : enter 'onPowerFinishing'";

    switch (a)
    {
    case GA_USEPOWER_ARMORE:
    {
        if(n1 != 0)
            sendAction(a, n1->getId(), -1, 0);
        break;
    }
    case GA_USEPOWER_INVINCIBILITY:
    {
        if(n1 != 0)
            sendAction(a, n1->getId(), -1, 0);
        break;
    }
    default:
        break;
    }
}

void GameView::onDoAction(ACTIONS action, NodeCombat *n)
{
    qDebug()<<"GameView : enter 'onDoAction'";

    switch (action)
    {
    case GA_USEPOWER_DESTROY:
        if(n != 0 && (n->getOwner() == 0 || n->getOwner()->getId() != owner->getId()))
        {
            powerUi->usePower(action,n,0);
            am.reset();
        }
        break;
    case GA_USEPOWER_ARMORE:
    case GA_USEPOWER_INVINCIBILITY:
        if(n != 0 && n->getOwner() != 0 && n->getOwner()->getId() == owner->getId())
        {
            powerUi->usePower(action,n,0);
            am.reset();
        }
        break;
    default:
        break;
    }
}

void GameView::onDoAction(ACTIONS action, NodeCombat *n1, NodeCombat *n2)
{
    qDebug()<<"GameView : enter 'onDoAction'";
    qDebug()<<action;

    switch (action)
    {
    case GA_SEND:
        sendSquad(n1, n2);
        am.reset();
        break;
    case GA_USEPOWER_TELEPORTATION:
        if(n1 != 0 && n2 != 0 && n1->getOwner() != 0 &&
                n1->getOwner()->getId() == owner->getId())
        {
            powerUi->usePower(action,n1,n2);
            am.reset();
        }
        break;
    default:
        break;
    }
}

void GameView::applyGamerAction(QString s)
{
    QStringList msgStr = s.split(".");
    if(msgStr.size() != 5) return;
    ACTIONS cmd = (ACTIONS)msgStr.first().toInt();
    msgStr.pop_front();
    int gamerId = msgStr.first().toInt(); //Identifiant du joueur
    msgStr.pop_front();
    NodeCombat *nodeFrom = scene->getNode(msgStr.first().toInt()); //noeud source
    msgStr.pop_front();
    NodeCombat *nodeTo = scene->getNode(msgStr.first().toInt()); //noeud cible
    msgStr.pop_front();
    int param = msgStr.first().toInt(); //Parametre de l'action (nb ressource / pouvoir id)

    switch (cmd)
    {
    case GA_SEND:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_SEND";

        if(nodeFrom != 0 && nodeTo != 0 && nodeFrom->getOwner() != 0 &&
                nodeFrom->getOwner()->getId() == gamerId)
        {
            nodeFrom->sendSquad(param, nodeTo->getId());
        }
        break;
    }
    case GA_USEPOWER_DESTROY:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_USEPOWER_DESTROY";

        if(nodeFrom != 0)
        {
            if(nodeFrom->getOwner() == 0 || nodeFrom->getOwner()->getId() != gamerId)
            {
                nodeFrom->setRessources(0);
            }
        }
        break;
    }
    case GA_USEPOWER_INVINCIBILITY:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_USEPOWER_INVINCIBILITY";

        if(nodeFrom != 0 && nodeFrom->getOwner() != 0 &&
                nodeFrom->getOwner()->getId() == gamerId)
        {
            nodeFrom->setInvicibility(param);
        }
        break;
    }
    case GA_USEPOWER_ARMORE:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_USEPOWER_ARMORE";

        if(nodeFrom != 0 && nodeFrom->getOwner() != 0 &&
                nodeFrom->getOwner()->getId() == gamerId)
        {
            nodeFrom->setArmorLvl(param);
        }
        break;
    }
    case GA_USEPOWER_TELEPORTATION:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_USEPOWER_TELEPORTATION";

        if(nodeFrom != 0 && nodeTo != 0 && nodeFrom->getOwner() != 0 &&
                nodeFrom->getOwner()->getId() == gamerId)
        {
            int ressources = nodeFrom->getRessources()/2;
            nodeFrom->setRessources(nodeFrom->getRessources() - ressources);
            Squad s(*nodeFrom->getOwner());
            s.setNbRessources(ressources);
            nodeTo->incoming(s);
        }
        break;
    }
    case GA_GAME_FINISHED:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_GAME_FINISHED";
        qDebug()<<owner->getId()<<" - "<< param;
        emit gameFinish(param == owner->getId());
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

void GameView::setUpUI()
{
    powerUi = new PowerInterface();
    powerUi->setX(0);
    powerUi->setY(0);
    powerUi->setMana(1000);

    const PowerCountDown &pcd = powerUi->getCountDownManager();
    connect(powerUi,SIGNAL(powerPressed(ACTIONS)),this,SLOT(onPowerPressed(ACTIONS)));
    connect(&pcd,SIGNAL(powerFinishing(ACTIONS,NodeCombat*,NodeCombat*)),this,SLOT(onPowerFinishing(ACTIONS,NodeCombat*,NodeCombat*)));
    connect(&pcd,SIGNAL(powerStarting(ACTIONS,NodeCombat*,NodeCombat*)),this,SLOT(onPowerStarting(ACTIONS,NodeCombat*,NodeCombat*)));
    connect(&am,SIGNAL(doAction(ACTIONS,NodeCombat*)),this,SLOT(onDoAction(ACTIONS,NodeCombat*)));
    connect(&am,SIGNAL(doAction(ACTIONS,NodeCombat*,NodeCombat*)),this,SLOT(onDoAction(ACTIONS,NodeCombat*,NodeCombat*)));

    // Désactivation des scrollbars
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );
    setRenderHint( QPainter::Antialiasing, true );

    setScene(scene);

    scene->addItem(powerUi);
}

void GameView::sendSquad(NodeCombat *from, NodeCombat *to)
{
    if(from != 0 && to != 0)
    {
        sendAction(GA_SEND, from->getId(), to->getId(),
                   (int)(from->getRessources()*(percentToSend/100)));
    }
}


void GameView::sendAction(ACTIONS a, int nodeFromId, int nodeToId, int param)
{
    int ownerId = owner == 0 ? -1 : owner->getId();
    emit gamerAction(QString("%1.%2.%3.%4.%5").arg(a).
                     arg(ownerId).arg(nodeFromId).
                     arg(nodeToId).arg(param));
}
