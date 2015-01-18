#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <QWidget>

class GameClient;
class GameServer;
class Map;

class GameContext : public QWidget
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    GameContext(GameClient *c, GameServer *s=0, QWidget *parent=0);
    ~GameContext();
private:
    GameClient *c;
    GameServer *s;
};


#endif // GAMECONTEXT_H
