#include "gameclient.h"
#include "enumlibrary.h"
#include "client.h"
#include "GameComponent/gameview.h"
#include "gamerlist.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameClient::GameClient(QString host, QObject *parent) : QObject(parent),
    port(8000), gamerId(-1), map(0), client(0), lstGamer(*new GamerList())
{
    client = new Client(port, host, this);

    connect(client, SIGNAL(messageReciveFromServeur(QString)),
            this, SLOT(onMessageRecive(QString)));
    connect(client, SIGNAL(connected()),
            this, SLOT(onClientConnected()));
}

GameClient::~GameClient()
{
    qDebug()<<"GameClient : destroy";
    if(map != 0) delete map;
    if(&lstGamer != 0) delete &lstGamer;
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

GameView *GameClient::getMap() const
{
    return map;
}

const QHash<int, Gamer *> &GameClient::getListGamer()
{
    return lstGamer.getLstGamer();
}

const Gamer *GameClient::getCurrentGamer() const
{
    return lstGamer.getGamer(gamerId);
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameClient::launchGame(QString mapName)
{
    qDebug()<<"GameClient : enter 'launchGame'";
    client->sendMessageToServer(QString("%1#%2#%3").arg(C_LAUNCH_GAME).
                                arg(mapName));
}

void GameClient::setName(QString &name)
{
    qDebug()<<"GameClient : enter 'setName'";
    client->sendMessageToServer(QString("%1#%2#").arg(C_SET_NAME).
                                arg(name));
}

void GameClient::setReady(bool r)
{
    qDebug()<<"GameClient : enter 'setName'";
    client->sendMessageToServer(QString("%1#%2#").arg(C_SET_READY).
                                arg(r));
}

void GameClient::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    qWarning()<<"GameClient : enter 'onErrorOccured'"<<socketError;
    emit errorOccured(socketError);
}

void GameClient::onMessageRecive(QString s)
{
    QStringList msgStr = s.split("#");
    if(msgStr.size() < 2) return;
    NETWORK_COMMANDE cmd = (NETWORK_COMMANDE)msgStr.first().toInt();
    msgStr.pop_front();
    QString msg = msgStr.first();

    switch (cmd)
    {
    case C_GAMER_INFO:
    {
        qDebug()<<"GameClient : in 'onMessageRecive' recive C_GAMER_INFO";
        receive_C_GAMER_INFO(msg);
        break;
    }
    case C_REFUSE:
    {
        qDebug()<<"GameClient : in 'onMessageRecive' recive C_REFUSE";
        receive_C_REFUSE(msg);
        break;
    }
    case C_LAUNCH_GAME:
    {
        qDebug()<<"GameClient : in 'onMessageRecive' recive C_LAUNCH_GAME";
        receive_C_LAUNCH_GAME(msg);
        break;
    }
    case C_LOBBY_UPDATE:
    {
        qDebug()<<"GameClient : in 'onMessageRecive' recive C_LOBBY_UPDATE";
        receive_C_LOBBY_UPDATE(msg);
        break;
    }
    case C_MAP_UPDATE:
    {
        receive_C_MAP_UPDATE(msg);
        break;
    }
    case C_ADD_MAP:
    {
        qDebug()<<"GameClient : in 'onMessageRecive' recive C_ADD_MAP";
        receive_C_ADD_MAP(msg);
        break;
    }
    default:
        qCritical()<<"GameClient : unexpected case in 'onMessageRecive'";
        break;
    }
}

void GameClient::onClientConnected()
{
    qDebug()<<"GameClient : enter 'onClientConnected'";
    client->sendMessageToServer(QString("%1##").arg(C_REQUEST_SLOT));
    emit connexionOk();
}

void GameClient::sendClientAction(QString actionString)
{
    qDebug()<<"GameClient : enter 'sendClientAction'";
    client->sendMessageToServer(QString("%1#%2#").arg(C_GAMER_ACTION).
                                arg(actionString));
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/


/*----------------------------------------------------*/
/*RECEPTION*/
/*----------------------------------------------------*/

void GameClient::receive_C_GAMER_INFO(QString msg)
{
    gamerId = msg.toInt();
}

void GameClient::receive_C_REFUSE(QString msg)
{
    emit errorOccured(QAbstractSocket::ConnectionRefusedError);
}

void GameClient::receive_C_LAUNCH_GAME(QString msg)
{
    if(gamerId != -1)
    {
        map = new GameView(msg, lstGamer, lstGamer.getGamer(gamerId));
        connect(map, SIGNAL(gamerAction(QString)),
                this, SLOT(sendClientAction(QString)));
        emit switchToGame();
    }
    else
    {
        qCritical()<<"GameClient : unexpected case in 'onMessageRecive' recive C_LAUNCH_GAME";
    }
}

void GameClient::receive_C_LOBBY_UPDATE(QString msg)
{
    lstGamer.updateLstGamerFromString(msg);
    emit updateLobby();
}

void GameClient::receive_C_MAP_UPDATE(QString msg)
{
    if(map != 0)map->updateFromString(msg);
}

void GameClient::receive_C_ADD_MAP(QString msg)
{
    emit addMapName(msg);
}
