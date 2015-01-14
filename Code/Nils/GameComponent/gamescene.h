#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

/**
 * @class GameScene
 * @brief Scene de jeu
 */
class GameScene : public QGraphicsScene
{
public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    GameScene(QObject * parent = 0);

    /*SURCHARGE*/
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // GAMESCENE_H
