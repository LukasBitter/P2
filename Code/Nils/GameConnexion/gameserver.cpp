#include "gameserver.h"
#include "server.h"
#include "GameComponent/gameview.h"
#include "gamer.h"
#include <QTcpSocket>
#include <QDir>
#include "mapfile.h"


#define MAP_FILE "./maps"
#define MAP_EXTENSION "*.rtsmap"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameServer::GameServer(int maxConnexion, QObject *parent) : QObject(parent),
    lockConnexion(false), refreshLoopMS(100), port(8000), map(0)
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
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameServer::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    qWarning()<<"GameServer : enter 'onErrorOccured'"<<socketError;
    emit errorOccured(socketError);
}

void GameServer::onMessageRecive(QTcpSocket *t, QString &s)
{
    QStringList msgStr = s.split("#");
    if(msgStr.size() != 2 || t == 0) return;
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
    case C_UPDATE_CURRENT_GAMER:
    {
        qDebug()<<"GameServer : in 'onMessageRecive' recive C_UPDATE_CURRENT_GAMER";
        receive_C_UPDATE_CURRENT_GAMER(t, msg);
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
        server->sendMessageToClient(*g->getSocket(),s);
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

NETWORK_INFORMATION GameServer::checkReadyToLaunchGame()
{
    QList<Gamer *> lst = lstGamer.getLstGamer().values();
    if(lst.size() > 1)
    {
        for(int i = 0; i < lst.size()-1; ++i)
        {
            for(int j = i+1; j < lst.size(); ++j)
            {
                if(lst.at(i)->getColor() == lst.at(j)->getColor())
                    return I_SAME_COLOR;
                if(lst.at(i)->getSlotNumber() == lst.at(j)->getSlotNumber())
                    return I_SAME_SLOT;
            }
        }
    }
    return I_OK;
}

/*----------------------------------------------------*/
/*RECEPTION*/
/*----------------------------------------------------*/

void GameServer::receive_C_REQUEST_SLOT(QTcpSocket *t, QString msg)
{
    QString message;
    if(!lockConnexion)
    {
        qDebug()<<"GameServer : accept client";
        Gamer *g = new Gamer();
        g->setSocket(t);
        lstGamer.addGamer(g);
        message = QString("%1#%2").arg(C_GAMER_INFO).arg(g->getId());
        server->sendMessageToClient(*t,message);
        foreach (QString s, lstMapName)
        {
            message = QString("%1#%2").arg(C_ADD_MAP).arg(s);
            server->sendMessageToClient(*t,message);
        }
        updateGamerList();
    }
    else
    {
        qDebug()<<"GameServer : refuse client";
        message = QString("%1#").arg(C_INFORMATION).arg(I_GAME_STARTED);
        server->sendMessageToClient(*t,message);
    }
}

void GameServer::receive_C_LAUNCH_GAME(QTcpSocket *t, QString msg)
{
    NETWORK_INFORMATION invalid = checkReadyToLaunchGame();
    if(invalid != I_OK)
    {
        QString message = QString("%1#%2").arg(C_INFORMATION).
                arg(invalid);
        server->sendMessageToClient(*t,message);
        return;
    }

    lockConnexion = true;

    MapFile m;
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
}

void GameServer::receive_C_UPDATE_CURRENT_GAMER(QTcpSocket *t, QString msg)
{
    Gamer *g = lstGamer.getGamer(t);
    g->updateFromString(msg);
    updateGamerList();
}

void GameServer::receive_C_GAMER_ACTION(QTcpSocket *t, QString msg)
{
    map->applyGamerAction(msg);
}
