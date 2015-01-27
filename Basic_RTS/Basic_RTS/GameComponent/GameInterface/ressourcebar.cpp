#include "ressourcebar.h"
#include "gamer.h"
#include "gamerlist.h"
#include "enumlibrary.h"
#include "GameComponent/Logic/gamescene.h"

RessourceBar::RessourceBar(int x, int y, int w, int h, GamerList &gl,
                           GameScene &scene, QGraphicsItem *parent):
    ProgressBar(x,y,w,h,parent), scene(scene), gl(gl)
{
    totalRessourcesOfMap = scene.getTotalRessources();
    startTimer(RESSOURCES_BAR_TIC);
    setVertical(false);
}

void RessourceBar::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    foreach (Gamer *g, gl.getLstGamer())
    {
        this->insertPlage(g->getId(),scene.getTotalRessources(*g),
                          totalRessourcesOfMap,g->getColor());
    }
}

