#include "gamescene.h"
#include <QGraphicsSceneDragDropEvent>

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameScene::GameScene(QObject * parent) : QGraphicsScene(parent)
{
}

/*----------------------------------------------------*/
/*SURCHARGE*/
/*----------------------------------------------------*/

void GameScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    //Pas d'appel au parent sinon sa marche pas !
}
