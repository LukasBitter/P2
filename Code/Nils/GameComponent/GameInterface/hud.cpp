#include "hud.h"
#include "enumlibrary.h"

Hud::Hud(GamerList &gl, GameScene &scene, QGraphicsItem *parent) : QGraphicsWidget(parent)
{
    ressourceBar = new ProgressBar(120,0,680,10);
    ressourceBar->setFillMode(true);

    powerUi = new PowerInterface(am);
    powerUi->setX(0);
    powerUi->setY(0);
    powerUi->setMana(P_INITIAL_MANA);
}
