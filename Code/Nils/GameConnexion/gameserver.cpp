#include "gameserver.h"
#include "server.h"
#include "gamer.h"
#include "mapfile.h"
#include "GameComponent/GameInterface/gameview.h"


/*----------------------------------------------------*/
/*CONSTRUCTEUR / DESTRUCTEUR*/
/*----------------------------------------------------*/

GameServer::GameServer(int maxConnexion, QObject *parent) : QObject(parent),
    lockConnexion(false), refreshLoopMS(TIC), port(PORT), map(0)
{
    server = new Server(port, maxConnexion, this);

    connect(server, SIGNAL(messageReciveFromClient(QTcpSocket*,QString)),
            this, SLOT(onMessageRecive(QTcpSocket*,QString)));

    loadMapsFromFile();
}

GameServer::~GameServer()
{
    qDebug()<<"GameServer : destroy";
    if(map != 0) delete map;
}

/*----------------------------------------------------*/
/*ASSESSEUR / MUTATEUR*/
/*----------------------------------------------------*/

bool GameServer::isContainsPrivateChar(QString &s)
{
    return s.contains("#");
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
    case C_SEND_CHAT_MESSAGE:
    {
        qDebug()<<"GameServer : in 'onMessageRecive' recive C_GAMER_ACTION";
        receive_C_SEND_CHAT_MESSAGE(t, msg);
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

void GameServer::sendToAllGamer(const QString s)
{
    foreach(Gamer *g, lstGamer.getLstGamer())
    {
        server->sendMessageToClient(g->getSocket(),s);
    }
}

void GameServer::sendGamerAction(QString actionString)
{
    qDebug()<<"GameServer : enter 'sendGamerAction'";

    QString message = QString("%1#%2").arg(C_GAMER_ACTION).arg(actionString);
    sendToAllGamer(message);
}

void GameServer::updateGamerList()
{
    qDebug()<<"GameServer : enter 'updateGamerList'";

    sendToAllGamer(QString("%1#%2").
                   arg(C_LOBBY_UPDATE).
                   arg(lstGamer.getLstGamerUpdateString()));
}

void GameServer::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    map->advance();
    sendToAllGamer(QString("%1#%2").
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
    filter << MAP_EXTENSION_FILTER;
    lstMapName = d.entryList(filter);

    //Controle des noms
    int i = 0;
    foreach (QString s, lstMapName)
    {
        if(isContainsPrivateChar(s))
        {
            lstMapName.removeAt(i);
            qCritical()<<"GameServer : map remove from the list : "<<s;
        }
        ++i;
    }
}

NETWORK_INFORMATION GameServer::checkReadyToLaunchGame(MapFile &m)
{
    QList<Gamer *> lst = lstGamer.getLstGamer().values();

    //CONTROL INDIVIDUEL
    foreach (Gamer *g, lst)
    {
        if(g->getSlotNumber() == -1)
            return I_SLOT_NOT_SELECTED;

        if(g->getColor() == Qt::white)
            return I_COLOR_NOT_SELECTED;

        if(g->getSlotNumber() > m.getNumberOfSlot())
            return I_MAP_NOT_BIG_ENOUGH;

        if(!g->isReady()) return I_NOT_READY;
    }

    //CONTROL PAR RAPPORT AUX AUTRES
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

void GameServer::receive_C_REQUEST_SLOT(QTcpSocket *t, const QString &msg)
{
    Q_UNUSED(msg);

    if(lstGamer.getLstGamer().size() == MAX_GAMER)
    {
        qDebug()<<"GameServer : refuse client (1)";

        server->sendMessageToClient(t,QString("%1#%2").arg(C_INFORMATION).arg(I_LOBBY_FULL));
    }

    if(!lockConnexion)
    {
        qDebug()<<"GameServer : accept client";

        //Tableau des couleurs de joueur
        QColor colorArray [MAX_GAMER] = PLAYER_COLOR;

        Gamer *g = new Gamer();
        g->setSocket(t);
        g->setColor(colorArray[lstGamer.getLstGamer().size()]);
        lstGamer.addGamer(g);
        g->setSlotNumber(lstGamer.getLstGamer().size());
        server->sendMessageToClient(t,QString("%1#%2").arg(C_GAMER_INFO).arg(g->getId()));

        foreach (QString s, lstMapName)
        {
            server->sendMessageToClient(t,QString("%1#%2").arg(C_ADD_MAP).arg(s));
        }

        updateGamerList();
        server->sendMessageToClient(t,QString("%1#%2").arg(C_INFORMATION).arg(I_CLIENT_PARAMETRED));
    }
    else
    {
        qDebug()<<"GameServer : refuse client (2)";

        server->sendMessageToClient(t,QString("%1#%2").arg(C_INFORMATION).arg(I_GAME_STARTED));
    }
}

void GameServer::receive_C_LAUNCH_GAME(QTcpSocket *t, const QString &msg)
{
    MapFile m;
    m.loadFromFile(QString("%1/%2").arg(MAP_FILE).arg(msg));

    if(!m.isValide())
    {
        qCritical()<<"GameServer : in 'receive_C_LAUNCH_GAME' map is not valid ";

        server->sendMessageToClient(t,QString("%1#%2").
                                    arg(C_INFORMATION).
                                    arg(I_MAP_INVALID));
        return;
    }

    NETWORK_INFORMATION invalid = checkReadyToLaunchGame(m);

    if(invalid != I_OK)
    {
        server->sendMessageToClient(t,QString("%1#%2").arg(C_INFORMATION).
                                    arg(invalid));
        return;
    }

    lockConnexion = true;

    if(map != 0) delete map;
    map = new GameView(m.getCreationString(), lstGamer);
    map->updateFromString(m.getUpdateString());
    sendToAllGamer(QString("%1#%2").arg(C_TRANSIT_GAME).arg(m.getCreationString()));

    QList<Gamer *> lst = lstGamer.getLstGamer().values();

    foreach (Gamer *g, lst)
    {
        map->updateFromString(m.getSlot(g->getSlotNumber()-1, g));
    }

    connect(map, SIGNAL(gamerAction(QString)),
            this, SLOT(sendGamerAction(QString)));

    startTimer(refreshLoopMS);
}

void GameServer::receive_C_UPDATE_CURRENT_GAMER(QTcpSocket *t, const QString &msg)
{
    Gamer *g = lstGamer.getGamer(t);
    g->updateFromString(msg);
    updateGamerList();
}

void GameServer::receive_C_GAMER_ACTION(QTcpSocket *t, const QString &msg)
{
    Q_UNUSED(t);

    map->applyGamerAction(msg);
}

void GameServer::receive_C_SEND_CHAT_MESSAGE(QTcpSocket *t, const QString &msg)
{
    Q_UNUSED(t);

    sendToAllGamer(QString("%1#%2").arg(C_RECIVE_CHAT_MESSAGE).arg(msg));
}
