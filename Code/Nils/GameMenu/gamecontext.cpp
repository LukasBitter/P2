#include "gamecontext.h"
#include "GameConnexion/gameclient.h"
#include "GameConnexion/gameserver.h"
#include "GameComponent/gameview.h"
#include <QGridLayout>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameContext::GameContext(GameClient *c, GameServer *s, QWidget *parent):
    QWidget(parent), c(0),s(0)
{
    //AJOUT CLIENT
    if(c != 0)
    {
        QGridLayout *l = new QGridLayout(this);
        l->addWidget(c->getMap(),0,0);
        this->setLayout(l);
        this->c = c;
    }
    else
    {
        qCritical()<<"GameContext : unexpected case in 'GameContext'";
    }

    //AJOUT SERVEUR
    if(s != 0)
    {
        qDebug()<<"GameContext : created with server";
        this->s = s;
    }
}


GameContext::~GameContext()
{
    qDebug()<<"GameContext : destroy";
    if(c != 0) delete c;
    if(s != 0) delete s;
}
