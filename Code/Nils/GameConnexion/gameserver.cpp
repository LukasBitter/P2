#include "gameserver.h"
#include "enumLib.h"
#include "server.h"
#include "GameComponent/map.h"
#include "GameComponent/gamer.h"
#include "GameComponent/gamerlist.h"
#include <QTcpSocket>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameServer::GameServer(int maxConnexion, QObject *parent) : QObject(parent),
    lockConnexion(false), refreshLoopMS(100), port(8000)
{
    server = new Server(port, maxConnexion, this);

    connect(server, SIGNAL(messageReciveFromClient(QTcpSocket*,QString)),
            this, SLOT(onMessageRecive(QTcpSocket*,QString)));
}

GameServer::~GameServer()
{
    if(map != 0 ) delete map;
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameServer::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    emit errorOccured(socketError);
}

void GameServer::onMessageRecive(QTcpSocket *t, QString s)
{
    QStringList msgStr = s.split("#");
    if(msgStr.size() < 3) return;
    INTERNALCOMMANDE cmd = (INTERNALCOMMANDE)msgStr.first().toInt();
    msgStr.pop_front();
    QString msg1 = msgStr.first();
    msgStr.pop_front();
    QString msg2 = msgStr.first();

    switch (cmd)
    {
    case C_REQUESTSLOT:
    {
        if(!lockConnexion)
        {
            Gamer *g = new Gamer();
            g->setSocket(t);
            server->sendMessageToClient(t,QString("%1#%2#").arg(C_GAMERINFO).
                                        arg(g->getId()));
        }
        else
        {
            server->sendMessageToClient(t,QString("%1##").arg(C_REFUSE));
        }
        break;
    }
    case C_LAUNCHGAME:
    {
        map = new Map(msg1);
        map->updateFromString(msg2);
        sendToAllGamer(QString("%1#%2#%3").arg(C_LAUNCHGAME).arg(msg1).arg(msg2));
        this->startTimer(refreshLoopMS);
        break;
    }
    case C_SETREADY:
    {
        Gamer *g = GamerList::getGamer(t);
        bool b = msg1.toInt();
        g->setReady(b);
        updateGamerList();
        break;
    }
    default:
        break;
    }

}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void GameServer::sendToAllGamer(QString s)
{
    foreach(Gamer *g, GamerList::getLstGamer())
    {
        server->sendMessageToClient(g->getSocket(),s);
    }
}

void GameServer::updateGamerList()
{
    sendToAllGamer(QString("%1#%2%#").
                   arg(C_LOBBYUPDATE).
                   arg(GamerList::getLstGamerUpdateString()));
}

void GameServer::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    map->advance();
    sendToAllGamer(QString("%1#%2%#").
                   arg(C_MAPUPDATE).
                   arg(map->getUpdateString()));
}
