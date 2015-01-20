#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QAbstractSocket>
#include <QStringList>

class Server;
class QTcpSocket;
class GameView;
class GamerList;

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
    void serverIsListening();
private slots:
    void onErrorOccured(QAbstractSocket::SocketError socketError);
    void onMessageRecive(QTcpSocket *t, QString msg);
    void onServerIsListening();

private:
    /*OUTIL*/
    Server *server;
    GameView *map;
    bool lockConnexion;
    int const refreshLoopMS;
    int const port;
    GamerList &lstGamer;
    QStringList lstMapName;

    /*METHODE PRIVE*/
    void sendToAllGamer(QString s);
    void updateGamerList();
    void timerEvent(QTimerEvent *event);
    void loadMapsFromFile();
    QString checkReadyToLaunchGame();

    /*RECEPTION*/
    void receive_C_REQUEST_SLOT(QTcpSocket *t, QString msg);
    void receive_C_LAUNCH_GAME(QTcpSocket *t, QString msg);
    void receive_C_SET_READY(QTcpSocket *t, QString msg);
    void receive_C_SET_NAME(QTcpSocket *t, QString msg);
    void receive_C_GAMER_ACTION(QTcpSocket *t, QString msg);
};

#endif // GAMESERVER_H
