#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QAbstractSocket>

class Client;
class QTcpSocket;
class GameView;
class GamerList;
class Gamer;

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

    /*ASSESSEUR / MUTATEUR*/
    GameView *getMap()const;
    const QHash<int, Gamer *> &getListGamer();
    const Gamer *getCurrentGamer()const;

    /*SIGNALS/SLOTS*/
signals:
    void errorOccured(QAbstractSocket::SocketError socketError);
    void updateLobby();
    void addMapName(QString s);
    void connexionOk();
    void switchToGame();
public slots:
    void launchGame(QString mapName);
    void setName(QString &name);
    void setReady(bool r);
    void setColor(QColor c);
    void setSlot(int s);

private slots:
    void onErrorOccured(QAbstractSocket::SocketError socketError);
    void onMessageRecive(QString msg);
    void onClientConnected();
    void sendClientAction(QString actionString);

private:
    /*OUTIL*/
    Client *client;
    GameView *map;
    int const port;
    int gamerId;
    GamerList &lstGamer;

    /*METHODE PRIVE*/
    void updateCurrentGamer();

    /*RECEPTION*/
    void receive_C_GAMER_INFO(QString msg);
    void receive_C_REFUSE(QString msg);
    void receive_C_LAUNCH_GAME(QString msg);
    void receive_C_LOBBY_UPDATE(QString msg);
    void receive_C_MAP_UPDATE(QString msg);
    void receive_C_ADD_MAP(QString msg);
};

#endif // GAMECLIENT_H
