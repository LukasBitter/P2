#include "gamescene.h"
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameScene::GameScene(QObject * parent) : QGraphicsScene(parent)
{
    setSceneRect(-400, -300, 400, 300);
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void GameScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    //Pas d'appel au parent sinon sa marche pas !
}
