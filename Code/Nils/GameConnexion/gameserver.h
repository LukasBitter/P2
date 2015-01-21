#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QAbstractSocket>
#include <QStringList>
#include "enumlibrary.h"
#include "gamerlist.h"

class Server;
class QTcpSocket;
class GameView;
class GamerList;
class MapFile;

namespace GameConnexion {
    class GameServer;
}

class GameServer: public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit GameServer(int maxConnexion, QObject *parent = 0);
    ~GameServer();

    /*SIGNALS/SLOTS*/
signals:
    void errorOccured(QAbstractSocket::SocketError socketError);
private slots:
    void onErrorOccured(QAbstractSocket::SocketError socketError);
    void onMessageRecive(QTcpSocket *t, QString msg);

private:
    /*OUTIL*/
    Server *server;
    GameView *map;
    bool lockConnexion;
    int const refreshLoopMS;
    int const port;
    GamerList lstGamer;
    QStringList lstMapName;

    /*METHODE PRIVE*/
    void sendToAllGamer(QString s);
    void updateGamerList();
    void timerEvent(QTimerEvent *event);
    void loadMapsFromFile();
    NETWORK_INFORMATION checkReadyToLaunchGame(MapFile &m);

    /*RECEPTION*/
    void receive_C_REQUEST_SLOT(QTcpSocket *t, QString msg);
    void receive_C_LAUNCH_GAME(QTcpSocket *t, QString msg);
    void receive_C_UPDATE_CURRENT_GAMER(QTcpSocket *t, QString msg);
    void receive_C_SET_NAME(QTcpSocket *t, QString msg);
    void receive_C_GAMER_ACTION(QTcpSocket *t, QString msg);
};

#endif // GAMESERVER_H
