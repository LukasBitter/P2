#include "gameclient.h"
#include "enumLib.h"
#include "client.h"
#include "GameComponent/map.h"
#include "GameComponent/gamerlist.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameClient::GameClient(QString host, QObject *parent) : QObject(parent),
    port(8000), gamerId(-1), map(0), client(0)
{
    client = new Client(port, host, this);

    connect(client, SIGNAL(messageReciveFromServeur(QString)),
            this, SLOT(onMessageRecive(QString)));
    connect(client, SIGNAL(connected()),
            this, SLOT(onClientConnected()));
}

GameClient::~GameClient()
{
    delete map;
}

Map *GameClient::getMap() const
{
    return map;
}

/*----------------------------------------------------*/
/*SIGNALS/SLOTS*/
/*----------------------------------------------------*/

void GameClient::launchGame(QString mapCreationStr, QString mapUpdateStr)
{
    client->sendMessageToServer(QString("%1#%2#%3").arg(C_LAUNCHGAME).
                                arg(mapCreationStr).arg(mapUpdateStr));
}

void GameClient::onErrorOccured(QAbstractSocket::SocketError socketError)
{
    emit errorOccured(socketError);
}

void GameClient::onMessageRecive(QString s)
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
    case C_GAMERINFO:
    {
        gamerId = msg1.toInt();
        break;
    }
    case C_REFUSE:
    {
        emit errorOccured(QAbstractSocket::ConnectionRefusedError);
        break;
    }
    case C_LAUNCHGAME:
    {
        if(gamerId != -1)
        {
            map = new Map(msg1, GamerList::getGamer(gamerId));
            map->updateFromString(msg2);
            emit switchToGame();
        }
        break;
    }
    case C_LOBBYUPDATE:
    {
        GamerList::updateLstGamerFromString(msg1);
        emit updateLobby();
        break;
    }
    case C_MAPUPDATE:
    {
        if(map != 0)map->updateFromString(msg1);
        break;
    }
    default:
        break;
    }
}

void GameClient::onClientConnected()
{
    client->sendMessageToServer(QString("%1##").arg(C_REQUESTSLOT));
    emit connexionOk();
}

/*----------------------------------------------------*/
/*METHODE PRIVE*/
/*----------------------------------------------------*/
