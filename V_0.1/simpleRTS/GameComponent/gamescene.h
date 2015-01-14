#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

/**
 * @brief Scene de jeu
 */
class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject * parent = 0);
    ~GameScene();

    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // GAMESCENE_H
