#include "gamecontext.h"
#include "GameConnexion/gameclient.h"
#include "GameConnexion/gameserver.h"
#include "GameConnexion/parser.h"
#include "GameComponent/map.h"
#include "GameComponent/gamerlist.h"
#include <QGridLayout>

/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameContext::GameContext(GameClient *c, GameServer *s, QWidget *parent):
    QWidget(parent), c(0),s(0)
{
    if(c != 0)
    {
         QGridLayout *l = new QGridLayout(this);
         l->addWidget(c->getMap(),0,0);
         this->setLayout(l);
         this->c = c;
    }
    if(s != 0)
    {
        this->s = s;
    }
}


GameContext::~GameContext()
{
    delete c;
    delete s;
}
