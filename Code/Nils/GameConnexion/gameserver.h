#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QAbstractSocket>

class Server;
class QTcpSocket;
class Map;

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
    Map *map;
    bool lockConnexion;
    int const refreshLoopMS;
    int const port;

    /*METHODE PRIVE*/
    void sendToAllGamer(QString s);
    void updateGamerList();
    void timerEvent(QTimerEvent *event);
};

#endif // GAMESERVER_H
