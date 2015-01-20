#include "gameserver.h"
#include "enumlibrary.h"
#include "server.h"
#include "GameComponent/gameview.h"
#include "gamer.h"
#include "gamerlist.h"
#include <QTcpSocket>
#include <QDir>
#include "mapfile.h"


#define MAP_FILE "./maps"
#define MAP_EXTENSION "*.rtsmap"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameServer::GameServer(int maxConnexion, QObject *parent) : QObject(parent),
    lockConnexion(false), refreshLoopMS(100), port(8000), map(0),
    lstGamer(*new GamerList())
{
    server = new Server(port, maxConnexion, this);

    connect(server, SIGNAL(messageReciveFromClient(QTcpSocket*,QString)),
            this, SLOT(onMessageRecive(QTcpSocket*,QString)));
    connect(server, SIGNAL(serverIsListening()),
            this, SLOT(onServerIsListening()));

    loadMapsFromFile();
}

GameServer::~GameServer()
{
    qDebug()<<"GameServer : destroy";
    if(map != 0) delete map;
    if(&lstGamer != 0) delete &lstGamer;
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
    if(msgStr.size() < 2) return;
    NETWORK_COMMANDE cmd = (NETWORK_COMMANDE)msgStr.first().toInt();
    msgStr.pop_front();
    QString msg = msgStr.first();

    switch (cmd)
    {
    case C_REQUEST_SLOT:
    {
        qDebug()<<"GameServer : in 'onMessageRecive' recive C_REQUEST_SLOT";
        receive_C_REQUEST_SLOT(t, msg);
        break;
    }
    case C_LAUNCH_GAME:
    {
        qDebug()<<"GameServer : in 'onMessageRecive' recive C_LAUNCH_GAME";
        receive_C_LAUNCH_GAME(t, msg);
        break;
    }
    case C_SET_READY:
    {
        qDebug()<<"GameServer : in 'onMessageRecive' recive C_SET_READY";
        receive_C_SET_READY(t, msg);
        break;
    }
    case C_SET_NAME:
    {
        qDebug()<<"GameServer : in 'onMessageRecive' recive C_SET_NAME";
        receive_C_SET_NAME(t, msg);
        break;
    }
    case C_GAMER_ACTION:
    {
        qDebug()<<"GameServer : in 'onMessageRecive' recive C_GAMER_ACTION";
        receive_C_GAMER_ACTION(t, msg);
        break;
    }
    default:
        qCritical()<<"GameServer : unexpected case in 'onMessageRecive'";
        break;
    }

}

void GameServer::onServerIsListening()
{
    emit serverIsListening();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void GameServer::sendToAllGamer(QString s)
{
    foreach(Gamer *g, lstGamer.getLstGamer())
    {
        server->sendMessageToClient(g->getSocket(),s);
    }
}

void GameServer::updateGamerList()
{
    qDebug()<<"GameServer : enter 'updateGamerList'";
    sendToAllGamer(QString("%1#%2%#").
                   arg(C_LOBBY_UPDATE).
                   arg(lstGamer.getLstGamerUpdateString()));
}

void GameServer::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    map->advance();
    sendToAllGamer(QString("%1#%2%#").
                   arg(C_MAP_UPDATE).
                   arg(map->getUpdateString()));
}

void GameServer::loadMapsFromFile()
{
    QDir d(MAP_FILE);
    if(!d.exists())
    {
        d.mkpath(".");
        return;
    }

    QStringList filter;
    filter << MAP_EXTENSION;
    lstMapName = d.entryList(filter);
}

QString GameServer::checkReadyToLaunchGame()
{
    return "";
}

/*----------------------------------------------------*/
/*RECEPTION*/
/*----------------------------------------------------*/

void GameServer::receive_C_REQUEST_SLOT(QTcpSocket *t, QString msg)
{
    if(!lockConnexion)
    {
        qDebug()<<"GameServer : accept client";
        Gamer *g = new Gamer();
        g->setSocket(t);
        lstGamer.addGamer(g);
        server->sendMessageToClient(t,QString("%1#%2").arg(C_GAMER_INFO).
                                    arg(g->getId()));
        foreach (QString s, lstMapName)
        {
            server->sendMessageToClient(t,QString("%1#%2").arg(C_ADD_MAP).
                                        arg(s));
        }
        updateGamerList();
    }
    else
    {
        qDebug()<<"GameServer : refuse client";
        server->sendMessageToClient(t,QString("%1#").arg(C_REFUSE));
    }
}

void GameServer::receive_C_LAUNCH_GAME(QTcpSocket *t, QString msg)
{
    QString invalid = checkReadyToLaunchGame();
    if(!invalid.isEmpty())
    {
        server->sendMessageToClient(t,QString("%1#%2").arg(C_NOT_READY).arg(invalid));
        return;
    }

    lockConnexion = true;

    MapFile m;
    qDebug()<<QString("%1/%2").arg(MAP_FILE).arg(msg);
    m.loadFromFile(QString("%1/%2").arg(MAP_FILE).arg(msg));
    if(!m.isValide())
    {
        qCritical()<<"GameServer : in 'receive_C_LAUNCH_GAME' map is not valid ";
        return;
    }

    map = new GameView(m.getCreationString(), lstGamer);
    map->updateFromString(m.getUpdateString());
    sendToAllGamer(QString("%1#%2").arg(C_LAUNCH_GAME).arg(m.getCreationString()));
    sendToAllGamer(QString("%1#%2").arg(C_MAP_UPDATE).arg(m.getUpdateString()));
    this->startTimer(refreshLoopMS);
}

void GameServer::receive_C_SET_READY(QTcpSocket *t, QString msg)
{
    Gamer *g = lstGamer.getGamer(t);
    bool b = msg.toInt();
    g->setReady(b);
    updateGamerList();
}

void GameServer::receive_C_SET_NAME(QTcpSocket *t, QString msg)
{
    Gamer *g = lstGamer.getGamer(t);
    g->setName(msg);
    g->setReady(false); //Afin de nw pas lancer le jeu sans que son nom lui plaise
    updateGamerList();
}

void GameServer::receive_C_GAMER_ACTION(QTcpSocket *t, QString msg)
{
    map->applyGamerAction(msg);
}
