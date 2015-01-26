#include "gameview.h"
#include "GameComponent/Logic/nodecombat.h"
#include "GameComponent/Logic/nodeconnectable.h"
#include "GameComponent/Logic/nodemana.h"
#include "GameComponent/Logic/connexion.h"
#include "GameComponent/Logic/gamescene.h"
#include "GameComponent/Logic/squad.h"
#include "gamer.h"
#include "gamerlist.h"
#include "powerinterface.h"


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

    Node *n = dynamic_cast <Node*>(itemAt(e->pos()));

    am.selectionChanged(n);

    QGraphicsView::mousePressEvent(e);
}

void GameView::dropEvent(QDropEvent *event)
{
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

bool GameView::isContainsPrivateChar(QString &s)
{
    return NodeCombat::isContainsPrivateChar(s) || Connexion::isContainsPrivateChar(s) ||
            GameScene::isContainsPrivateChar(s) || NodeMana::isContainsPrivateChar(s);
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

void GameView::onPowerStarting(ACTIONS a, Node *n1,Node *n2)
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

void GameView::onPowerFinishing(ACTIONS a, Node *n1,Node *n2)
{
    Q_UNUSED(n2);
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

void GameView::onDoAction(ACTIONS action, Node *n)
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

void GameView::onDoAction(ACTIONS action, Node *n1, Node *n2)
{
    qDebug()<<"GameView : enter 'onDoAction'";

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

/**
 * @brief GameView::applyGamerAction Réception des action des joueurs
 * @param s Chaine d'action
 *
 * Cette methode est utilisée par la GameView coté serveur afin d'executer
 * les actions des clients
 */
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
        receive_GA_SEND(gamerId, nodeFrom, nodeTo, param);
        break;
    }
    case GA_USEPOWER_DESTROY:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_USEPOWER_DESTROY";
        receive_GA_USEPOWER_DESTROY(gamerId, nodeFrom, nodeTo, param);
        break;
    }
    case GA_USEPOWER_INVINCIBILITY:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_USEPOWER_INVINCIBILITY";
        receive_GA_USEPOWER_INVINCIBILITY(gamerId, nodeFrom, nodeTo, param);
        break;
    }
    case GA_USEPOWER_ARMORE:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_USEPOWER_ARMORE";
        receive_GA_USEPOWER_ARMORE(gamerId, nodeFrom, nodeTo, param);
        break;
    }
    case GA_USEPOWER_TELEPORTATION:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_USEPOWER_TELEPORTATION";
        receive_GA_USEPOWER_TELEPORTATION(gamerId, nodeFrom, nodeTo, param);
        break;
    }
    case GA_GAME_FINISHED:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_GAME_FINISHED";
        receive_GA_GAME_FINISHED(gamerId, nodeFrom, nodeTo, param);
        break;
    }
    case GA_MANA_BURN:
    {
        qDebug()<<"GameView : in 'applyGamerAction' recive GA_MANA_BURN";
        receive_GA_MANA_BURN(gamerId, nodeFrom, nodeTo, param);
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
    powerUi = new PowerInterface(am);
    powerUi->setX(0);
    powerUi->setY(0);
    powerUi->setMana(P_INITIAL_MANA);

    const PowerCountDown &pcd = powerUi->getCountDownManager();
    connect(&pcd,SIGNAL(powerFinishing(ACTIONS,Node*,Node*)),this,SLOT(onPowerFinishing(ACTIONS,Node*,Node*)));
    connect(&pcd,SIGNAL(powerStarting(ACTIONS,Node*,Node*)),this,SLOT(onPowerStarting(ACTIONS,Node*,Node*)));
    connect(&am,SIGNAL(doAction(ACTIONS,Node*)),this,SLOT(onDoAction(ACTIONS,Node*)));
    connect(&am,SIGNAL(doAction(ACTIONS,Node*,Node*)),this,SLOT(onDoAction(ACTIONS,Node*,Node*)));

    // Désactivation des scrollbars
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );
    setRenderHint( QPainter::Antialiasing, true );

    setScene(scene);

    scene->addItem(powerUi);
}

/*----------------------------------------------------*/
/*ENVOIS*/
/*----------------------------------------------------*/

/**
 * @brief GameView::sendSquad Action utilisateur demandant l'envoi de squad
 * @param from Noeud source
 * @param to Noeud de destination
 */
