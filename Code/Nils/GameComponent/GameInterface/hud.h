#ifndef HUD_H
#define HUD_H

#include "global.h"

class PowerInterface;
class ProgressBar;
class GamerList;
class GameScene;

class Hud : public QGraphicsWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    Hud(GamerList &gl, GameScene &scene, QGraphicsItem *parent = 0);

    /*ASSESSEUR / MUTATEUR*/
    PowerInterface *getPowerUi();
    PowerInterface *getRessourceBar();

private:
    /*INTERFACE*/
    PowerInterface *powerUi; ///< Palette de gestion des pouvoirs
    ProgressBar *ressourceBar; ///< Barre d'indication des ressources

    GamerList &gl;
    GameScene &scene;
};

#endif // HUD_H
