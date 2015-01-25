#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include "global.h"
#include "enumlibrary.h"
#include "gamerlist.h"

class Client;
class GameView;
class Gamer;

namespace GameConnexion
{
    class GameClient;
}

/**
 * @class GameClient
 * @brief Gère le jeu coté client et les communications avec le serveur de jeu
 */
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
    static bool isContainsPrivateChar(QString &s);

    /*SIGNALS/SLOTS*/
signals:
    void errorOccured(QAbstractSocket::SocketError socketError);
    void errorOccured(NETWORK_INFORMATION socketError);
    void updateLobby();
    void addMapName(QString s);
    void connexionOk();
    void switchToGame();
public slots:
    void launchGame(QString mapName);
    bool setName(QString name);
    void setReady(bool r);
    void setColor(QColor c);
    void setSlot(int s);

private slots:
    void onErrorOccured(QAbstractSocket::SocketError socketError);
    void onMessageRecive(QString msg);
    void onClientConnected();
    void sendGamerAction(QString actionString);

private:
    /*OUTIL*/
    Client *client; ///< Client de communication textuelle
    GameView *map; ///< Map d'affichage de jeu coté client
    int const port; ///< Port utilisé
    int gamerId; ///< Identifiant du joueur client
    GamerList lstGamer; ///< Liste des joueurs présents

    /*METHODE PRIVE*/
    void updateCurrentGamer();

    /*RECEPTION*/
    void receive_C_GAMER_INFO(const QString &msg);
    void receive_C_INFORMATION(const QString &msg);
    void receive_C_TRANSIT_GAME(const QString &msg);
    void receive_C_LOBBY_UPDATE(const QString &msg);
    void receive_C_MAP_UPDATE(const QString &msg);
    void receive_C_ADD_MAP(const QString &msg);
};

#endif // GAMECLIENT_H
