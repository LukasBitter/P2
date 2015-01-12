#include "gamescene.h"
#include <QGraphicsSceneDragDropEvent>

GameScene::GameScene(QObject * parent) : QGraphicsScene(parent)
{
}

GameScene::~GameScene()
{

}

void GameScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    //Pas d'appel au parent sinon sa marche pas !
}
