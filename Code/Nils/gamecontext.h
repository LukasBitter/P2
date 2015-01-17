#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <QObject>
#include <QAbstractSocket>

class Client;
class Server;
class Parser;
class Map;
class QString;

class GameContext : QObject
{
    Q_OBJECT

public:
    /*CONSTRUCTEUR / DESTRUCTEUR*/
    GameContext(bool host);
    ~GameContext();
private:
    int const maxGamer;
    int const port;
    int numGamer;

    Client *client;
    Server *server;
    Parser *parser;
    Map *game;

/*----------------------------------------------------*/
/*COMMUNICATION AVEC AFFICHAGE*/
/*----------------------------------------------------*/

signals:
    void errorOccured(QAbstractSocket::SocketError socketError); ///< Quand une erreur arrive sur le client ou le serveur
    void connexionOk(); ///< Quand la connexion est valide
    void update(); ///< Quand une mise a jour à été faite

public slots:
    void connectToServer(QString ip); ///< Connecte le client a l'adresse IP
private slots:
    void onClientConnect();
    void onErrorOccured(QAbstractSocket::SocketError socketError);

/*----------------------------------------------------*/
/*COMMUNICATION AVEC LE PARSER*/
/*----------------------------------------------------*/

signals:

private slots:
    void onReciveGameInfo(int gamerId); ///< Reçois le numero de joueur atribué
    void onParserUpdate(); ///< Indication de mise a jour du parser
    void onTransitToGame(); ///< Indication de passer au jeu
    void onMapCreated(); ///< Indication de passer au jeu
};

#endif // GAMECONTEXT_H
