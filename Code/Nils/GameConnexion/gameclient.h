#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QAbstractSocket>

class Client;
class QTcpSocket;
class Map;

namespace GameConnexion {
    class GameClient;
}

class GameClient : public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    GameClient(QString host = "localhost", QObject *parent = 0);
    ~GameClient();

    Map *getMap()const;

    /*SIGNALS/SLOTS*/
signals:
    void errorOccured(QAbstractSocket::SocketError socketError);
    void updateLobby();
    void connexionOk();
    void switchToGame();
public slots:
    void launchGame(QString mapCreationStr, QString mapUpdateStr);

private slots:
    void onErrorOccured(QAbstractSocket::SocketError socketError);
    void onMessageRecive(QString msg);
    void onClientConnected();

private:
    /*OUTIL*/
    Client *client;
    Map *map;
    int const port;
    int gamerId;

    /*METHODE PRIVE*/
};

#endif // GAMECLIENT_H
