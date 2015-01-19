#include "gameserver.h"
#include "enumlibrary.h"
#include "server.h"
#include "GameComponent/map.h"
#include "GameComponent/gamer.h"
#include "gamerlist.h"
#include <QTcpSocket>


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameServer::GameServer(int maxConnexion, QObject *parent) : QObject(parent),
    lockConnexion(false), refreshLoopMS(100), port(8000), map(0)
{
    server = new Server(port, maxConnexion, this);

    connect(server, SIGNAL(messageReciveFromClient(QTcpSocket*,QString)),
            this, SLOT(onMessageRecive(QTcpSocket*,QString)));
}

GameServer::~GameServer()
{
    if(map != 0) delete map;
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameServer::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    qWarning()<<"GameServer : enter 'onErrorOccured'"<<socketError;
    emit errorOccured(socketError);
}

void GameServer::onMessageRecive(QTcpSocket *t, QString s)
{
    QStringList msgStr = s.split("#");
    if(msgStr.size() < 3) return;
    NETWORK_COMMANDE cmd = (NETWORK_COMMANDE)msgStr.first().toInt();
    msgStr.pop_front();
    QString msg1 = msgStr.first();
    msgStr.pop_front();
    QString msg2 = msgStr.first();

    switch (cmd)
    {
    case C_REQUEST_SLOT:
    {
        qDebug()<<"GameServer : in 'onMessageRecive' recive C_REQUEST_SLOT";
        if(!lockConnexion)
        {
            qDebug()<<"GameServer : accept client";
            Gamer *g = new Gamer();
            g->setSocket(t);
            server->sendMessageToClient(t,QString("%1#%2#").arg(C_GAMER_INFO).
                                        arg(g->getId()));
            updateGamerList();
        }
        else
        {
            qDebug()<<"GameServer : refuse client";
            server->sendMessageToClient(t,QString("%1##").arg(C_REFUSE));
        }
        break;
    }
    case C_LAUNCH_GAME:
    {
        qDebug()<<"GameServer : in 'onMessageRecive' recive C_LAUNCH_GAME";
        lockConnexion = true;
        map = new Map(msg1);
        map->updateFromString(msg2);
        sendToAllGamer(QString("%1#%2#%3").arg(C_LAUNCH_GAME).arg(msg1).arg(msg2));
        this->startTimer(refreshLoopMS);
        break;
    }
    case C_SET_READY:
    {
        qDebug()<<"GameServer : in 'onMessageRecive' recive C_SET_READY";
        Gamer *g = GamerList::getGamer(t);
        bool b = msg1.toInt();
        g->setReady(b);
        updateGamerList();
        break;
    }
    default:
        qCritical()<<"GameServer : unexpected case in 'onMessageRecive'";
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
    qDebug()<<"GameServer : enter 'updateGamerList'";
    sendToAllGamer(QString("%1#%2%#").
                   arg(C_LOBBY_UPDATE).
                   arg(GamerList::getLstGamerUpdateString()));
}

void GameServer::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    map->advance();
    sendToAllGamer(QString("%1#%2%#").
                   arg(C_MAP_UPDATE).
                   arg(map->getUpdateString()));
}
