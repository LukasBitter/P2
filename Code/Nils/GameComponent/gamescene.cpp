#include "gamescene.h"
#include <QGraphicsSceneDragDropEvent>

GameScene::GameScene(QObject * parent) : QGraphicsScene(parent)
{
}

void GameScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    //Pas d'appel au parent sinon sa marche pas !
}