void GameView::sendSquad(Node *from, Node *to)
{
    NodeCombat *nodeFromTmp = dynamic_cast <NodeCombat*>(from);
    int nbRessource = (int)(nodeFromTmp->getRessources()*(percentToSend/100));
    if(nodeFromTmp != 0)
    {
        NodeConnectable *nodeToComba = dynamic_cast <NodeConnectable*>(to);
        NodeMana *nodeToMana = dynamic_cast <NodeMana*>(to);
        if(nodeToComba != 0)
        {
            sendAction(GA_SEND, nodeFromTmp->getId(), nodeToComba->getId(),nbRessource);
        }
        else if(nodeToMana != 0)
        {
            powerUi->addMana(nbRessource);
            sendAction(GA_MANA_BURN, nodeFromTmp->getId(), 0,nbRessource);
        }
    }
}

/**
 * @brief GameView::sendAction Envoit une action utilisateur de la GameView client
 * a la GameView serveur
 * @param a Action voulu
 * @param from Noeud source
 * @param to Noeud de destination
 * @param param Parametre optionnel
 */
void GameView::sendAction(ACTIONS a, int nodeFromId, int nodeToId, int param)
{
    int ownerId = owner == 0 ? -1 : owner->getId();
    emit gamerAction(QString("%1.%2.%3.%4.%5").arg(a).
                     arg(ownerId).arg(nodeFromId).
                     arg(nodeToId).arg(param));
}

/*----------------------------------------------------*/
/*RECEPTION*/
/*----------------------------------------------------*/


void GameView::receive_GA_SEND(int gamerId, Node *nodeFrom, Node *nodeTo, int param)
{

    if(nodeFrom != 0 && nodeTo != 0 && nodeFrom->getOwner() != 0 &&
            nodeFrom->getOwner()->getId() == gamerId)
    {
        nodeFrom->sendSquad(param, nodeTo->getId());
    }
}

void GameView::receive_GA_USEPOWER_DESTROY(int gamerId, Node *nodeFrom, Node *nodeTo, int param)
{
    Q_UNUSED(nodeTo);
    Q_UNUSED(param);

    NodeCombat *nodeFromTmp = dynamic_cast <NodeCombat*>(nodeFrom);
    if(nodeFromTmp != 0)
    {
        if(nodeFromTmp->getOwner() == 0 || nodeFromTmp->getOwner()->getId() != gamerId)
        {
            nodeFromTmp->setRessources(0);
        }
    }
}

void GameView::receive_GA_USEPOWER_INVINCIBILITY(int gamerId, Node *nodeFrom, Node *nodeTo, int param)
{
    Q_UNUSED(nodeTo);

    NodeCombat *nodeFromTmp = dynamic_cast <NodeCombat*>(nodeFrom);
    if(nodeFromTmp != 0 && nodeFromTmp->getOwner() != 0 &&
            nodeFromTmp->getOwner()->getId() == gamerId)
    {
        nodeFromTmp->setInvicibility(param);
    }
}

void GameView::receive_GA_USEPOWER_ARMORE(int gamerId, Node *nodeFrom, Node *nodeTo, int param)
{
    Q_UNUSED(nodeTo);

    NodeCombat *nodeFromTmp = dynamic_cast <NodeCombat*>(nodeFrom);
    if(nodeFromTmp != 0 && nodeFromTmp->getOwner() != 0 &&
            nodeFromTmp->getOwner()->getId() == gamerId)
    {
        nodeFromTmp->setArmorLvl(param);
    }
}

void GameView::receive_GA_USEPOWER_TELEPORTATION(int gamerId, Node *nodeFrom, Node *nodeTo, int param)
{
    Q_UNUSED(param);

    NodeCombat *nodeFromTmp = dynamic_cast <NodeCombat*>(nodeFrom);
    if(nodeFromTmp != 0 && nodeTo != 0 && nodeFromTmp->getOwner() != 0 &&
            nodeFromTmp->getOwner()->getId() == gamerId)
    {
        int ressources = nodeFromTmp->getRessources()/2;
        nodeFromTmp->setRessources(nodeFromTmp->getRessources() - ressources);
        Squad s(*nodeFromTmp->getOwner());
        s.setNbRessources(ressources);
        nodeTo->incoming(s);
    }
}

void GameView::receive_GA_GAME_FINISHED(int gamerId, Node *nodeFrom, Node *nodeTo, int param)
{
    Q_UNUSED(gamerId);
    Q_UNUSED(nodeTo);
    Q_UNUSED(nodeFrom);

    emit gameFinish(param == owner->getId());
}

void GameView::receive_GA_MANA_BURN(int gamerId, Node *nodeFrom, Node *nodeTo, int param)
{
    Q_UNUSED(nodeFrom);
    Q_UNUSED(nodeTo);

    NodeCombat *nodeFromTmp = dynamic_cast <NodeCombat*>(nodeFrom);
    if(nodeFromTmp != 0 && nodeFromTmp->getOwner() != 0 &&
            nodeFromTmp->getOwner()->getId() == gamerId)
    {
        nodeFromTmp->setRessources(nodeFromTmp->getRessources() - param);
    }
}
