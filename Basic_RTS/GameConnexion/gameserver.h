#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "global.h"
#include "enumlibrary.h"
#include "gamerlist.h"

class Server;
class QTcpSocket;
class GameView;
class GamerList;
class MapFile;

namespace GameConnexion
{
    class GameServer;
}


/**
 * @class GameServer
 * @brief Gère le jeu coté serveur et les communications avec les clients de jeu
 */
class GameServer: public QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    explicit GameServer(int maxConnexion, QObject *parent = 0);
    ~GameServer();

    /*ASSESSEUR / MUTATEUR*/
    static bool isContainsPrivateChar(QString &s);

    /*SIGNALS/SLOTS*/
signals:
    void errorOccured(QAbstractSocket::SocketError socketError);
private slots:
    void onErrorOccured(QAbstractSocket::SocketError socketError);
    void onMessageRecive(QTcpSocket *t, QString msg);
    void sendGamerAction(QString actionString);

private:
    /*OUTIL*/
    Server *server; ///< Serveur de communication textuelle
    GameView *map; ///< Map de déroulement du jeu coté serveur
    bool lockConnexion; ///< Indique si les connexion sont refusées (partie commencée)
    int const refreshLoopMS; ///< Temps de rafraichissement
    int const port; ///< Port utilisé
    GamerList lstGamer; ///< Liste des joueurs présents
    QStringList lstMapName; ///< Liste des map présentes sur le serveur
    int mapSelected; ///< Numéro de la map sélectionnée

    /*METHODE PRIVE*/
    void sendToAllGamer(const QString s);
    void updateGamerList();
    void timerEvent(QTimerEvent *event);
    void loadMapsFromFile();
    NETWORK_INFORMATION checkReadyToLaunchGame(MapFile &m);

    /*RECEPTION*/
    void receive_C_REQUEST_SLOT(QTcpSocket *t, const QString &msg);
    void receive_C_LAUNCH_GAME(QTcpSocket *t, const QString &msg);
    void receive_C_UPDATE_CURRENT_GAMER(QTcpSocket *t, const QString &msg);
    void receive_C_SET_NAME(QTcpSocket *t, const QString &msg);
    void receive_C_GAMER_ACTION(QTcpSocket *t, const QString &msg);
    void receive_C_SEND_CHAT_MESSAGE(QTcpSocket *t, const QString &msg);
    void receive_C_MAP_CHANGE(QTcpSocket *t, const QString &msg);
};

#endif // GAMESERVER_H
