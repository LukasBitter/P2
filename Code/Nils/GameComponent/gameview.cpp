#include "gameview.h"
#include "node.h"
#include "connexion.h"
#include "gamer.h"
#include "gamerlist.h"
#include "gamescene.h"
#include "GameInterface/powerinterface.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameView::GameView(GamerList &gl, const Gamer *g, QWidget *parent) :
    QGraphicsView(parent), owner(g), scene(0), ui(0),
    percentToSend(100)
{
    scene = new GameScene(gl, g, this);
    setUpUI();
}

GameView::GameView(QString create, GamerList &gl, const Gamer *g, QWidget *parent):
    QGraphicsView(parent), owner(g), scene(0), ui(0),
    percentToSend(100)
{
    scene = new GameScene(create, gl, g, this);
    setUpUI();
}

GameView::~GameView()
{
    delete scene;
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void GameView::keyPressEvent(QKeyEvent *e)
{
    QGraphicsView::keyPressEvent(e);
    if(e->key() == Qt::Key_Space)
    {
        sendSquad(lastSelection, currentSelection);
    }
}

void GameView::mousePressEvent(QMouseEvent *e)
{
    if(e->button()== Qt::RightButton)
    {
        //Ordre déplacement via clic droit
        Node *nodeTo = dynamic_cast <Node*>(itemAt(e->pos()));
        sendSquad(currentSelection, nodeTo);
    }
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

void GameView::setPercentToSend(int percent)
{
    if(percent>=0 && percent<=100) percentToSend = percent;
}

/*----------------------------------------------------*/
/*MISE A JOUR*/
/*----------------------------------------------------*/

QString GameView::getUpdateString()
{
    return scene->getUpdateString();
}

void GameView::updateFromString(QString s)
{
    scene->updateFromString(s);
}

QString GameView::getCreationString()
{
    return scene->getCreationString();
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameView::advance()
{
    scene->advance();
}

void GameView::applyGamerAction(QString s)
{
    QStringList msgStr = s.split(".");
    if(msgStr.size() != 5) return;
    GAMER_ACTION cmd = (GAMER_ACTION)msgStr.first().toInt();
    msgStr.pop_front();
    int gamerId = msgStr.first().toInt(); //Identifiant du joueur
    msgStr.pop_front();
    int nodeFromId = msgStr.first().toInt(); //Identifiant du noeud source
    msgStr.pop_front();
    int nodeToId = msgStr.first().toInt(); //Identifiant du noeud cible
    msgStr.pop_front();
    int param = msgStr.first().toInt(); //Parametre de l'action (nb ressource / pouvoir id)

    switch (cmd)
    {
    case GA_SEND:
    {
        qDebug()<<"Map : in 'applyGamerAction' recive GA_SEND";

        Node *nodeFrom = scene->getNode(nodeFromId);
        Node *nodeTo = scene->getNode(nodeToId);
        if(nodeFrom != 0 && nodeTo != 0 &&
                nodeFrom->getOwner()->getId() == gamerId)
        {
            nodeFrom->sendSquad(param, *nodeTo);
        }
        break;
    }
    case GA_USEPOWER:
    {
        qDebug()<<"Map : in 'applyGamerAction' recive GA_USEPOWER";
        break;
    }
    default:
        qCritical()<<"Map : unexpected case in 'applyGamerAction'";
        break;
    }

}

void GameView::selectionChange()
{
    QList<QGraphicsItem *> lst = scene->selectedItems();
    if(!lst.isEmpty())
    {
        lastSelection = currentSelection;
        currentSelection = dynamic_cast <Node*>(lst.first());
    }
    else
    {
        lastSelection = 0;
        currentSelection = 0;
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
    emit gamerAction(QString("%1.%2.%3.%4.%5").arg(GA_USEPOWER).
                     arg(owner->getId()).arg(nodeFromId).
                     arg(nodeToId).arg(p));
}

void GameView::setUpUI()
{
    setScene(scene);
    connect(scene,SIGNAL(selectionChanged()),this,SLOT(selectionChange()));

    // Désactivation des scrollbars
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );
    setRenderHint( QPainter::Antialiasing, true );

    ui = new PowerInterface();
    ui->setX(0);
    ui->setY(0);
    ui->setMana(1000);
    scene->addItem(ui);
}
