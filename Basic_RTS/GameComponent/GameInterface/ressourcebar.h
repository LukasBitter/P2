#ifndef RESSOURCEBAR_H
#define RESSOURCEBAR_H

#include "progressbar.h"
#include "global.h"

class GamerList;
class GameScene;

namespace GameInterface
{
    class RessourceBar;
}

class RessourceBar : public QObject, public ProgressBar
{
    Q_OBJECT

public:
    RessourceBar(int x, int y, int w, int h, GamerList &gl, GameScene &scene, QGraphicsItem* parent = 0);
    void timerEvent(QTimerEvent *event);

private:
    GamerList &gl;
    GameScene &scene;
    int totalRessourcesOfMap;
};

#endif // RESSOURCEBAR_H
