#include "gameclient.h"
#include "gameserver.h"
#include "client.h"
#include "gamer.h"
#include "GameComponent/GameInterface/gameview.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameClient::GameClient(QString host, QObject *parent) : QObject(parent),
    port(PORT), gamerId(-1), map(0), client(0)
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

    client->sendMessageToServer(QString("%1#%2").arg(C_LAUNCH_GAME).arg(mapName));
}

bool GameClient::setName(QString name)
{
    qDebug()<<"GameClient : enter 'setName'";

    if(GameView::isContainsPrivateChar(name) ||
            GameServer::isContainsPrivateChar(name)) return false;

    Gamer *g = lstGamer.getGamer(gamerId);
    g->setName(name);
    updateCurrentGamer();

    return true;
}

void GameClient::setReady(bool r)
{
    qDebug()<<"GameClient : enter 'setReady'";

    Gamer *g = lstGamer.getGamer(gamerId);
    g->setReady(r);
    updateCurrentGamer();
}

void GameClient::setColor(QColor c)
{
    qDebug()<<"GameClient : enter 'setColor'";

    Gamer *g = lstGamer.getGamer(gamerId);
    g->setColor(c);
    updateCurrentGamer();
}

void GameClient::setSlot(int s)
{
    qDebug()<<"GameClient : enter 'setSlot'";

    Gamer *g = lstGamer.getGamer(gamerId);
    g->setSlotNumber(s);
    updateCurrentGamer();
}

void GameClient::sendChatMessage(QString msg)
{
    if(GameServer::isContainsPrivateChar(msg)) return;

    QString name = lstGamer.getGamer(gamerId) == 0 ? "" : lstGamer.getGamer(gamerId)->getName();
    QString message = QString("%1#%2 : %3").arg(C_SEND_CHAT_MESSAGE).
            arg(name).arg(msg);
    client->sendMessageToServer(message);
}

void GameClient::setMap(int index)
{
    QString message = QString("%1#%2").arg(C_MAP_CHANGE).arg(index);
    client->sendMessageToServer(message);
}

void GameClient::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    qWarning()<<"GameClient : enter 'onErrorOccured'"<<socketError;

    emit errorOccured(socketError);
}

void GameClient::onMessageRecive(QString s)
{
    QStringList msgStr = s.split("#");

    if(msgStr.size() != 2) return;

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
    case C_INFORMATION:
    {
        qDebug()<<"GameClient : in 'onMessageRecive' recive C_INFORMATION";
        receive_C_INFORMATION(msg);
        break;
    }
    case C_TRANSIT_GAME:
    {
        qDebug()<<"GameClient : in 'onMessageRecive' recive C_TRANSIT_GAME";
        receive_C_TRANSIT_GAME(msg);
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
    case C_GAMER_ACTION:
    {
        qDebug()<<"GameClient : in 'onMessageRecive' recive C_GAMER_ACTION";
        map->applyGamerAction(msg);
        break;
    }
    case C_RECIVE_CHAT_MESSAGE:
    {
        qDebug()<<"GameClient : in 'onMessageRecive' recive C_RECIVE_CHAT_MESSAGE";
        receive_C_RECIVE_CHAT_MESSAGE(msg);
        break;
    }
    case C_MAP_CHANGE:
    {
        qDebug()<<"GameClient : in 'onMessageRecive' recive C_MAP_CHANGE";
        receive_C_MAP_CHANGE(msg);
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

    QString message = QString("%1#").arg(C_REQUEST_SLOT);
    client->sendMessageToServer(message);
}

void GameClient::sendGamerAction(QString actionString)
{
    qDebug()<<"GameClient : enter 'sendClientAction'";

    QString message = QString("%1#%2").arg(C_GAMER_ACTION).arg(actionString);
    client->sendMessageToServer(message);
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/

void GameClient::updateCurrentGamer()
{
    qDebug()<<"GameClient : enter 'updateCurrentGamer'";

    Gamer *g = lstGamer.getGamer(gamerId);
    QString message = QString("%1#%2").arg(C_UPDATE_CURRENT_GAMER).
            arg(g->getUpdateString());
    client->sendMessageToServer(message);
}

/*----------------------------------------------------*/
/*RECEPTION*/
/*----------------------------------------------------*/

void GameClient::receive_C_GAMER_INFO(const QString &msg)
{
    gamerId = msg.toInt();
}

void GameClient::receive_C_INFORMATION(const QString &msg)
{
    NETWORK_INFORMATION info = (NETWORK_INFORMATION)msg.toInt();

    if(info == I_CLIENT_PARAMETRED)
    {
        emit connexionOk();
    }
    else
    {
        emit errorOccured(info);
    }
}

void GameClient::receive_C_TRANSIT_GAME(const QString &msg)
{
    if(gamerId != -1)
    {
        if(map != 0) delete map;
        map = new GameView(msg, lstGamer, lstGamer.getGamer(gamerId));
        connect(map, SIGNAL(gamerAction(QString)),
                this, SLOT(sendGamerAction(QString)));

        emit switchToGame();
    }
    else
    {
        qCritical()<<"GameClient : unexpected case in 'onMessageRecive' recive C_TRANSIT_GAME";
    }
}

void GameClient::receive_C_LOBBY_UPDATE(const QString &msg)
{
    lstGamer.updateLstGamerFromString(msg);

    emit updateLobby();
}

void GameClient::receive_C_MAP_UPDATE(const QString &msg)
{
    if(map != 0)map->updateFromString(msg);
}

void GameClient::receive_C_ADD_MAP(const QString &msg)
{
    emit addMapName(msg);
}

void GameClient::receive_C_RECIVE_CHAT_MESSAGE(const QString &msg)
{
    emit reciveChatMessage(msg);
}

void GameClient::receive_C_MAP_CHANGE(const QString &msg)
{
    mapSelectionChange(msg);
}
